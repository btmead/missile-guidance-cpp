//
// Created by benme on 25/08/2026.
//

#ifndef GUIDANCE_SIM_CPP_VARIABLE_TYPES_H
#define GUIDANCE_SIM_CPP_VARIABLE_TYPES_H

#include <Eigen/Dense>

struct State {
    Eigen::Vector2d pos;
    Eigen::Vector2d vel;


};


struct Parameters {
    double nav_ratio {0.0};
    double missile_vmax {0.0};
    double target_vmax {0.0};
    double missile_amax {0.0};
    double target_amax {0.0};
    double h {0.0};
};

struct Result_Sample {
    double time;
    Eigen::Vector2d state;
    double acceleration;
    double t_go;
};

#endif //GUIDANCE_SIM_CPP_VARIABLE_TYPES_H
