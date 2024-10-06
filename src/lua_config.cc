#include "lua_config.hh"

namespace HOWLING_NAMESPACE
{

LuaConfig::LuaConfig(const std::string& scriptPath)
{
    sInstance = this;
    runScript(scriptPath);
}

LuaConfig::~LuaConfig()
{
    sInstance = nullptr;
}

}
