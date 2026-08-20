//
// Created by benme on 19/08/2026.
//

#include "main.h"
#include <iostream>
#include <cmath>


void coord_rotation(State &mstate, State &tstate) {
    double vm {hypot(mstate.vel)};
    double vt {hypot(tstate.vel)};
    Vector2D r {tstate.pos - mstate.pos};
    double lambda { std::atan2(r.y, r.x) };
    double beta { std::atan2(tstate.vel.y, tstate.vel.x) };
    double lead { std:: asin((vt / vm) * std::sin(beta+lambda))};
    mstate = coord_rotation(mstate, lambda + lead);
    tstate = coord_rotation(tstate, lambda + lead);
}

#if 0
LinearState state_derivative (const LinearState& state, const Parameters& params) {

}
#endif

Vector2D v_closing (State &mstate, State &tstate) {
    Vector2D v_rel { mstate.vel - tstate.vel };
    Vector2D r { tstate.pos - mstate.pos };

    Vector2D v_closing {(r.scalar(r.dot(v_rel) / hypot(r)))};
    return v_closing;
}

Vector2D r (State &mstate, State &tstate) {
    return { tstate.pos - mstate.pos};
}


std::ostream& operator<< (std::ostream& out, State state) {
    out << "Coordinates: (" << state.pos.x << "," << state.pos.y << ")" << std::endl <<
        "Velocity: (" << state.vel.x << "," << state.vel.y << ") \n";
    return out;
}

std::ostream &operator<<(std::ostream &out, Matrix2D matrix) {
    out << "| " << matrix.m00 << " " << matrix.m01 << " |\n| " <<
        matrix.m10 << " " << matrix.m11 << " |" << std::endl;
    return out;
}


int main() {
    double t {0.0};
    Parameters params {get_parameters("parameters.toml")};
    State missile_state { import_state("parameters.toml", "missile_state", params.missile_vmax) };
    State target_state { import_state("parameters.toml", "target_state", params.target_vmax) };
    coord_rotation(missile_state, target_state);

    double t_final {
        hypot(r(missile_state, target_state)) /
            hypot(v_closing(missile_state, target_state))
    };
    double t_go {t_final - t};
    Matrix2D propnav_matrix {0, 1, -params.nav_ratio / std::pow(t_go, 2), -params.nav_ratio / t_go};

    
    return 0;
}

