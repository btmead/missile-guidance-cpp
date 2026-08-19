//
// Created by benme on 19/08/2026.
//

#ifndef GUIDANCE_SIM_CPP_MAIN_H
#define GUIDANCE_SIM_CPP_MAIN_H

struct State {
    double x;
    double y;
    double xd;
    double yd;
};


struct LinearState {
    double y;
    double yd;
};

struct Matrix2D {
    double m00;
    double m01;
    double m10;
    double m11;
};


double coord_angle(const State&, const State&);
State matrixmultiply(const Matrix2D&, const State&);
Matrix2D rotationmatrix(double);

#endif //GUIDANCE_SIM_CPP_MAIN_H
