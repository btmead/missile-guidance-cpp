//
// Created by benme on 28/08/2026.
//

#include "IMU.h"

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

void IMU::update_values(const Vector2d & a_dot, const Vector2d & v, const double h) {
    m_acc += h * a_dot;
    m_omega = m_acc.y() / v.norm();
}
