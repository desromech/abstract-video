set(AVCodec_Headers
    ac3_parser.h
    adts_parser.h
    avcodec.h
    avdct.h
    avfft.h
    bsf.h
    codec.h
    codec_desc.h
    codec_id.h
    codec_par.h
    d3d11va.h
    defs.h
    dirac.h
    dv_profile.h
    dxva2.h
    jni.h
    mediacodec.h
    packet.h
    qsv.h
    vdpau.h
    version.h
    version_major.h
    videotoolbox.h
    vorbis_parser.h
)

set(AVCodec_Sources
    ac3_parser.c
    adts_parser.c
    allcodecs.c
    avcodec.c
    avdct.c
    avfft.c
    packet.c
    bitstream.c
    bitstream_filters.c
    bsf.c
    codec_desc.c
    codec_par.c
    d3d11va.c
    decode.c
    dirac.c
    dv_profile.c
    encode.c
    get_buffer.c
    imgconvert.c
    jni.c
    mathtables.c
    mediacodec.c
    mpeg12framerate.c
    options.c
    parser.c
    parsers.c
    profiles.c
    qsv_api.c
    raw.c
    refstruct.c
    threadprogress.c
    utils.c
    version.c
    vlc.c
    vorbis_parser.c
    xiph.c
)

configure_file(bsf_list.c.in bsf_list.c)
configure_file(codec_list.c.in codec_list.c)
configure_file(parser_list.c.in parser_list.c)

add_library(avcodec SHARED ${AVCodec_Headers} ${AVCodec_Sources})
target_link_libraries(avcodec avutil)

