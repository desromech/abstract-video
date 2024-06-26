#include "stream.hpp"

namespace AvideoAVCodec
{
AVCodecStream::AVCodecStream()
{
}

AVCodecStream::~AVCodecStream()
{
    if(isOpened)
        avformat_close_input(&formatContext);
    else
        avformat_free_context(formatContext);
}

bool AVCodecStream::initializeWithURL(const char *url)
{
    formatContext = avformat_alloc_context();
    if(!formatContext)
        return false;

    if(avformat_open_input(&formatContext, url, nullptr, nullptr) != 0)
        return false;
    isOpened = true;

    if (avformat_find_stream_info(formatContext,  NULL) < 0)
        return false;

    return true;
}

} // End of namespace AvideoAVCodec
