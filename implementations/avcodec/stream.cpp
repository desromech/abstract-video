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
    // See https://github.com/leandromoreira/ffmpeg-libav-tutorial for the
    // sample which is adapted for implementing this.
    formatContext = avformat_alloc_context();
    if(!formatContext)
        return false;

    if(avformat_open_input(&formatContext, url, nullptr, nullptr) != 0)
        return false;
    isOpened = true;

    if (avformat_find_stream_info(formatContext,  NULL) < 0)
        return false;

    for(unsigned int i = 0; i < formatContext->nb_streams; ++i)
    {
        auto localCodecParameters = formatContext->streams[i]->codecpar;
        auto decoder = avcodec_find_decoder(localCodecParameters->codec_id);
        if(!decoder)
            continue;

        if(localCodecParameters->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            printf("Video stream %d: %dx%d\n", i, localCodecParameters->width, localCodecParameters->height);
        }
        else if(localCodecParameters->codec_type == AVMEDIA_TYPE_AUDIO)
        {
            printf("Audio stream %d: channels %d sample rate %d\n", i, localCodecParameters->ch_layout.nb_channels, localCodecParameters->sample_rate);
        }
    }

    return true;
}

} // End of namespace AvideoAVCodec
