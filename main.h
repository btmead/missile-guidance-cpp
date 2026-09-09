//
// Created by benme on 19/08/2026.
//

#ifndef GUIDANCE_SIM_CPP_MAIN_H
#define GUIDANCE_SIM_CPP_MAIN_H
#include <Eigen/Dense>
#include "State.h"
#include "TrueState.h"



Eigen::Vector2d state_derivative (const Eigen::Vector2d&, const double, const double);

Eigen::Vector2d rk4_derivative (const Eigen::Vector2d&, const double, const double, const double);

Eigen::Vector2d target_accel (const double, const double);

struct Result_Sample {
    double time;
    State mstate;
    TrueState truestate;
    double t_go;
};

void plotting(std::string);

#endif //GUIDANCE_SIM_CPP_MAIN_H
