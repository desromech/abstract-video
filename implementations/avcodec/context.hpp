#ifndef AVIDEO_CONTEXT_HPP
#define AVIDEO_CONTEXT_HPP

#include "common.hpp"

namespace AvideoAVCodec
{

class AVCodecContext : public avideo::context
{
public:
    static avideo::context_ref open(avideo_context_open_info* openInfo);

    bool initialize(avideo_context_open_info* openInfo);
	
    virtual avideo::container_ptr openContainerWithURL(avideo_cstring url) override;
};

} // End of namespace AvideoAVCodec

#endif //AVIDEO_CONTEXT_HPP
