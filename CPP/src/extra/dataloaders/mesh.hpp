#pragma once
#include <armadillo>
#include <vector>
namespace Simengine {
    /// Holds the necessary data for handling with a Mesh. Feel free to clear any lists you don't need to save system resources.
    struct Mesh {
        /// Data structure: { { 0.0, 0.0, 0.0  } }
        std::vector<arma::fvec3> vertices;

        /// Data structure: { { 0.0, 0.0, 0.0  } }
        std::vector<arma::fvec3> normals;

        /// Data structure: { { 0.0, 0.0 } }
        std::vector<arma::fvec2> texturecoordinates;

        /// Matches vertices;
        /// Data structure: { { 0.0, 0.0, 0.0  } }
        std::vector<arma::fvec3> colors;

        //std::vector<tinyobj::material_t> materials;
    };
};
