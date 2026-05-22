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
    }

    return result;
  }
}  // namespace assimp_eigen