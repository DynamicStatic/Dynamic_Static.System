
set(stb.include "${CMAKE_BINARY_DIR}/stb/")
# file(
#     DOWNLOAD
#     https://github.com/nothings/stb/blob/master/stb.h
#     ${stb.include}/stb.h
# )

file(
    DOWNLOAD
    https://raw.githubusercontent.com/nothings/stb/master/stb_vorbis.c
    ${stb.include}/stb_vorbis.c
)
