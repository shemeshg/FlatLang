# [[[cog
# import cog
# from CMakeCog import getCmake
# cog.outl(getCmake())
# ]]]

SET(GEN_HPP TRUE)
if(GEN_HPP)
    make_directory(${CMAKE_CURRENT_BINARY_DIR}/GenHpp)
make_directory(${CMAKE_CURRENT_BINARY_DIR}/genPrpt)


    set(HPP_GEN_FILES
        ${CMAKE_SOURCE_DIR}/scripts/hppTemplates.txt
        
    )
    add_custom_target(runScript_fd2865362298c5d64e5b21b59b88f05282db5158918520af2478cd2659e47cbd ALL
        COMMAND python3 ${CMAKE_SOURCE_DIR}/scripts/parseHpp.py ${HPP_GEN_FILES}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Running parseHpp shell script")

    # Run a shell script before everything else
    execute_process(
        COMMAND python3 ${CMAKE_SOURCE_DIR}/scripts/parseHpp.py ${HPP_GEN_FILES}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        RESULT_VARIABLE result
    )

    # Check the result of the script execution
    if(NOT result EQUAL 0)
        message(FATAL_ERROR "Script execution failed with result: ${result}")
    endif()

    # Continue with the rest of your CMake configuration
endif()
                     

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz)
FetchContent_MakeAvailable(json)                            


add_library(libFlatLang STATIC
  FlatLangConfig.h
FlatLangConfig.cpp
)        
                     
target_link_libraries(libFlatLang PRIVATE nlohmann_json::nlohmann_json) 
target_compile_definitions(libFlatLang PRIVATE LIBFLATLANG_LIBRARY) 

target_include_directories(libFlatLang PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})                     
        

if(GEN_HPP)
  add_dependencies(libFlatLang runScript_fd2865362298c5d64e5b21b59b88f05282db5158918520af2478cd2659e47cbd)
endif()
        
# [[[end]]]