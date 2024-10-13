#pragma once
#include <algorithm>
#include <cstddef>
#include <functional>
#include <vector>

#include "observed_vector.hh"

namespace howl
{
/**
 * A wrapper for std::vector that automatically runs std::sort after any modification
 * made via the mutate method. This class is designed as an alternative to std::set,
 * which does not allow modification of its elements (because the keys in std::set are immutable).
 *
 * Use this wrapper when frequent element modifications are needed, which would make std::set
 * unsuitable due to its immutability requirements. Additionally, iterating over elements
 * in this wrapper may be faster than iterating over a std::set, since std::set maintains
 * a strict order on insertion.
 *
 * When modifying elements, always use the mutate method to ensure the container remains sorted.
 */
template<typename T>
class ordered_vector
{
public:
    constexpr ordered_vector(std::size_t size, T defaultValue = {})
        : mVec(size, defaultValue)
    {
    }

    constexpr ordered_vector() = default;

    template<typename Func>
    constexpr void mutate(Func mutateFunc)
    {
        mutateFunc(mVec);
        sortInplace();
    }

    /// use this when not editing keys
    constexpr std::vector<T>& bypass()
    {
        return mVec;
    }

    constexpr void sortInplace()
    {
        std::sort(mVec.begin(), mVec.end());
    }

    /// read only access to vector
    constexpr const std::vector<T>& operator*() const
    {
        return mVec;
    }

    /// read only access to vector
    constexpr const std::vector<T>* operator->() const
    {
        return &mVec;
    }

private:
    std::vector<T> mVec;
};

}
