#pragma once
#include "raylib.h"

#include <string>
#include <vector>
#include <unordered_map>
#include <boost/core/noncopyable.hpp>

namespace HOWLING_NAMESPACE
{

/// Game should inherit this class and call load functions in constructor.
class GameAssets : private boost::noncopyable
{
public:
    virtual ~GameAssets();

    /// @brief Loads or gets model
    [[nodiscard]] Model loadModel(const std::string& path);

    /// @brief Loads or gets asset
    [[nodiscard]] Font loadFont(const std::string& path);

    /// @brief Loads or gets asset
    [[nodiscard]] Texture loadTexture(const std::string& path);

protected:
    std::unordered_map<std::string, Model> mModels {};
    std::unordered_map<std::string, Font> mFonts {};
    std::unordered_map<std::string, Texture> mTextures {};
};

}
