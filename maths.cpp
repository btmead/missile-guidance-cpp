//
// Created by benme on 19/08/2026.
//

#include "main.h"
#include <cmath>

struct Vector2D;

State matrixmultiply(const Matrix2D& matrix, const State& vector) {
    return {
        matrix.m00 * vector.x + matrix.m01 * vector.y,
        matrix.m10 * vector.x + matrix.m11 * vector.y,
        vector.xd,
        vector.yd
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