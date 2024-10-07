#pragma once
#include "lua_machine.hh"

#include <string>
#include <cassert>

namespace HOWLING_NAMESPACE
{

class LuaConfig : public LuaMachine
{
public:
    LuaConfig(const std::string& scriptPath);
    ~LuaConfig();

    template<typename T>
    [[nodiscard]] static T getValue(const std::string& name, T defaultValue = {}) {
        return ins().state["config"][name].get_or<T>(defaultValue);
    }

    [[nodiscard]] static bool getBool(const std::string& name) {
        return ins().getValue<bool>(name, false);
    }

private:
    static inline LuaConfig* sInstance {};

    static LuaConfig& ins() {
        assert(sInstance);
        return *sInstance;
    }
};

}
