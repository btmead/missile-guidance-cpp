//
// Created by benme on 28/08/2026.
//

#include "TrueState.h"
#include "Parameters.h"
#include "State.h"
#include "maths.h"
#include <Eigen/Dense>
#include <numbers>

using namespace Eigen;

TrueState::TrueState(const std::string_view file, const Parameters& params) {
    try {
        double missile_vmax {params.get_vmax("missile")};
        double target_vmax {params.get_vmax("target")};
        const toml::table parameters = toml::parse_file(file);

        const auto xmpos =
            parameters["missile"]["x"].value<double>();

        const auto ympos =
            parameters["missile"]["y"].value<double>();

        auto mangle =
            parameters["missile"]["theta"].value<double>();
        
        const auto xtpos =
            parameters["target"]["x"].value<double>();

        const auto ytpos =
            parameters["target"]["y"].value<double>();

        auto tangle =
            parameters["target"]["theta"].value<double>();

        if (xmpos.value() != 0 || ympos.value() != 0) {
            throw std::runtime_error{"Incorrect missile initial position. Should be (0,0)"};
        }

        mangle = mangle.value() * (std::numbers::pi_v<double> / 180);
        tangle = tangle.value() * (std::numbers::pi_v<double> / 180);

        double xmvel {missile_vmax * std::cos(*mangle)};
        double ymvel {missile_vmax * std::sin(*mangle)};

        double xtvel {target_vmax * std::cos(*tangle)};
        double ytvel {target_vmax * std::sin(*tangle)};

        m_mpos.x() = xmpos.value();
        m_mpos.y() = ympos.value();
        m_mvel.x() = xmvel;
        m_mvel.y() = ymvel;
        m_macc = {0,0};
        m_mgamma = mangle.value();
        
        m_tpos.x() = xtpos.value();
        m_tpos.y() = ytpos.value();
        m_tvel.x() = xtvel;
        m_tvel.y() = ytvel;
        m_tacc = {0,0};
        m_tgamma = tangle.value();
    }
    catch (const toml::parse_error& error) {
        std::cerr << "Could not parse " << file << " file: " << error << std::endl;
        throw;
    }
    catch (const std::exception& error) {
        std::cerr << error.what() << std::endl;
        throw;
    }
}

Vector2d TrueState::get_rel_pos() const{
    return m_tpos - m_mpos;
}

double TrueState::missile_angle() const {
    return m_mgamma;
}

State TrueState::true_missile_state() const{
    State state (m_mpos, m_mvel, m_macc, m_mgamma);
    return state;
}

State TrueState::true_target_state() const{
    State state (m_tpos, m_tvel, m_tacc, m_tgamma);
    return state;
}

Vector2d TrueState::get_m_accel() const{
    return m_macc;
}

Vector2d TrueState::get_m_vel() const {
    return m_mvel;
}

void TrueState::update_state(Vector2d & a_c , const Parameters & params, const Vector2d & target_accel) {
    double h {params.get_h()};
    double tau {params.get_tau()};

    a_c = rotation_matrix(m_mgamma) * a_c;
    Vector2d a_dot {(a_c - m_macc) / tau};
    m_mpos += h * m_mvel + 0.5 * std::pow(h,2) * m_macc;
    m_mvel += h * m_macc;
    m_mgamma += h * ((m_macc.y() * m_mvel.x() - m_macc.x() * m_mvel.y()) / m_mvel.squaredNorm());
    m_macc += h * a_dot;

    m_tpos += h * m_tvel + 0.5 * std::pow(h,2) * m_tacc;
    m_tvel += h * m_tacc;
    m_tgamma += h * ((m_tacc.x() * m_tvel.y() - m_tacc.y() * m_tvel.x()) / m_tvel.squaredNorm());
    m_tacc = target_accel;
}

