#include <array>
#include <cstddef>

namespace howl
{

/// Ring buffer on the stack, based on std::array. Aims to not rely
/// on the heap and be a faster alternative than an std::vector
/// containing raw pointers or unique_ptrs. It is meant for short lived
/// objects as old ones get reused.
template <typename T, std::size_t S>
class ring_buffer
{
public:
    ring_buffer() = default;
    virtual ~ring_buffer() = default;

    T& obtain() {
        T& it = mBuffer[mCurrent];
        assertObtainValid(it);
        mCurrent = (mCurrent + 1) % S;
        return it;
    }

    /// Virtual method that can be overriden to check
    /// if obtain didn't retake active item.
    ///
    /// Example body: assert(!it->alive);
    virtual void assertObtainValid(T& it) const {
    }

    // Access to the array

    using iterator = typename std::array<T, S>::iterator;
    using const_iterator = typename std::array<T, S>::const_iterator;

    iterator begin() {
        return mBuffer.begin();
    }

    const_iterator begin() const {
        return mBuffer.begin();
    }

    iterator end() {
        return mBuffer.end();
    }

    const_iterator end() const {
        return mBuffer.end();
    }

    const T& operator[](std::size_t index) const {
        return mBuffer[index];
    }

    T& operator[](std::size_t index) {
        return mBuffer[index];
    }

private:
    std::size_t mCurrent;
    std::array<T, S> mBuffer;
};

}
