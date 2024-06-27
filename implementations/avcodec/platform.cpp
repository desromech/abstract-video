#include "platform.hpp"
#include "context.hpp"
#include <mutex>
#include "AVIDEO/avideo_impl_dispatch.inc"

namespace AvideoAVCodec
{

static avideo::platform_ref theAVCodecPlatform;

avideo::context_ptr AVCodecPlatform::openContext(avideo_context_open_info* openInfo)
{
    return AVCodecContext::open(openInfo).disown();
}

avideo_cstring AVCodecPlatform::getName()
{
    return "FFMpeg libavcodec";
}

} // End of namespace AvideoAVCodec

AVIDEO_EXPORT avideo_error avideoGetPlatforms(avideo_size numplatforms, avideo_platform** platforms, avideo_size* ret_numplatforms)
{
    using namespace AvideoAVCodec;
    
    static std::once_flag platformCreatedFlag;
    std::call_once(platformCreatedFlag, []{
        theAVCodecPlatform = avideo::makeObject<AVCodecPlatform> ();
    });
    
    if(numplatforms > 0)
        platforms[0] = reinterpret_cast<avideo_platform*> (theAVCodecPlatform.asPtrWithoutNewRef());

    if(ret_numplatforms)
        *ret_numplatforms = 1;

    return AVIDEO_OK;
}
