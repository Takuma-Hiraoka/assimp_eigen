#include "assimp_eigen/assimp_eigen.h"

namespace assimp_eigen {
  MeshData loadMesh(const std::string& meshPath) {
    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(
      meshPath, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices |
                  aiProcess_GenSmoothNormals);

    if (!scene || !scene->HasMeshes()) {
      throw std::runtime_error(std::string("Failed to load mesh: ") +
                               importer.GetErrorString());
    }

    MeshData result;

    for (unsigned int meshIdx = 0; meshIdx < scene->mNumMeshes; ++meshIdx) {
      const aiMesh* mesh = scene->mMeshes[meshIdx];
      const int vertexOffset = static_cast<int>(result.vertices.size());

      for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
        const aiVector3D& v = mesh->mVertices[i];

        result.vertices.emplace_back(v.x, v.y, v.z);

        if (mesh->HasNormals()) {
          const aiVector3D& n = mesh->mNormals[i];
          result.normals.emplace_back(n.x, n.y, n.z);
        } else {
          result.normals.emplace_back(Eigen::Vector3d::Zero());
        }
      }

      for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
        const aiFace& face = mesh->mFaces[i];
        if (face.mNumIndices == 3) {
          result.triangles.emplace_back(vertexOffset + static_cast<int>(face.mIndices[0]),
                                        vertexOffset + static_cast<int>(face.mIndices[1]),
                                        vertexOffset + static_cast<int>(face.mIndices[2]));
        }
      }
    }

    return result;
  }
}  // namespace assimp_eigen
