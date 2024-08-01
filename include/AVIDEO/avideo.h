
#ifndef _AVIDEO_H_
#define _AVIDEO_H_

#include <stdlib.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifdef _WIN32
#   ifdef AVIDEO_BUILD
#       define AVIDEO_EXPORT __declspec(dllexport)
#   else
#       define AVIDEO_EXPORT __declspec(dllimport)
#   endif
#else
#   if __GNUC__ >= 4
#       define AVIDEO_EXPORT __attribute__ ((visibility ("default")))
#   endif
#endif

typedef unsigned char avideo_byte;
typedef signed char avideo_sbyte;
typedef signed short avideo_short;
typedef unsigned short avideo_ushort;
typedef signed int avideo_int;
typedef unsigned int avideo_uint;
typedef void* avideo_pointer;
typedef unsigned int avideo_size;
typedef int avideo_enum;
typedef int avideo_bool;
typedef float avideo_float;
typedef double avideo_double;
typedef unsigned int avideo_bitfield;
typedef const char* avideo_cstring;
typedef const char* avideo_string;
typedef int avideo_string_length;
typedef char* avideo_cstring_buffer;
typedef char* avideo_string_buffer;

typedef struct _avideo_platform avideo_platform;
typedef struct _avideo_context avideo_context;
typedef struct _avideo_container avideo_container;

typedef enum {
	AVIDEO_OK = 0,
	AVIDEO_ERROR = -1,
	AVIDEO_NULL_POINTER = -2,
	AVIDEO_INVALID_OPERATION = -3,
	AVIDEO_INVALID_PARAMETER = -4,
	AVIDEO_OUT_OF_BOUNDS = -5,
	AVIDEO_UNSUPPORTED = -6,
	AVIDEO_UNIMPLEMENTED = -7,
	AVIDEO_NOT_CURRENT_CONTEXT = -8,
	AVIDEO_OUT_OF_MEMORY = -9,
	AVIDEO_AGAIN = -10,
	AVIDEO_END_OF_STREAM = -11,
} avideo_error;


/* Structure avideo_context_open_info. */
typedef struct avideo_context_open_info {
} avideo_context_open_info;

/* Global functions. */
typedef avideo_error (*avideoGetPlatforms_FUN) (avideo_size numplatforms, avideo_platform** platforms, avideo_size* ret_numplatforms);

AVIDEO_EXPORT avideo_error avideoGetPlatforms(avideo_size numplatforms, avideo_platform** platforms, avideo_size* ret_numplatforms);

/* Methods for interface avideo_platform. */
typedef avideo_context* (*avideoOpenDevice_FUN) (avideo_platform* platform, avideo_context_open_info* openInfo);
typedef avideo_cstring (*avideoGetPlatformName_FUN) (avideo_platform* platform);

AVIDEO_EXPORT avideo_context* avideoOpenDevice(avideo_platform* platform, avideo_context_open_info* openInfo);
AVIDEO_EXPORT avideo_cstring avideoGetPlatformName(avideo_platform* platform);

/* Methods for interface avideo_context. */
typedef avideo_error (*avideoAddContextReference_FUN) (avideo_context* context);
typedef avideo_error (*avideoReleaseContext_FUN) (avideo_context* context);
typedef avideo_container* (*avideoOpenContainerWithURL_FUN) (avideo_context* context, avideo_cstring url);

AVIDEO_EXPORT avideo_error avideoAddContextReference(avideo_context* context);
AVIDEO_EXPORT avideo_error avideoReleaseContext(avideo_context* context);
AVIDEO_EXPORT avideo_container* avideoOpenContainerWithURL(avideo_context* context, avideo_cstring url);

/* Methods for interface avideo_container. */
typedef avideo_error (*avideoAddContainerReference_FUN) (avideo_container* container);
typedef avideo_error (*avideoReleaseContainer_FUN) (avideo_container* container);
typedef avideo_double (*avideoContainerGetStartTime_FUN) (avideo_container* container);
typedef avideo_double (*avideoContainerGetDuration_FUN) (avideo_container* container);
typedef avideo_error (*avideoContainerSeekTime_FUN) (avideo_container* container, avideo_double time);
typedef avideo_error (*avideoContainerSeekFrameIndex_FUN) (avideo_container* container, avideo_size frame_index);
typedef avideo_bool (*avideoContainerHasVideoStream_FUN) (avideo_container* container);
typedef avideo_size (*avideoContainerGetVideoStreamWidth_FUN) (avideo_container* container);
typedef avideo_size (*avideoContainerGetVideoStreamHeight_FUN) (avideo_container* container);
typedef avideo_size (*avideoContainerGetVideoStreamFrameCount_FUN) (avideo_container* container);
typedef avideo_float (*avideoContainerGetVideoStreamFrameRate_FUN) (avideo_container* container);
typedef avideo_error (*avideoContainerFetchAndDecodeNextPacket_FUN) (avideo_container* container);
typedef avideo_error (*avideoContainerFetchAndDecodeNextVideoFrame_FUN) (avideo_container* container);
typedef avideo_size (*avideoContainerGetVideoFrameIndex_FUN) (avideo_container* container);
typedef avideo_size (*avideoContainerGetVideoFrameWidth_FUN) (avideo_container* container);
typedef avideo_size (*avideoContainerGetVideoFrameHeight_FUN) (avideo_container* container);
typedef avideo_error (*avideoContainerReadSRGB32ConvertedFrame_FUN) (avideo_container* container, avideo_int pitch, avideo_pointer buffer);
typedef avideo_bool (*avideoContainerHasAudioStream_FUN) (avideo_container* container);
typedef avideo_size (*avideoContainerGetAudioStreamChannels_FUN) (avideo_container* container);
typedef avideo_size (*avideoContainerGetAudioStreamSampleRate_FUN) (avideo_container* container);

AVIDEO_EXPORT avideo_error avideoAddContainerReference(avideo_container* container);
AVIDEO_EXPORT avideo_error avideoReleaseContainer(avideo_container* container);
AVIDEO_EXPORT avideo_double avideoContainerGetStartTime(avideo_container* container);
AVIDEO_EXPORT avideo_double avideoContainerGetDuration(avideo_container* container);
AVIDEO_EXPORT avideo_error avideoContainerSeekTime(avideo_container* container, avideo_double time);
AVIDEO_EXPORT avideo_error avideoContainerSeekFrameIndex(avideo_container* container, avideo_size frame_index);
AVIDEO_EXPORT avideo_bool avideoContainerHasVideoStream(avideo_container* container);
AVIDEO_EXPORT avideo_size avideoContainerGetVideoStreamWidth(avideo_container* container);
AVIDEO_EXPORT avideo_size avideoContainerGetVideoStreamHeight(avideo_container* container);
AVIDEO_EXPORT avideo_size avideoContainerGetVideoStreamFrameCount(avideo_container* container);
AVIDEO_EXPORT avideo_float avideoContainerGetVideoStreamFrameRate(avideo_container* container);
AVIDEO_EXPORT avideo_error avideoContainerFetchAndDecodeNextPacket(avideo_container* container);
AVIDEO_EXPORT avideo_error avideoContainerFetchAndDecodeNextVideoFrame(avideo_container* container);
AVIDEO_EXPORT avideo_size avideoContainerGetVideoFrameIndex(avideo_container* container);
AVIDEO_EXPORT avideo_size avideoContainerGetVideoFrameWidth(avideo_container* container);
AVIDEO_EXPORT avideo_size avideoContainerGetVideoFrameHeight(avideo_container* container);
AVIDEO_EXPORT avideo_error avideoContainerReadSRGB32ConvertedFrame(avideo_container* container, avideo_int pitch, avideo_pointer buffer);
AVIDEO_EXPORT avideo_bool avideoContainerHasAudioStream(avideo_container* container);
AVIDEO_EXPORT avideo_size avideoContainerGetAudioStreamChannels(avideo_container* container);
AVIDEO_EXPORT avideo_size avideoContainerGetAudioStreamSampleRate(avideo_container* container);

/* Installable client driver interface. */
typedef struct _avideo_icd_dispatch {
	int icd_interface_version;
	avideoGetPlatforms_FUN avideoGetPlatforms;
	avideoOpenDevice_FUN avideoOpenDevice;
	avideoGetPlatformName_FUN avideoGetPlatformName;
	avideoAddContextReference_FUN avideoAddContextReference;
	avideoReleaseContext_FUN avideoReleaseContext;
	avideoOpenContainerWithURL_FUN avideoOpenContainerWithURL;
	avideoAddContainerReference_FUN avideoAddContainerReference;
	avideoReleaseContainer_FUN avideoReleaseContainer;
	avideoContainerGetStartTime_FUN avideoContainerGetStartTime;
	avideoContainerGetDuration_FUN avideoContainerGetDuration;
	avideoContainerSeekTime_FUN avideoContainerSeekTime;
	avideoContainerSeekFrameIndex_FUN avideoContainerSeekFrameIndex;
	avideoContainerHasVideoStream_FUN avideoContainerHasVideoStream;
	avideoContainerGetVideoStreamWidth_FUN avideoContainerGetVideoStreamWidth;
	avideoContainerGetVideoStreamHeight_FUN avideoContainerGetVideoStreamHeight;
	avideoContainerGetVideoStreamFrameCount_FUN avideoContainerGetVideoStreamFrameCount;
	avideoContainerGetVideoStreamFrameRate_FUN avideoContainerGetVideoStreamFrameRate;
	avideoContainerFetchAndDecodeNextPacket_FUN avideoContainerFetchAndDecodeNextPacket;
	avideoContainerFetchAndDecodeNextVideoFrame_FUN avideoContainerFetchAndDecodeNextVideoFrame;
	avideoContainerGetVideoFrameIndex_FUN avideoContainerGetVideoFrameIndex;
	avideoContainerGetVideoFrameWidth_FUN avideoContainerGetVideoFrameWidth;
	avideoContainerGetVideoFrameHeight_FUN avideoContainerGetVideoFrameHeight;
	avideoContainerReadSRGB32ConvertedFrame_FUN avideoContainerReadSRGB32ConvertedFrame;
	avideoContainerHasAudioStream_FUN avideoContainerHasAudioStream;
	avideoContainerGetAudioStreamChannels_FUN avideoContainerGetAudioStreamChannels;
	avideoContainerGetAudioStreamSampleRate_FUN avideoContainerGetAudioStreamSampleRate;
} avideo_icd_dispatch;


#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* _AVIDEO_H_ */
