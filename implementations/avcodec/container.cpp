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
    avcodec_free_context(&videoCodecContext);
    av_packet_free(&containerPacket);
    av_frame_free(&videoFrame);
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
            audioStreamChannels = localCodecParameters->ch_layout.nb_channels;
            audioStreamSampleRate = localCodecParameters->sample_rate;
            audioCodec = decoder;
        }
    }

    // Prepare for video decoding.
    if(hasVideoStream_)
    {
        videoCodecContext = avcodec_alloc_context3(videoCodec);
        avcodec_parameters_to_context(videoCodecContext, formatContext->streams[videoStreamIndex]->codecpar);
        avcodec_open2(videoCodecContext, videoCodec, nullptr);

        containerPacket = av_packet_alloc();
        videoFrame = av_frame_alloc();
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
    av_seek_frame(formatContext, -1, int64_t(time * AV_TIME_BASE), AVSEEK_FLAG_ANY);
    avcodec_flush_buffers(videoCodecContext);
    return AVIDEO_OK;
}
avideo_error AVCodecContainer::seekFrame(avideo_size frame_index)
{
    av_seek_frame(formatContext, -1, int64_t(frame_index / videoStreamFrameRate * AV_TIME_BASE), AVSEEK_FLAG_FRAME);
    avcodec_flush_buffers(videoCodecContext);
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

/*
avideo_error AVCodecContainer::fetchAndDecodeNextPacket()
{
    bool hasReadVideoPacket = false;
    while((av_read_frame(formatContext, containerPacket) >= 0) & !hasReadVideoPacket)
    {
        if(containerPacket->stream_index == int(videoStreamIndex))
        {
            avcodec_send_packet(videoCodecContext, containerPacket);

            hasReadVideoPacket = true;
        }

        av_packet_unref(containerPacket);
    }

    return hasReadVideoPacket ? AVIDEO_OK : AVIDEO_END_OF_STREAM;

}
*/

avideo_error AVCodecContainer::fetchAndDecodeNextVideoFrame()
{
    while((av_read_frame(formatContext, containerPacket) >= 0))
    {
        if(containerPacket->stream_index == int(videoStreamIndex))
        {
            if (avcodec_send_packet(videoCodecContext, containerPacket) == AVERROR(EAGAIN))
                break;
        }

        av_packet_unref(containerPacket);
    }


    int response = avcodec_receive_frame(videoCodecContext, videoFrame);
    if(response == AVERROR(EAGAIN))
        return AVIDEO_AGAIN;
    if(response == AVERROR_EOF)
        return AVIDEO_END_OF_STREAM;
    if(response < 0)
        return AVIDEO_ERROR;

    //sws_scale_frame(swsContext, convertedVideoFrame, videoFrame);

    return AVIDEO_OK;
}

avideo_size AVCodecContainer::getVideoFrameIndex()
{
    return videoCodecContext ? videoCodecContext->frame_num : 0;
}

avideo_size AVCodecContainer::getVideoFrameWidth()
{
    return videoFrame ? videoFrame->width : 0;
}

avideo_size AVCodecContainer::getVideoFrameHeight()
{
    return videoFrame ? videoFrame->height : 0;
}

avideo_error AVCodecContainer::readYUVFrame(avideo_int planeIndex, avideo_int pitch, avideo_pointer buffer)
{
    return AVIDEO_NO_FRAME;
}

avideo_error AVCodecContainer::readRGBA32ConvertedFrame(avideo_int pitch, avideo_pointer buffer)
{
    if(!convertedVideoFrame || convertedVideoFrame->width != videoFrame->width || convertedVideoFrame->height != videoFrame->height)
    {
        if(convertedVideoFrame)
            av_frame_free(&convertedVideoFrame);
        convertedVideoFrame = av_frame_alloc();
        convertedVideoFrame->format = AV_PIX_FMT_RGBA;
        convertedVideoFrame->width = videoFrame->width;
        convertedVideoFrame->height = videoFrame->height;
        av_frame_get_buffer(convertedVideoFrame, 0);
    } 

    if(!swsContext)
    {
        swsContext = sws_getContext(
        videoFrame->width, videoFrame->height, AVPixelFormat(videoFrame->format),
        convertedVideoFrame->width, convertedVideoFrame->height, AVPixelFormat(convertedVideoFrame->format),
        SWS_FAST_BILINEAR, nullptr, nullptr, 0);
    }

    sws_scale(swsContext, videoFrame->data, videoFrame->linesize, 0,
        videoFrame->height, convertedVideoFrame->data, convertedVideoFrame->linesize);

    avideo_size frameWidth = convertedVideoFrame->width;
    avideo_size frameHeight = convertedVideoFrame->height;

    uint8_t *destRow = (uint8_t*)buffer;
    uint8_t *sourceRow = convertedVideoFrame->data[0];
    int sourcePitch = convertedVideoFrame->linesize[0];
    for(avideo_size y = 0; y < frameHeight; ++y)
    {
        memcpy(destRow, sourceRow, frameWidth*4);
        destRow += pitch;
        sourceRow += sourcePitch;
    }

    return AVIDEO_OK;
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
