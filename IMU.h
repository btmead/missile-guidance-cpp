//
// Created by benme on 28/08/2026.
//

#ifndef GUIDANCE_SIM_CPP_IMU_H
#define GUIDANCE_SIM_CPP_IMU_H

#include <Eigen/Dense>

class TrueState;
class Parameters;

using namespace Eigen;

class IMU {
private:
    Vector2d m_acc;
    double m_omega;
public:
    IMU ();
    Vector2d get_acc();
    double get_omega();
    void update_values (const TrueState &, const Vector2d &, const Parameters&);
};


#endif //GUIDANCE_SIM_CPP_IMU_H
