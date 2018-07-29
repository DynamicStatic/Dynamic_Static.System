
# ==========================================
#   Copyright (c) 2017-2018 Dynamic_Static
#     Patrick Purcell
#       Licensed under the MIT license
#     http://opensource.org/licenses/MIT
# ==========================================

set(imgui.includeDirectories "${CMAKE_CURRENT_LIST_DIR}/imgui/")
file(GLOB imgui.clutter "${imgui.includeDirectories}/*")
list(REMOVE_ITEM imgui.clutter "${imgui.includeDirectories}/imconfig.h")
list(REMOVE_ITEM imgui.clutter "${imgui.includeDirectories}/imgui.cpp")
list(REMOVE_ITEM imgui.clutter "${imgui.includeDirectories}/imgui.h")
list(REMOVE_ITEM imgui.clutter "${imgui.includeDirectories}/imgui_demo.cpp")
list(REMOVE_ITEM imgui.clutter "${imgui.includeDirectories}/imgui_draw.cpp")
list(REMOVE_ITEM imgui.clutter "${imgui.includeDirectories}/imgui_internal.h")
list(REMOVE_ITEM imgui.clutter "${imgui.includeDirectories}/stb_rect_pack.h")
list(REMOVE_ITEM imgui.clutter "${imgui.includeDirectories}/stb_textedit.h")
list(REMOVE_ITEM imgui.clutter "${imgui.includeDirectories}/stb_truetype.h")
if(imgui.clutter)
    file(REMOVE_RECURSE ${imgui.clutter})
endif()
