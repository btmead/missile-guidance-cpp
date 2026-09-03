//
// Created by benme on 28/08/2026.
//

#include "TrueState.h"
#include "State.h"
#include "Parameters.h"
#include "IMU.h"
#include "maths.h"

IMU::IMU() {
    m_acc = {0.0, 0.0};
    m_omega = 0.0;
}

Vector2d IMU::get_acc() {
    return m_acc;
}

double IMU::get_omega() {
    return m_omega;
}

void IMU::update_values(const TrueState & state, const Vector2d & a_c, const Parameters& p) {
    double angle {state.missile_angle()};
    Vector2d acc { rotation_matrix(angle) * state.get_m_accel() };
    Vector2d vel {state.get_m_vel()};

    Vector2d a_dot {(a_c - acc) / p.get_tau()};
    m_acc += p.get_h() * a_dot;
    m_omega = m_acc.y() / vel.norm();
}
