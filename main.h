//
// Created by benme on 19/08/2026.
//

#ifndef GUIDANCE_SIM_CPP_MAIN_H
#define GUIDANCE_SIM_CPP_MAIN_H
#include <string_view>
#include <ostream>
#include <Eigen/Dense>



double v_closing (const State&, const State&);

Eigen::Vector2d state_derivative (const Eigen::Vector2d&, const double, const double);

Eigen::Vector2d rk4_derivative (const Eigen::Vector2d&, const double, const double, const double);


std::ostream& operator << (std::ostream&, State);

std::vector<Result_Sample> linear_guidance (const State&, const State&, const Parameters&, const double);

#endif //GUIDANCE_SIM_CPP_MAIN_H
