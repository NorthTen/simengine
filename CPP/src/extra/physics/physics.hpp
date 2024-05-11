#pragma once
#include <armadillo>
#include <boost/smart_ptr.hpp>
#include <iostream>
#include "../ecs/object.hpp"
#include "../../simengine.hpp"
namespace Simengine {

struct Physics {
  /// Structure for handling collisions; if A hit B at X speed, deduct X
  /// speed from each-other.
  void handle_collision(boost::shared_ptr<Simengine::Object> *lhs,
                        boost::shared_ptr<Simengine::Object> *rhs) {
    if (!lhs->get()->angularvelocity.affectedbyphysics ||
        !rhs->get()->angularvelocity.affectedbyphysics) {
      if (Simengine::DEBUG) {
        std::cout << "[Physics]: Either object do not want to be affected by "
                     "physics. IDs: "
                  << lhs->get()->id << ", " << rhs->get()->id << ".";
      };
      return;
    }

    if (lhs->get()->angularvelocity.collision_processed ||
        rhs->get()->angularvelocity.collision_processed) {
      if (Simengine::DEBUG) {
        std::cout << "[Physics]: Either object's collisions have already been "
                     "processed. IDs: "
                  << lhs->get()->id << ", " << rhs->get()->id << ".";
      };

      return;
    }

    // continue then
    float result = (lhs->get()->angularvelocity.speed - rhs->get()->angularvelocity.speed)/((lhs->get()->mass+rhs->get()->mass));
    lhs->get()->angularvelocity.speed=result+(magnitudefvec3((lhs->get()->position-lhs->get()->origin)));
    rhs->get()->angularvelocity.speed=result+(magnitudefvec3((rhs->get()->position-rhs->get()->origin)));

    lhs->get()->angularvelocity.dir= (-lhs->get()->angularvelocity.dir) * lhs->get()->origin; // Invert the direction.
    rhs->get()->angularvelocity.dir= (-rhs->get()->angularvelocity.dir) * rhs->get()->origin;
  };
};
};
