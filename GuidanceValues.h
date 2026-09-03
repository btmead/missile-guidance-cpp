//
// Created by benme on 28/08/2026.
//

#ifndef GUIDANCE_SIM_CPP_GUIDANCE_VALUES_H
#define GUIDANCE_SIM_CPP_GUIDANCE_VALUES_H

#include <Eigen/Dense>
#include "State.h"

using namespace Eigen;

class GuidanceValues {
private:
    Vector2d m_r;
    Vector2d m_v;

public:
    GuidanceValues ();
    GuidanceValues (const State&, const State&);
    double r_dot ();
    double dot_lambda ();
    double t_final ();
    Vector2d v_rel ();
    void update_values(const State& missile, const State &target);
};


#endif //GUIDANCE_SIM_CPP_GUIDANCE_VALUES_H
