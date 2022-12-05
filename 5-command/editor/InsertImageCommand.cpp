#include "InsertImageCommand.h"

constexpr auto ImageNamePrefix = "img";

InsertImageCommand::InsertImageCommand(const std::shared_ptr<IImage>& image, 
	std::function<void(const std::shared_ptr<IImage>&)> onExecute, std::function<void()> onUnexecute,
	std::function<void(std::unique_ptr<Command>&&)> commandSaver)
	: m_onExecute(std::move(onExecute))
	, m_onUnexecute(std::move(onUnexecute))
	, m_commandSaver(std::move(commandSaver))
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
	m_onExecute(m_image);
}

void InsertImageCommand::UnexecuteImpl()
{
	m_onUnexecute();
}

void InsertImageCommand::Destroy() noexcept
{
	// исправить удаление изображения при превышении глубины команд
	std::error_code ec;
	if (!std::filesystem::remove(m_image->GetPath(), ec))
	{
		std::cout << ec.message() << std::endl;
	}

	if (std::filesystem::is_empty(PathConstants::TempImageStorageDir))
	{
		std::filesystem::remove_all(PathConstants::TempDir);
	}
}

std::shared_ptr<IImage> InsertImageCommand::CreateImageTempCopy(const std::shared_ptr<IImage>& image) const
{
	if (!std::filesystem::exists(PathConstants::TempImageStorageDir))
	{
		std::filesystem::create_directories(PathConstants::TempImageStorageDir);
	}

	std::filesystem::path tmpCopyPath(PathConstants::TempImageStorageDir);
	std::string tmpFileName = ImageNamePrefix + std::to_string(++m_tmpImageCopyIndex) + image->GetPath().extension().string();
	tmpCopyPath /= tmpFileName;

	std::filesystem::copy_file(image->GetPath(), tmpCopyPath, std::filesystem::copy_options::overwrite_existing);

	return std::make_shared<Image>(tmpCopyPath, image->GetWidth(), image->GetHeight(), m_commandSaver);
}
