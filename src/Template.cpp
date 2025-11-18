#include "Template.hpp"
#include <fstream>

namespace fs = std::filesystem;

[[nodiscard]] Template::Error Template::createDirs()
{
    fs::path projectPath = m_pwd / m_projectName;
    bool isCreated = fs::create_directory(projectPath);
    if (!isCreated)
    {
        std::fprintf(stderr, "error: failed to create project directory.\n");
        return Error::FailedToCreateDir;
    }

    for (const char *dir : s_dirs)
    {
        fs::path fullpath = m_pwd / m_projectName / dir;
        isCreated = fs::create_directory(fullpath);
        if (!isCreated)
        {
            std::fprintf(stderr, "error: failed to create directory: %s\n", dir);
            return Error::FailedToCreateDir;
        }
    }

    return Error::NoError;
}

[[nodiscard]] Template::Error Template::createGitignore()
{
    try
    {
        const fs::path fullpath = m_pwd / m_projectName / ".gitignore";
        std::ofstream file(fullpath);
        for (const char *line : s_gitignore)
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

[[nodiscard]] Template::Error Template::createFiles()
{
    fs::path mainCppPath = m_pwd / m_projectName / "src" / "main.cpp";
    fs::path cmakelistsPath = m_pwd / m_projectName / "CMakeLists.txt";

    try
    {
        std::ofstream mainCppFile(mainCppPath);
        mainCppFile << s_mainCppContent;
        mainCppFile.close();

        std::ofstream cmakelistsFile(cmakelistsPath);
        cmakelistsFile << s_cmakeListsTxtContent;
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
    Error err = createDirs();
    if (err != Error::NoError)
    {
        return err;
    }

    err = createGitignore();
    if (err != Error::NoError)
    {
        return err;
    }

    err = createFiles();
    if (err != Error::NoError)
    {
        return err;
    }

    return Error::NoError;
}
