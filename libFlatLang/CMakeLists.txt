FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz)
FetchContent_MakeAvailable(json)



set(libFlatLang_SRCS
   FlatLangConfig.cpp
)

# Declare the library
add_library(libFlatLang STATIC
    ${libFlatLang_SRCS}
)

# Specify here the include directories exported
# by this library
target_include_directories(libFlatLang PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(libFlatLang PRIVATE nlohmann_json::nlohmann_json )