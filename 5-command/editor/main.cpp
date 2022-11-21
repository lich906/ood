#include <iostream>

#include "Menu.h"
#include "CommandLineEditor.h"
#include "DocumentHtmlSaveStrategy.h"
#include "Document.h"

int main()
{
	CommandLineEditor editor(std::make_unique<Document>(std::make_unique<DocumentHtmlSaveStrategy>()));

	Menu menu;

	menu.AddItem({ "InsertParagraph",
		{ "<position>|end", "<text>" },
		"��������� � ��������� ������� ��������� �������� � ��������� �������. � �������� ������� ������� ����� ������� ���� ���������� ����� �����, ���� end ��� ������� ��������� � �����.",
		std::bind(&CommandLineEditor::InsertParagraph, &editor) });

	menu.AddItem({ "InsertImage",
		{ "<position>|end", "<width>", "<height>", "<path to file>" },
		"��������� � ��������� ������� ��������� �����������, ����������� �� ���������� ����. ��� ������� ����������� ������ � ������, ��� ��������� ���������� ����������� � ��������� ���������.",
		std::bind(&CommandLineEditor::InsertImage, &editor) });

	menu.AddItem({ "InsertParagraph",
		{ "<position>|end", "<text>" },
		"��������� � ��������� ������� ��������� �������� � ��������� �������. � �������� ������� ������� ����� ������� ���� ���������� ����� �����, ���� end ��� ������� ��������� � �����.",
		std::bind(&CommandLineEditor::InsertParagraph, &editor) });

	menu.AddItem({ "SetTitle",
		{ "<new title>" },
		"�������� ��������� ���������",
		std::bind(&CommandLineEditor::SetTitle, &editor) });

	menu.AddItem({ "List",
		{},
		"������� �������� � ������ ��������� ��������� � ����������� ����� ������.",
		std::bind(&CommandLineEditor::List, &editor) });

	menu.AddItem({ "ReplaceText",
		{ "<position>", "<text>" },
		"�������� ����� � ���������, ����������� � ��������� ������� ���������. ���� � ������ ������� �� ��������� ��������, �������� ��������� �� ������, � ������� ������������.",
		std::bind(&CommandLineEditor::ReplaceText, &editor) });

	menu.AddItem({ "ResizeImage",
		{ "<position>", "<width>", "<height>" },
		"�������� ������ �����������, ������������ � ��������� ������� ���������. ���� � ������ ������� �� ���������  �����������, �������� ��������� �� ������.",
		std::bind(&CommandLineEditor::ResizeImage, &editor) });

	menu.AddItem({ "DeleteItem",
		{ "<position>" },
		"������� ������� ���������, ����������� � ��������� �������. ���� ������� ������������ ������� ���������, ������� ������������, � ������������ ��������� ��������� �� ������.",
		std::bind(&CommandLineEditor::DeleteItem, &editor) });

	menu.AddItem({ "Help",
		{},
		"������� ������� � ��������� �������� �������������� � �� ����������.",
		std::bind(&Menu::ShowHelpMessage, &menu) });

	menu.AddItem({ "Undo",
		{},
		"�������� �������� ����� ��������� ������� ��������������, ��������� �������� � ���������� ���������.",
		std::bind(&CommandLineEditor::Undo, &editor) });

	menu.AddItem({ "Redo",
		{},
		"��������� ����� ���������� ������� ��������������, ��������� �������� � ���������, �������� �������� ������� Undo.",
		std::bind(&CommandLineEditor::Redo, &editor) });

	menu.AddItem({ "Save",
		{ "<path>" },
		"��������� ������� ��������� ��������� � ���� ������� html � �������������.",
		std::bind(&CommandLineEditor::DeleteItem, &editor) });

	menu.Run();
}
