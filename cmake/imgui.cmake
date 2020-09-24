
# ==========================================
#   Copyright (c) 2017-2018 Dynamic_Static
#     Patrick Purcell
#       Licensed under the MIT license
#     http://opensource.org/licenses/MIT
# ==========================================

set(imgui_includeDirectories "${externalDirectory}/imgui/")
# file(GLOB imgui_clutter "${imgui_includeDirectories}/*")
# list(
#     REMOVE_ITEM imgui_clutter
#         "${imgui_includeDirectories}/imconfig.h"
#         "${imgui_includeDirectories}/imgui.cpp"
#         "${imgui_includeDirectories}/imgui.h"
#         "${imgui_includeDirectories}/imgui_demo.cpp"
#         "${imgui_includeDirectories}/imgui_draw.cpp"
#         "${imgui_includeDirectories}/imgui_internal.h"
#         "${imgui_includeDirectories}/stb_rect_pack.h"
#         "${imgui_includeDirectories}/stb_textedit.h"
#         "${imgui_includeDirectories}/stb_truetype.h"
# )
set(imgui_sourceFiles
    "${imgui_includeDirectories}/imgui.cpp"
    "${imgui_includeDirectories}/imgui_demo.cpp"
    "${imgui_includeDirectories}/imgui_draw.cpp"
    "${imgui_includeDirectories}/imgui_widgets.cpp"
)
# if(imgui_clutter)
#     file(REMOVE_RECURSE ${imgui_clutter})
# endif()
