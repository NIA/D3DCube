#include "Window.h"

const TCHAR *WINDOW_CLASS = _T("Cube");
const TCHAR *WINDOW_TITLE = _T("Cube");

Window::Window(int width, int height)
{
    ZeroMemory( &wc, sizeof(wc) );

    wc.cbSize = sizeof( WNDCLASSEX );
    wc.style = CS_CLASSDC;
    wc.lpfnWndProc = Window::MsgProc;
    wc.hInstance = GetModuleHandle( NULL );
    wc.lpszClassName = WINDOW_CLASS;

    RegisterClassEx( &wc );

    hwnd = CreateWindow( WINDOW_CLASS, WINDOW_TITLE,
                         WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height,
                         NULL, NULL, wc.hInstance, NULL );
    if( hwnd == NULL )
    {
        unregister_class();
        throw WindowInitError();
    }
}

LRESULT WINAPI Window::MsgProc( HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam )
{
    switch( msg )
    {
        case WM_DESTROY:
            PostQuitMessage( 0 );
            return 0;
    }

    return DefWindowProc( hwnd, msg, wparam, lparam );
}

void Window::show()
{
    ShowWindow( *this, SW_SHOWDEFAULT );
}

void Window::update()
{
    UpdateWindow( *this );
}

void Window::unregister_class()
{
    UnregisterClass( WINDOW_CLASS, wc.hInstance );
}

Window::~Window()
{
    unregister_class();
}

