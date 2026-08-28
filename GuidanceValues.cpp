//
// Created by benme on 28/08/2026.
//

#include "GuidanceValues.h"
#include "State.h"
#include <Eigen/Dense>

using namespace Eigen;

GuidanceValues::GuidanceValues() {
    m_r = {0.0, 0.0};
    m_v = {0.0, 0.0};
}

GuidanceValues::GuidanceValues(const State & missile, const State & target) {
    m_r = target.get_pos() - missile.get_pos();
    m_v = target.get_vel() - missile.get_vel();
}

double GuidanceValues::r_dot() {
    return m_v.dot(m_r) / m_r.squaredNorm();
}

double GuidanceValues::dot_lambda() {
    return (m_r.x() * m_v.y() - m_r.y() * m_v.x()) / m_r.squaredNorm();
}

double GuidanceValues::t_final() {
    return m_v.dot(m_r) / m_r.norm();
}
