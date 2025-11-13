#pragma once
#include <cstdint>
#include <filesystem>

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


    const char* m_mainCppContent = "#include <iostream>\n"
                                   "\n"
                                   "int main()\n"
                                   "{\n"
                                   "    std::cout << \"hello world\\n\";\n"
                                   "    return 0;\n"
                                   "}\n";

    const char *m_cmakeListsTxtContent = "cmake_minimum_required(VERSION 3.10)\n"
                                         "project(sandbox)\n"
                                         "set(CMAKE_CXX_COMPILER \"clang++\")\n"
                                         "set(CMAKE_CXX_STANDARD 23)\n"
                                         "set(CMAKE_BUILD_TYPE Release)\n"
                                         "set(CMAKE_EXPORT_COMPILE_COMMANDS ON)\n"
                                         "add_compile_options(-Wall -Wextra -pedantic -Werror -O2)\n\n"
                                         "add_executable(sandbox src/main.cpp)\n"
                                         "target_include_directories(sandbox PUBLIC \"include\")\n";


    [[nodiscard]] Error createDirs() const;
    [[nodiscard]] Error createGitignore() const;
    [[nodiscard]] Error createFiles() const;
};
