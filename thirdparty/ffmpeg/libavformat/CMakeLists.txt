set(AVFormat_Headers
    avformat.h
    avio.h
    version.h
    version_major.h
)

set(AVFormat_Sources
    allformats.c
    avformat.c
    avio.c
    aviobuf.c
    demux.c
    demux_utils.c
    dump.c
    dv.c
    format.c
    id3v1.c
    id3v2.c
    isom_tags.c
    metadata.c
    mux.c
    mux_utils.c
    options.c
    os_support.c
    protocols.c
    riff.c
    sdp.c
    seek.c
    url.c
    utils.c
    version.c
)

configure_file(muxer_list.c.in muxer_list.c)
configure_file(demuxer_list.c.in demuxer_list.c)
configure_file(protocol_list.c.in protocol_list.c)

add_library(avformat SHARED ${AVFormat_Headers} ${AVFormat_Sources})
target_link_libraries(avformat avutil avcodec)
