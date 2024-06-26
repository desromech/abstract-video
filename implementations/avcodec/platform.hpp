#ifndef AVIDEO_PLATFORM_HPP
#define AVIDEO_PLATFORM_HPP

#include "common.hpp"

namespace AvideoAVCodec
{

class AVCodecPlatform : public avideo::platform
{
public:
	virtual avideo::context_ptr openContext(avideo_context_open_info* openInfo) override;
	virtual avideo_cstring getName() override;
};

} // End of namespace AvideoAVCodec
#endif //AVIDEO_PLATFORM_HPP