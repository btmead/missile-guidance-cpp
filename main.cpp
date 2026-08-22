//
// Created by benme on 19/08/2026.
//

#include "main.h"
#include <iostream>

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

std::ostream& operator<< (std::ostream &out, LinearState state) {
    out << "(" << state.vec.x << ", " << state.vec.y << ")" << std::endl << "Time: " << state.t_go << std::endl;
    return out;
}


int main() {
    Parameters params {get_parameters("parameters.toml")};
    State missile_state { import_state("parameters.toml", "missile_state", params.missile_vmax) };
    State target_state { import_state("parameters.toml", "target_state", params.target_vmax) };
    coord_rotation(missile_state, target_state);

    try {
        double t_final { 1 / v_closing(missile_state, target_state) };
        linear_guidance (missile_state, target_state, params, t_final);
        return 0;
    }

    catch (const std::invalid_argument& err) {
        std::cerr << err.what() << std::endl;
    }

}

