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

        Vertex square_vertices[] =
        {
            { -0.5f, -0.5f, 0.5f, D3DCOLOR_XRGB(255,  0,  0), },    // x, y, z, color
            {  0.5f, -0.5f, 0.5f, D3DCOLOR_XRGB(  0,255,255), },
            { -0.5f,  0.5f, 0.5f, D3DCOLOR_XRGB(  0,255,  0), },
            {  0.5f,  0.5f, 0.5f, D3DCOLOR_XRGB(255,255,  0), },    // - a square
        };
        DWORD square_indices[] =
        {
            0, 1, 2, //  
            2, 1, 3, //  - a square
        };
        Model square(   app.get_device(),
                        D3DPT_TRIANGLELIST,
                        square_vertices,
                        ARR_SIZE(square_vertices),
                        square_indices,
                        ARR_SIZE(square_indices),
                        ARR_SIZE(square_indices)/3 );
        
        Vertex triangle_vertices[]=
        {
            { -0.7f,  0.4f, 0.8f, D3DCOLOR_XRGB(255,255,255), },
            {  0.2f,  0.2f, 0.1f, D3DCOLOR_XRGB(255,255,255), },
            {  0.3f,  0.0f, 0.2f, D3DCOLOR_XRGB(255,255,255), },    // - a triangle
        };
        DWORD triangle_indices[] =
        {
            0, 1, 2, // - a triangle
        };
        Model triangle(   app.get_device(),
                        D3DPT_TRIANGLELIST,
                        triangle_vertices,
                        ARR_SIZE(triangle_vertices),
                        triangle_indices,
                        ARR_SIZE(triangle_indices),
                        ARR_SIZE(triangle_indices)/3 );
        
        app.add_model(square);
        app.add_model(triangle);
        app.run();
    }
    catch(RuntimeError &e)
    {
        MessageBoxA(NULL, e.what(), "Error!", MB_OK | MB_ICONERROR);
        return -1;
    }
    return 0;
}
