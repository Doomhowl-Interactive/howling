#pragma once
#include <array>
#include <cstddef>
#include <type_traits>

namespace howl
{
/**
 * @brief A `std::array`-based container for storing objects of any type,
 * as long as their size is smaller than the specified capacity (`C`).
 *
 * Attempting to store an object that exceeds the capacity will result
 * in a compile-time error, ensuring type safety.
 *
 * This class is similar to `howl::unsafe_variant`, but differs in that the
 * stored types are not predetermined. Instead, the user manually specifies the
 * capacity, making it a flexible solution for handling various types from
 * different headers, without the complications of cyclic dependencies.
 *
 * It is particularly useful when storing multiple types that may inherit from
 * a common base class.
 */
template<std::size_t C>
class bucket
{
public:
    template<typename T>
    bucket(T&& value) {
        set(value);
    }

    template<typename T>
    T& set(T&& value) {
        static_assert(sizeof(T) <= C);
        new (&mBuffer) std::decay_t<T>(std::forward<T>(value));
        return get<T>();
    }

    template <typename T>
    [[nodiscard]] T& get()
    {
        return *reinterpret_cast<T*>(mBuffer.data());
    }

    template <typename T>
    [[nodiscard]] T& get() const
    {
        return *reinterpret_cast<T*>(mBuffer.data());
    }
private:
    std::array<char, C> mBuffer;
};
}