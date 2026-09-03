//
// Created by benme on 28/08/2026.
//

#ifndef GUIDANCE_SIM_CPP_STATE_H
#define GUIDANCE_SIM_CPP_STATE_H

#include <Eigen/Dense>

class TrueState;
class IMU;

using namespace Eigen;

class State {
private:
    Vector2d m_pos;
    Vector2d m_vel;
    Vector2d m_acc;
    double m_gamma;

    Vector2d target_pos_N(const TrueState&) const;

public:
    State (const Vector2d &, const Vector2d &, const Vector2d &, const double);
    void coord_rotation (double);

    /* Takes target relative position which is hidden from the missile. True state which is
     * in the normal frame N converts to the missile's body frame B through a rotation matrix
     * in target_pos_N().
     * Then rotates the target relative position into normal frame N and adds missile position
     * to form an accurate position.
     */
    Vector2d get_target (const TrueState&) const;

    Vector2d get_pos () const;
    Vector2d get_vel () const;
    Vector2d get_accel () const;

    void update_state (IMU&, const double); //For missile state
    void update_state (const Vector2d &, const double, const Vector2d &); //For target state
};




#endif //GUIDANCE_SIM_CPP_STATE_H
