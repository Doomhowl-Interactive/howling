#pragma once
#include "raylib.h"

#include <vector>

namespace howling
{
/**
 * Constructed Mesh
 */
class MeshBuilder
{
public:
    void pushVertex(Vector3 pos, Vector3 normal);
    Mesh bake();

private:
    std::vector<Vector3> mVertices {};
    std::vector<Vector3> mNormals {};
    std::vector<Vector2> mTexCoords {};
    std::vector<unsigned short> mIndices {};

    template <typename T, typename U>
    void copyIntoBuffer(const std::vector<T>& vec, U* dest) {
        std::memcpy(dest, vec.data(), sizeof(T) * vec.size());
    }
};
}