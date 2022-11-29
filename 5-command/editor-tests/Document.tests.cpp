#include <catch.hpp>
#include <fstream>
#include <sstream>

#include "Document.h"
#include "DocumentHtmlSaveStrategy.h"

TEST_CASE("Getting item of empty document should cause exception")
{
	SECTION("Non-const version")
	{
		std::unique_ptr<IDocument> doc = std::make_unique<Document>(std::shared_ptr<IDocumentSaveStrategy>());

		CHECK_THROWS_AS(doc->GetItem(2), std::out_of_range);
	}

	SECTION("Const version")
	{
		std::unique_ptr<const IDocument> doc = std::make_unique<Document>(std::shared_ptr<IDocumentSaveStrategy>());

		CHECK_THROWS_AS(doc->GetItem(2), std::out_of_range);
	}
}

TEST_CASE("Items count of empty document should be zero")
{
	std::unique_ptr<IDocument> doc = std::make_unique<Document>(std::shared_ptr<IDocumentSaveStrategy>());

	CHECK(doc->GetItemsCount() == 0);
}

TEST_CASE("Insert paragraphs into document")
{
	std::unique_ptr<IDocument> doc = std::make_unique<Document>(std::shared_ptr<IDocumentSaveStrategy>());

	SECTION("Insert paragraph into bad position, should cause CommandExecutionException")
	{
		CHECK_THROWS_AS(doc->InsertParagraph("Text", 1), CommandExecutionException);
	}

	SECTION("Insert paragraph to the end of document, single item should be that paragraph")
	{
		CHECK_NOTHROW(doc->InsertParagraph("I'm here", {}));

		CHECK(doc->GetItemsCount() == 1);

		CHECK(doc->GetItem(0).GetImage() == nullptr);

		CHECK(doc->GetItem(0).GetParagraph()->GetText() == "I'm here");
	}

	SECTION("Insert paragraph one before another, paragraphs should be in correct order")
	{
		CHECK_NOTHROW(doc->InsertParagraph("First", {}));
		CHECK_NOTHROW(doc->InsertParagraph("Second", 0));

		CHECK(doc->GetItemsCount() == 2);
		CHECK(doc->GetItem(0).GetParagraph()->GetText() == "Second");
		CHECK(doc->GetItem(1).GetParagraph()->GetText() == "First");
	}
}

TEST_CASE("Undo/redo paragraph insertions into document")
{
	std::unique_ptr<IDocument> doc = std::make_unique<Document>(std::shared_ptr<IDocumentSaveStrategy>());

	SECTION("Insert single paragraph and undo changes")
	{
		CHECK_NOTHROW(doc->InsertParagraph("Single paragraph", {}));

		CHECK(doc->GetItemsCount() == 1);
		CHECK(doc->GetItem(0).GetParagraph()->GetText() == "Single paragraph");

		CHECK(doc->CanUndo());

		doc->Undo();

		CHECK(!doc->CanUndo());

		CHECK(doc->GetItemsCount() == 0);
	}

	SECTION("Insert single paragraph then undo and redo changes")
	{
		doc->InsertParagraph("Single paragraph", {});
		doc->Undo();

		CHECK(doc->CanRedo());

		doc->Redo();

		CHECK(!doc->CanRedo());

		CHECK(doc->GetItemsCount() == 1);
		CHECK(doc->GetItem(0).GetParagraph()->GetText() == "Single paragraph");
	}

	SECTION("Insert two paragraphs then undo insertions and redo again or apply new command and discard undone edit")
	{
		doc->InsertParagraph("First", {});
		doc->InsertParagraph("Second", {});

		CHECK(doc->GetItemsCount() == 2);
		CHECK(doc->GetItem(0).GetParagraph()->GetText() == "First");
		CHECK(doc->GetItem(1).GetParagraph()->GetText() == "Second");

		CHECK(doc->CanUndo());
		CHECK(!doc->CanRedo());

		doc->Undo(); // Undo "Second" insertion

		CHECK(doc->GetItemsCount() == 1);
		CHECK(doc->GetItem(0).GetParagraph()->GetText() == "First");
		CHECK_THROWS_AS(doc->GetItem(1), std::out_of_range);

		CHECK(doc->CanUndo());
		CHECK(doc->CanRedo());

		doc->Undo(); // Undo "First" insertion

		CHECK(doc->GetItemsCount() == 0);
		CHECK_THROWS_AS(doc->GetItem(0), std::out_of_range);
		CHECK_THROWS_AS(doc->GetItem(1), std::out_of_range);

		CHECK(!doc->CanUndo());
		CHECK(doc->CanRedo());

		doc->Redo(); // Redo "First" insertion

		CHECK(doc->GetItemsCount() == 1);
		CHECK(doc->GetItem(0).GetParagraph()->GetText() == "First");
		CHECK_THROWS_AS(doc->GetItem(1), std::out_of_range);

		CHECK(doc->CanUndo());
		CHECK(doc->CanRedo());

		SECTION("Redo second executed command")
		{
			doc->Redo(); // Redo "Second" insertion

			CHECK(doc->GetItemsCount() == 2);
			CHECK(doc->GetItem(0).GetParagraph()->GetText() == "First");
			CHECK(doc->GetItem(1).GetParagraph()->GetText() == "Second");

			CHECK(doc->CanUndo());
			CHECK(!doc->CanRedo());
		}

		SECTION("Execute new command and discard undone second command")
		{
			doc->InsertParagraph("New", {}); // Insert paragraph, insertion of paragraph "Second" is unreachable future

			CHECK(doc->GetItemsCount() == 2);
			CHECK(doc->GetItem(0).GetParagraph()->GetText() == "First");
			CHECK(doc->GetItem(1).GetParagraph()->GetText() == "New");

			CHECK(doc->CanUndo());
			CHECK(!doc->CanRedo());
		}
	}
}

TEST_CASE("Execute more than 10 commands, commands older than 10 previous ones are removed from command history")
{
	std::unique_ptr<IDocument> doc = std::make_unique<Document>(std::shared_ptr<IDocumentSaveStrategy>());

	doc->InsertParagraph("First", {});
	doc->InsertParagraph("Second", {});
	doc->InsertParagraph("Third", {});
	doc->InsertParagraph("Fourth", {});
	doc->InsertParagraph("Fifth", {});
	doc->InsertParagraph("Sixth", {});
	doc->InsertParagraph("Seventh", {});
	doc->InsertParagraph("Eighth", {});
	doc->InsertParagraph("Ninth", {});
	doc->InsertParagraph("Tenth", {});
	doc->InsertParagraph("Eleventh", {}); // Paragraph "First" removed from history

	while (doc->CanUndo()) // Undo all undoable edits, can't undo "First" paragraph insertion
		doc->Undo();

	CHECK(doc->GetItemsCount() == 1);
	CHECK(doc->GetItem(0).GetParagraph()->GetText() == "First");
}

TEST_CASE("Insert image into document")
{
	std::unique_ptr<IDocument> doc = std::make_unique<Document>(std::shared_ptr<IDocumentSaveStrategy>());
	std::filesystem::path path("img.png");

	SECTION("Insert image with valid size")
	{
		CHECK_NOTHROW(doc->InsertImage(path, 1, 10000, {}));
		CHECK(doc->GetItemsCount() == 1);

		auto img = doc->GetItem(0).GetImage();

		CHECK(img->GetPath() == "temp\\images\\img1.png");
		CHECK(img->GetWidth() == 1);
		CHECK(img->GetHeight() == 10000);
	}

	SECTION("Insert image with invalid size")
	{
		CHECK_THROWS_AS(doc->InsertImage(path, -1, 10000, {}), CommandExecutionException);
		CHECK_THROWS_AS(doc->InsertImage(path, 1, 10001, {}), CommandExecutionException);
	}

	SECTION("Insert image and undo insertion")
	{
		int w = 200, h = 300;
		doc->InsertImage(path, w, h, {});

		CHECK(doc->GetItemsCount() == 1);
		CHECK(doc->CanUndo());

		doc->Undo();

		CHECK(!doc->CanUndo());
		CHECK(doc->GetItemsCount() == 0);
		CHECK_THROWS_AS(doc->GetItem(0), std::out_of_range);

		SECTION("Try undo when undo is unavailable, should cause exception")
		{
			CHECK_THROWS_AS(doc->Undo(), CommandExecutionException);
		}
	}

	SECTION("Redo image insertion, image should become first element of document")
	{
		int w = 200, h = 300;
		doc->InsertImage(path, w, h, {});

		doc->Undo();

		CHECK(doc->CanRedo());

		doc->Redo();

		auto img = doc->GetItem(0).GetImage();

		CHECK(img->GetPath() == "temp\\images\\img3.png");
		CHECK(img->GetWidth() == w);
		CHECK(img->GetHeight() == h);
	}
}

TEST_CASE("Replace paragraph text")
{
	std::unique_ptr<IDocument> doc = std::make_unique<Document>(std::shared_ptr<IDocumentSaveStrategy>());
	std::string initial = "init", replace = "repl";

	doc->InsertParagraph(initial, {});

	SECTION("Replace text of paragraph")
	{
		CHECK_NOTHROW(doc->GetItem(0).GetParagraph()->SetText(replace));
		CHECK(doc->GetItem(0).GetParagraph()->GetText() == replace);

		SECTION("Insert another paragraph and ensure that text is replaced of correct paragraph")
		{
			doc->InsertParagraph(initial, {});
			doc->GetItem(0).GetParagraph()->SetText(initial);

			CHECK(doc->GetItem(0).GetParagraph()->GetText() == initial);
			CHECK(doc->GetItem(1).GetParagraph()->GetText() == initial);
		}
	}

	SECTION("Replace text then undo changes")
	{
		doc->GetItem(0).GetParagraph()->SetText(replace);

		CHECK(doc->CanUndo());
		CHECK_NOTHROW(doc->Undo());
		CHECK(doc->GetItem(0).GetParagraph()->GetText() == initial);

		SECTION("And redo changes")
		{
			CHECK(doc->CanRedo());
			CHECK_NOTHROW(doc->Redo());
			CHECK(doc->GetItem(0).GetParagraph()->GetText() == replace);
		}
	}

	SECTION("Replace text at bad index, should cause exception")
	{
		CHECK(doc->GetItemsCount() == 1);
		CHECK_THROWS_AS(doc->GetItem(1).GetParagraph()->SetText(replace), std::out_of_range);
	}
}

TEST_CASE("Resize image")
{
	std::unique_ptr<IDocument> doc = std::make_unique<Document>(std::shared_ptr<IDocumentSaveStrategy>());
	std::filesystem::path path("img.png");
	int w = 200, h = 300;

	doc->InsertImage(path, w, h, {});

	SECTION("Resize image with valid size")
	{
		CHECK_NOTHROW(doc->GetItem(0).GetImage()->Resize(w + h, h - w));

		auto img = doc->GetItem(0).GetImage();

		CHECK(img->GetWidth() == w+h);
		CHECK(img->GetHeight() == h-w);
	}

	SECTION("Resize image with invalid size")
	{
		CHECK_THROWS_AS(doc->GetItem(0).GetImage()->Resize(w-h, h-w), CommandExecutionException);
	}

	SECTION("Resize image then undo changes")
	{
		doc->GetItem(0).GetImage()->Resize(w+h, h-w);
		doc->Undo();
		auto img = doc->GetItem(0).GetImage();

		CHECK(img->GetWidth() == w);
		CHECK(img->GetHeight() == h);

		SECTION("Redo changes")
		{
			CHECK(doc->CanRedo());

			doc->Redo();

			auto img = doc->GetItem(0).GetImage();

			CHECK(img->GetWidth() == w+h);
			CHECK(img->GetHeight() == h-w);
		}
	}
}

TEST_CASE("Deleting item")
{
	std::unique_ptr<IDocument> doc = std::make_unique<Document>(std::shared_ptr<IDocumentSaveStrategy>());

	doc->InsertParagraph("Paragraph", {});
	doc->InsertImage("img.png", 100, 200, {});

	CHECK(doc->GetItemsCount() == 2);

	SECTION("Delete paragraph")
	{
		doc->DeleteItem(0);

		CHECK(doc->GetItemsCount() == 1);
		CHECK(doc->GetItem(0).GetImage()->GetPath() == "temp\\images\\img7.png");
		CHECK(doc->GetItem(0).GetImage()->GetWidth() == 100);
		CHECK(doc->GetItem(0).GetImage()->GetHeight() == 200);
	}

	SECTION("Delete image and undo deletion")
	{
		doc->DeleteItem(1);
		doc->Undo();

		CHECK(doc->GetItemsCount() == 2);
		CHECK(doc->GetItem(0).GetParagraph()->GetText() == "Paragraph");
		CHECK(doc->GetItem(1).GetImage()->GetPath() == "temp\\images\\img8.png");
		CHECK(doc->GetItem(1).GetImage()->GetWidth() == 100);
		CHECK(doc->GetItem(1).GetImage()->GetHeight() == 200);
	}

	SECTION("Delete pagraph and undo deletion")
	{
		doc->DeleteItem(0);
		doc->Undo();

		CHECK(doc->GetItemsCount() == 2);
		CHECK(doc->GetItem(0).GetParagraph()->GetText() == "Paragraph");
		CHECK(doc->GetItem(1).GetImage()->GetPath() == "temp\\images\\img9.png");
		CHECK(doc->GetItem(1).GetImage()->GetWidth() == 100);
		CHECK(doc->GetItem(1).GetImage()->GetHeight() == 200);
	}

	SECTION("Undo deletions then redo again")
	{
		doc->DeleteItem(0);
		doc->DeleteItem(0);

		doc->Undo();
		doc->Undo();

		CHECK(doc->GetItemsCount() == 2);
		CHECK(doc->GetItem(0).GetParagraph()->GetText() == "Paragraph");
		CHECK(doc->GetItem(1).GetImage()->GetPath() == "temp\\images\\img10.png");
		CHECK(doc->GetItem(1).GetImage()->GetWidth() == 100);
		CHECK(doc->GetItem(1).GetImage()->GetHeight() == 200);

		while (doc->CanRedo())
			doc->Redo();

		CHECK(doc->GetItemsCount() == 0);
	}
}

TEST_CASE("Set document's title")
{
	std::unique_ptr<IDocument> doc = std::make_unique<Document>(std::shared_ptr<IDocumentSaveStrategy>());
	std::string title = "New title";

	doc->SetTitle(title);

	CHECK(doc->GetTitle() == title);

	doc->Undo();

	CHECK(doc->GetTitle() == "Untitled");

	doc->Redo();

	CHECK(doc->GetTitle() == title);
}

TEST_CASE("Set title, then undo changes, then set another title, then undo changes, title should be Untitled")
{
	std::unique_ptr<IDocument> doc = std::make_unique<Document>(std::shared_ptr<IDocumentSaveStrategy>());
	std::string title1 = "First title";
	std::string title2 = "Second title";

	doc->SetTitle(title1);
	doc->Undo();
	doc->SetTitle(title2);
	doc->Undo();

	CHECK(doc->GetTitle() == "Untitled");
	CHECK(doc->CanRedo());
	CHECK(!doc->CanUndo());
}

bool FileContentEqual(std::filesystem::path filePath, const std::string& expectFileContent)
{
	std::ifstream file(filePath);
	std::stringstream ss;
	ss << file.rdbuf();

	return ss.str() == expectFileContent;
}

TEST_CASE("Saving document with image")
{
	std::unique_ptr<IDocument> doc = std::make_unique<Document>(std::make_shared<DocumentHtmlSaveStrategy>());
	std::filesystem::path imgPath("img.png"), savedDocPath("doc.html");
	doc->InsertImage(imgPath, 100, 100, {});

	SECTION("Undo image insertion and redo again, document should be saved correctly")
	{
		doc->Undo();
		doc->Redo();

		CHECK_NOTHROW(doc->Save(savedDocPath));

		REQUIRE(std::filesystem::exists(savedDocPath));

		CHECK(FileContentEqual(savedDocPath,
			"<!DOCTYPE html>\n"
			"<html>\n"
			"<head>\n"
			"    <title>Untitled</title>\n"
			"</head>\n"
			"<body>\n"
			"    <img src=\"images\\img11.png\" width=\"100\" height=\"100\" />\n"
			"</body>\n"
			"</html>\n"));
	}

	SECTION("Push out image insertion command from history, document saving should complete sucessfully")
	{
		for (int i = 0; i < CommandHistory::HistoryDepthLimit; ++i)
			doc->SetTitle("Push commands out.");

		CHECK_NOTHROW(doc->Save(savedDocPath));

		REQUIRE(std::filesystem::exists(savedDocPath));

		CHECK(FileContentEqual(savedDocPath,
			"<!DOCTYPE html>\n"
			"<html>\n"
			"<head>\n"
			"    <title>Push commands out.</title>\n"
			"</head>\n"
			"<body>\n"
			"    <img src=\"images\\img12.png\" width=\"100\" height=\"100\" />\n"
			"</body>\n"
			"</html>\n"));
	}

	std::filesystem::remove(savedDocPath);
	std::filesystem::remove_all(PathConstants::ImagesDir);
}
