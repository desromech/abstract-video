project(ffmpeg)

if(NOT WIN32)
    include(ExternalProject)

    ExternalProject_Add(ffmpeg
        SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/ffmpeg"
        PREFIX ${CMAKE_CURRENT_BINARY_DIR}/ffmpeg_install
        CONFIGURE_COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/ffmpeg/configure --prefix=${CMAKE_CURRENT_BINARY_DIR}/ffmpeg_install --disable-static --enable-shared
    )
endif()
