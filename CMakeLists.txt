cmake_minimum_required(VERSION 3.10.0)
project(FlatLang VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz)
FetchContent_MakeAvailable(json)

include_directories(${PROJECT_SOURCE_DIR}/external/inja/include/inja)

add_subdirectory(external/pybind11)
pybind11_add_module(flatLangPy flatLangPy/flatLangPy.cpp)

add_executable(FlatLang main.cpp)
target_link_libraries(FlatLang PRIVATE nlohmann_json::nlohmann_json )

