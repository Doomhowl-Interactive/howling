#pragma once
#include "lua_machine.hh"

namespace HOWLING_NAMESPACE
{
class LuaRaylibPlugin : public LuaPlugin
{
public:
    void registerLuaPlugin(LuaMachine& machine) override;
};
}
