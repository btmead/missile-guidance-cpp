//
// Created by benme on 19/08/2026.
//

#ifndef GUIDANCE_SIM_CPP_MAIN_H
#define GUIDANCE_SIM_CPP_MAIN_H

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
};

struct State {
    Vector2D pos;
    Vector2D vel;
};


struct LinearState {
    double y    {0.0};
    double yd   {0.0};
};




void coord_rotation(State&, State&);
State coord_rotation(State&, double);
Vector2D matrixmultiply(const Matrix2D&, const Vector2D&);
Matrix2D rotationmatrix(double);
double hypot(const Vector2D&);

#endif //GUIDANCE_SIM_CPP_MAIN_H
