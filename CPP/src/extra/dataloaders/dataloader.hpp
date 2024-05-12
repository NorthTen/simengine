#pragma once
#include <tuple>
#include <string>
namespace Simengine {
    struct Mesh;

    class Dataloaders {
    public:
        /// Loads an .obj file from a filepath.
        /// Returns a boolean which determines if the operation succeeded or not, and the actual mesh data.
        /// If it fails, it'll return false, but as well as an empty mesh object.
        inline static std::tuple<bool, Simengine::Mesh> loadobj(std::string filepath);


    };
};
#include "obj.hpp"
#include "mesh.hpp"
