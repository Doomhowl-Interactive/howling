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

template <typename Type, typename Map, typename LoadFunc>
static Type getOrLoadAsset(const std::string& path, Map& map, LoadFunc loadFunc)
{
    Type asset;
    try {
        asset = map[path];
    } catch (std::out_of_range&) {
        asset = loadFunc(path.c_str());
        map.emplace(path, asset);
    }
    return asset;
}

Model GameAssets::loadModel(const std::string& path)
{
    return getOrLoadAsset<Model>(path, mModels, LoadModel);
}

Font GameAssets::loadFont(const std::string& path)
{
    return getOrLoadAsset<Font>(path, mFonts, LoadFont);
}

Texture GameAssets::loadTexture(const std::string& path)
{
   return getOrLoadAsset<Texture>(path, mTextures, LoadTexture);
}

}
