#include "lua_raylib_plugin.hh"
#include "raylib-lua-sol.hpp"

namespace HOWLING_NAMESPACE
{

void LuaRaylibPlugin::registerLuaPlugin(LuaMachine& machine)
{
    raylib_lua_sol(machine.state);
}

}
