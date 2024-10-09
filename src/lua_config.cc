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

Vector3 LuaConfig::getVector3(const std::string& name)
{
    Vector3 result {};
    if (ins().state["config"][name].get_type() == sol::type::table) {
        sol::table table = ins().state["config"][name];
        for (const auto& [key,value] : table) {
            auto keyStr = key.as<std::string>();
            if (keyStr == "x") {
                result.x = value.as<float>();
            } else if (keyStr == "y") {
                result.y = value.as<float>();
            } else if (keyStr == "z") {
                result.z = value.as<float>();
            }
        }
    }
    return result;
}

}
