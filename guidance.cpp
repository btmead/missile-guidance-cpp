//
// Created by benme on 21/08/2026.
//

#include "main.h"
#include <cmath>

Matrix2D get_propnav (const double t_go, const Parameters& params) {
    return Matrix2D {
        0,                                          1,
        -params.nav_ratio / std::pow(t_go, 2),    -params.nav_ratio / t_go};
}

LinearState to_linear (const State& mstate, const State& tstate) {
    double y { tstate.pos.y - mstate.pos.y };
    double yd { tstate.vel.y - mstate.vel.y };
    return {y, yd};
}

Vector2D v_closing (State &mstate, State &tstate) {
    Vector2D v_rel { mstate.vel - tstate.vel };
    Vector2D r { tstate.pos - mstate.pos };

    Vector2D v_closing {(r.dot(v_rel) / hypot(r))};
    return v_closing;
}