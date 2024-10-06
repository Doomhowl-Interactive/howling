#include "lua_config.hh"

namespace howling
{

LuaConfig::LuaConfig()
{
    sInstance = this;
    runScript(ASSETS_DIR "scripts/config.lua");
}

LuaConfig::~LuaConfig()
{
    sInstance = nullptr;
}

}
