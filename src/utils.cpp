
#include "utils.h"
#include <filesystem>

void createFolderIfNotExist(const std::string& path)
{
	if (!std::filesystem::exists(path))
		std::filesystem::create_directories(path);
}
