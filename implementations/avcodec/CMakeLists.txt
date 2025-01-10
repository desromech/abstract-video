set(AvideoAVCodec_Sources
    common.hpp
    container.cpp
    container.hpp
    context.cpp
    context.hpp
    platform.cpp
    platform.hpp
)

add_definitions(
    -DAVIDEO_BUILD
)

if(BUILD_MULTIPLE_BACKENDS)
    set(AvideoAVCodec AvideoAVCodec)
else()
    set(AvideoAVCodec Avideo)
endif()

add_library(${AvideoAVCodec} SHARED ${AvideoAVCodec_Sources})
target_link_libraries(${AvideoAVCodec} avcodec avformat swscale)
