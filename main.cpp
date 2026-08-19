//
// Created by benme on 19/08/2026.
//

#include "main.h"
#include <iostream>
#include <cmath>


void coord_rotation(State &mstate, State &tstate) {
    double vm {hypot(mstate.vel)};
    double vt {hypot(tstate.vel)};
    Vector2D r {tstate.pos - mstate.pos};
    double lambda { std::atan(r.y / r.x) };
    double beta { std::atan(tstate.pos.y / tstate.pos.x) };
    double lead { std:: asin((vt / vm) * std::sin(beta+lambda))};
    mstate = coord_rotation(mstate, lambda + lead);
    tstate = coord_rotation(tstate, lambda + lead);
}

std::ostream& operator<< (std::ostream& out, State state) {
    out << "Coordinates: (" << state.pos.x << "," << state.pos.y << ")" << std::endl <<
        "Velocity: (" << state.vel.x << "," << state.vel.y << ") \n";

    return out;
}


int main() {

    double n_c {};
    State missile_state {300, 400, 360, 1000};
    State target_state {1000, 1500, 360, 800};

    std::cout << "Initial state: \n" << missile_state;
    coord_rotation(missile_state, target_state);
    std::cout << "Final state: \n" << missile_state;

    return 0;
}

