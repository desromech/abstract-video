#ifndef AVIDEO_STREAM_HPP
#define AVIDEO_STREAM_HPP

#include "common.hpp"

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

namespace AvideoAVCodec
{

class AVCodecContainer : public avideo::container
{
public:
    AVCodecContainer();
    ~AVCodecContainer();

    bool initializeWithURL(const char *url);

	virtual avideo_double getStartTime() override;
	virtual avideo_double getDuration() override;

	virtual avideo_error seekTime(avideo_double time) override;
	virtual avideo_error seekFrame(avideo_size frame_index) override;
    
	virtual avideo_bool hasVideoStream() override;
	virtual avideo_size getVideoStreamWidth() override;
	virtual avideo_size getVideoStreamHeight() override;
	virtual avideo_size getVideoStreamFrameCount() override;
	virtual avideo_float getVideoStreamFrameRate() override;

	virtual avideo_error fetchAndDecodeNextPacket() override;
	virtual avideo_error fetchAndDecodeNextVideoFrame() override;

	virtual avideo_size getVideoFrameIndex() override;
	virtual avideo_size getVideoFrameWidth() override;
	virtual avideo_size getVideoFrameHeight() override;

	virtual avideo_bool hasAudioStream() override;
	virtual avideo_size getAudioStreamChannels() override;
	virtual avideo_size getAudioStreamSampleRate() override;

    bool isOpened = false;
    AVFormatContext *formatContext = nullptr;

    double startTime = 0.0;
    double duration = 0.0;

    bool hasVideoStream_ = false;
    unsigned int videoStreamIndex = 0;
    unsigned int videoStreamWidth = 0;
    unsigned int videoStreamHeight = 0;
    unsigned int videoStreamFrameCount = 0;
    float videoStreamFrameRate = 1.0f;
    AVCodec *videoCodec = nullptr;
    AVCodecContext *videoCodecContext = nullptr;
    AVPacket *containerPacket = nullptr;
    AVFrame *videoFrame = nullptr;

    bool hasAudioStream_ = false;
    unsigned int audioStreamIndex = 0;
    unsigned int audioStreamChannels = 0;
    unsigned int audioStreamSampleRate = 0;
    AVCodec *audioCodec = nullptr;
};

} // End of namespace AvideoAVCodec

#endif //AVIDEO_STREAM_HPP
