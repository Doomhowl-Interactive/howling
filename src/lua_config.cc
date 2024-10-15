#include <filesystem>
#include <spdlog/spdlog.h>

#include "lua_config.hh"

namespace HOWLING_NAMESPACE
{

LuaConfig::LuaConfig(const std::string& scriptPath)
    : mScriptPath(scriptPath)
{
    sInstance = this;
    runScript(scriptPath);

    registerLuaReloadCallback([this](const std::filesystem::path& file) {
        if (sInstance) {
            if (mScriptPath.ends_with(file.string())) {
                mCachedOptions.clear();
                spdlog::debug("Reset configuration cache");
            }
        }
    });
}

LuaConfig::~LuaConfig()
{
    sInstance = nullptr;
}

// TODO: dry
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

Vector4 LuaConfig::getVector4(const std::string& name)
{
    Vector4 result {};
    if (ins().state["config"][name].get_type() == sol::type::table)
    {
        sol::table table = ins().state["config"][name];
        for (const auto& [key, value] : table)
        {
            auto keyStr = key.as<std::string>();
            if (keyStr == "x")
            {
                result.x = value.as<float>();
            }
            else if (keyStr == "y")
            {
                result.y = value.as<float>();
            }
            else if (keyStr == "z")
            {
                result.z = value.as<float>();
            }
            else if (keyStr == "w")
            {
                result.w = value.as<float>();
            }
        }
    }
    return result;
}

}
