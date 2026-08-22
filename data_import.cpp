//
// Created by benme on 20/08/2026.
//

#include "main.h"
#include <toml++/toml.hpp>
#include <iostream>
#include <cmath>

Parameters get_parameters(std::string_view name) {
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

        return Parameters {
            nav_ratio.value(),
            missile_vmax.value(),
            target_vmax.value(),
            missile_amax.value(),
            target_amax.value(),
            h.value()
        };
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

State import_state(std::string_view name, std::string_view type, const double vmax) {
    try {
        const toml::table parameters = toml::parse_file(name);

        const auto xpos =
            parameters[type]["x"].value<double>();

        const auto ypos =
            parameters[type]["y"].value<double>();

        auto angle =
            parameters[type]["theta"].value<double>();
        

        if (!xpos || !ypos || !angle) {
            throw std::runtime_error{
                "Parameters.toml contain missing or incorrectly typed values"
            };
        }

        *angle = *angle * (M_PI /180);

        double xvel {vmax * std::cos(*angle)};
        double yvel {vmax * std::sin(*angle)};

        return State {
            {*xpos, *ypos},
            {xvel, yvel}
        };
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

