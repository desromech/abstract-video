
#include "avideo_impl.hpp"

inline void* hideType(void *t)
{
	return t;
}

#define asRef(O, I) (*reinterpret_cast<avideo::ref<O> *> (hideType(&I)) )
#define asRefCounter(O, I) (reinterpret_cast<avideo::ref_counter<O> *> (I))

//==============================================================================
// platform C dispatching functions.
//==============================================================================

AVIDEO_EXPORT avideo_context* avideoOpenDevice(avideo_platform* self, avideo_context_open_info* openInfo)
{
	return reinterpret_cast<avideo_context*> (asRef(avideo::platform, self)->openContext(openInfo));
}

AVIDEO_EXPORT avideo_cstring avideoGetPlatformName(avideo_platform* self)
{
	return asRef(avideo::platform, self)->getName();
}

//==============================================================================
// context C dispatching functions.
//==============================================================================

AVIDEO_EXPORT avideo_error avideoAddContextReference(avideo_context* self)
{
	if(!self) return AVIDEO_NULL_POINTER;
	return asRefCounter(avideo::context, self)->retain();
}

AVIDEO_EXPORT avideo_error avideoReleaseContext(avideo_context* self)
{
	if(!self) return AVIDEO_NULL_POINTER;
	return asRefCounter(avideo::context, self)->release();
}

AVIDEO_EXPORT avideo_container* avideoOpenContainerWithURL(avideo_context* self, avideo_cstring url)
{
	return reinterpret_cast<avideo_container*> (asRef(avideo::context, self)->openContainerWithURL(url));
}

//==============================================================================
// container C dispatching functions.
//==============================================================================

AVIDEO_EXPORT avideo_error avideoAddContainerReference(avideo_container* self)
{
	if(!self) return AVIDEO_NULL_POINTER;
	return asRefCounter(avideo::container, self)->retain();
}

AVIDEO_EXPORT avideo_error avideoReleaseContainer(avideo_container* self)
{
	if(!self) return AVIDEO_NULL_POINTER;
	return asRefCounter(avideo::container, self)->release();
}

AVIDEO_EXPORT avideo_double avideoContainerGetStartTime(avideo_container* self)
{
	return asRef(avideo::container, self)->getStartTime();
}

AVIDEO_EXPORT avideo_double avideoContainerGetDuration(avideo_container* self)
{
	return asRef(avideo::container, self)->getDuration();
}

AVIDEO_EXPORT avideo_error avideoContainerSeekTime(avideo_container* self, avideo_double time)
{
	if(!self) return AVIDEO_NULL_POINTER;
	return asRef(avideo::container, self)->seekTime(time);
}

AVIDEO_EXPORT avideo_error avideoContainerSeekFrameIndex(avideo_container* self, avideo_size frame_index)
{
	if(!self) return AVIDEO_NULL_POINTER;
	return asRef(avideo::container, self)->seekFrame(frame_index);
}

AVIDEO_EXPORT avideo_bool avideoContainerHasVideoStream(avideo_container* self)
{
	return asRef(avideo::container, self)->hasVideoStream();
}

AVIDEO_EXPORT avideo_size avideoContainerGetVideoStreamWidth(avideo_container* self)
{
	return asRef(avideo::container, self)->getVideoStreamWidth();
}

AVIDEO_EXPORT avideo_size avideoContainerGetVideoStreamHeight(avideo_container* self)
{
	return asRef(avideo::container, self)->getVideoStreamHeight();
}

AVIDEO_EXPORT avideo_size avideoContainerGetVideoStreamFrameCount(avideo_container* self)
{
	return asRef(avideo::container, self)->getVideoStreamFrameCount();
}

AVIDEO_EXPORT avideo_float avideoContainerGetVideoStreamFrameRate(avideo_container* self)
{
	return asRef(avideo::container, self)->getVideoStreamFrameRate();
}

AVIDEO_EXPORT avideo_bool avideoContainerHasAudioStream(avideo_container* self)
{
	return asRef(avideo::container, self)->hasAudioStream();
}

AVIDEO_EXPORT avideo_size avideoContainerGetAudioStreamChannels(avideo_container* self)
{
	return asRef(avideo::container, self)->getAudioStreamChannels();
}

AVIDEO_EXPORT avideo_size avideoContainerGetAudioStreamSampleRate(avideo_container* self)
{
	return asRef(avideo::container, self)->getAudioStreamSampleRate();
}



#undef asRef
#undef asRefCounter

namespace avideo
{
avideo_icd_dispatch cppRefcountedDispatchTable = {
#include "avideo_icd.10.inc"
};
} // End of avideo
