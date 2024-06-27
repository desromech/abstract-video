
#ifndef AVIDEO_HPP_
#define AVIDEO_HPP_

#include <stdexcept>
#include "avideo.h"

/**
 * Abstract Video exception.
 */
class avideo_exception : public std::runtime_error
{
public:
    explicit avideo_exception(avideo_error error)
        : std::runtime_error("Abstract Video Error"), errorCode(error)
    {
    }

    avideo_error getErrorCode() const
    {
        return errorCode;
    }

private:
    avideo_error errorCode;
};

/**
 * Abstract GPU reference smart pointer.
 */
template<typename T>
class avideo_ref
{
public:
    avideo_ref()
        : pointer(0)
    {
    }

    avideo_ref(const avideo_ref<T> &other)
    {
        if(other.pointer)
            other.pointer->addReference();
        pointer = other.pointer;
    }

    avideo_ref(T* pointer)
        : pointer(0)
    {
		reset(pointer);
    }

    ~avideo_ref()
    {
        if (pointer)
            pointer->release();
    }

    avideo_ref<T> &operator=(T *newPointer)
    {
        if (pointer)
            pointer->release();
        pointer = newPointer;
        return *this;
    }

    avideo_ref<T> &operator=(const avideo_ref<T> &other)
    {
        if(pointer != other.pointer)
        {
            if(other.pointer)
                other.pointer->addReference();
            if(pointer)
                pointer->release();
            pointer = other.pointer;
        }
        return *this;
    }

    bool operator==(const avideo_ref<T> &other) const
    {
        return pointer == other.pointer;
    }

    bool operator==(const T *otherPointer) const
    {
        return pointer == otherPointer;
    }

    bool operator!=(const avideo_ref<T> &other) const
    {
        return pointer != other.pointer;
    }

    bool operator!=(const T *otherPointer) const
    {
        return pointer != otherPointer;
    }

    bool operator<(const avideo_ref<T> &other) const
    {
        return pointer < other.pointer;
    }

    bool operator<(const T *otherPointer) const
    {
        return pointer < otherPointer;
    }

    bool operator<=(const avideo_ref<T> &other) const
    {
        return pointer < other.pointer;
    }

    bool operator<=(const T *otherPointer) const
    {
        return pointer <= otherPointer;
    }

    bool operator>(const avideo_ref<T> &other) const
    {
        return pointer > other.pointer;
    }

    bool operator>(const T *otherPointer) const
    {
        return pointer > otherPointer;
    }

    bool operator>=(const avideo_ref<T> &other) const
    {
        return pointer > other.pointer;
    }

    bool operator>=(const T *otherPointer) const
    {
        return pointer >= otherPointer;
    }
    
	void reset(T *newPointer = nullptr)
	{
		if(pointer)
			pointer->release();
		pointer = newPointer;
	}

    operator bool() const
    {
        return pointer;
    }

    bool operator!() const
    {
        return !pointer;
    }

    T* get() const
    {
        return pointer;
    }

    T *operator->() const
    {
        return pointer;
    }

private:
    T *pointer;
};

/**
 * Helper function to convert an error code into an exception.
 */
inline void avideoThrowIfFailed(avideo_error error)
{
    if(error < 0)
        throw avideo_exception(error);
}

// Interface wrapper for avideo_platform.
struct _avideo_platform
{
private:
	_avideo_platform() {}

public:
	inline avideo_ref<avideo_context> openContext(avideo_context_open_info* openInfo)
	{
		return avideoOpenDevice(this, openInfo);
	}

	inline avideo_cstring getName()
	{
		return avideoGetPlatformName(this);
	}

};

typedef avideo_ref<avideo_platform> avideo_platform_ref;

// Interface wrapper for avideo_context.
struct _avideo_context
{
private:
	_avideo_context() {}

public:
	inline void addReference()
	{
		avideoThrowIfFailed(avideoAddContextReference(this));
	}

	inline void release()
	{
		avideoThrowIfFailed(avideoReleaseContext(this));
	}

	inline avideo_ref<avideo_container> openContainerWithURL(avideo_cstring url)
	{
		return avideoOpenContainerWithURL(this, url);
	}

};

typedef avideo_ref<avideo_context> avideo_context_ref;

// Interface wrapper for avideo_container.
struct _avideo_container
{
private:
	_avideo_container() {}

public:
	inline void addReference()
	{
		avideoThrowIfFailed(avideoAddContainerReference(this));
	}

	inline void release()
	{
		avideoThrowIfFailed(avideoReleaseContainer(this));
	}

	inline avideo_double getStartTime()
	{
		return avideoContainerGetStartTime(this);
	}

	inline avideo_double getDuration()
	{
		return avideoContainerGetDuration(this);
	}

	inline void seekTime(avideo_double time)
	{
		avideoThrowIfFailed(avideoContainerSeekTime(this, time));
	}

	inline void seekFrame(avideo_size frame_index)
	{
		avideoThrowIfFailed(avideoContainerSeekFrameIndex(this, frame_index));
	}

	inline avideo_bool hasVideoStream()
	{
		return avideoContainerHasVideoStream(this);
	}

	inline avideo_size getVideoStreamWidth()
	{
		return avideoContainerGetVideoStreamWidth(this);
	}

	inline avideo_size getVideoStreamHeight()
	{
		return avideoContainerGetVideoStreamHeight(this);
	}

	inline avideo_size getVideoStreamFrameCount()
	{
		return avideoContainerGetVideoStreamFrameCount(this);
	}

	inline avideo_float getVideoStreamFrameRate()
	{
		return avideoContainerGetVideoStreamFrameRate(this);
	}

	inline void fetchAndDecodeNextFrame()
	{
		avideoThrowIfFailed(avideoContainerFetchAndDecodeNextFrame(this));
	}

	inline avideo_size getVideoFrameIndex()
	{
		return avideoContainerGetVideoFrameIndex(this);
	}

	inline avideo_size getVideoFrameWidth()
	{
		return avideoContainerGetVideoFrameWidth(this);
	}

	inline avideo_size getVideoFrameHeight()
	{
		return avideoContainerGetVideoFrameHeight(this);
	}

	inline avideo_bool hasAudioStream()
	{
		return avideoContainerHasAudioStream(this);
	}

	inline avideo_size getAudioStreamChannels()
	{
		return avideoContainerGetAudioStreamChannels(this);
	}

	inline avideo_size getAudioStreamSampleRate()
	{
		return avideoContainerGetAudioStreamSampleRate(this);
	}

};

typedef avideo_ref<avideo_container> avideo_container_ref;


#endif /* AVIDEO_HPP_ */
