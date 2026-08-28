//
// Created by benme on 25/08/2026.
//

#include "data.h"
#include "main.h"
#include <iostream>
#include <fstream>
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
    << "estimated missile position x (m), "
    << "estimated missile position y (m), "
    << "estimated missile velocity x (m/s), "
    << "estimated missile velocity y (m/s), "
    << "estimated missile acceleration x (m/s^2), "
    << "estimated missile acceleration y (m/s^2), "
    << "true missile position x (m), "
    << "true missile position y (m), "
    << "true missile velocity x (m/s), "
    << "true missile velocity y (m/s), "
    << "true missile acceleration x (m/s^2), "
    << "true missile acceleration y (m/s^2), "
    << "true target position x (m), "
    << "true target position y (m), "
    << "true target velocity x (m/s), "
    << "true target velocity y (m/s), "
    << "true target acceleration x (m/s^2), "
    << "true target acceleration y (m/s^2), "
    << "time_to_go (s) \n";

    output_file << std::setprecision(17);

    for (const Result_Sample &result : results) {
        State true_missile {result.truestate.true_missile_state()};
        State true_target {result.truestate.true_target_state()};

        output_file
        << result.time << ", "
        << result.mstate.get_pos().x() << ", "
        << result.mstate.get_pos().y() << ", "
        << result.mstate.get_vel().x() << ", "
        << result.mstate.get_vel().y() << ", "
        << result.mstate.get_accel().x() << ", "
        << result.mstate.get_accel().y() << ", "
        << true_missile.get_pos().x() << ", "
        << true_missile.get_pos().y() << ", "
        << true_missile.get_vel().x() << ", "
        << true_missile.get_vel().y() << ", "
        << true_missile.get_accel().x() << ", "
        << true_missile.get_accel().y() << ", "
        << true_target.get_pos().x() << ", "
        << true_target.get_pos().y() << ", "
        << true_target.get_vel().x() << ", "
        << true_target.get_vel().y() << ", "
        << true_target.get_accel().x() << ", "
        << true_target.get_accel().y() << ", "
        << result.t_go << "\n";
    }

    if (!output_file) {
        throw std::runtime_error{
            "Failed while writing output file: " +
            file_path.string()
        };
    }
}

