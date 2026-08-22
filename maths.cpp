//
// Created by benme on 19/08/2026.
//

#include "main.h"
#include <cmath>
#include <numbers>


Vector2D matrixmultiply(const Matrix2D& matrix, const Vector2D& vector) {
    return {
        matrix.m00 * vector.x + matrix.m01 * vector.y,
        matrix.m10 * vector.x + matrix.m11 * vector.y,

    };
}

Vector3D matrixmultiply(const Matrix3D& matrix, const Vector3D& vector) {
    return {
        matrix.m00 * vector.x + matrix.m01 * vector.y + matrix.m02 * vector.z,
        matrix.m10 * vector.x + matrix.m11 * vector.y + matrix.m12 * vector.z,
        matrix.m20 * vector.x + matrix.m21 * vector.y + matrix.m22 * vector.z
    };
}

Matrix2D rotationmatrix(const double angle) {
    double cosine {std::cos(angle)};
    double sine {std::sin(angle)};

    return{
        cosine, sine,
        -sine, cosine
    };
}

double hypot (const Vector2D& vector) {
    return std::hypot(vector.x, vector.y);
}

State coord_rotation(State &state, const double angle) {
    state.pos = (matrixmultiply(rotationmatrix(angle), state.pos));
    state.vel = (matrixmultiply(rotationmatrix(angle), state.vel));
    return state;
}

double Vector2D::dot(const Vector2D & vector) {
    return x * vector.x + y * vector.y;
}

Vector2D Vector2D::scalar(const double scalar) const{
    return {scalar * x, scalar * y};
}

void coord_rotation(State &mstate, State &tstate) {
    double vm {hypot(mstate.vel)};
    double vt {hypot(tstate.vel)};
    Vector2D r {tstate.pos - mstate.pos};
    double lambda { std::atan2(r.y, r.x) };
    double beta { std::atan2(tstate.vel.y, tstate.vel.x) };
    double lead { std:: asin((vt / vm) * std::sin(lambda - beta))};
    mstate = coord_rotation(mstate, lambda+lead);
    tstate = coord_rotation(tstate, lambda+lead);
}

LinearState rk4_derivative (const LinearState& state, const double nav_ratio, const double h) {
    LinearState k1, k2, k3, k4;
    double t_go {state.t_go};

    k1 = state_derivative( state,                   nav_ratio,  t_go         );
    k2 = state_derivative( state + (k1 * (h/2)),    nav_ratio,  t_go + (h/2) );
    k3 = state_derivative( state + (k2 * (h/2)),    nav_ratio,  t_go + (h/2) );
    k4 = state_derivative( state + (k3 * h),        nav_ratio,  t_go + (h/2) );

    LinearState new_state { state + ( (k1 + (k2 * 2) + (k3 * 2) + k4) * (h/6) ) };
    return new_state;
}