
#==========================================
#  Copyright (c) 2016-2018 Dynamic_Static
#    Patrick Purcell
#      Licensed under the MIT license
#    http://opensource.org/licenses/MIT
#==========================================

set(stb_includeDirectory "${externalDirectory}/stb/")
file(
    DOWNLOAD
    https://raw.githubusercontent.com/nothings/stb/master/stb_image.h
    "${stb_includeDirectory}/stb_image.h"
)
file(
    DOWNLOAD
    https://raw.githubusercontent.com/nothings/stb/master/stb_image_write.h
    "${stb_includeDirectory}/stb_image_write.h"
)
file(
    DOWNLOAD
    https://raw.githubusercontent.com/nothings/stb/master/stb_truetype.h
    "${stb_includeDirectory}/stb_truetype.h"
)
