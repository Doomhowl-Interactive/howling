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
    virtual ~ring_buffer() = default;

    T& obtain() {
        T& it = &mBuffer[mCurrent];
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

private:
    std::size_t mCurrent;
    std::array<T, S> mBuffer;
};

}
