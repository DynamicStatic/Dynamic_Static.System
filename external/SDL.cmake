
# ==========================================
#   Copyright (c) 2018-2018 Dynamic_Static
#     Patrick Purcell
#       Licensed under the MIT license
#     http://opensource.org/licenses/MIT
# ==========================================

set(SDL.projectDirectory "${CMAKE_CURRENT_LIST_DIR}/SDL2-2.0.8/")
if(MSVC)
    set(SDL.includeDirectory "${SDL.projectDirectory}/include/")
    set(SDL.staticLinkLibraries
        "${SDL.projectDirectory}/lib/Windows/$(Platform)/SDL2.lib"
        "${SDL.projectDirectory}/lib/Windows/$(Platform)/SDL2main.lib"
    )
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E copy
        "${SDL.projectDirectory}/lib/Windows/$(Platform)/SDL2.dll"
        "${CMAKE_BUILD_DIRECTORY}/SDL2.dll"
    )
else()
    # TODO :
    set(SDL.includeDirectory "${SDL.projectDirectory}/include/")
    set(SDL.staticLinkLibraries "")
endif()
