
set(tinysound.include "${CMAKE_BINARY_DIR}/tinysound.h")
file(
    DOWNLOAD
    https://github.com/RandyGaul/tinyheaders/blob/master/tinysound.h
    ${tinysound.include}
)
