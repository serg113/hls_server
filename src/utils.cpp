
#include "utils.h"
#include <experimental/filesystem>

void createFolderIfNotExist(const std::string& path)
{
	if (!std::experimental::filesystem::exists(path))
		std::experimental::filesystem::create_directories(path);
}
