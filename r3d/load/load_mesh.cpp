#include <vector>
#include <cstdio>
#include <string>
#include <cstring>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "load_mesh.hpp"
#include "../core/utils.hpp"

bool r3d::load_mesh(std::string path,
                    std::vector<unsigned short> &indices,
                    std::vector<glm::vec3> &vertices,
                    std::vector<glm::vec2> &uvs,
                    std::vector<glm::vec3> &normals
)
{
    path.insert(0, get_running_dir());

    std::vector<glm::vec3> temp_vertices;
    std::vector<glm::vec2> temp_uvs;
    std::vector<glm::vec3> temp_normals;

    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(path, aiProcess_JoinIdenticalVertices);

    if(!scene)
    {
        printf("%s", importer.GetErrorString());
        getchar();
        return false;
    }

    const aiMesh* mesh = scene->mMeshes[0]; // 1st mesh

    // Fill vertices positions
    vertices.reserve(mesh->mNumVertices);
    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        aiVector3D pos = mesh->mVertices[i];
        vertices.push_back(glm::vec3(pos.x, pos.y, pos.z));
    }

    // Fill vertices texture coordinates
    uvs.reserve(mesh->mNumVertices);
    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        aiVector3D UVW = mesh->mTextureCoords[0][i]; // Assume only 1 set of UV coords; AssImp supports 8 UV sets.
        uvs.push_back(glm::vec2(UVW.x, UVW.y));
    }

    // Fill vertices normals
    normals.reserve(mesh->mNumVertices);
    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        aiVector3D n = mesh->mNormals[i];
        normals.push_back(glm::vec3(n.x, n.y, n.z));
    }

    indices.reserve(3 * mesh->mNumFaces);
    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        // Assume the model has only triangles.
        indices.push_back(mesh->mFaces[i].mIndices[0]);
        indices.push_back(mesh->mFaces[i].mIndices[1]);
        indices.push_back(mesh->mFaces[i].mIndices[2]);
    }

    return true;
}