cmake_minimum_required(VERSION 3.10.0)
project(FlatLang VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)



include_directories(${PROJECT_SOURCE_DIR}/external/inja/include/inja)

add_subdirectory(libFlatLang)

add_subdirectory(external/pybind11)
pybind11_add_module(flatLangPy flatLangPy/flatLangPy.cpp)
target_link_libraries(flatLangPy PRIVATE libFlatLang)

add_executable(FlatLang main.cpp)
target_link_libraries(FlatLang PRIVATE libFlatLang)

