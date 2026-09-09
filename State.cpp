//
// Created by benme on 28/08/2026.
//

#include "maths.h"
#include "State.h"
#include "TrueState.h"
#include "IMU.h"
#include <Eigen/Dense>

using namespace Eigen;

State::State (const Vector2d& pos, const Vector2d& vel, const Vector2d& acc, double gamma) {
    m_pos = pos;
    m_vel = vel;
    m_acc = acc;
    m_gamma = gamma;
}

void State::coord_rotation(double angle) {
    m_pos = rotation_matrix(angle) * m_pos;
    m_vel = rotation_matrix(angle) * m_vel;
}


Vector2d State::target_pos_N(const TrueState & tstate) const{
    //Rotated by negative because it is rotated from normal to missile
    Vector2d relative_pos_N {rotation_matrix(-tstate.missile_angle()) * tstate.get_rel_pos()};
    return relative_pos_N;
}

Vector2d State::get_target(const TrueState & state) const{
    //Rotated by positive because it is from body to normal
    return rotation_matrix(m_gamma) * target_pos_N(state) + m_pos;
}

Vector2d State::get_pos() const{
    return m_pos;
}

Vector2d State::get_vel() const {
    return m_vel;
}

Vector2d State::get_accel () const {
    return m_acc;
}

void State::update_state(IMU& IMU, const double h) {
    Vector2d acc {rotation_matrix(m_gamma) * IMU.get_acc()};
    m_acc = acc;
    m_vel += h * m_acc;
    m_pos += h * m_vel + 0.5 * std::pow(h,2) * m_acc;
    m_gamma += h * IMU.get_omega();
}

void State::update_state(const Vector2d & pos, const double h, const Vector2d & v_rel) {
    Vector2d vel {((pos - m_pos) / h)};
    m_pos = pos;
    m_acc = (vel - m_vel) / h;
    m_vel = vel;
    m_gamma += h * (m_acc.y() / m_vel.norm());
}
