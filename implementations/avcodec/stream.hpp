#ifndef AVIDEO_STREAM_HPP
#define AVIDEO_STREAM_HPP

#include "common.hpp"
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>

namespace AvideoAVCodec
{

class AVCodecStream : public avideo::stream
{
public:
    AVCodecStream();
    ~AVCodecStream();

    bool initializeWithURL(const char *url);
    
    bool isOpened = false;
    AVFormatContext *formatContext = nullptr;
};

} // End of namespace AvideoAVCodec

#endif //AVIDEO_STREAM_HPP
