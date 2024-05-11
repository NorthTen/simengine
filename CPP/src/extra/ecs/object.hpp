#pragma once
#include <armadillo>
#include <boost/smart_ptr.hpp>
/// No functions, just contains both position and rotation.
struct CFrame {
    arma::fvec3 position;
    arma::fvec3 rotation;
};
/// Ripped from Physics, due to compilation issues.
struct AngularVelocity {
public:
  bool affectedbyphysics;
  /// Don't directly modify this property.
  bool collision_processed;
  arma::fvec3 dir;
  float speed;
  AngularVelocity() { affectedbyphysics = true; };
};
namespace Simengine {
    struct Object {
        /// Useful for having a reference to this Object.
        boost::shared_ptr<Object> refptr;
        /// Useful for wanting to modify this object without others modifying it at the same time as you.
        boost::weak_ptr<Object> lockptr;
        int id;
        /// Whether or not this object will be rendered or not.
        bool visible;
        CFrame cframe;
        arma::fvec3 origin;
        arma::fvec3 position;
        arma::fvec3 rotation;
        arma::fvec3 size;
        AngularVelocity angularvelocity;
        arma::fmat mesh;
        float mass;

        Object () {
            refptr = boost::shared_ptr<Object>(this);
            lockptr = boost::weak_ptr<Object>(refptr);
            visible = false;
        };

        bool operator >(Object &rhs){
            return id>rhs.id;
        };
        bool operator <(Object &rhs){
            return id<rhs.id;
        };
    };
};
