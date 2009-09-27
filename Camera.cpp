#include "Camera.h"

const float NEAR_CLIP = 0.5f;
const float FAR_CLIP = 1e10;
const float COEFF_A = FAR_CLIP / (NEAR_CLIP - FAR_CLIP);
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
    D3DXVECTOR3 c = at - eye;
    D3DXVECTOR3 b, a;
    D3DXVec3Normalize( &c, &c );
    D3DXVec3Cross( &a, &up, &c );
    D3DXVec3Normalize( &a, &a );
    D3DXVec3Cross( &b, &c, &a );
    D3DXVECTOR3 d( - D3DXVec3Dot( &eye, &a ),
                   - D3DXVec3Dot( &eye, &b ),
                   - D3DXVec3Dot( &eye, &c ) );

    D3DXMATRIX view_mx( a.x, a.y, a.z, d.x,
                        b.x, b.y, b.z, d.y,
                        c.x, c.y, c.z, d.z,
                          0,   0,   0,   1 );

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