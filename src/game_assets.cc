#include "game_assets.hh"

#include <cassert>
#include <stdexcept>

namespace HOWLING_NAMESPACE
{

template <typename Map, typename UnloadFunc>
static void unloadAssets(Map& map, UnloadFunc unloadFunc)
{
    for (auto& it: map) {
        unloadFunc(it.second);
    }
}

GameAssets::~GameAssets()
{
    unloadAssets(mModels, UnloadModel);
    unloadAssets(mTextures, UnloadTexture);
    unloadAssets(mFonts, UnloadFont);
}

Model GameAssets::getOrLoadModel(const std::string& path)
{
    return getOrLoadAsset<Model>(path, mModels, LoadModel);
}

Font GameAssets::getOrLoadFont(const std::string& path)
{
    return getOrLoadAsset<Font>(path, mFonts, LoadFont);
}

Texture GameAssets::getOrLoadTexture(const std::string& path)
{
   return getOrLoadAsset<Texture>(path, mTextures, LoadTexture);
}

void GameAssets::registerLuaPlugin(LuaMachine& machine)
{
    machine.registerLuaFunction("get_or_load_asset_texture", [this](std::string path)
        { return getOrLoadTexture(mAssetsDir + path); });
    machine.registerLuaFunction("get_or_load_asset_model", [this](std::string path)
        { return getOrLoadModel(mAssetsDir + path); });
    machine.registerLuaFunction("get_or_load_asset_font", [this](std::string path)
        { return getOrLoadModel(mAssetsDir + path); });
}

}
