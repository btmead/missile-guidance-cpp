//
// Created by benme on 19/08/2026.
//

#include "main.h"
#include "TrueState.h"
#include "State.h"
#include "Parameters.h"
#include "GuidanceValues.h"
#include "IMU.h"
#include "data.h"
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

    GuidanceValues values (missile_state, target_state);
    double t_final {values.t_final()};
    double h {params.get_h()};
    double a_max {params.get_amax("missile")};

    std::size_t steps (std::floor(t_final / h));
    std::vector<Result_Sample> results;
    results.reserve(steps+1);
    results.push_back(Result_Sample{
        0,
        missile_state,
        true_state,
        t_final
    });

    for (int i = 1; i <= steps; i++) {
        double t {h * i};
        double t_go {t_final - t};

        Vector2d target_pos {missile_state.get_target(true_state)};
        Vector2d a_c {
            std::clamp(0.0, -a_max, a_max),
            std::clamp(-params.get_nav_ratio() * values.r_dot() * values.dot_lambda(),
                -a_max, a_max)
        };

        sensor.update_values(true_state, a_c, params);
        missile_state.update_state(sensor, h);

        target_state.update_state(target_pos, h);
        Vector2d a_target = target_accel(t, params.get_amax("target"));

        true_state.update_state(a_c, params, a_target);
        values.update_values(missile_state, target_state);


        results.push_back(Result_Sample{
            t,
            missile_state,
            true_state,
            t_go
            });
    }

    write_data(results);
}

