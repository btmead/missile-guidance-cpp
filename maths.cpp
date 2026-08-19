//
// Created by benme on 19/08/2026.
//

#include "main.h"
#include <cmath>


Vector2D matrixmultiply(const Matrix2D& matrix, const Vector2D& vector) {
    return {
        matrix.m00 * vector.x + matrix.m01 * vector.y,
        matrix.m10 * vector.x + matrix.m11 * vector.y,

    };
}

Matrix2D rotationmatrix(double angle) {
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

State coord_rotation(State &state, double angle) {
    state.pos = (matrixmultiply(rotationmatrix(angle), state.pos));
    state.vel = (matrixmultiply(rotationmatrix(angle), state.vel));
    return state;
}