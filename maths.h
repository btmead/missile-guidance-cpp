//
// Created by benme on 28/08/2026.
//

#ifndef GUIDANCE_SIM_CPP_MATHS_H
#define GUIDANCE_SIM_CPP_MATHS_H

#include <Eigen/Dense>

using namespace Eigen;

Matrix2d rotation_matrix (const double angle);
Vector2d rk4_derivatives (const Vector2d&, const double, const double, const double);

#endif //GUIDANCE_SIM_CPP_MATHS_H
