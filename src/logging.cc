#include "logging.hh"
#include "raylib.h"
// #include "spdlog/sinks/android_sink.h"

namespace HOWLING_NAMESPACE
{

static int logTypeLevel = 0;

static void passToSpdlog(int logType, const char* text, va_list args)
{
    if (logType < logTypeLevel)
    {
        return;
    }

    char buffer[512];
    vsnprintf(buffer, sizeof(buffer), text, args);

    switch (logType)
    {
    case LOG_INFO:
        spdlog::info(buffer);
        break;
    case LOG_WARNING:
        spdlog::warn(buffer);
        break;
    case LOG_ERROR:
        spdlog::error(buffer);
        break;
    case LOG_DEBUG:
        spdlog::debug(buffer);
        break;
    default:
        spdlog::info(buffer);
        break;
    }

    if (logType == LOG_FATAL)
    {
        throw howl::formatted_error("Logged FATAL :: {}", buffer);
    }
}

void setupLogging(const std::string& gameName)
{
#ifdef NDEBUG
    logTypeLevel = LOG_INFO;
    spdlog::set_level(spdlog::level::info);
#else
    logTypeLevel = LOG_TRACE;
    spdlog::set_level(spdlog::level::debug);
#endif

    /*
    auto androidLogger = spdlog::android_logger_mt("vortex");
    androidLogger->set_pattern("[vortex:%^%l%$:%oms] %v");
    spdlog::set_default_logger(androidLogger);
    */

    spdlog::set_pattern(fmt::format("[{}:%^%l%$:%oms] %v", gameName));

    SetTraceLogCallback(passToSpdlog);
}

}
