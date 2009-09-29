#include "Camera.h"

const float NEAR_CLIP = 0.8f;
const float FAR_CLIP = 1e10f;
const float COEFF_A = FAR_CLIP / (FAR_CLIP - NEAR_CLIP);
const float COEFF_B = - COEFF_A * NEAR_CLIP;

const D3DXMATRIX PROJ_MX ( NEAR_CLIP,         0,       0,       0,
                                    0, NEAR_CLIP,       0,       0,
                                    0,         0, COEFF_A, COEFF_B,
                                    0,         0,       1,       0 );


void Camera::set_position(float x, float y, float z, bool update_mx)
{
    eye = D3DXVECTOR3(x, y, z);
    if( update_mx )
        update_matrices();
}

void Camera::set_at_position(float x, float y, float z, bool update_mx)
{
    at = D3DXVECTOR3(x, y, z);
    if( update_mx )
        update_matrices();
}

void Camera::set_up_direction(float x, float y, float z, bool update_mx)
{
    up = D3DXVECTOR3(x, y, z);
    if( update_mx )
        update_matrices();
}

void Camera::update_matrices()
{
    D3DXVECTOR3 axis_z = at - eye;
    D3DXVECTOR3 axis_x, axis_y;
    D3DXVec3Cross( &axis_x, &up, &axis_z );
    D3DXVec3Cross( &axis_y, &axis_z, &axis_x );
    D3DXVec3Normalize( &axis_x, &axis_x );
    D3DXVec3Normalize( &axis_y, &axis_y );
    D3DXVec3Normalize( &axis_z, &axis_z );
    D3DXVECTOR3 d( - D3DXVec3Dot( &eye, &axis_x ),
                   - D3DXVec3Dot( &eye, &axis_y ),
                   - D3DXVec3Dot( &eye, &axis_z ) );

    D3DXMATRIX view_mx( axis_x.x, axis_x.y, axis_x.z, d.x,
                        axis_y.x, axis_y.y, axis_y.z, d.y,
                        axis_z.x, axis_z.y, axis_z.z, d.z,
                               0,        0,        0,   1 );
    mx = PROJ_MX * view_mx;
}

D3DXMATRIX Camera::get_matrix()
{
    return mx;
        //D3DXMATRIX(1,0,0,0,
        //           0,1,0,0,
        //           0,0,1,0,
        //           0,0,0,1);
}