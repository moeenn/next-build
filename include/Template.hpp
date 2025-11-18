#pragma once

#include <array>
#include <filesystem>

class Template
{
  public:
    enum class Error : uint8_t
    {
        NoError,
        FailedToCreateDir,
        FailedToCreateGitignore,
        FailedToWriteTemplatedFiles,
    };

    Template(const char *projectName) : m_projectName(projectName)
    {
    }

    [[nodiscard]] Error create();

  private:
    const std::filesystem::path m_pwd = std::filesystem::current_path();
    const char *m_projectName = "sandbox";
    static constexpr std::array<const char *, 3> s_dirs = {
        "src",
        "include",
        "build",
    };

    static constexpr std::array<const char *, 3> s_gitignore = {
        "build/*",
        ".cache/",
        "compile_commands.json",
    };

    static constexpr const char *s_mainCppContent = R"(
#include <iostream>

int main()
{
	std::cout << "hello world\n";
	return 0;	
}
)";

    static constexpr const char *s_cmakeListsTxtContent = R"(
cmake_minimum_required(VERSION 3.10)

set(PROJECT sandbox)
project(${PROJECT})

set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_compile_options(-Wall -Wextra -pedantic -Werror -O2)

add_executable(${PROJECT} src/main.cpp)
target_include_directories(${PROJECT} PUBLIC "include")
)";

    [[nodiscard]] Error createDirs();
    [[nodiscard]] Error createGitignore();
    [[nodiscard]] Error createFiles();
};
