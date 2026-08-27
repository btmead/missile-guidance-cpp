//
// Created by benme on 21/08/2026.
//

#include "main.h"
#include <cmath>
#include <iostream>
#include <Eigen/Dense>

using namespace Eigen;

Matrix2d get_propnav (const double t_go, const double nav_ratio) {
    return Matrix2d {
        {0, 1},
        {-nav_ratio / std::pow(t_go, 2),    -nav_ratio / t_go}};
}

Vector2d to_linear (const State& mstate, const State& tstate) {
    double y { tstate.pos.y() - mstate.pos.y() };
    double yd { tstate.vel.y() - mstate.vel.y() };
    return {y, yd};
}

double v_closing (const State &mstate, const State &tstate) {
    Vector2d v_rel { mstate.vel - tstate.vel };
    Vector2d r { tstate.pos - mstate.pos };

    double v_closing { (r.dot(v_rel) / r.squaredNorm()) };

    if (v_closing < 0) {
        throw std::invalid_argument("Closing velocity less than 0");
    }

    return v_closing;
}

Vector2d state_derivative (const Vector2d& state, const double nr, const double t_go) {
    Matrix2d propnav_matrix { get_propnav( t_go, nr )};
    return propnav_matrix * state;
}

std::vector<Result_Sample> linear_guidance (const State &mstate, const State& tstate, const Parameters& params, const double t_final) {
    double t {0.0};
    Vector2d state { to_linear( mstate, tstate ) };

    if (params.h > 0 && (t_final - t) >= 0) {
        std::size_t steps (std::floor(t_final / params.h));
        std::vector<Result_Sample> results;
        results.reserve(steps+1);

        for (int i=0; i <= steps; i++) {
            try {
                v_closing(mstate, tstate);
                t = i * params.h;
                double t_go = t_final - t;
                state = rk4_derivative( state, params.nav_ratio, params.h, t_go );
                double a = state_derivative(state, params.nav_ratio, t_go).y();

                results.push_back(Result_Sample {
                    t,
                    state,
                    a,
                    t_go
                });
                // std::cout <<"Time: " << t << std::endl << "State: \n" << state << std::endl <<std::endl;
            }
            catch (const std::invalid_argument&) {
                throw;
            }
        }
        return results;
    }
    else {
        throw std::invalid_argument("Cannot produce num_steps. Check h and t_final value");
    }


}