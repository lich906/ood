#include <catch.hpp>
#include <sstream>

#include "CommandLineEditor.h"
#include "Menu.h"

/*
Mock implementation for IDocument interface.
Prints info about invoked methods to std::ostream passed to it's constructor.
*/
class MockDocument : public IDocument
{
public:
	explicit MockDocument(std::ostream& output)
		: m_output(output)
	{
	}

	std::shared_ptr<IParagraph> InsertParagraph(const std::string& text,
		std::optional<size_t> position = std::nullopt) override
	{
		m_output << "Insert paragraph text='" << text << "' in position " << PositionToStr(position) << std::endl;
		return {};
	}

	std::shared_ptr<IImage> InsertImage(const std::filesystem::path& path, int width, int height,
		std::optional<size_t> position = std::nullopt)
	{
		m_output << "Insert image path='" << path << "' w='" << width << "' h='" << height << "' in position " << PositionToStr(position) << std::endl;
		return {};
	}

	void ReplaceParagraphText(size_t index, const std::string& text) override
	{
		m_output << "Replace text text='" << text << "' at index " << index << std::endl;
	}

	void ResizeImage(size_t index, int width, int height) override
	{
		m_output << "Resize image w='" << width << "' h='" << height << "' at index " << index << std::endl;
	}

	DocumentItem GetItem(size_t index) override
	{
		m_output << "Get item at index " << index << std::endl;
		return DocumentItem(std::shared_ptr<IParagraph>());
	}

	void DeleteItem(size_t index) override
	{
		m_output << "Delete item at index " << index << std::endl;
	}

	void SetTitle(const std::string& title) override
	{
		m_output << "Set title " << title << std::endl;
	}

	void Save(const std::filesystem::path& path) const override
	{
		m_output << "Save at path " << path << std::endl;
	}

	ConstDocumentItem GetItem(size_t index) const override
	{
		m_output << "Get const item at index " << index << std::endl;
		return ConstDocumentItem(std::shared_ptr<const IParagraph>());
	}

	size_t GetItemsCount() const override
	{
		m_output << "GetItemsCount invoked" << std::endl;
		return 0;
	}

	std::string GetTitle() const override
	{
		m_output << "GetTitle invoked" << std::endl;
		return "";
	}

	virtual bool CanUndo() const override
	{
		m_output << "CanUndo invoked" << std::endl;
		return false;
	}
	virtual void Undo() override
	{
		m_output << "Undo invoked" << std::endl;
	}

	virtual bool CanRedo() const override
	{
		m_output << "CanRedo invoked" << std::endl;
		return false;
	}
	virtual void Redo() override
	{
		m_output << "Redo invoked" << std::endl;
	}

private:
	std::ostream& m_output;

	std::string PositionToStr(std::optional<size_t> position)
	{
		if (position.has_value())
		{
			return std::to_string(*position);
		}
		else
		{
			return POSITION_END;
		}
	}
};

TEST_CASE("Passing CommandLineEditor's methods to MenuItem's lambdas then invoke edit methods with commands from input")
{
	std::istringstream input("InsertParagraph 2 Some kind of text\n"
							 "InsertParagraph end Dopustim\n"
							 "InsertImage 4 100 200 /path/img.png\n"
							 "InsertImage end 100 200 /now/insert/to/the/end/img.png\n"
							 "SetTitle New title oh yeah!\n"
							 "ReplaceText 2 This text is better than previous one\n"
							 "ResizeImage 4 666 228\n"
							 "DeleteItem 88\n"
							 "Undo\n"
							 "Redo\n"
							 "Save trolleybus/is/on/fire.html\n");

	std::ostringstream output;
	Menu menu(input);
	CommandLineEditor editor(std::make_unique<MockDocument>(output), input);

	menu.AddItem({ "InsertParagraph", {}, "", std::bind(&CommandLineEditor::InsertParagraph, &editor) });
	menu.AddItem({ "InsertImage", {}, "", std::bind(&CommandLineEditor::InsertImage, &editor) });
	menu.AddItem({ "SetTitle", {}, "", std::bind(&CommandLineEditor::SetTitle, &editor) });
	menu.AddItem({ "ReplaceText", {}, "", std::bind(&CommandLineEditor::ReplaceText, &editor) });
	menu.AddItem({ "ResizeImage", {}, "", std::bind(&CommandLineEditor::ResizeImage, &editor) });
	menu.AddItem({ "DeleteItem", {}, "", std::bind(&CommandLineEditor::DeleteItem, &editor) });
	menu.AddItem({ "Undo", {}, "", std::bind(&CommandLineEditor::Undo, &editor) });
	menu.AddItem({ "Redo", {}, "", std::bind(&CommandLineEditor::Redo, &editor) });
	menu.AddItem({ "Save", {}, "", std::bind(&CommandLineEditor::Save, &editor) });

	menu.Run();

	CHECK(output.str() == "Insert paragraph text='Some kind of text' in position 2\n"
						  "Insert paragraph text='Dopustim' in position end\n"
						  "Insert image path='\"/path/img.png\"' w='100' h='200' in position 4\n"
						  "Insert image path='\"/now/insert/to/the/end/img.png\"' w='100' h='200' in position end\n"
						  "Set title New title oh yeah!\n"
						  "Replace text text='This text is better than previous one' at index 2\n"
						  "Resize image w='666' h='228' at index 4\n"
						  "Delete item at index 88\n"
						  "Undo invoked\n"
						  "Redo invoked\n"
						  "Save at path \"trolleybus/is/on/fire.html\"\n");
}
