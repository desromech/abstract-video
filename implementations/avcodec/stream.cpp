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

        if(!hasVideoStream && localCodecParameters->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            hasVideoStream = true;
            videoStreamIndex = i;
            videoStreamWidth = localCodecParameters->width;
            videoStreamHeight = localCodecParameters->height;
            videoCodec = decoder;
        }
        else if(!hasAudioStream && localCodecParameters->codec_type == AVMEDIA_TYPE_AUDIO)
        {
            hasAudioStream = true;
            audioStreamIndex = i;
            audioStreamChannels = localCodecParameters->channels;
            audioStreamSampleRate = localCodecParameters->sample_rate;
            audioCodec = decoder;
        }
    }

    return true;
}

} // End of namespace AvideoAVCodec
