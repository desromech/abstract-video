
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
typedef struct _avideo_stream avideo_stream;

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
typedef avideo_stream* (*avideoOpenStreamWithURL_FUN) (avideo_context* context, avideo_cstring url);

AVIDEO_EXPORT avideo_error avideoAddContextReference(avideo_context* context);
AVIDEO_EXPORT avideo_error avideoReleaseContext(avideo_context* context);
AVIDEO_EXPORT avideo_stream* avideoOpenStreamWithURL(avideo_context* context, avideo_cstring url);

/* Methods for interface avideo_stream. */
typedef avideo_error (*avideoAddStreamReference_FUN) (avideo_stream* stream);
typedef avideo_error (*avideoReleaseStream_FUN) (avideo_stream* stream);

AVIDEO_EXPORT avideo_error avideoAddStreamReference(avideo_stream* stream);
AVIDEO_EXPORT avideo_error avideoReleaseStream(avideo_stream* stream);

/* Installable client driver interface. */
typedef struct _avideo_icd_dispatch {
	int icd_interface_version;
	avideoGetPlatforms_FUN avideoGetPlatforms;
	avideoOpenDevice_FUN avideoOpenDevice;
	avideoGetPlatformName_FUN avideoGetPlatformName;
	avideoAddContextReference_FUN avideoAddContextReference;
	avideoReleaseContext_FUN avideoReleaseContext;
	avideoOpenStreamWithURL_FUN avideoOpenStreamWithURL;
	avideoAddStreamReference_FUN avideoAddStreamReference;
	avideoReleaseStream_FUN avideoReleaseStream;
} avideo_icd_dispatch;


#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* _AVIDEO_H_ */
