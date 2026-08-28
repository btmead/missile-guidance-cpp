//
// Created by benme on 28/08/2026.
//

#include <Eigen/Dense>
#include "main.h"

using namespace Eigen;

Vector2d target_accel (const double time, const double max) { //ENSURE MAX IS POSITIVE
    Vector2d accel {std::clamp(0.0, -max, max), std::clamp(0.0, -max, max)};
    return accel;
}