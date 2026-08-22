cmake_minimum_required(VERSION 4.2)
project(
        guidance_sim_cpp
        LANGUAGES CXX
)

include(FetchContent)

FetchContent_Declare(
        tomlplusplus
        GIT_REPOSITORY https://github.com/marzer/tomlplusplus
        GIT_TAG v3.4.0
)

FetchContent_MakeAvailable(tomlplusplus)


add_executable(guidance_sim_cpp
        main.cpp
        main.h
        maths.cpp
        data_import.cpp
        linear_guidance.cpp
)

add_custom_command(
        TARGET guidance_sim_cpp
        POST_BUILD
        COMMAND
        ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/parameters.toml"
        "$<TARGET_FILE_DIR:guidance_sim_cpp>/parameters.toml"
)

target_compile_features(
        guidance_sim_cpp
        PRIVATE
        cxx_std_17
)

target_link_libraries(
        guidance_sim_cpp
        PRIVATE
        tomlplusplus::tomlplusplus
)


