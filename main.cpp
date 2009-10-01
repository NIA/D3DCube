#include "main.h"
#include "Application.h"

INT WINAPI wWinMain( HINSTANCE, HINSTANCE, LPWSTR, INT )
{
    try
    {
        Application app;

        const Vertex cube_vertices[]=
        {
            { -1.0f, -1.0f, -1.0f, D3DCOLOR_XRGB(  0,  0,  0), },
            { -1.0f,  1.0f, -1.0f, D3DCOLOR_XRGB(  0,255,  0), },
            {  1.0f,  1.0f, -1.0f, D3DCOLOR_XRGB(255,255,  0), },
            {  1.0f, -1.0f, -1.0f, D3DCOLOR_XRGB(255,  0,  0), },
            { -1.0f, -1.0f,  1.0f, D3DCOLOR_XRGB(  0,  0,255), },
            { -1.0f,  1.0f,  1.0f, D3DCOLOR_XRGB(  0,255,255), },
            {  1.0f,  1.0f,  1.0f, D3DCOLOR_XRGB(255,255,255), },
            {  1.0f, -1.0f,  1.0f, D3DCOLOR_XRGB(255,  0,255), },
        };
        const WORD cube_indices[] =
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

            0, 5, 4,
            0, 5, 1,
        };
        const int VERTICES_NUM = sizeof(cube_vertices)/sizeof(cube_vertices[0]);
        const int INDICES_NUM = sizeof(cube_indices)/sizeof(cube_indices[0]);

        Model cube( app.get_device(),
                    D3DPT_TRIANGLELIST,
                    cube_vertices,
                    VERTICES_NUM,
                    cube_indices,
                    INDICES_NUM,
                    triangles_count(INDICES_NUM) );
        
        app.add_model(cube);
        app.run();
    }
    catch(RuntimeError &e)
    {
        const TCHAR *MESSAGE_BOX_TITLE = _T("Cube error!");
        MessageBox(NULL, e.message(), MESSAGE_BOX_TITLE, MB_OK | MB_ICONERROR);
        return -1;
    }
    return 0;
}
