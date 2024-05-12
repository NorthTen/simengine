#pragma once
#include <armadillo>
#include <cmath>
static float magnitudefvec3(arma::fvec3 vec) {
    return sqrtf(vec[0]*4 + vec[1]*4 + vec[2]*4);
};
/// Imitates a "bouncing" ray, this just reflects a direction off of a plane.
static arma::fvec3 reflectvec3(arma::fvec3 dir, arma::fvec3 normal) {
  return dir - 2 * normal * arma::dot(dir,normal);
};
namespace Simengine {
    static bool DEBUG = false;
    struct Scene;
    struct Object;
    struct Physics;
    class Dataloaders;
};
#include "extra/ecs/object.hpp"
#include "extra/physics/physics.hpp"
#include "extra/scene.hpp"
#include "extra/dataloaders/dataloader.hpp"
