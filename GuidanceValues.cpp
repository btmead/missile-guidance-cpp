//
// Created by benme on 28/08/2026.
//

#include "GuidanceValues.h"
#include "State.h"
#include <Eigen/Dense>

using namespace Eigen;

GuidanceValues::GuidanceValues() {
    throw std::runtime_error("Cannot have 0 values for division by r");
}

GuidanceValues::GuidanceValues(const State & missile, const State & target) {
    m_r = target.get_pos() - missile.get_pos();
    m_v = target.get_vel() - missile.get_vel();
}

double GuidanceValues::r_dot() {
    return m_v.dot(m_r) / m_r.norm();
}

double GuidanceValues::dot_lambda() {
    return (m_r.x() * m_v.y() - m_r.y() * m_v.x()) / m_r.squaredNorm();
}

double GuidanceValues::t_final() {
    return -1 / (m_v.dot(m_r) / m_r.squaredNorm());
}

Vector2d GuidanceValues::v_rel() {
    return m_v;
}

void GuidanceValues::update_values(const State &missile, const State &target) {
    //Add checks that r is not 0 and that closing velocity is not negative
    m_r = target.get_pos() - missile.get_pos();
    m_v = target.get_vel() - missile.get_vel();
}
