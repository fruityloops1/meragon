cmake_minimum_required(VERSION 3.5)
project(ExheaderCli)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_SOURCE_DIR}/Include)

add_executable(ExheaderCli Source/main.cpp Source/Exheader.cpp Source/Patch/ReplacePatch.cpp Source/Patch/PatchBase.cpp Source/Patch/AsmPatch.cpp Source/Patch/BranchHook.cpp)
