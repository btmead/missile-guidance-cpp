//
// Created by benme on 19/08/2026.
//

#include "main.h"
#include "State.h"
#include "Parameters.h"
#include "GuidanceValues.h"
#include "IMU.h"
#include <iostream>
#include <Eigen/Dense>

using namespace Eigen;


int main() {
    std::string file {"parameters.toml"};

    Parameters params (file);
    TrueState true_state { file, params };

    State missile_state (true_state.true_missile_state());
    State target_state (true_state.true_target_state());
    IMU sensor {};

    GuidanceValues value (missile_state, target_state);
    double t_final {value.t_final()};
    double h {params.get_h()};

    std::size_t steps (std::floor(t_final / h));

    for (int i = 0; i <= steps; i++) {
        Vector2d target_pos {missile_state.get_target(true_state)};
        target_state.update_state(target_pos, h);
        Vector2d a_c {0, -params.get_nav_ratio() * value.r_dot() * value.dot_lambda() };
        Vector2d a_dot {a_c - missile_state.get_accel()};

        sensor.update_values(a_dot, missile_state.get_vel(), h);
        missile_state.update_state(sensor, h);
    }
}

