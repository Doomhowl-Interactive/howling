#pragma once
#include <functional>

namespace HOWLING_NAMESPACE
{

template<typename T>
inline std::size_t makeHash(const T& value)
{
    return std::hash<T> {}(value);
}

template<typename T, typename... Rest>
inline std::size_t makeHash(const T& value, const Rest&... rest)
{
    std::size_t hash1 = std::hash<T> {}(value);
    std::size_t hash_rest = makeHash(rest...);
    return hash1 ^ (hash_rest << 1);
}

}