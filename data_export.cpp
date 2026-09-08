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
    << "time,"
    << "estimated_missile_position_x,"
    << "estimated_missile_position_y,"
    << "estimated_missile_velocity_x,"
    << "estimated_missile_velocity_y,"
    << "estimated_missile_acceleration_x,"
    << "estimated_missile_acceleration_y,"
    << "true_missile_position_x,"
    << "true_missile_position_y,"
    << "true_missile_velocity_x,"
    << "true_missile_velocity_y,"
    << "true_missile_acceleration_x,"
    << "true_missile_acceleration_y,"
    << "true_target_position_x,"
    << "true_target_position_y,"
    << "true_target_velocity_x,"
    << "true_target_velocity_y,"
    << "true_target_acceleration_x,"
    << "true_target_acceleration_y,"
    << "time_to_go\n";

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

