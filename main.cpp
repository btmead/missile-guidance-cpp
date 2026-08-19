//
// Created by benme on 19/08/2026.
//

#include "main.h"
#include <iostream>
#include <cmath>


double coord_angle(const State &mstate, const State &tstate) {
    double vm {std::hypot(mstate.xd, mstate.yd)};
    double vt {std::hypot(tstate.xd, tstate.yd)};
    double lambda { std::atan(mstate.y / mstate.x) };
    double beta { std::atan(tstate.y / tstate.x) };
    double lead { std:: asin((vt / vm) * std::sin(beta+lambda))};
    return lambda + lead;
}

std::ostream& operator<< (std::ostream& out, State state) {
    out << "Coordinates: (" << state.x << "," << state.y << ")" << std::endl <<
        "Velocity: (" << state.xd << "," << state.yd << ") \n";

    return out;
}


int main() {

    double n_c {};
    State missile_state {300, 400, 360, 1000};
    State target_state {1000, 1500, 360, 800};

    std::cout << "Initial state: \n" << missile_state;

    double rotation_angle { coord_angle(missile_state, target_state)};
    missile_state = matrixmultiply(rotationmatrix(rotation_angle), missile_state);

    std::cout << "Final state: \n" << missile_state;

    return 0;
}

