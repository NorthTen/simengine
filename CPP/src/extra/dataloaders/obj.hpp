#pragma once
#include "dataloader.hpp"
#define TINYOBJLOADER_IMPLEMENTATION
#include "../../../libs/tinyobjloader/tiny_obj_loader.h"
#include <armadillo>
#include <string>
#include "mesh.hpp"
#include <iostream>
#include <tuple>
namespace Simengine {
inline std::tuple<bool, Simengine::Mesh>
Simengine::Dataloaders::loadobj(std::string filepath) {
  tinyobj::attrib_t attrib;
  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials;

  std::string warn;
  std::string err;

  Simengine::Mesh mesh;

  bool success = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err,
                                  filepath.c_str());
  if (!success) {
    std::cout << "[dataloader][obj.hpp][error] Couldn't load Object File ("
              << filepath << ").";
    return {false, mesh};
  }
  if (!err.empty()) {
    std::cout << "[dataloader][obj.hpp][error] Object File (" << filepath
              << ") error: " << warn;
    return {false, mesh};
  };
  if (!warn.empty()) {
    std::cout << "[dataloader][obj.hpp][warn] Object File (" << filepath
              << ") warning: " << warn;
    return {false, mesh};
  };

  // convert colors to mesh.colors
  arma::fvec3 temp;
  bool x;
  bool y;
  bool z;
  for (float vertexs : attrib.colors) {
    if (x && y && z) {
      x = false;
      y = false;
      z = false;
      mesh.colors[mesh.colors.size()] = temp;
    }
    if (x) {
      temp[1] = vertexs;
      y = true;
      if (y) {
        temp[2] = vertexs;
        z = true;
      }
    } else {
      temp[0] = vertexs;
      x = true;
    }
  }
  x = false;
  y = false;
  z = false;

  // convert vertices to mesh.triangles
  for (float vertexs : attrib.vertices) {
    if (x && y && z) {
      x = false;
      y = false;
      z = false;
      mesh.vertices[mesh.vertices.size()] = temp;
    }
    if (x) {
      temp[1] = vertexs;
      y = true;
      if (y) {
        temp[2] = vertexs;
        z = true;
      }
    } else {
      temp[0] = vertexs;
      x = true;
    }
  }
  x = false;
  y = false;
  z = false;

  // convert normals to mesh.normals
  for (float vertexs : attrib.normals) {
    if (x && y && z) {
      x = false;
      y = false;
      z = false;
      mesh.normals[mesh.normals.size()] = temp;
    }
    if (x) {
      temp[1] = vertexs;
      y = true;
      if (y) {
        temp[2] = vertexs;
        z = true;
      }
    } else {
      temp[0] = vertexs;
      x = true;
    }
  }
  x = false;
  y = false;
  z = false;

  // convert texcoords to mesh.texturecoordinates
  for (float vertexs : attrib.texcoords) {
    if (x && y) {
      x = false;
      y = false;
      mesh.texturecoordinates[mesh.texturecoordinates.size()] = {temp[0],
                                                                 temp[1]};
    }
    if (x) {
      temp[1] = vertexs;
      y = true;
    } else {
      temp[0] = vertexs;
      x = true;
    }
  }

  return {true, mesh};
};
}; // namespace Simengine
