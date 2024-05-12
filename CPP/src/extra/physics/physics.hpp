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

    auto intersectionpos = lhs->get()->position-rhs->get()->position;

    lhs->get()->angularvelocity.dir= (reflectvec3(lhs->get()->angularvelocity.dir,intersectionpos)) * lhs->get()->origin;
    rhs->get()->angularvelocity.dir= (reflectvec3(rhs->get()->angularvelocity.dir,intersectionpos)) * rhs->get()->origin;
  };



  /// Call this to update an object's position according to their angularvelocity if they're affected by physics at all.
  void update_object(boost::shared_ptr<Simengine::Object> *targ, float airweight){
        float targspeed = targ->get()->angularvelocity.speed;
        AngularVelocity angvel = targ->get()->angularvelocity;
        if (!angvel.affectedbyphysics){
            // If it's not affected by physics; return
            return;
        }

        if (angvel.speed<0.0000) {
            // If it's not moving then don't affect it.
            return;
        }

        arma::fvec3 targdistfromdestination = targ->get()->position-angvel.dir;

        targ->get()->position=(targ->get()->position*angvel.speed)/targ->get()->position/angvel.dir;
        targ->get()->rotation=((targ->get()->rotation*angvel.speed)/targ->get()->size/targ->get()->mass)/airweight;
        targ->get()->angularvelocity.speed-=magnitudefvec3((targ->get()->size/targ->get()->mass)/airweight);

        // check to see if the speed is below 0.0
        if (angvel.speed<0.0000) {
            angvel.speed=0;
            angvel.dir=arma::fvec3{0.0,0.0,0.0};
        }
    };
};
};
