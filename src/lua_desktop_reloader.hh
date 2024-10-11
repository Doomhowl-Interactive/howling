#pragma once
#include "logging.hh"
#include "lua_machine.hh"

#include <chrono>
#include <filesystem>
#include <unordered_map>

namespace HOWLING_NAMESPACE
{

class LuaDesktopReloader : public LuaReloader
{
public:
    void registerScript(const std::string& scriptPath) override
    {
        spdlog::debug("Registered lua script {} for hot-reloading", scriptPath);
        std::filesystem::path path = scriptPath;
        if (std::filesystem::is_regular_file(path))
        {
            mWriteTimes[path] = std::filesystem::last_write_time(path);
        }
    }

    void update(LuaMachine& machine) override
    {
        for (auto& [p, savedWrite] : mWriteTimes)
        {
            const auto lastWrite = std::filesystem::last_write_time(p);
            if (lastWrite > savedWrite)
            {
                machine.runScript(p.string(), false);
                savedWrite = lastWrite;
                spdlog::info("Hot reloaded lua script: {}", p);
                notifyCallbacks(p);
            }
        }
    }

private:
    std::unordered_map<std::filesystem::path, std::filesystem::file_time_type> mWriteTimes;
};

}
