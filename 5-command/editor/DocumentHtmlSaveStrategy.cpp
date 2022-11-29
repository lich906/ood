#include "DocumentHtmlSaveStrategy.h"

const std::string HtmlExtension(".html");

void DocumentHtmlSaveStrategy::Save(std::filesystem::path path, const IDocument* document)
try
{
	if (!path.has_filename())
	{
		throw std::runtime_error("specified path does not contain filename.");
	}

	m_parentPath = path.parent_path();

	if (!m_parentPath.string().empty() && !std::filesystem::exists(m_parentPath))
	{
		throw std::runtime_error("directory '" + m_parentPath.string() + "' does not exist.");
	}

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
			SaveImageToFile(image);
		}
		else
		{
			throw std::logic_error("document item isn't paragraph or image.");
		}
	}

	file << "</body>\n"
		 << "</html>\n";
}
catch (const std::exception& e)
{
	throw CommandExecutionException(std::string("Failed to save document: ") + e.what());
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
	return "<img src=\"images\\" + image->GetPath().filename().string() + 
		"\" width=\"" + std::to_string(image->GetWidth()) + 
		"\" height=\"" + std::to_string(image->GetHeight()) + "\" />";
}

std::filesystem::path DocumentHtmlSaveStrategy::GetSavedImagePath(const std::filesystem::path& imagePath) const
{
	std::filesystem::path resultPath(m_parentPath);
	resultPath /= PathConstants::ImagesDir;
	return resultPath /= imagePath.filename();
}

void DocumentHtmlSaveStrategy::SaveImageToFile(const std::shared_ptr<const IImage>& image) const
{
	std::filesystem::path imagesDir(m_parentPath);
	imagesDir /= PathConstants::ImagesDir;
	if (!std::filesystem::exists(imagesDir))
	{
		std::filesystem::create_directory(imagesDir);
	}

	try
	{
		std::filesystem::copy_file(image->GetPath(), GetSavedImagePath(image->GetPath()), std::filesystem::copy_options::overwrite_existing);
	}
	catch(...)
	{
		throw std::runtime_error("Failed to save file: unable to save image file, temporary copy is corrupted");
	}
}
