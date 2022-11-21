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
		"Вставляет в указанную позицию документа параграф с указанным текстом. В качестве позиции вставки можно указать либо порядковый номер блока, либо end для вставки параграфа в конец.",
		std::bind(&CommandLineEditor::InsertParagraph, &editor) });

	menu.AddItem({ "InsertImage",
		{ "<position>|end", "<width>", "<height>", "<path to file>" },
		"Вставляет в указанную позицию документа изображение, находящееся по указанному пути. При вставке указывается ширина и высота, что позволяет разместить изображение с указанным масштабом.",
		std::bind(&CommandLineEditor::InsertImage, &editor) });

	menu.AddItem({ "InsertParagraph",
		{ "<position>|end", "<text>" },
		"Вставляет в указанную позицию документа параграф с указанным текстом. В качестве позиции вставки можно указать либо порядковый номер блока, либо end для вставки параграфа в конец.",
		std::bind(&CommandLineEditor::InsertParagraph, &editor) });

	menu.AddItem({ "SetTitle",
		{ "<new title>" },
		"Изменяет заголовок документа",
		std::bind(&CommandLineEditor::SetTitle, &editor) });

	menu.AddItem({ "List",
		{},
		"Выводит название и список элементов документа в стандартный поток вывода.",
		std::bind(&CommandLineEditor::List, &editor) });

	menu.AddItem({ "ReplaceText",
		{ "<position>", "<text>" },
		"Заменяет текст в параграфе, находящемся в указанной позиции документа. Если в данной позиции не находится параграф, выдается сообщение об ошибке, а команда игнорируется.",
		std::bind(&CommandLineEditor::ReplaceText, &editor) });

	menu.AddItem({ "ResizeImage",
		{ "<position>", "<width>", "<height>" },
		"Изменяет размер изображения, находящегося в указанной позиции документа. Если в данной позиции не находится  изображение, выдается сообщение об ошибке.",
		std::bind(&CommandLineEditor::ResizeImage, &editor) });

	menu.AddItem({ "DeleteItem",
		{ "<position>" },
		"Удаляет элемент документа, находящийся в указанной позиции. Если указана недопустимая позиция документа, команда игнорируется, а пользователю выводится сообщение об ошибке.",
		std::bind(&CommandLineEditor::DeleteItem, &editor) });

	menu.AddItem({ "Help",
		{},
		"Выводит справку о доступных командах редактирования и их аргументах.",
		std::bind(&Menu::ShowHelpMessage, &menu) });

	menu.AddItem({ "Undo",
		{},
		"Отменяет действие ранее введенной команды редактирования, возвращая документ в предыдущее состояние.",
		std::bind(&CommandLineEditor::Undo, &editor) });

	menu.AddItem({ "Redo",
		{},
		"Выполняет ранее отмененную команду редактирования, возвращая документ в состояние, отменяет действие команды Undo.",
		std::bind(&CommandLineEditor::Redo, &editor) });

	menu.AddItem({ "Save",
		{ "<path>" },
		"Сохраняет текущее состояние документа в файл формата html с изображениями.",
		std::bind(&CommandLineEditor::DeleteItem, &editor) });

	menu.Run();
}
