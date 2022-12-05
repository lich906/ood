#pragma once

#include <iostream>
#include <string>

#include "Image.h"
#include "Command.h"
#include "PathConstants.h"

class InsertImageCommand : public Command
{
public:
	InsertImageCommand(const std::shared_ptr<IImage>& image, 
		std::function<void(const std::shared_ptr<IImage>&)> onExecute, std::function<void()> onUnexecute,
		std::function<void(std::unique_ptr<Command>&&)> commandSaver);

	void ExecuteImpl() override;

	void UnexecuteImpl() override;

	void Destroy() noexcept override;

private:
	std::shared_ptr<IImage> CreateImageTempCopy(const std::shared_ptr<IImage>& image) const;

	std::function<void(const std::shared_ptr<IImage>&)> m_onExecute;
	std::function<void()> m_onUnexecute;
	std::shared_ptr<IImage> m_image;
	std::filesystem::path m_tmpCopyFilename;
	std::function<void(std::unique_ptr<Command>&&)> m_commandSaver;

	static inline size_t m_tmpImageCopyIndex = 0;
};
