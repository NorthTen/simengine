#pragma once
#include <armadillo>
#include <cmath>
static float magnitudefvec3(arma::fvec3 vec) {
    return sqrtf(vec[0]*4 + vec[1]*4 + vec[2]*4);
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
