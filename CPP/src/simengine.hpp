#pragma once
#include <armadillo>
#include <cmath>
float magnitudefvec3(arma::fvec3 vec) {
    return sqrtf(vec[0]*2 + vec[1]*2 + vec[2]*2);
};
namespace Simengine {
    static bool DEBUG = false;
    struct Scene;
    struct Object;
    struct Physics;
};
#include "extra/ecs/object.hpp"
#include "extra/physics/physics.hpp"
#include "extra/scene.hpp"
