set(SOURCES src/nfd_common.c)

if (WIN32)
    list(APPEND SOURCES src/nfd_win.cpp)
elseif (APPLE)
    list(APPEND SOURCES src/nfd_cocoa.m)
elseif (UNIX)
    list(APPEND SOURCES src/nfd_gtk.c)
endif ()

add_library(nativefiledialog ${SOURCES})

target_include_directories(nativefiledialog PUBLIC src/include)