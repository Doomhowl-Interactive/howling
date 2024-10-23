#pragma once
#include <functional>
#include <string_view>

namespace HOWLING_NAMESPACE
{

template<typename... Args>
inline constexpr std::size_t makeHash(const Args&... args)
{
    std::size_t hash = 0;
    (..., (hash = hash * 31 + std::hash<Args> {}(args)));
    return hash;
}

}