#include "lua_machine.hh"
#include "logging.hh"

#include <sstream>
#include <cassert>

namespace HOWLING_NAMESPACE
{

LuaMachine::LuaMachine(const std::initializer_list<LuaPlugin*>& plugins)
    : mReload(LuaReloader::getInstance())
    , mLuaIncludeDirs(sDefaultLuaIncludeDirs)
{
    state.open_libraries(sol::lib::base, sol::lib::math, sol::lib::table);

    // register core plugin
    registerLuaPlugin(*this);

    for (LuaPlugin* plugin : plugins)
    {
        assert(plugin);
        plugin->registerLuaPlugin(*this);
    }
}

LuaMachine::LuaMachine()
    : LuaMachine({})
{
}

void LuaMachine::addLuaIncludeDirs(const std::initializer_list<std::string>& dirs)
{
    mLuaIncludeDirs.insert(mLuaIncludeDirs.end(), dirs.begin(), dirs.end());
}

void LuaMachine::setDefaultLuaIncludeDirs(const std::initializer_list<std::string>& dirs)
{
    sDefaultLuaIncludeDirs.insert(sDefaultLuaIncludeDirs.end(), dirs.begin(), dirs.end());
}

bool LuaMachine::runScript(const std::string& scriptPath, bool hotReload)
{
    try
    {
        state.safe_script_file(scriptPath);
        spdlog::info("Loaded lua script {}", scriptPath);

        if (hotReload)
        {
            if (auto reload = LuaReloader::getInstance().lock())
            {
                reload->registerScript(scriptPath);
            }
        }
        return true;
    }
    catch (const sol::error& err)
    {
        spdlog::error("Lua syntax error: {}", err.what());
        assert(0);
        return false;
    }
}

std::optional<std::string> LuaMachine::resolveLuaFile(const std::string& scriptPath) const
{
    namespace fs = std::filesystem;

    std::optional<std::string> result = {};

    if (mLuaIncludeDirs.size() == 1)
    {
        // fastest, no disk checks needed
        result = fmt::format("{}/{}", mLuaIncludeDirs[0], scriptPath);
    }
    else
    {
        // slower, disk checks needed
        for (const std::string& dir : mLuaIncludeDirs) {
            auto path = fs::path(dir) / scriptPath;
            if (fs::is_regular_file(path)) {
                // script found
                result = path.string();
                goto end;
            }
        }

        const auto pathsStr = stringifyVector(mLuaIncludeDirs);
        spdlog::error("Did not find lua script '{}' in include paths: {}",
                      scriptPath, pathsStr);
    }
end:
    return result;
}

void LuaMachine::registerLuaPlugin(LuaMachine& machine)
{
    // callable functions from lua
    machine.registerLuaFunction("info", [](std::string msg)
                                { spdlog::info("lua: {}", msg); });
    machine.registerLuaFunction("debug", [](std::string msg)
                                { spdlog::debug("lua: {}", msg); });

    machine.registerLuaFunction("include", [this](std::string file) {
        if (auto resolved = resolveLuaFile(file); resolved) {
            runScript(*resolved);
        }
    });
}

}
