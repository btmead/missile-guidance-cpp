//
// Created by benme on 19/08/2026.
//

#ifndef GUIDANCE_SIM_CPP_MAIN_H
#define GUIDANCE_SIM_CPP_MAIN_H
#include <string_view>
#include <ostream>
#include <Eigen/Dense>
#include "State.h"



Eigen::Vector2d state_derivative (const Eigen::Vector2d&, const double, const double);

Eigen::Vector2d rk4_derivative (const Eigen::Vector2d&, const double, const double, const double);

Eigen::Vector2d target_accel (const double, const double);

struct Result_Sample {
    double time;
    State state;
    double t_go;
};
#endif //GUIDANCE_SIM_CPP_MAIN_H
