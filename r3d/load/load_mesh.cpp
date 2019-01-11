#include <vector>
#include <cstdio>
#include <string>
#include <cstring>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "load_mesh.hpp"
#include "../util/file.hpp"

bool r3d::load_mesh(std::string path,
                    std::vector<unsigned short> &indices,
                    std::vector<glm::vec3> &vertices,
                    std::vector<glm::vec2> &uvs,
                    std::vector<glm::vec3> &normals,
                    std::vector<glm::vec3> &tangents,
                    bool flip_uvs,
                    bool calculate_tangents)
{
    path.insert(0, get_running_dir());

    unsigned int p_flags =  aiProcess_GenSmoothNormals |
                            aiProcess_JoinIdenticalVertices |
                            aiProcess_ImproveCacheLocality |
                            aiProcess_LimitBoneWeights |
                            aiProcess_RemoveRedundantMaterials |
                            aiProcess_SplitLargeMeshes |
                            aiProcess_Triangulate |
                            aiProcess_GenUVCoords |
                            aiProcess_TransformUVCoords |
                            aiProcess_SortByPType |
                            aiProcess_FindDegenerates |
                            aiProcess_FindInvalidData | 
                            0;

    if(flip_uvs)
    {
        p_flags |= aiProcess_FlipUVs;
    }

    if(calculate_tangents)
    {
        p_flags |= aiProcess_CalcTangentSpace;
    }

    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(path, p_flags);

    if(!scene)
    {
        printf("%s", importer.GetErrorString());
        getchar();
        return false;
    }

    const aiMesh* mesh = scene->mMeshes[0]; // 1st mesh

    // Fill vertices positions
    if(mesh->HasPositions())
    {
        vertices.reserve(mesh->mNumVertices);
        for(unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            aiVector3D pos = mesh->mVertices[i];
            vertices.push_back(glm::vec3(pos.x, pos.y, pos.z));
        }
    }

    // Fill vertices texture coordinates
    if(mesh->HasTextureCoords(0))
    {
        uvs.reserve(mesh->mNumVertices);
        for(unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            aiVector3D UVW = mesh->mTextureCoords[0][i]; // Assume only 1 set of UV coords; AssImp supports 8 UV sets.
            uvs.push_back(glm::vec2(UVW.x, UVW.y));
        }
    }

    // Fill vertices normals
    if(mesh->HasNormals())
    {
        normals.reserve(mesh->mNumVertices);
        for(unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            aiVector3D n = mesh->mNormals[i];
            normals.push_back(glm::vec3(n.x, n.y, n.z));
        }
    }

    if(mesh->HasFaces())
    {
        indices.reserve(3 * mesh->mNumFaces);
        for(unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            // Assume the model has only triangles.
            indices.push_back(mesh->mFaces[i].mIndices[0]);
            indices.push_back(mesh->mFaces[i].mIndices[1]);
            indices.push_back(mesh->mFaces[i].mIndices[2]);
        }
    }

    if(mesh->HasTangentsAndBitangents())
    {
        tangents.reserve(mesh->mNumVertices);
        for(int i = 0; i < mesh->mNumVertices; i++)
        {
            aiVector3D t = mesh->mTangents[i];
            tangents.push_back(glm::vec3(t.x, t.y, t.z));
        }
    }

    return true;
}