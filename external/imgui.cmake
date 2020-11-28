
# ==========================================
#   Copyright (c) 2017-2020 dynamic_ctatic
#     Patrick Purcell
#       Licensed under the MIT license
#     http://opensource.org/licenses/MIT
# ==========================================

include(FetchContent)
FetchContent_Declare(
    imgui
    GIT_REPOSITORY "https://github.com/ocornut/imgui.git"
    GIT_TAG v1.79
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(imgui)
add_library(
    imgui STATIC
    "${imgui_SOURCE_DIR}/imconfig.h"
    "${imgui_SOURCE_DIR}/imgui.cpp"
    "${imgui_SOURCE_DIR}/imgui.h"
    "${imgui_SOURCE_DIR}/imgui_demo.cpp"
    "${imgui_SOURCE_DIR}/imgui_draw.cpp"
    "${imgui_SOURCE_DIR}/imgui_internal.h"
    "${imgui_SOURCE_DIR}/imgui_widgets.cpp"
    "${imgui_SOURCE_DIR}/imstb_rectpack.h"
    "${imgui_SOURCE_DIR}/imstb_textedit.h"
    "${imgui_SOURCE_DIR}/imstb_truetype.h"
)
target_include_directories(imgui PUBLIC "${imgui_SOURCE_DIR}")
set_target_properties(imgui PROPERTIES FOLDER "external/")
set_target_properties(imgui PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(imgui PUBLIC cxx_std_17)
