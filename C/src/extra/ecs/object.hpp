#pragma once
#include "../../simengine.hpp"
#include <armadillo>
/// No functions, just contains both position and rotation.
struct CFrame {
    arma::vec position;
    arma::vec rotation;
};
namespace Simengine {
    struct Object {
        int id;
        /// Whether or not this object will be rendered or not.
        bool visible;
        CFrame cframe;
        arma::vec position;
        arma::vec rotation;
        arma::fmat mesh;

        Object (Simengine::Scene scene) {

        };
    };
};
