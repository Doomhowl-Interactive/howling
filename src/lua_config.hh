#pragma once
#include "lua_machine.hh"
#include <string>

namespace howling
{

class LuaConfig : public LuaMachine
{
public:
    LuaConfig();
    ~LuaConfig();

    template<typename T>
    T getConfigValue(const std::string& name, T defaultValue)
    {
        return state["config"][name].get_or<T>(defaultValue);
    }

    bool getConfigBool(const std::string& name)
    {
        return getConfigValue<bool>(name, false);
    }

private:
    static inline LuaConfig* sInstance {};
};

}
