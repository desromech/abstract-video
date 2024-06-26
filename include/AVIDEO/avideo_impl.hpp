
#ifndef AVIDEO_HPP_
#define AVIDEO_HPP_

#include "avideo.h"
#include <stdexcept>
#include <memory>
#include <atomic>

namespace avideo
{

extern avideo_icd_dispatch cppRefcountedDispatchTable;

/**
 * Phanapi reference counter
 */
template <typename T>
class ref_counter
{
public:
    ref_counter(T *cobject)
        : dispatchTable(&cppRefcountedDispatchTable), object(cobject), strongCount(1), weakCount(1)
    {
        object->setRefCounterPointer(this);
    }

    avideo_error retain()
    {
        // First sanity check.
        if(strongCount.load(std::memory_order_acquire) == 0)
            return AVIDEO_INVALID_OPERATION;

        // Increase the reference count.
        strongCount.fetch_add(1, std::memory_order_acq_rel);
        return AVIDEO_OK;
    }

    avideo_error release()
    {
        // First sanity check.
        if(strongCount.load(std::memory_order_acquire) == 0)
            return AVIDEO_INVALID_OPERATION;

        // Decrease the strong count.
        auto old = strongCount.fetch_sub(1, std::memory_order_acq_rel);
        if(old == 1)
        {
            delete object;
            weakRelease();
        }

        return AVIDEO_OK;
    }

    bool weakLock()
    {
        unsigned int oldCount;
        while((oldCount = strongCount.load(std::memory_order_acquire)) != 0)
        {
            if(strongCount.compare_exchange_weak(oldCount, oldCount + 1, std::memory_order_acq_rel))
                return true;
        }

        return false;
    }

    void weakRetain()
    {
        weakCount.fetch_add(1, std::memory_order_acq_rel);
    }

    void weakRelease()
    {
        auto old = weakCount.fetch_sub(1, std::memory_order_acq_rel);
        if(old == 1)
        {
            // Nobody else is referencing me.
            delete this;
        }
    }

    avideo_icd_dispatch *dispatchTable;
    T * object;
    std::atomic_uint strongCount;
    std::atomic_uint weakCount;
};

template<typename T>
class weak_ref;

/**
 * Phanapi strong reference
 */
template<typename T>
class ref
{
public:
    typedef ref_counter<T> Counter;
    typedef ref<T> StrongRef;
    typedef weak_ref<T> WeakRef;

private:
    Counter *counter;
    friend WeakRef;

public:
    ref() : counter(nullptr) {}

    ref(const StrongRef &other)
        : counter(nullptr)
    {
        *this = other;
    }

    explicit ref(Counter *theCounter)
        : counter(theCounter)
    {
    }

    ~ref()
    {
        reset();
    }

    static StrongRef import(void *rawCounter)
    {
        auto castedCounter = reinterpret_cast<Counter*> (rawCounter);
        if(castedCounter)
            castedCounter->retain();
        return StrongRef(castedCounter);
    }

    StrongRef &operator=(const StrongRef &other)
    {
        auto newCounter = other.counter;
        if(newCounter)
            newCounter->retain();
        if(counter)
            counter->release();
        counter = newCounter;
        return *this;
    }

    void reset(Counter *newCounter = nullptr)
    {
        auto c = counter;
        counter = newCounter;
        if(c)
            c->release();
    }

    Counter *disown()
    {
        Counter *result = counter;
        counter = nullptr;
        return result;
    }

    Counter *disownedNewRef() const
    {
        if(counter)
            counter->retain();
        return counter;
    }

    Counter *asPtrWithoutNewRef() const
    {
        return counter;
    }

    template<typename U>
    U *as() const
    {
        return static_cast<U*> (counter->object);
    }

    T *get() const
    {
        return counter ? counter->object : nullptr;
    }

    T *operator->() const
    {
        return counter->object;
    }

    explicit operator bool() const
    {
        return counter != nullptr;
    }

    bool operator==(const StrongRef &other) const
    {
        return counter == other.counter;
    }

    bool operator!=(const StrongRef &other) const
    {
        return counter != other.counter;
    }

    bool operator<(const StrongRef &other) const
    {
        return counter < other.counter;
    }

    size_t hash() const
    {
        return std::hash<Counter*> () (counter);
    }
};

/**
 * Phanapi weak reference
 */
template<typename T>
class weak_ref
{
public:
    typedef ref_counter<T> Counter;
    typedef ref<T> StrongRef;
    typedef weak_ref<T> WeakRef;

private:
    Counter *counter;

public:
    weak_ref()
        : counter(nullptr) {}

    explicit weak_ref(const StrongRef &ref)
    {
        counter = ref.counter;
        if(counter)
            counter->weakRetain();
    }

    weak_ref(const WeakRef &ref)
    {
        counter = ref.counter;
        if(counter)
            counter->weakRetain();
    }

    ~weak_ref()
    {
        reset();
    }

    WeakRef &operator=(const StrongRef &other)
    {
        auto newCounter = other.counter;
        if(newCounter)
            newCounter->weakRetain();
        if(counter)
            counter->weakRelease();
        counter = newCounter;
        return *this;
    }

    WeakRef &operator=(const WeakRef &other)
    {
        auto newCounter = other.counter;
        if(newCounter)
            newCounter->weakRetain();
        if(counter)
            counter->weakRelease();
        counter = newCounter;
        return *this;
    }

    void reset()
    {
        auto c = counter;
        counter = nullptr;
        if(c)
            c->weakRelease();
    }

    StrongRef lock()
    {
        if(!counter)
            return StrongRef();

        return counter->weakLock() ? StrongRef(counter) : StrongRef();
    }

    bool operator==(const WeakRef &other) const
    {
        return counter == other.counter;
    }

    bool operator!=(const WeakRef &other) const
    {
        return counter != other.counter;
    }

    bool operator<(const WeakRef &other) const
    {
        return counter < other.counter;
    }

    size_t hash() const
    {
        return std::hash<Counter*> () (counter);
    }
};

template<typename I, typename T, typename...Args>
inline ref<I> makeObjectWithInterface(Args... args)
{
    std::unique_ptr<T> object(new T(args...));
    std::unique_ptr<ref_counter<I>> counter(new ref_counter<I> (object.release()));
    return ref<I> (counter.release());
}

template<typename T, typename...Args>
inline ref<typename T::main_interface> makeObject(Args... args)
{
   return makeObjectWithInterface<typename T::main_interface, T> (args...);
}

/**
 * Phanapi base interface
 */
class base_interface
{
public:
    virtual ~base_interface() {}

    void setRefCounterPointer(void *newPointer)
    {
        myRefCounter = newPointer;
    }

    template<typename T=base_interface>
    const ref<T> &refFromThis()
    {
        return reinterpret_cast<const ref<T> &> (myRefCounter);
    }

private:
    void *myRefCounter;
};

} // End of namespace avideo

namespace std
{
template<typename T>
struct hash<avideo::ref<T>>
{
    size_t operator()(const avideo::ref<T> &ref) const
    {
        return ref.hash();
    }
};

template<typename T>
struct hash<avideo::weak_ref<T>>
{
    size_t operator()(const avideo::ref<T> &ref) const
    {
        return ref.hash();
    }
};

}

namespace avideo
{
struct platform;
typedef ref_counter<platform> *platform_ptr;
typedef ref<platform> platform_ref;
typedef weak_ref<platform> platform_weakref;

struct context;
typedef ref_counter<context> *context_ptr;
typedef ref<context> context_ref;
typedef weak_ref<context> context_weakref;

struct stream;
typedef ref_counter<stream> *stream_ptr;
typedef ref<stream> stream_ref;
typedef weak_ref<stream> stream_weakref;

// Interface wrapper for avideo_platform.
struct platform : base_interface
{
public:
	typedef platform main_interface;
	virtual context_ptr openContext(avideo_context_open_info* openInfo) = 0;
	virtual avideo_cstring getName() = 0;
};


// Interface wrapper for avideo_context.
struct context : base_interface
{
public:
	typedef context main_interface;
	virtual stream_ptr openStreamWithURL(avideo_cstring url) = 0;
};


// Interface wrapper for avideo_stream.
struct stream : base_interface
{
public:
	typedef stream main_interface;
};


} // End of avideo

#endif /* AVIDEO_HPP_ */
