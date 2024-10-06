#pragma once
#include "lua_machine.hh"

namespace HOWLING_NAMESPACE
{

class GuiPrimitives : public LuaPlugin
{
    using LuaRectangle = sol::table;

public:
    void registerLuaPlugin(LuaMachine& machine) override;
};

}
