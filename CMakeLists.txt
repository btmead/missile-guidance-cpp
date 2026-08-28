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

FetchContent_Declare(
        Eigen3
        GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)


FetchContent_MakeAvailable(tomlplusplus)
FetchContent_MakeAvailable(Eigen3)
FetchContent_MakeAvailable(googletest)


add_executable(guidance_sim_cpp
        main.cpp
        main.h
        maths.cpp
        maths.h
        data_import.cpp
        guidance.cpp
        guidance.h
        data_export.cpp
        data.h
        State.cpp
        State.h
        Parameters.cpp
        Parameters.h
        TrueState.cpp
        TrueState.h
        GuidanceValues.cpp
        GuidanceValues.h
        IMU.cpp
        IMU.h
        target.cpp
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
        Eigen3::Eigen
)


