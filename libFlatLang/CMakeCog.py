import ImportScript
from CMakeCogLib import * 

def getCmake():   
    s = [] 
    cmc = CMakeCog("libFlatLang")

    # cmc.find_package_qt_components = []
    # s.append(cmc.find_package_qt())



    genApp = GenHpp(cmc.exeName)
    genApp.makeDirectories = ["${CMAKE_CURRENT_BINARY_DIR}/GenHpp",
                              "${CMAKE_CURRENT_BINARY_DIR}/genPrpt"]
    genApp.hppGenFilesTemplates = ["${CMAKE_SOURCE_DIR}/scripts/hppTemplates.txt"]
    genApp.hppGenFilesGlobes = ['hpp/*.hpp']
    genApp.parseHppPyPath = "${CMAKE_SOURCE_DIR}/scripts/parseHpp.py"

    
    s.append(genApp.getStr())

    cmc.libFilesExtendCppAndH([''])

    cmc.libFiles.extend(genApp.getDefineFiles("${CMAKE_CURRENT_BINARY_DIR}/"))

    cmc.fetchContent = [FetchContent('json URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz',
                                     'json',
                                     'nlohmann_json::nlohmann_json')]

    s.append(cmc.add_library())
    s.append(cmc.target_link_libraries())
    s.append(cmc.target_compile_definitions())

    cmc.targetIncludeDirs = [
        '${CMAKE_CURRENT_SOURCE_DIR}'
    
                         ]
    s.append(cmc.target_include_directories())
    s.append(genApp.add_dependencies())
    return "\n".join(s)

#print(getCmake())
