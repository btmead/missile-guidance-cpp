# Missile Guidance Simulator

An educational C++ simulator for exploring two-dimensional missile guidance and interception geometry. The project currently models a linear proportional-navigation engagement, using scenario data loaded from a TOML file and a fourth-order Runge-Kutta (RK4) integrator.

This is a learning and estimation project. It is not intended for operational use, formal safety certification, or verified AUTOSAR compliance.

## Current Status

The simulator currently:

- imports missile, target, and simulation parameters from `parameters.toml`;
- converts speeds and heading angles into two-dimensional position and velocity states;
- rotates the engagement into a linearized reference frame;
- calculates the closing-rate term and estimated time to intercept;
- forms a linear proportional-navigation state model; and
- advances that model using RK4 integration.

CSV result export is under development and is not yet part of the completed runtime path.

## Guidance Model

The linear state is defined as \(\mathbf{x} = [y,\dot{y}]^T\), where \(y\) is lateral separation and \(\dot{y}\) is relative lateral velocity.

The current proportional-navigation model uses \(\dot{\mathbf{x}} = A\mathbf{x}\), with \(A = \begin{bmatrix}0 & 1 \\ -N/t_{go}^{2} & -N/t_{go}\end{bmatrix}\), where \(N\) is the navigation ratio and \(t_{go}\) is the estimated time remaining.

The numerical solution is advanced at the configured time step \(h\) using a fourth-order Runge-Kutta method.

## Requirements

- CMake 4.2 or newer
- A C++17-compatible compiler
- Git and an internet connection during the initial CMake configuration

CMake downloads the following dependencies automatically:

- [toml++](https://github.com/marzer/tomlplusplus) v3.4.0 for configuration parsing
- [Eigen](https://gitlab.com/libeigen/eigen) for vectors and matrices

The Eigen dependency is not currently pinned to a specific release, so fully reproducible builds are not yet guaranteed.

## Build

From the project root:

```powershell
cmake -S . -B build
cmake --build build
```

CMake copies `parameters.toml` beside the executable after a successful build.

## Configure a Scenario

Edit `parameters.toml` before building or running the simulator:

```toml
[metadata]
parameter_ID = "P001 R01"

[parameters]
nav_ratio = 3
missile_vmax = 1000
target_vmax = 700
missile_amax = 30
target_amax = 7
h = 0.01

[missile_state]
x = 300
y = 300
theta = 30

[target_state]
x = 800
y = 900
theta = 46
```

The heading values `theta` are entered in degrees and converted to radians during import. The code does not yet attach explicit physical units to position, speed, acceleration, or time, so each scenario must use one internally consistent unit system.

The maximum-acceleration values are imported but are not yet applied by the linear guidance model.

## Run

Run the executable from the directory that contains both the executable and its copied `parameters.toml` file.

For a single-configuration build on Windows:

```powershell
Set-Location build
.\guidance_sim_cpp.exe
```

For a multi-configuration generator, the executable may instead be placed in a configuration subdirectory such as `build\Debug`. If so, ensure `parameters.toml` is in that same directory before running it.

The program reports invalid engagement inputs to standard error. A successful run currently completes without producing a user-facing results file.

## Project Structure

- `main.cpp` — program entry point and scenario setup
- `data_import.cpp` — TOML parameter and state import
- `maths.cpp` — coordinate rotation and RK4 calculations
- `linear_guidance.cpp` — proportional-navigation model and simulation loop
- `data_export.cpp` — work-in-progress CSV export
- `variable_types.h` — shared state, parameter, and result structures
- `parameters.toml` — example engagement configuration
- `CMakeLists.txt` — build configuration and dependencies

## Development Notes

The project uses the C++ Core Guidelines as its main modern C++ reference, ROS 2 conventions where appropriate for robotics-oriented style, and selected AUTOSAR C++14 guidance for predictable and defensive code. These are development references, not a claim of standards certification.

Useful next milestones include completing and testing CSV output, validating every imported parameter before use, guarding singular values as \(t_{go}\) approaches zero, pinning Eigen to a known version, and adding automated tests for the geometry and integration routines.
