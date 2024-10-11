#pragma once
#include "lua_machine.hh"
#include "raylib.h"

#include <cassert>
#include <string>
#include <unordered_map>
#include <variant>

namespace HOWLING_NAMESPACE
{

class LuaConfig : public LuaMachine
{
    // add stuff when needed, as long as this thing is big enough
    using OptionType = std::variant<bool, int, float, double, Vector3, Vector2, Vector4, sol::table, std::string>; 
public:
    LuaConfig(const std::string& scriptPath);
    ~LuaConfig();

    template<typename T>
    [[nodiscard]] static T getValue(const std::string& name, T defaultValue = {})
    {
        try
        {
            return std::get<T>(ins().mCachedOptions.at(name));
        }
        catch (std::exception&)
        {
            T opt = ins().state["config"][name].get_or<T>(defaultValue);
            ins().mCachedOptions.emplace(name, opt);
            return opt;
        }
    }

    [[nodiscard]] static bool getBool(const std::string& name)
    {
        return getValue<bool>(name, false);
    }

    [[nodiscard]] static Vector3 getVector3(const std::string& name);

private:
    const std::string mScriptPath;

    std::unordered_map<std::string, OptionType> mCachedOptions;

    static inline LuaConfig* sInstance {};

    static LuaConfig& ins()
    {
        assert(sInstance);
        return *sInstance;
    }
};

}
