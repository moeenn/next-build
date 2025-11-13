#include <fstream>
#include "CppProjectTemplate.hpp"

CppProjectTemplate::Error CppProjectTemplate::createDirs() const
{
    namespace fs = std::filesystem;

    fs::path projectPath = m_pwd / m_projectName;
    bool isCreated = fs::create_directory(projectPath);
    if (!isCreated)
    {
        std::fprintf(stderr, "error: failed to create project directory.\n");
        return Error::FailedToCreateDir;
    }

    for (const char* dir : m_dirs)
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

CppProjectTemplate::Error CppProjectTemplate::createGitignore() const
{
    namespace fs = std::filesystem;
    try {
        const fs::path fullpath = m_pwd / m_projectName / ".gitignore";
        std::ofstream file(fullpath);
        for (const char* line : m_gitignore)
        {
            file << line << "\n";
        }
        file.close();
    } catch (const std::exception& ex) {
        std::fprintf(stderr, "error: failed to write .gitignore file: %s", ex.what());
        return Error::FailedToCreateGitignore;
    }

     return Error::NoError;
}

CppProjectTemplate::Error CppProjectTemplate::create() const
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

CppProjectTemplate::Error CppProjectTemplate::createFiles() const
{
    namespace fs = std::filesystem;

    fs::path mainCppPath = m_pwd / m_projectName / "src" / "main.cpp";
    fs::path cmakelistsPath = m_pwd / m_projectName / "CMakeLists.txt";

    try {
        std::ofstream mainCppFile(mainCppPath);
        mainCppFile << CppProjectTemplate::m_mainCppContent;
        mainCppFile.close();

        std::ofstream cmakelistsFile(cmakelistsPath);
        cmakelistsFile << CppProjectTemplate::m_cmakeListsTxtContent;
        cmakelistsFile.close();
    } catch (const std::exception& ex) {
        std::fprintf(stderr, "error: failed to write templated files: %s\n", ex.what());
        return Error::FailedToWriteTemplatedFiles;
    }

    return Error::NoError;
}
