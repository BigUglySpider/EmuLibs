#ifndef EMU_CORE_PATH_VALIDATION_H_INC_
#define EMU_CORE_PATH_VALIDATION_H_INC_ 1

#include <filesystem>
#include <string>

namespace EmuCore::FileHelpers
{
	/// <summary>
	/// <para> Creates the parent directories of the provided path if they do not currently exist. </para>
	/// </summary>
	/// <param name="path_">Path to create the parent directories of if nonexistent.</param>
	void CreateParentPathIfNonexistent(const std::filesystem::path& path_);
	/// <summary>
	/// <para> Returns a variant of the provided path which will avoid overwriting existing files of the same name within that directory. </para>
	/// </summary>
	/// <param name="path_">Path to return a non-overwriting variant of.</param>
	/// <returns>Non-overwriting variant of the provided path. If the provided path would not cause an overwrite, this will be equal to the passed path.</returns>
	std::filesystem::path CreateNonOverwritingFilename(const std::filesystem::path& path_);
	/// <summary>
	/// <para> Replaces the filename of the passed path to avoid overwrites. If it would not cause an overwrite when passed, it will be unchanged. </para>
	/// </summary>
	/// <param name="path_">Path to overwrite the filename of if it would cause an overwrite.</param>
	void ReplaceFilenameToAvoidOverwrite(std::filesystem::path& path_);
	/// <summary>
	/// <para> Ensures that the provided path's directory exists and, if it contains a filename, will prevent it from replacing existing files if the provided bool is false. </para>
	/// </summary>
	/// <param name="path_">Path to validate.</param>
	/// <param name="allowReplacementOfExistingFiles">If false, the path's filename will be modified until it will not overwrite any existing files in its directory.</param>
	void ValidateFilePath(std::filesystem::path& path_, const bool allowReplacementOfExistingFiles = false);
}

#endif
