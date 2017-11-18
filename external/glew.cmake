
if (MSVC)
    set(glew.include "${PROJECT_SOURCE_DIR}/external/glew-2.1.0/include/")
    set(glew.library "${PROJECT_SOURCE_DIR}/external/glew-2.1.0/lib/Release/x64/glew32s.lib")
endif()
set(glew.ready TRUE)
