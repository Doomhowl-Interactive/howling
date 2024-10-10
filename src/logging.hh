#pragma once
#include <filesystem>
#include <spdlog/spdlog.h>
#include <stdexcept>
#include <vector>
#include <string>
#include <sstream>

#include "raylib.h"

// blursed templates for logging

template<>
struct fmt::formatter<std::filesystem::path>
{
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }
    template<typename FormatContext>
    auto format(const std::filesystem::path& path, FormatContext& ctx) const
    {
        return fmt::format_to(ctx.out(), "{}", path.string());
    }
};

template<>
struct fmt::formatter<std::exception>
{
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }
    template<typename FormatContext>
    auto format(const std::exception& ex, FormatContext& ctx) const
    {
        return fmt::format_to(ctx.out(), "{}", ex.what());
    }
};

template<>
struct fmt::formatter<Color>
{
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }
    template<typename FormatContext>
    auto format(const Color& c, FormatContext& ctx) const
    {
        return fmt::format_to(ctx.out(), "(r={},g={},b={},a={})", c.r, c.g, c.b, c.a);
    }
};

template<>
struct fmt::formatter<Vector2>
{
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }
    template<typename FormatContext>
    auto format(const Vector2& v, FormatContext& ctx) const
    {
        return fmt::format_to(ctx.out(), "({},{})", v.x, v.y);
    }
};

template<>
struct fmt::formatter<Vector3>
{
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }
    template<typename FormatContext>
    auto format(const Vector3& v, FormatContext& ctx) const
    {
        return fmt::format_to(ctx.out(), "({},{},{})", v.x, v.y, v.z);
    }
};

template<>
struct fmt::formatter<Vector4>
{
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }
    template<typename FormatContext>
    auto format(const Vector4& v, FormatContext& ctx) const
    {
        return fmt::format_to(ctx.out(), "({},{},{},{})", v.x, v.y, v.z, v.w);
    }
};

namespace howl
{

class formatted_error : public std::runtime_error
{
public:
    // Constructor with variadic template to handle formatting
    template<typename... Args>
    constexpr formatted_error(std::string_view fmt, Args&&... args)
        : std::runtime_error(fmt::vformat(fmt, fmt::make_format_args(std::forward<Args>(args)...)))
    {
    }
};

}

namespace HOWLING_NAMESPACE
{

template <typename T>
std::string stringifyVector(const std::vector<T>& vec) {
    std::ostringstream oss;
    oss << "[";
    for (std::size_t i = 0; i < vec.size(); ++i) {
        oss << vec[i];
        if (i != vec.size() - 1) {
            oss << ", ";
        }
    }
    oss << "]";
    return oss.str();
}

void setupLogging(const std::string& gameName);

}
