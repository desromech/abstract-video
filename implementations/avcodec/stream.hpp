#ifndef AVIDEO_STREAM_HPP
#define AVIDEO_STREAM_HPP

#include "common.hpp"

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
}

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

    bool hasVideoStream = false;
    unsigned int videoStreamIndex = 0;
    unsigned int videoStreamWidth = 0;
    unsigned int videoStreamHeight = 0;
    AVCodec *videoCodec = nullptr;

    bool hasAudioStream = false;
    unsigned int audioStreamIndex = 0;
    unsigned int audioStreamChannels = 0;
    unsigned int audioStreamSampleRate = 0;
    AVCodec *audioCodec = nullptr;
};

} // End of namespace AvideoAVCodec

#endif //AVIDEO_STREAM_HPP
