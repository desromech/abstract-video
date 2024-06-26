#include "context.hpp"

namespace AvideoAVCodec
{

avideo::context_ref AVCodecContext::open(avideo_context_open_info* openInfo)
{
    auto context = avideo::makeObject<AVCodecContext> ();
    if (!context.as<AVCodecContext>()->initialize(openInfo))
        return avideo::context_ref();

    return context;
}

bool AVCodecContext::initialize(avideo_context_open_info* openInfo)
{
    (void)openInfo;
    return true;
}

avideo::stream_ptr AVCodecContext::openStreamWithURL(avideo_cstring url)
{
    return nullptr;
}

} // End of namespace AvideoAVCodec
