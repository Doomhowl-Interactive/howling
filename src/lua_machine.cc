#include "lua_machine.hh"
#include "logging.hh"

#include <cassert>

namespace howling
{

LuaMachine::LuaMachine(const std::initializer_list<LuaPlugin*>& plugins)
{
    state.open_libraries(sol::lib::base, sol::lib::math, sol::lib::table);

    // register core plugin
    registerLuaPlugin(*this);

    for (LuaPlugin* plugin: plugins) {
        assert(plugin);
        plugin->registerLuaPlugin(*this);
    }

    mReload = LuaReloader::getInstance();
}

LuaMachine::LuaMachine()
    : LuaMachine({})
{
}

bool LuaMachine::runScript(const std::string& scriptPath, bool hotReload)
{
    try
    {
        state.safe_script_file(scriptPath);
        spdlog::info("Loaded lua script {}", scriptPath);

        if (hotReload) {
            if (auto reload = LuaReloader::getInstance().lock()) {
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

void LuaMachine::registerLuaPlugin(LuaMachine& machine)
{
    // callable functions from lua
    machine.registerLuaFunction("info", [](std::string msg) {
        spdlog::info("lua: {}", msg);
    });
    machine.registerLuaFunction("debug", [](std::string msg) {
        spdlog::debug("lua: {}", msg);
    });

    machine.registerLuaFunction("include", [this](std::string file) {
        runScript(fmt::format(ASSETS_DIR "scripts/{}", file));
    });
}

}
