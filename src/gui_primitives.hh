#pragma once
#include "lua_machine.hh"

namespace howling
{

class GuiPrimitives : public LuaPlugin
{
    using LuaRectangle = sol::table;
public:
    void registerLuaPlugin(LuaMachine& machine) override;
};

}
