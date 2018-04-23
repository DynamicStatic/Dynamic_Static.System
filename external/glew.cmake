
if(MSVC)
    set(glew.includeDirectories "${CMAKE_CURRENT_LIST_DIR}/glew-2.1.0/include/")
    set(glew.staticLinkLibraries "${CMAKE_CURRENT_LIST_DIR}/glew-2.1.0/lib/Release/$(Platform)/glew32s.lib")
else()
    set(glew.includeDirectories "")
    set(glew.staticLinkLibraries "")
endif()
