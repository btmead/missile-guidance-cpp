//
// Created by benme on 28/08/2026.
//

#include "TrueState.h"
#include <Eigen/Dense>

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

        if (*xmpos == 0 || *ympos == 0) {
            throw std::runtime_error{"Incorrect missile initial position. Should be (0,0)"};
        }

        *mangle = *mangle * (M_PI /180);

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

