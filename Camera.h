#pragma once
#include "main.h"



class Camera
{
private:
    D3DXVECTOR3 eye;  // a point
    D3DXVECTOR3 at;   // a point
    D3DXVECTOR3 up;   // a vector

    D3DXMATRIX mx;
    
public:
    void set_position(float x, float y, float z, bool update_mx = true);
    void set_up_direction(float x, float y, float z, bool update_mx = true);
    void set_at_position(float x, float y, float z, bool update_mx = true);

    void set(float pos_x, float pos_y, float pos_z, float at_x, float at_y, float at_z)
    {
        set_position(pos_x,pos_y,pos_z, false);
        set_at_position(at_x, at_y, at_z, false);
        set_up_direction(0,0,1);
    }

    Camera() { set(1.1f, 0.0f, -1.1f, 0, 0, 0); };
    Camera(float x, float y, float z) { set(x,y,z,0,0,0); }
    Camera(float pos_x, float pos_y, float pos_z, float at_x, float at_y, float at_z) { set(pos_x,pos_y,pos_z,at_x,at_y,at_z); }
    void update_matrices();

    D3DXMATRIX get_matrix();
};
