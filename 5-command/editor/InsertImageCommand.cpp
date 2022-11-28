#include "InsertImageCommand.h"

InsertImageCommand::InsertImageCommand(IDocumentEditContext* document, const std::shared_ptr<IImage>& image, std::optional<size_t> position)
	: Command(document)
	, m_position(position)
{
	try
	{
		m_image = CreateImageTempCopy(image);
	}
	catch (...)
	{
		--m_tmpImageCopyIndex;
		throw std::runtime_error("Failed to insert image: image file does not exists or uncopyable");
	}
}

void InsertImageCommand::ExecuteImpl()
{
	m_documentEditContext->InsertImageEdit(m_image, m_position);
}

void InsertImageCommand::UnexecuteImpl()
{
	if (m_position.has_value())
	{
		m_documentEditContext->DeleteItemEdit(*m_position);
	}
	else
	{
		m_documentEditContext->DeleteLastItemEdit();
	}
}

InsertImageCommand::~InsertImageCommand() noexcept
{
	// исправить удаление изображения при превышении глубины команд
	std::error_code ec;
	if (!std::filesystem::remove(m_image->GetPath(), ec))
	{
		std::cout << ec.message() << std::endl;
	}

	if (std::filesystem::is_empty(PathConstants::TempImageStorageDir))
	{
		std::filesystem::remove(PathConstants::TempImageStorageDir);
	}
}

std::shared_ptr<IImage> InsertImageCommand::CreateImageTempCopy(const std::shared_ptr<IImage>& image) const
{
	if (!std::filesystem::exists(PathConstants::TempImageStorageDir))
	{
		std::filesystem::create_directory(PathConstants::TempImageStorageDir);
	}

	std::filesystem::path tmpCopyPath(PathConstants::TempImageStorageDir);
	std::string tmpFileName = "img" + std::to_string(++m_tmpImageCopyIndex) + image->GetPath().extension().string();
	tmpCopyPath /= tmpFileName;

	std::filesystem::copy_file(image->GetPath(), tmpCopyPath, std::filesystem::copy_options::overwrite_existing);

	return std::make_shared<Image>(m_documentEditContext, tmpCopyPath, image->GetWidth(), image->GetHeight());
}
