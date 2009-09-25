#include "main.h"
#include "Application.h"

//-----------------------------------------------------------------------------
// Name: wWinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
INT WINAPI wWinMain( HINSTANCE hInst, HINSTANCE, LPWSTR, INT )
{
    try
    {
        Application app;
        app.run();
    }
    catch(RuntimeError &e)
    {
        MessageBoxA(NULL, e.what(), "Error!", MB_OK | MB_ICONERROR);
        return -1;
    }
    return 0;
}
