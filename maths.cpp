//
// Created by benme on 19/08/2026.
//

#include "main.h"
#include <cmath>
#include <Eigen/Dense>

using namespace Eigen;


Matrix2d rotationmatrix(const double angle) {
    double cosine {std::cos(angle)};
    double sine {std::sin(angle)};

    Matrix2d m {{cosine, sine},
                    {-sine, cosine}};
    return  m;
}


State coord_rotation(State &state, const double angle) {
    state.pos = (rotationmatrix(angle) * state.pos);
    state.vel = (rotationmatrix(angle) * state.vel);
    return state;
}


void coord_rotation(State &mstate, State &tstate) {
    double vm {mstate.vel.norm()};
    double vt {tstate.vel.norm()};
    Vector2d r { tstate.pos - mstate.pos };
    double lambda { std::atan2(r.y(), r.x()) };
    double beta { std::atan2(tstate.vel.y(), tstate.vel.x()) };
    double lead { std:: asin((vt / vm) * std::sin(lambda - beta))};
    mstate = coord_rotation(mstate, lambda+lead);
    tstate = coord_rotation(tstate, lambda+lead);
}

Vector2d rk4_derivative (const Vector2d& state, const double nav_ratio, const double h, const double t_go) {
    Vector2d k1, k2, k3, k4;

    k1 = state_derivative( state,                   nav_ratio,  t_go         );
    k2 = state_derivative( state + (k1 * (h/2)),    nav_ratio,  t_go + (h/2) );
    k3 = state_derivative( state + (k2 * (h/2)),    nav_ratio,  t_go + (h/2) );
    k4 = state_derivative( state + (k3 * h),        nav_ratio,  t_go + (h/2) );

    Vector2d new_state { state + ( (k1 + (k2 * 2) + (k3 * 2) + k4) * (h/6) ) };
    return new_state;
}