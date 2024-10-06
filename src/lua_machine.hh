#pragma once

#include <cassert>
#include <memory>
#include <string>
#define SOL_ALL_SAFETIES_ON 1
#include <boost/core/noncopyable.hpp>
#include <initializer_list>
#include <sol/sol.hpp>

#include "logging.hh"

namespace howling
{

class LuaMachine;
class LuaPlugin
{
public:
    virtual ~LuaPlugin() = default;
    virtual void registerLuaPlugin(LuaMachine& machine) = 0;
};

class LuaReloader
{
public:
    virtual ~LuaReloader() = default;
    virtual void registerScript(const std::string& scriptPath) = 0;

    virtual void update(LuaMachine& machine) = 0;

    void pollUpdate(LuaMachine& machine, float delta)
    {
        mTimer += delta;
        if (mTimer > CHECK_TIME)
        {
            mTimer = 0.f;
            update(machine);
        }
    }

    static void setInstance(LuaReloader* reloader)
    {
        assert(!sInstance && "LuaReloader instance already set");
        sInstance = std::shared_ptr<LuaReloader>(reloader);
    }

    static std::weak_ptr<LuaReloader> getInstance()
    {
        return sInstance;
    }

private:
    float mTimer {};
    constexpr static float CHECK_TIME = 1.f;

    static inline std::shared_ptr<LuaReloader> sInstance = nullptr;
};

class LuaMachine : public LuaPlugin, private boost::noncopyable
{
public:
    LuaMachine();
    LuaMachine(const std::initializer_list<LuaPlugin*>& plugins);

    bool runScript(const std::string& scriptPath, bool hotReload = true);

    void update(float delta)
    {
        if (auto reload = mReload.lock())
        {
            reload->update(*this);
        }
    }

    template<typename... Args>
    bool callVoidFunc(const std::string& name, Args&&... args)
    {
        try
        {
            sol::protected_function func = state[name];
            sol::protected_function_result result = func(std::forward<Args>(args)...);
            if (!result.valid())
            {
                sol::error err = result;
                spdlog::error("Lua void function caused error: {}", err.what());
                return false;
            }
        }
        catch (sol::error& ex)
        {
            spdlog::error("Failed to call lua void function {} -> {}", name, ex.what());
            return false;
        }
        return true;
    }

    template<typename Func>
    void registerLuaFunction(const std::string& name, Func func)
    {
        state[name] = func;
    }

    void registerLuaPlugin(LuaMachine& machine) override;

    sol::state state {};

private:
    std::weak_ptr<LuaReloader> mReload;
};

}
