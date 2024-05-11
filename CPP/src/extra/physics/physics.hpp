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
    float lhsresult = (lhs->get()->angularvelocity.speed - rhs->get()->angularvelocity.speed)+magnitudefvec3(lhs->get()->size)/((lhs->get()->mass+rhs->get()->mass));
    float rhsresult = (lhs->get()->angularvelocity.speed - rhs->get()->angularvelocity.speed)+magnitudefvec3(rhs->get()->size)/((lhs->get()->mass+rhs->get()->mass));
    lhs->get()->angularvelocity.speed=lhsresult+(magnitudefvec3((lhs->get()->position-lhs->get()->origin)));
    rhs->get()->angularvelocity.speed=rhsresult+(magnitudefvec3((rhs->get()->position-rhs->get()->origin)));

    auto subpos = lhs->get()->position-rhs->get()->position;

    lhs->get()->angularvelocity.dir= (-lhs->get()->angularvelocity.dir) * lhs->get()->origin; // Invert the direction.
    rhs->get()->angularvelocity.dir= (-rhs->get()->angularvelocity.dir) * rhs->get()->origin;
  };

  /// Call this to update an object's position according to their angularvelocity if they're affected by physics at all.
  void update_object(boost::shared_ptr<Simengine::Object> *targ, float airweight){
        if (!targ->get()->angularvelocity.affectedbyphysics){
            // If it's not affected by physics; return
            return;
        }

        targ->get()->position=(targ->get()->position*targ->get()->angularvelocity.speed)/targ->get()->angularvelocity.dir;
        targ->get()->rotation=(targ->get()->position/targ->get()->angularvelocity.dir);
        targ->get()->angularvelocity.speed-=airweight+targ->get()->mass;
        // check to see if the speed is below 0.0
        if (targ->get()->angularvelocity.speed<0.0) {
            targ->get()->angularvelocity.speed=0;
            targ->get()->angularvelocity.dir=arma::fvec3{0.0,0.0,0.0};
        }
    };
};
};
