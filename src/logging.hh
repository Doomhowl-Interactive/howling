#pragma once
#include <filesystem>
#include <spdlog/spdlog.h>
#include <stdexcept>

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

void setupLogging(const std::string& gameName);

}