#pragma once
#include "main.h"

#define _USE_MATH_DEFINES
#include <cmath>


class Camera
{
private:
    D3DXVECTOR3 eye_spheric;  // a point, spheric coordinates
    D3DXVECTOR3 at;           // a point, cartesian coordinates
    D3DXVECTOR3 up;           // a vector, cartesian coordinates

    D3DXMATRIX mx;
    
public:
    void set_position(float rho, float theta, float phi, bool update_mx = true);
    void set_up_direction(float x, float y, float z, bool update_mx = true);
    void set_at_position(float x, float y, float z, bool update_mx = true);

    void set(float pos_rho, float pos_theta, float pos_phi, float at_x, float at_y, float at_z)
    {
        set_position(pos_rho,pos_theta,pos_phi, false);
        set_at_position(at_x, at_y, at_z, false);
        set_up_direction(0,0,1);
    }

    Camera() { set(2.0f, M_PI/2, M_PI/3, 0, 0, 0); };
    Camera(float rho, float theta, float phi) { set(rho,theta,phi,0,0,0); }
    Camera(float pos_rho, float pos_theta, float pos_phi, float at_x, float at_y, float at_z) { set(pos_rho,pos_theta,pos_phi,at_x,at_y,at_z); }
    void update_matrices();

    D3DXMATRIX get_matrix();
};
