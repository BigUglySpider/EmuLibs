#include "PathValidation.h"

void EmuCore::FileHelpers::CreateParentPathIfNonexistent(const std::filesystem::path& path_)
{
	auto parentPath = std::filesystem::absolute(path_).parent_path();
	if (!std::filesystem::exists(parentPath))
	{
		std::filesystem::create_directories(parentPath);
	}
}

std::filesystem::path EmuCore::FileHelpers::CreateNonOverwritingFilename(const std::filesystem::path& path_)
{
	std::filesystem::path out = path_;
	ReplaceFilenameToAvoidOverwrite(out);
	return out;
}

void EmuCore::FileHelpers::ReplaceFilenameToAvoidOverwrite(std::filesystem::path& path_)
{
	if (std::filesystem::exists(path_))
	{
		if (path_.has_filename())
		{
			std::size_t i = 1;
			if (path_.has_extension())
			{
				const std::wstring stem = path_.stem().wstring() + L" (";
				const std::wstring extension = L")" + path_.extension().wstring();
				do
				{
					path_.replace_filename(stem + std::to_wstring(i) + extension);
					++i;
				} while (std::filesystem::exists(path_));
			}
			else
			{
				const std::wstring fileName = path_.filename().wstring() + L" (";
				do
				{
					path_.replace_filename(fileName + std::to_wstring(i) + L")");
					++i;
				} while (std::filesystem::exists(path_));
			}
		}
	}
}

void EmuCore::FileHelpers::ValidateFilePath(std::filesystem::path& path_, const bool allowReplacementOfExistingFiles)
{
	CreateParentPathIfNonexistent(path_);
	if (!allowReplacementOfExistingFiles)
	{
		ReplaceFilenameToAvoidOverwrite(path_);
	}
}
