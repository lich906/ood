#include "DocumentHtmlSaveStrategy.h"

const std::string HtmlExtension(".html");

void DocumentHtmlSaveStrategy::Save(std::filesystem::path path, const IDocument* document)
{
	if (!path.has_extension())
	{
		path += HtmlExtension;
	}

	std::ofstream file(path);

	file << "<!DOCTYPE html>\n"
		 << "<html>\n"
		 << "<head>\n"
		 << "    <title>" << GetHtmlEncodedString(document->GetTitle()) << "</title>\n"
		 << "</head>\n"
		 << "<body>\n";

	for (size_t i = 0; i < document->GetItemsCount(); ++i)
	{
		file << "    ";

		auto item = document->GetItem(i);
		if (auto paragraph = item.GetParagraph())
		{
			file << GetParagraphHtml(paragraph) << std::endl;
		}
		else if (auto image = item.GetImage())
		{
			file << GetImageHtml(image) << std::endl;
			SaveImageFile(path.parent_path(), image);
		}
		else
		{
			throw std::logic_error("Failed to save document: document item isn't paragraph or image");
		}
	}

	file << "</body>\n"
		 << "</html>\n";
}

std::string DocumentHtmlSaveStrategy::GetHtmlEncodedString(const std::string& source) const
{
	std::string html;

	std::for_each(source.begin(), source.end(), [&](const char& ch) {
		auto it = m_encodeTable.find(ch);
		if (it != m_encodeTable.end())
		{
			html.append(it->second);
		}
		else
		{
			html.push_back(ch);
		}
	});

	return html;
}

std::string DocumentHtmlSaveStrategy::GetParagraphHtml(const std::shared_ptr<const IParagraph>& paragraph) const
{
	return "<p>" + GetHtmlEncodedString(paragraph->GetText()) + "</p>";
}

std::string DocumentHtmlSaveStrategy::GetImageHtml(const std::shared_ptr<const IImage>& image) const
{
	return "<img src=\"" + image->GetPath().string() + "\" width=\"" + std::to_string(image->GetWidth()) + "\" height=\"" + std::to_string(image->GetHeight()) + "\" />";
}

void DocumentHtmlSaveStrategy::SaveImageFile(std::filesystem::path path, const std::shared_ptr<const IImage>& image) const
{
	path /= PathConstants::ImagesDir;

	if (!std::filesystem::exists(PathConstants::ImagesDir))
	{
		std::filesystem::create_directory(PathConstants::ImagesDir);
	}

	path /= image->GetPath().filename();

	try
	{
		std::filesystem::copy_file(image->GetPath(), path, std::filesystem::copy_options::overwrite_existing);
	}
	catch(...)
	{
		throw std::runtime_error("Failed to save file: unable to save image file, temporary copy is corrupted");
	}
}
