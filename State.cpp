//
// Created by benme on 28/08/2026.
//

#include "maths.h"
#include "State.h"
#include "TrueState.h"
#include <Eigen/Dense>

using namespace Eigen;

State::State (const Vector2d& pos, const Vector2d& vel, const Vector2d& acc, double gamma) {
    m_pos = pos;
    m_vel = vel;
    m_acc = acc;
    m_gamma = gamma;
}

void State::coord_rotation(double angle) {
    m_pos = (rotation_matrix(angle) * m_pos);
    m_vel = (rotation_matrix(angle) * m_vel);
}


Vector2d State::target_pos_N(const TrueState & state) const{

    Vector2d relative_pos_N {rotation_matrix(state.missile_angle()) * state.get_rel_pos()};
    return relative_pos_N;
}

Vector2d State::get_target(const TrueState & state) const{
    return rotation_matrix(m_gamma) * target_pos_N(state) + m_pos;
}

Vector2d State::get_pos() const{
    return m_pos;
}

Vector2d State::get_vel() const {
    return m_vel;
}

double State::omega() {  //NEEDS FIXING
    return m_acc.y() / m_vel.y();
}
