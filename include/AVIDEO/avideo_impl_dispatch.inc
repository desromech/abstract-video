
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

AVIDEO_EXPORT avideo_stream* avideoOpenStreamWithURL(avideo_context* self, avideo_cstring url)
{
	return reinterpret_cast<avideo_stream*> (asRef(avideo::context, self)->openStreamWithURL(url));
}

//==============================================================================
// stream C dispatching functions.
//==============================================================================

AVIDEO_EXPORT avideo_error avideoAddStreamReference(avideo_stream* self)
{
	if(!self) return AVIDEO_NULL_POINTER;
	return asRefCounter(avideo::stream, self)->retain();
}

AVIDEO_EXPORT avideo_error avideoReleaseStream(avideo_stream* self)
{
	if(!self) return AVIDEO_NULL_POINTER;
	return asRefCounter(avideo::stream, self)->release();
}



#undef asRef
#undef asRefCounter

namespace avideo
{
avideo_icd_dispatch cppRefcountedDispatchTable = {
#include "avideo_icd.10.inc"
};
} // End of avideo
