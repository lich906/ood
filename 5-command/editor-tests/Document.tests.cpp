#include <catch.hpp>

#include "Document.h"

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
