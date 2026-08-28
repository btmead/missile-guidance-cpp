//
// Created by benme on 28/08/2026.
//

#ifndef GUIDANCE_SIM_CPP_TRUESTATE_H
#define GUIDANCE_SIM_CPP_TRUESTATE_H

#include <Eigen/Dense>
#include <string_view>

class State;
class Parameters;

using namespace Eigen;

class TrueState {
private:
    Vector2d m_mpos;
    Vector2d m_mvel;
    Vector2d m_macc;
    double m_mgamma;

    Vector2d m_tpos;
    Vector2d m_tvel;
    Vector2d m_tacc;
    double m_tgamma;

public:
    TrueState(std::string_view, const Parameters &);
    Vector2d get_rel_pos() const;
    double missile_angle () const;
    State true_missile_state () const;
    State true_target_state () const;
    Vector2d get_m_accel() const;
    Vector2d get_m_vel() const;
    void update_state (Vector2d &, const Parameters &, const Vector2d &);
};


#endif //GUIDANCE_SIM_CPP_TRUESTATE_H
