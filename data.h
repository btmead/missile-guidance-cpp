//
// Created by benme on 25/08/2026.
//

#ifndef GUIDANCE_SIM_CPP_DATA_H
#define GUIDANCE_SIM_CPP_DATA_H

#include <string_view>
#include "variable_types.h"

Parameters get_parameters(std::string_view);

State import_state(std::string_view, std::string_view, const double);

std::string get_name(std::string_view);

void write_data(const std::vector<Result_Sample>&);

#endif //GUIDANCE_SIM_CPP_DATA_H
