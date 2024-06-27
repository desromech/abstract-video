#include "container.hpp"

namespace AvideoAVCodec
{

AVCodecContainer::AVCodecContainer()
{
}

AVCodecContainer::~AVCodecContainer()
{
    if(isOpened)
        avformat_close_input(&formatContext);
    else
        avformat_free_context(formatContext);
}

bool AVCodecContainer::initializeWithURL(const char *url)
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

    startTime = double(formatContext->start_time) / double(AV_TIME_BASE);
    duration = double(formatContext->duration) / double(AV_TIME_BASE);

    for(unsigned int i = 0; i < formatContext->nb_streams; ++i)
    {
        auto stream = formatContext->streams[i];
        auto localCodecParameters = stream->codecpar;
        auto decoder = avcodec_find_decoder(localCodecParameters->codec_id);
        if(!decoder)
            continue;

        if(!hasVideoStream_ && localCodecParameters->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            hasVideoStream_ = true;
            videoStreamIndex = i;
            videoStreamWidth = localCodecParameters->width;
            videoStreamHeight = localCodecParameters->height;
            videoCodec = decoder;
            videoStreamFrameCount = stream->nb_frames;
            videoStreamFrameRate = float(stream->r_frame_rate.num) / float(stream->r_frame_rate.den);
        }
        else if(!hasAudioStream_ && localCodecParameters->codec_type == AVMEDIA_TYPE_AUDIO)
        {
            hasAudioStream_ = true;
            audioStreamIndex = i;
            audioStreamChannels = localCodecParameters->channels;
            audioStreamSampleRate = localCodecParameters->sample_rate;
            audioCodec = decoder;
        }
    }

    return true;
}

avideo_double AVCodecContainer::getStartTime()
{
    return startTime;
}

avideo_double AVCodecContainer::getDuration()
{
    return duration;
}

avideo_error AVCodecContainer::seekTime(avideo_double time)
{
    return AVIDEO_OK;
}
avideo_error AVCodecContainer::seekFrame(avideo_size frame_index)
{
    return AVIDEO_OK;
}

avideo_bool AVCodecContainer::hasVideoStream()
{
    return hasVideoStream_;
}

avideo_size AVCodecContainer::getVideoStreamWidth()
{
    return videoStreamWidth;
}

avideo_size AVCodecContainer::getVideoStreamHeight()
{
    return videoStreamHeight;
}

avideo_size AVCodecContainer::getVideoStreamFrameCount()
{
    return videoStreamFrameCount;
}

avideo_float AVCodecContainer::getVideoStreamFrameRate()
{
    return videoStreamFrameRate;
}

avideo_bool AVCodecContainer::hasAudioStream()
{
    return hasAudioStream_;
}

avideo_size AVCodecContainer::getAudioStreamChannels()
{
    return audioStreamChannels;
}

avideo_size AVCodecContainer::getAudioStreamSampleRate()
{
    return audioStreamSampleRate;
}

} // End of namespace AvideoAVCodec
