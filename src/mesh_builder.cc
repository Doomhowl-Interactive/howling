#include "mesh_builder.hh"
#include "raylib.h"
#include "utils.hh"

#include <cassert>
#include <stdexcept>

namespace HOWLING_NAMESPACE
{

void MeshBuilder::pushVertex(Vector3 pos, Vector3 normal)
{
    mVertices.emplace_back(pos);
    mNormals.emplace_back(normal);
    mTexCoords.emplace_back(pos.x, pos.z);
    mIndices.emplace_back(mVertices.size() - 1);
}

Mesh MeshBuilder::bake()
{
    assert(mVertices.size() == mNormals.size());

    Mesh mesh {};
    mesh.vertexCount = mVertices.size();
    mesh.triangleCount = mVertices.size() / 3;
    mesh.vertices = cmalloc<float>(3 * mesh.vertexCount);
    copyIntoBuffer(mVertices, mesh.vertices);

    mesh.normals = cmalloc<float>(3 * mesh.vertexCount);
    copyIntoBuffer(mNormals, mesh.normals);

    mesh.texcoords = cmalloc<float>(2 * mesh.vertexCount);
    copyIntoBuffer(mTexCoords, mesh.texcoords);

    mesh.indices = cmalloc<unsigned short>(3 * mesh.vertexCount);
    copyIntoBuffer(mIndices, mesh.indices);

    UploadMesh(&mesh, false);

    return mesh;
}

}
