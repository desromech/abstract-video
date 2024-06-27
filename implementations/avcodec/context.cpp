#include "context.hpp"
#include "container.hpp"

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

avideo::container_ptr AVCodecContext::openContainerWithURL(avideo_cstring url)
{
    auto stream = avideo::makeObject<AVCodecContainer> ();
    if(!stream.as<AVCodecContainer>()->initializeWithURL(url))
        return nullptr;

    return stream.disown();
}

} // End of namespace AvideoAVCodec
