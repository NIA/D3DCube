#include "main.h"
#include "Application.h"

//-----------------------------------------------------------------------------
// Name: wWinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
INT WINAPI wWinMain( HINSTANCE, HINSTANCE, LPWSTR, INT )
{
    try
    {
        Application app;

        Vertex cube_vertices[]=
        {
            { -0.5f, -0.5f, -0.5f, D3DCOLOR_XRGB(  0,  0,  0), },
            { -0.5f,  0.5f, -0.5f, D3DCOLOR_XRGB(  0,255,  0), },
            {  0.5f,  0.5f, -0.5f, D3DCOLOR_XRGB(255,255,  0), },
            {  0.5f, -0.5f, -0.5f, D3DCOLOR_XRGB(255,  0,  0), },
            { -0.5f, -0.5f,  0.5f, D3DCOLOR_XRGB(  0,  0,255), },
            { -0.5f,  0.5f,  0.5f, D3DCOLOR_XRGB(  0,255,255), },
            {  0.5f,  0.5f,  0.5f, D3DCOLOR_XRGB(255,255,255), },
            {  0.5f, -0.5f,  0.5f, D3DCOLOR_XRGB(255,  0,255), },
        };
        DWORD cube_indices[] =
        {
            0, 1, 2,
            0, 3, 2,

            6, 7, 4,
            6, 5, 4,

            0, 4, 7,
            0, 3, 7,

            6, 5, 1,
            6, 2, 1,

            6, 7, 3,
            6, 2, 3,

            0, 4, 5,
            0, 4, 1,
        };

        Vertex triangles_vertices[] =
        {
            {  0.5f, -0.5f, -0.5f, D3DCOLOR_XRGB(255,  0,  0), },
            { -0.5f, -0.5f, -0.5f, D3DCOLOR_XRGB(  0,255,  0), },
            {  0.0f,  0.5f,  0.5f, D3DCOLOR_XRGB(  0,  0,255), },
            { -0.5f,  0.5f, -0.5f, D3DCOLOR_XRGB(  0,255,255), },
            {  0.5f,  0.5f, -0.5f, D3DCOLOR_XRGB(255,  0,255), },
            {  0.0f, -0.5f,  0.5f, D3DCOLOR_XRGB(255,255,  0), },
        };

        DWORD triangles_indices[] =
        {
            0, 1, 2,
            3, 4, 5,
        };

        Model triangles( app.get_device(),
                         D3DPT_TRIANGLELIST,
                         triangles_vertices,
                         ARR_SIZE(triangles_vertices),
                         triangles_indices,
                         ARR_SIZE(triangles_indices),
                         ARR_SIZE(triangles_indices)/3 );


        Model cube( app.get_device(),
                    D3DPT_TRIANGLELIST,
                    cube_vertices,
                    ARR_SIZE(cube_vertices),
                    cube_indices,
                    ARR_SIZE(cube_indices),
                    ARR_SIZE(cube_indices)/3 );
        
        app.add_model(triangles);
        app.run();
    }
    catch(RuntimeError &e)
    {
        MessageBoxA(NULL, e.what(), "Error!", MB_OK | MB_ICONERROR);
        return -1;
    }
    return 0;
}
