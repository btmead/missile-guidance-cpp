//
// Created by benme on 19/08/2026.
//

#include "main.h"
#include "data.h"
#include "variable_types.h"
#include <iostream>
#include <Eigen/Dense>

Eigen::Vector2d r (const State &mstate, const State &tstate) {
    return tstate.pos - mstate.pos;
}


std::ostream& operator<< (std::ostream& out, State state) {
    out << "Coordinates: (" << state.pos.x() << "," << state.pos.y() << ")" << std::endl <<
        "Velocity: (" << state.vel.x() << "," << state.vel.y() << ") \n";
    return out;
}


int main() {
    Parameters params {get_parameters("parameters.toml")};
    State missile_state { import_state("parameters.toml", "missile_state", params.missile_vmax) };
    State target_state { import_state("parameters.toml", "target_state", params.target_vmax) };
    coord_rotation(missile_state, target_state);

    try {
        double t_final { 1 / v_closing(missile_state, target_state) };
        std::vector<Result_Sample> results { linear_guidance (missile_state, target_state, params, t_final) };
        write_data(results);
        return 0;
    }

    catch (const std::invalid_argument& err) {
        std::cerr << err.what() << std::endl;
    }

}

