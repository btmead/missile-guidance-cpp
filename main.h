//
// Created by benme on 19/08/2026.
//

#ifndef GUIDANCE_SIM_CPP_MAIN_H
#define GUIDANCE_SIM_CPP_MAIN_H
#include <string_view>
#include <ostream>

struct Matrix2D {
    double m00 {0.0};
    double m01 {0.0};
    double m10 {0.0};
    double m11 {0.0};
};

struct Vector2D {
    double x {0.0};
    double y {0.0};

    Vector2D operator-(const Vector2D & rhs) const {
        return Vector2D{x - rhs.x, y-rhs.y};
    };
    double dot(const Vector2D&);
    Vector2D scalar(const double) const;

};

struct State {
    Vector2D pos;
    Vector2D vel;


};


struct LinearState {
    double y    {0.0};
    double yd   {0.0};
    double t_go {1e-6};
};

struct Parameters {
    double nav_ratio {0.0};
    double missile_vmax {0.0};
    double target_vmax {0.0};
    double missile_amax {0.0};
    double target_amax {0.0};
};


void coord_rotation(State&, State&);

State coord_rotation(State&, double);

Vector2D matrixmultiply(const Matrix2D&, const Vector2D&);

Matrix2D rotationmatrix(double);

double hypot(const Vector2D&);

Parameters get_parameters(std::string_view);

State import_state(std::string_view, std::string_view, const double);

std::ostream& operator << (std::ostream&, State);

std::ostream& operator << (std::ostream&, Matrix2D);

#endif //GUIDANCE_SIM_CPP_MAIN_H
