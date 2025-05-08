#include "MeshImporter.h"

#include <assimp/importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Flax
{
    Geometry MeshImporter::ReadGeometry(const String& path)
    {
        if (!std::filesystem::exists(path))
        {
            Log::Error(LogType::Importer, "File not found: {0}", path);
            return Geometry();
        }

        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path.c_str(),
            aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | 
            aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            Log::Error(LogType::Importer, "Assimp error: {0}", importer.GetErrorString());
            return Geometry();
        }

        aiMesh* mesh = scene->mMeshes[0];
        if (mesh)
        {
            Geometry geometry(mesh->mNumVertices, mesh->mNumFaces * 3);

            for (u32 v = 0; v < mesh->mNumVertices; v++)
            {
                geometry.AddPosition({ mesh->mVertices[v].x, mesh->mVertices[v].y, mesh->mVertices[v].z }, v);

                if (mesh->HasNormals())
                    geometry.AddNormal({ mesh->mNormals[v].x, mesh->mNormals[v].y, mesh->mNormals[v].z }, v);
                else
                    geometry.AddNormal({ 0.0f, 0.0f, 0.0f }, v);

                if (mesh->HasTangentsAndBitangents())
                {
                    geometry.AddTangent({ mesh->mTangents[v].x, mesh->mTangents[v].y, mesh->mTangents[v].z }, v);
                    geometry.AddBinormal({ mesh->mBitangents[v].x, mesh->mBitangents[v].y, mesh->mBitangents[v].z }, v);
                }
                else
                {
                    geometry.AddTangent({ 0.0f, 0.0f, 0.0f }, v);
                    geometry.AddBinormal({ 0.0f, 0.0f, 0.0f }, v);
                }

                if (mesh->HasVertexColors(0))
                    geometry.AddColor({ mesh->mColors[0][v].r, mesh->mColors[0][v].g, mesh->mColors[0][v].b, mesh->mColors[0][v].a }, v);
                else
                    geometry.AddColor({ 1.0f, 1.0f, 1.0f, 1.0f }, v);

                if (mesh->HasTextureCoords(0))
                    geometry.AddTexCoord({ mesh->mTextureCoords[0][v].x, mesh->mTextureCoords[0][v].y }, v);
                else
                    geometry.AddTexCoord({ 0.0f, 0.0f }, v);
            }

            for (u32 f = 0; f < mesh->mNumFaces; f++)
            {
                const aiFace& face = mesh->mFaces[f];
                for (u32 j = 0; j < face.mNumIndices; j++)
                    geometry.AddIndex((face.mIndices[j]), f * 3 + j);
            }

            importer.FreeScene();
            return geometry;
        }

        importer.FreeScene();
        return Geometry();
    }
}