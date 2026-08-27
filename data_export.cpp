//
// Created by benme on 25/08/2026.
//

#include "data.h"
#include <iostream>
#include <fstream>
#include <iterator>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <filesystem>


namespace {
    std::string make_timestamp() {
        const auto now {std::chrono::system_clock::now()};
        const std::time_t current_time{
            std::chrono::system_clock::to_time_t(now)};

        std::tm utc_time{};

        if (::gmtime_s(&utc_time, &current_time) != 0) {
            throw std::runtime_error{"Could not create UTC timestamp"};
        }

        std::ostringstream timestamp;
        timestamp << std::put_time(
            &utc_time,
            "%Y%m%dT%H%M%SZ");

        return timestamp.str();

    };
} //namespace

void write_data (const std::vector<Result_Sample>& results) {
    const std::filesystem::path output_directory{"Results"};
    std::filesystem::create_directories(output_directory);

    const std:: string filename = get_name("parameters.toml");
    const std::string output_name {filename + "-" + make_timestamp() + ".csv"};

    const std::filesystem::path file_path {output_directory / output_name};
    std::ofstream output_file (file_path);

    if (!output_file) {
        throw std::runtime_error{
        "Could not open output file: " + file_path.string()};
    }

    output_file
    << "time (s), "
    << "lateral displacement (m), "
    << "lateral velocity (m/s), "
    << "lateral acceleration (m/s^2), "
    << "time_to_go (s) \n";

    output_file << std::setprecision(17);

    for (const Result_Sample &result : results) {
        output_file
        << result.time << ", "
        << result.state.x() << ", "
        << result.state.y() << ", "
        << result.acceleration << ", "
        << result.t_go << "\n";
    }

    if (!output_file) {
        throw std::runtime_error{
            "Failed while writing output file: " +
            file_path.string()
        };
    }
}

