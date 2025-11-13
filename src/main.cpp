#include <cstdint>
#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <filesystem>

constexpr std::string read_content(const char* filepath)
{
    std::ifstream f(filepath);
    std::stringstream content;
    std::string line;

    while (std::getline(f, line)) {
        content << line << "\n";
    }

    f.close();
    return content.str();
}

class CppProjectTemplate
{
public:
    CppProjectTemplate(const char* projectName)
        :m_projectName(projectName) {}

    enum class Error : uint8_t
    {
        NoError,
        FailedToCreateDir,
        FailedToCreateGitignore,
        FailedToWriteTemplatedFiles,
    };

    [[nodiscard]] Error create() const;

private:
    const std::filesystem::path m_pwd = std::filesystem::current_path();
    const char* m_projectName = "sandbox";
    const std::array<const char*, 3> m_dirs = {
        "src",
        "include",
        "build",
    };

    const std::array<const char*, 3> m_gitignore = {
        "build/*",
        ".cache/",
        "compile_commands.json",
    };


    static constexpr std::string s_mainCppContent = read_content("../templates/main_cpp");
    static constexpr std::string s_cmakeListsTxtContent = read_content("../templates/CMakeLists_txt");

    [[nodiscard]] Error createDirs() const;
    [[nodiscard]] Error createGitignore() const;
    [[nodiscard]] Error createFiles() const;
};

// constexpr std::string CppProjectTemplate::s_mainCppContent = read_content("../templates/main_cpp");
// constexpr std::string CppProjectTemplate::s_cmakeListsTxtContent = read_content("../templates/CMakeLists_txt");

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
        mainCppFile << CppProjectTemplate::s_mainCppContent;
        mainCppFile.close();

        std::ofstream cmakelistsFile(cmakelistsPath);
        cmakelistsFile << CppProjectTemplate::s_cmakeListsTxtContent;
        cmakelistsFile.close();
    } catch (const std::exception& ex) {
        std::fprintf(stderr, "error: failed to write templated files: %s\n", ex.what());
        return Error::FailedToWriteTemplatedFiles;
    }

    return Error::NoError;
}

int main()
{
    const CppProjectTemplate tmpl{"sandbox"};
    CppProjectTemplate::Error err = tmpl.create();
    if (err != CppProjectTemplate::Error::NoError)
    {
        return 1;
    }

    std::cout << "Project created successfully!\n";
    return 0;
}
