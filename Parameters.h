//
// Created by benme on 25/08/2026.
//

#ifndef GUIDANCE_SIM_CPP_VARIABLE_TYPES_H
#define GUIDANCE_SIM_CPP_VARIABLE_TYPES_H

#include <Eigen/Dense>
#include <iostream>
#include <toml++/toml.hpp>

class Parameters {
private:
    double m_nav_ratio;
    double m_missile_vmax;
    double m_target_vmax;
    double m_missile_amax;
    double m_target_amax;
    double m_h;

public:
    Parameters(const std::string_view);
    double get_h () const;
    double get_vmax (const std::string_view) const;
    double get_amax (const std::string_view) const;
};

struct Result_Sample {
    double time;
    Eigen::Vector2d state;
    double acceleration;
    double t_go;
};

#endif //GUIDANCE_SIM_CPP_VARIABLE_TYPES_H
