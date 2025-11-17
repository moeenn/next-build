#pragma once

#include <array>
#include <filesystem>

namespace Template
{
enum class Error : uint8_t
{
    NoError,
    FailedToCreateDir,
    FailedToCreateGitignore,
    FailedToWriteTemplatedFiles,
};

const std::filesystem::path __pwd = std::filesystem::current_path();
constexpr const char *__projectName = "sandbox";
constexpr std::array<const char *, 3> __dirs = {
    "src",
    "include",
    "build",
};

constexpr std::array<const char *, 3> __gitignore = {
    "build/*",
    ".cache/",
    "compile_commands.json",
};

constexpr const char *__mainCppContent = R"(
#include <iostream>

int main()
{
	std::cout << "hello world\n";
	return 0;	
}
)";

constexpr const char *__cmakeListsTxtContent = R"(
cmake_minimum_required(VERSION 3.10)
project(sandbox)
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_compile_options(-Wall -Wextra -pedantic -Werror -O2)

add_executable(sandbox src/main.cpp)
target_include_directories(sandbox PUBLIC "include")
)";

[[nodiscard]] Error __createDirs();
[[nodiscard]] Error __createGitignore();
[[nodiscard]] Error __createFiles();
[[nodiscard]] Error create();
}; // namespace Template