//
// Created by benme on 28/08/2026.
//

#ifndef GUIDANCE_SIM_CPP_STATE_H
#define GUIDANCE_SIM_CPP_STATE_H

#include "TrueState.h"
#include <Eigen/Dense>

using namespace Eigen;

class State {
private:
    Vector2d m_pos;
    Vector2d m_vel;
    Vector2d m_acc;
    double m_gamma;

    Vector2d target_pos_N(const TrueState&) const;

public:
    State (const Vector2d &, const Vector2d &, const Vector2d &, const double);
    void coord_rotation (double);
    Vector2d get_target (const TrueState&) const;
    Vector2d get_pos () const;
    Vector2d get_vel () const;
    double omega ();

};




#endif //GUIDANCE_SIM_CPP_STATE_H
