#pragma once
#include <vector>
#include <algorithm>
#include <cstddef>
#include <functional>

namespace howl
{

/// A wrapper for std::vector that automatically runs std::sort after any modification
/// made via the mutate method. This class is designed as an alternative to std::set,
/// which does not allow modification of its elements (because the keys in std::set are immutable).
///
/// Use this wrapper when frequent element modifications are needed, which would make std::set
/// unsuitable due to its immutability requirements. Additionally, iterating over elements
/// in this wrapper may be faster than iterating over a std::set, since std::set maintains
/// a strict order on insertion.
///
/// When modifying elements, always use the mutate method to ensure the container remains sorted.
template <typename T>
class ordered_vector
{
public:
    constexpr ordered_vector(std::size_t size, T defaultValue = {})
        : mVec(size, defaultValue) {
    }

    constexpr ordered_vector() = default;

    void mutate(const std::function<void(std::vector<T>&)>& mutateFunc) {
        mutateFunc(mVec);
        sortInplace();
    }

    /// use this when not editing keys
    std::vector<T>& bypass() {
        return mVec;
    }

    /// read only access to vector
    const std::vector<T>& operator*() const {
        return mVec;
    }

    /// read only access to vector
    const std::vector<T>* operator->() const {
        return &mVec;
    }

private:
    void sortInplace() {
        std::sort(mVec.begin(), mVec.end());
    }

    std::vector<T> mVec;
};

}
