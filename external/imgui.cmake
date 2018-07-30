
# ==========================================
#   Copyright (c) 2017-2018 Dynamic_Static
#     Patrick Purcell
#       Licensed under the MIT license
#     http://opensource.org/licenses/MIT
# ==========================================

set(imgui.includeDirectories "${CMAKE_CURRENT_LIST_DIR}/imgui/")
file(GLOB imgui.clutter "${imgui.includeDirectories}/*")
list(
    REMOVE_ITEM imgui.clutter
        "${imgui.includeDirectories}/imconfig.h"
        "${imgui.includeDirectories}/imgui.cpp"
        "${imgui.includeDirectories}/imgui.h"
        "${imgui.includeDirectories}/imgui_demo.cpp"
        "${imgui.includeDirectories}/imgui_draw.cpp"
        "${imgui.includeDirectories}/imgui_internal.h"
        "${imgui.includeDirectories}/stb_rect_pack.h"
        "${imgui.includeDirectories}/stb_textedit.h"
        "${imgui.includeDirectories}/stb_truetype.h"
)
if(imgui.clutter)
    file(REMOVE_RECURSE ${imgui.clutter})
endif()
