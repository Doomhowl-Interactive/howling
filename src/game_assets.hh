#pragma once
#include "howl_assert.hh"
#include "lua_machine.hh"
#include "raylib.h"

#include <boost/core/noncopyable.hpp>
#include <string>
#include <unordered_map>
#include <vector>

#ifndef NDEBUG
#include <filesystem>
#endif

namespace HOWLING_NAMESPACE
{

/// Game should inherit this class and call load functions in constructor.
class GameAssets : public LuaPlugin,
                   private boost::noncopyable
{
public:
    virtual ~GameAssets();

    /// @brief Loads or gets model
    [[nodiscard]] Model getOrLoadModel(const std::string& path);

    /// @brief Loads or gets asset
    [[nodiscard]] Font getOrLoadFont(const std::string& path);

    /// @brief Loads or gets asset
    [[nodiscard]] Texture getOrLoadTexture(const std::string& path);

    void registerLuaPlugin(LuaMachine& machine) override;

    void setAssetsDir(const std::string& assetsDir)
    {
        mAssetsDir = assetsDir;
    }

protected:
    std::unordered_map<std::string, Model> mModels {};
    std::unordered_map<std::string, Font> mFonts {};
    std::unordered_map<std::string, Texture> mTextures {};

    std::string mAssetsDir = "";

private:
    template<typename Type, typename Map, typename LoadFunc>
    Type getOrLoadAsset(const std::string& path, Map& map, LoadFunc loadFunc)
    {
        Type asset;
        try
        {
            asset = map.at(path);
        }
        catch (std::out_of_range&)
        {
            assert(std::filesystem::exists(path));
            asset = loadFunc(path.c_str());
            map.emplace(path, asset);
        }
        return asset;
    }
};

}
