#pragma once
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <Eigen/Core>
#include <assimp/Importer.hpp>

#include <string>
#include <vector>

namespace assimp_eigen {
  struct MeshData {
    std::vector<Eigen::Vector3d> vertices;
    std::vector<Eigen::Vector3d> normals;
  };

  MeshData loadMesh(const std::string& meshPath);
}  // namespace assimp_eigen
