//
// Created by benme on 28/08/2026.
//

#include "Parameters.h"



Parameters::Parameters (const std::string_view name) {
    try {
        const toml::table parameters = toml::parse_file(name);

        const auto nav_ratio =
            parameters["parameters"]["nav_ratio"].value<double>();

        const auto missile_vmax =
            parameters["parameters"]["missile_vmax"].value<double>();

        const auto target_vmax =
            parameters["parameters"]["target_vmax"].value<double>();

        const auto missile_amax =
            parameters["parameters"]["missile_amax"].value<double>();

        const auto target_amax =
            parameters["parameters"]["target_amax"].value<double>();

        const auto h =
            parameters["parameters"]["h"].value<double>();

        const auto tau =
            parameters["parameters"]["h"].value<double>();

        m_nav_ratio = nav_ratio.value();
        m_missile_vmax = missile_vmax.value();
        m_target_vmax = target_vmax.value();
        m_missile_amax = missile_amax.value();
        m_target_amax = target_amax.value();
        m_h = h.value();
        m_tau = tau.value();
    }
    catch (const toml::parse_error& error) {
        std::cerr << "Could not parse " << name << " file: " << error << std::endl;
        throw;
    }
    catch (const std::exception& error) {
        std::cerr << error.what() << std::endl;
        throw;
    }
}

double Parameters::get_h() const {
    return m_h;
}

double Parameters::get_vmax(const std::string_view type) const {
    if (type == "missile") {
        return m_missile_vmax;
    }
    if (type == "target") {
        return m_target_vmax;
    }
    throw std::runtime_error("Invalid argument");
}

double Parameters::get_amax(const std::string_view type) const {
    if (type == "missile") {
        return m_missile_amax;
    }
    if (type == "target") {
        return m_target_amax;
    }
    throw std::runtime_error("Invalid argument");
}

double Parameters::get_nav_ratio() const {
    return m_nav_ratio;
}

double Parameters::get_tau() const {
    return m_tau;
}

