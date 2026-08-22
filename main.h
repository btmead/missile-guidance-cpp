//
// Created by benme on 19/08/2026.
//

#ifndef GUIDANCE_SIM_CPP_MAIN_H
#define GUIDANCE_SIM_CPP_MAIN_H
#include <string_view>

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

    Vector2D operator+ (const Vector2D& rhs) const {
        return Vector2D{x + rhs.x, y + rhs.y};
    }

    double dot(const Vector2D&);

    Vector2D scalar(const double) const;
};

struct Matrix3D {
    double m00 {0.0};
    double m01 {0.0};
    double m02 {0.0};
    double m10 {0.0};
    double m11 {0.0};
    double m12 {0.0};
    double m20 {0.0};
    double m21 {0.0};
    double m22 {0.0};
};

struct Vector3D {
    double x {0.0};
    double y {0.0};
    double z {0.0};

    Vector3D operator-(const Vector3D & rhs) const {
        return Vector3D{x - rhs.x, y - rhs.y, z - rhs.z};
    };

    Vector3D operator+ (const Vector3D& rhs) const {
        return Vector3D{x + rhs.x, y + rhs.y, z + rhs.z};
    }

    double dot(const Vector3D&);

    Vector3D scalar(const double) const;
};

struct State {
    Vector2D pos;
    Vector2D vel;


};


struct LinearState {
    Vector2D vec;
    double t_go {1e-6};

    LinearState operator+ (const LinearState& rhs) const {
        return LinearState {vec + rhs.vec, t_go};
    }

    LinearState operator* (const double& scalar) const {
        return LinearState { vec.scalar(scalar), t_go};
    }
};

struct Parameters {
    double nav_ratio {0.0};
    double missile_vmax {0.0};
    double target_vmax {0.0};
    double missile_amax {0.0};
    double target_amax {0.0};
    double h {0.0};
};


void coord_rotation(State&, State&);

State coord_rotation(State&, const double);

Vector2D matrixmultiply(const Matrix2D&, const Vector2D&);

double v_closing (const State&, const State&);

Matrix2D rotationmatrix(const double);

double hypot(const Vector2D&);

Parameters get_parameters(std::string_view);

State import_state(std::string_view, std::string_view, const double);

Matrix2D get_propnav (const double, const double);

LinearState state_derivative (const LinearState&, const double, const double);

LinearState rk4_derivative (const LinearState&, const double, const double);

LinearState to_linear (const State&, const State&);

std::ostream& operator << (std::ostream&, State);

std::ostream& operator << (std::ostream&, Matrix2D);

std::ostream& operator<< (std::ostream&, LinearState);

void linear_guidance (const State&, const State&, const Parameters, const double);
#endif //GUIDANCE_SIM_CPP_MAIN_H
