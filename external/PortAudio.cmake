
# cmake_minimum_required(VERSION 3.3)
# include(ExternalProject)
# ExternalProject_Add(
#     PortAudio
#     URL "${PROJECT_SOURCE_DIR}/external/PortAudio/pa_stable_v190600_20161030.tgz"
#     BINARY_DIR build
#     INSTALL_COMMAND ""
# )
# 
# ExternalProject_Get_Property(PortAudio SOURCE_DIR)
# ExternalProject_Get_Property(PortAudio BINARY_DIR)
# set(PortAudio.include "${SOURCE_DIR}/include/")
# if (MSVC)
#     set(PortAudio.library "${BINARY_DIR}/$(Configuration)/portaudio_static_x64.lib")
# else()
#     set(PortAudio.library "${BINARY_DIR}/libportaudio_static.a")
# endif()
