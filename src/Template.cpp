#include "Template.hpp"
#include <fstream>

namespace fs = std::filesystem;

[[nodiscard]] Template::Error Template::__createDirs()
{
    fs::path projectPath = __pwd / __projectName;
    bool isCreated = fs::create_directory(projectPath);
    if (!isCreated)
    {
        std::fprintf(stderr, "error: failed to create project directory.\n");
        return Error::FailedToCreateDir;
    }

    for (const char *dir : __dirs)
    {
        fs::path fullpath = __pwd / __projectName / dir;
        isCreated = fs::create_directory(fullpath);
        if (!isCreated)
        {
            std::fprintf(stderr, "error: failed to create directory: %s\n", dir);
            return Error::FailedToCreateDir;
        }
    }

    return Error::NoError;
}

[[nodiscard]] Template::Error Template::__createGitignore()
{
    try
    {
        const fs::path fullpath = __pwd / __projectName / ".gitignore";
        std::ofstream file(fullpath);
        for (const char *line : __gitignore)
        {
            file << line << "\n";
        }
        file.close();
    }
    catch (const std::exception &ex)
    {
        std::fprintf(stderr, "error: failed to write .gitignore file: %s", ex.what());
        return Error::FailedToCreateGitignore;
    }

    return Error::NoError;
}

[[nodiscard]] Template::Error Template::__createFiles()
{
    fs::path mainCppPath = __pwd / __projectName / "src" / "main.cpp";
    fs::path cmakelistsPath = __pwd / __projectName / "CMakeLists.txt";

    try
    {
        std::ofstream mainCppFile(mainCppPath);
        mainCppFile << __mainCppContent;
        mainCppFile.close();

        std::ofstream cmakelistsFile(cmakelistsPath);
        cmakelistsFile << __cmakeListsTxtContent;
        cmakelistsFile.close();
    }
    catch (const std::exception &ex)
    {
        std::fprintf(stderr, "error: failed to write templated files: %s\n", ex.what());
        return Error::FailedToWriteTemplatedFiles;
    }

    return Error::NoError;
}

[[nodiscard]] Template::Error Template::create()
{
    Error err = __createDirs();
    if (err != Error::NoError)
    {
        return err;
    }

    err = __createGitignore();
    if (err != Error::NoError)
    {
        return err;
    }

    err = __createFiles();
    if (err != Error::NoError)
    {
        return err;
    }

    return Error::NoError;
}