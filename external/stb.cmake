
#==========================================
#  Copyright (c) 2016-2018 Dynamic_Static
#    Patrick Purcell
#      Licensed under the MIT license
#    http://opensource.org/licenses/MIT
#==========================================

set(stb.includeDirectories "${CMAKE_CURRENT_LIST_DIR}/stb/")
file(
    DOWNLOAD
    https://raw.githubusercontent.com/nothings/stb/master/stb_image.h
    "${stb.includeDirectories}/stb_image.h"
)
file(
    DOWNLOAD
    https://github.com/nothings/stb/blob/master/stb_truetype.h
    "${stb.includeDirectories}/stb_truetype.h"
)
