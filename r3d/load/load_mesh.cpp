#include <vector>
#include <cstdio>
#include <string>
#include <cstring>
#include "load_mesh.hpp"
#include "../util/file.hpp"

#ifndef USE_TINY_OBJ
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

bool r3d::load_mesh(std::string path,
                    std::vector<unsigned short>& indices,
                    std::vector<glm::vec3>& vertices,
                    std::vector<glm::vec2>& uvs,
                    std::vector<glm::vec3>& normals,
                    std::vector<glm::vec3>& tangents,
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
        for(unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            aiVector3D t = mesh->mTangents[i];
            tangents.push_back(glm::vec3(t.x, t.y, t.z));
        }
    }

    return true;
}

#else

#define TINYOBJLOADER_IMPLEMENTATION
#include "../../external/include/tiny_obj_loader.h"

bool r3d::load_mesh(std::string path,
                    std::vector<glm::vec3>& vertices,
                    std::vector<glm::vec2>& uvs,
                    std::vector<glm::vec3>& normals)
{
    path.insert(0, get_running_dir());

    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string warn;
    std::string err;
    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path.c_str());

    if(!err.empty())
    {
        printf("OBJ Error: %s\n", err.c_str());
    }

    if(!ret)
    {
        return false;
    }

    // Loop over shapes
    for(size_t s = 0; s < shapes.size(); s++)
    {
        // Loop over faces(polygon)
        size_t index_offset = 0;
        for(size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
        {
            int fv = shapes[s].mesh.num_face_vertices[f];

            // Loop over vertices in the face.
            for(size_t v = 0; v < fv; v++)
            {
                tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
                tinyobj::real_t vx = attrib.vertices[3*idx.vertex_index+0];
                tinyobj::real_t vy = attrib.vertices[3*idx.vertex_index+1];
                tinyobj::real_t vz = attrib.vertices[3*idx.vertex_index+2];
                tinyobj::real_t nx = attrib.normals[3*idx.normal_index+0];
                tinyobj::real_t ny = attrib.normals[3*idx.normal_index+1];
                tinyobj::real_t nz = attrib.normals[3*idx.normal_index+2];
                tinyobj::real_t tx = attrib.texcoords[2*idx.texcoord_index+0];
                tinyobj::real_t ty = attrib.texcoords[2*idx.texcoord_index+1];

                vertices.push_back(glm::vec3(vx, vy, vz));
                normals.push_back(glm::vec3(nx, ny, nz));
                uvs.push_back(glm::vec2(tx, -ty));
            }

            index_offset += fv;
        }
    }

    return true;
}

#endif
