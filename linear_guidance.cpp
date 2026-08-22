//
// Created by benme on 21/08/2026.
//

#include "main.h"
#include <cmath>
#include <iostream>

Matrix2D get_propnav (const double t_go, const double nav_ratio) {
    return Matrix2D {
        0,                                          1,
        -nav_ratio / std::pow(t_go, 2),    -nav_ratio / t_go};
}

LinearState to_linear (const State& mstate, const State& tstate) {
    double y { tstate.pos.y - mstate.pos.y };
    double yd { tstate.vel.y - mstate.vel.y };
    return {y, yd};
}

double v_closing (const State &mstate, const State &tstate) {
    Vector2D v_rel { mstate.vel - tstate.vel };
    Vector2D r { tstate.pos - mstate.pos };

    double v_closing {(r.dot(v_rel) / std::pow(hypot(r), 2)) };

    if (v_closing < 0) {
        throw std::invalid_argument("Closing velocity less than 0");
    }

    return v_closing;
}

LinearState state_derivative (const LinearState& state, const double nr, const double t_go) {
    Matrix2D propnav_matrix { get_propnav( t_go, nr )};
    return { matrixmultiply(propnav_matrix, state.vec) };
}

void linear_guidance (const State &mstate, const State& tstate, const Parameters params, const double t_final) {
    double t {0.0};
    LinearState state { to_linear( mstate, tstate ) };

    if (params.h > 0 && (t_final - t) >= 0) {
        std::size_t steps (std::floor(t_final / params.h));

        for (int i=0; i <= steps; i++) {
            try {
                v_closing(mstate, tstate);
                t = i * params.h;
                state.t_go = t_final - t;
                state = rk4_derivative( state, params.nav_ratio, params.h );
                std::cout << state;
            }
            catch (const std::invalid_argument& err) {
                throw;
            }
        }
    }
    else {
        throw std::invalid_argument("Cannot produce num_steps. Check h and t_final value");
    }


}