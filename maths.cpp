//
// Created by benme on 19/08/2026.
//

#include "maths.h"
#include <cmath>
#include <Eigen/Dense>

using namespace Eigen;


Matrix2d rotationmatrix(const double angle) {
    double cosine {std::cos(angle)};
    double sine {std::sin(angle)};

    Matrix2d m {{cosine, -sine},
                    {sine, cosine}};
    return  m;
}

Matrix3d state_update (const double h) {
    Matrix3d m {
        {1, h, 0.5 * std::pow(h,2)},
            {0, 1, h},
            {0, 0, 1}};

    return m;
}


#if 0
Vector2d rk4_derivative (const Vector2d& state, const double nav_ratio, const double h, const double t_go) {
    Vector2d k1, k2, k3, k4;

    k1 = state_derivative( state,                   nav_ratio,  t_go         );
    k2 = state_derivative( state + (k1 * (h/2)),    nav_ratio,  t_go + (h/2) );
    k3 = state_derivative( state + (k2 * (h/2)),    nav_ratio,  t_go + (h/2) );
    k4 = state_derivative( state + (k3 * h),        nav_ratio,  t_go + (h/2) );

    Vector2d new_state { state + ( (k1 + (k2 * 2) + (k3 * 2) + k4) * (h/6) ) };
    return new_state;
}
#endif