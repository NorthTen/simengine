#pragma once
#include <armadillo>
namespace Simengine {
    class Physics {
        public:
            struct angularvelocity {
                arma::fvec3 dir;
                float speed;

                angularvelocity(){};
            };
    };
};
