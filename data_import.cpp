//
// Created by benme on 20/08/2026.
//

#include "data.h"
#include <toml++/toml.hpp>
#include <iostream>


std::string get_name(const std::string_view name) {
    try {
        const toml::table metadata = toml::parse_file(name);

        const auto ID =
            metadata["metadata"]["parameter_ID"].value<std::string>();

        if (!ID) {
            throw std::runtime_error (
                "Parameter ID could not be found or incorrect values"
                );
        }

        return *ID;
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

