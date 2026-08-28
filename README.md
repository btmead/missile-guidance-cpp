# Missile Guidance Simulator

An educational C++ simulator for exploring two-dimensional missile guidance,
coordinate frames, vehicle dynamics, state estimation, and interception geometry.

The current development branch is refactoring the original linear model into a
nonlinear simulation with separate truth and estimated states. It is a learning
project, not an operational guidance system, safety-certified product, or claim of
AUTOSAR, MISRA, CERT, or ROS 2 compliance.

## Current Status

The intended runtime path:

1. loads scenario and model parameters from `parameters.toml`;
2. constructs a hidden `TrueState` for the missile and target;
3. maintains separate estimated `State` objects;
4. obtains body-frame acceleration and target-position information through the
   current simulated measurement paths;
5. calculates range rate, line-of-sight rate, and a pure proportional-navigation
   acceleration command;
6. propagates truth and estimated states at the configured timestep; and
7. writes timestamped CSV results to the `Results` directory.

This architecture is under active development. The circular header dependency has
been removed using forward declarations, both initial headings are converted to
radians, and CSV export now writes scalar state components. Numerical and
validation issues remain under [Known Limitations](#known-limitations), so the
output must not yet be treated as validated simulation evidence.

## Guidance Model

The relative position and velocity are defined as
\(\mathbf r=\mathbf p_T-\mathbf p_M\) and
\(\mathbf v_{rel}=\mathbf v_T-\mathbf v_M\).

The range rate is \(\dot r=(\mathbf r\cdot\mathbf v_{rel})/\|\mathbf r\|\),
with closing speed \(V_c=-\dot r\) for an approaching engagement. The Cartesian
line-of-sight rate is
\(\dot\lambda=(r_xv_{rel,y}-r_yv_{rel,x})/\|\mathbf r\|^2\).

The intended pure proportional-navigation command is
\(a_c=N V_c\dot\lambda=-N\dot r\dot\lambda\), applied along the missile body
lateral axis. The command is limited by the configured missile acceleration
ceiling.

The initial local time-to-go estimate is
\(t_{go}=\|\mathbf r\|/V_c=-\|\mathbf r\|/\dot r\). This is a local estimate
based on current radial closing speed, not a guaranteed intercept time.

## Coordinate Conventions

- inertial \(x\) points right and inertial \(y\) points up;
- headings are measured counter-clockwise from inertial positive \(x\);
- scenario headings are entered in degrees and should be converted to radians on
  import;
- angles are stored and passed to trigonometric functions in radians;
- `rotation_matrix(theta)` is the active counter-clockwise matrix
  \(R(\theta)\);
- body-to-inertial conversion uses \(R(+\gamma)\);
- inertial-to-body conversion uses \(R(-\gamma)=R(\gamma)^T\); and
- positions are translated to the required origin before they are rotated.

For a missile-centred observation, the transformations are
\(\mathbf r_B=R(-\gamma)(\mathbf p_T-\mathbf p_M)\) and
\(\mathbf p_T=\mathbf p_M+R(+\gamma)\mathbf r_B\).

## Dynamics and Measurement Model

`TrueState` stores the actual missile and target position, velocity, acceleration,
and heading used by the simulator. `State` stores the corresponding estimated
quantities available to the guidance path.

The missile acceleration response is intended to use the first-order lag
\(\dot{\mathbf a}=(\mathbf a_c-\mathbf a)/\tau\). The discrete implementation
advances the state at timestep \(h\).

`IMU` currently uses truth data to construct body-frame acceleration information.
The measurement boundary is still being refined; sensor noise, bias, quantisation,
and independent attitude measurement are not yet modelled.

## Requirements

- CMake 4.2 or newer
- A C++20-compatible compiler (the code uses `std::numbers::pi_v<double>`)
- Git and an internet connection during initial CMake configuration

CMake currently downloads:

- [toml++](https://github.com/marzer/tomlplusplus) v3.4.0;
- [Eigen](https://gitlab.com/libeigen/eigen.git); and
- [GoogleTest](https://github.com/google/googletest).

Eigen is not pinned to a specific revision, so builds are not yet fully
reproducible. GoogleTest is downloaded, but automated tests have not yet been
connected to the CMake target.

## Build

From the project root:

```powershell
cmake -S . -B build
cmake --build build
```

After a successful build, CMake copies `parameters.toml` beside the executable.

## Configure a Scenario

The current configuration structure is:

```toml
[metadata]
parameter_ID = "P001 R02"

[parameters]
nav_ratio = 3
missile_vmax = 1000
target_vmax = 700
missile_amax = 30
target_amax = 7
h = 0.01
tau = 1

[missile]
x = 0
y = 0
theta = 30

[target]
x = 8000
y = 4000
theta = 46
```

The intended units are metres, seconds, metres per second, and metres per second
squared. `theta` is supplied in degrees; all internal angles should use radians.
The missile is currently required to begin at inertial position \((0,0)\).

## Run and Results

Run the executable from the directory containing both the executable and its
copied `parameters.toml` file.

For a single-configuration Windows build:

```powershell
Set-Location build
.\guidance_sim_cpp.exe
```

A successful run creates `Results/<parameter ID>-<UTC timestamp>.csv`. Each data
row contains:

- time;
- estimated missile position \(x\) and \(y\);
- estimated missile velocity \(x\) and \(y\);
- estimated missile acceleration \(x\) and \(y\); and
- estimated time-to-go.

Truth state and target-estimate histories are not yet exported.

## Project Structure

- `main.cpp` — simulation setup and timestep loop
- `State.h/.cpp` — estimated vehicle state and target-position reconstruction
- `TrueState.h/.cpp` — hidden missile and target truth state
- `IMU.h/.cpp` — current body-frame acceleration measurement model
- `GuidanceValues.h/.cpp` — relative geometry and guidance quantities
- `Parameters.h/.cpp` — access to scenario parameters
- `maths.h/.cpp` — coordinate rotation and mathematical helpers
- `target.cpp` — target manoeuvre command
- `data_import.cpp` — metadata import
- `data_export.cpp` — timestamped CSV export
- `parameters.toml` — example scenario
- `CMakeLists.txt` — build configuration and dependencies

## Coding Guidance

The project uses these references as guidance, not as certification claims:

- the [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines)
  as the primary modern C++ design reference;
- the [SEI CERT C++ Coding Standard](https://www.sei.cmu.edu/library/sei-cert-c-and-c-coding-standards/)
  for defensive handling of undefined behaviour, invalid inputs, arithmetic, and
  resource safety;
- the [ROS 2 C++ style guidance](https://docs.ros.org/en/rolling/The-ROS2-Project/Contributing/Code-Style-Language-Versions.html)
  selectively for robotics-oriented consistency, while retaining this project's
  existing C++20 mode and local naming conventions; and
- [AUTOSAR C++14 guidance](https://www.autosar.org/fileadmin/standards/R19-03/AP/AUTOSAR_RS_CPP14Guidelines.pdf)
  only as an additional safety-oriented checklist.

For this project, consistency and automated enforcement are more valuable than
trying to follow several style guides simultaneously. The immediate policy is:

- use one naming and formatting style throughout the repository;
- keep interfaces small and make ownership, units, frames, and invariants explicit;
- avoid relying on transitive includes;
- validate required configuration before dereferencing or calculating with it;
- enable strong compiler warnings and fix warnings rather than suppressing them;
- use `clang-format` for mechanical formatting and `clang-tidy` for selected
  static checks; and
- add automated tests for geometry, dimensions, coordinate round trips, and state
  propagation before claiming numerical accuracy.

## Commenting Policy

Comments should explain information that the language and names cannot express.
Prefer comments that record:

- why an equation, approximation, or update order was selected;
- the reference frame, sign convention, and units expected by an interface;
- assumptions and invariants, such as non-zero range or positive timestep;
- the source of a non-obvious guidance or dynamics equation;
- why an apparently simpler implementation would be incorrect; and
- temporary limitations linked to a specific issue or next action.

Do not comment obvious operations, repeat a function name in prose, preserve dead
code in comments, or use a comment to compensate for an unclear name. Public
interfaces should document their contract where the meaning is not evident:
inputs, outputs, units, frames, mutation, failure conditions, and singular cases.

Equation comments should name every quantity whose meaning could be ambiguous.
In this simulator, `theta`, `gamma`, `lambda`, acceleration vectors, and relative
velocity must always identify their frame and sign convention. A short accurate
comment beside the equation is preferable to a long explanation that can drift
away from the implementation.

Comments must be updated in the same change as the behaviour they describe.
Obsolete code should be removed and recovered from Git history rather than kept
inside `#if 0` blocks or commented-out sections.

## Known Limitations

- the target heading-rate numerator currently has the opposite sign from
  \(\dot\gamma=(v_xa_y-v_ya_x)/\|\mathbf v\|^2\);
- the target finite-difference update needs an explicitly aligned initial sample;
- truth, measurement, and estimated-state update ordering needs one-step tests to
  confirm that each acceleration belongs to the intended instant;
- divisions by range, speed, timestep, and time constant need singularity guards;
- required TOML values are dereferenced before their presence and type are fully
  validated, and positive timestep, time constant, speed, and limits are not yet
  enforced;
- the exported time-to-go is an initial estimate followed by a countdown rather
  than a value recomputed from the current engagement geometry;
- truth-versus-estimate data are not yet exported; and
- automated geometry, dynamics, import, and CSV tests are still required.

The next dependable milestone is a clean, verified executable run followed by
unit tests for
\(R(+\theta)R(-\theta)=I\), norm preservation, known \(90^\circ\) rotations,
range rate, line-of-sight rate, time-to-go units, and one-step state propagation.
