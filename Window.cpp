#include "Window.h"

const TCHAR *WND_CLASS = _T("Cube");
const TCHAR *WND_TITLE = _T("Cube");

Window::Window()
{
    ZeroMemory( &wc, sizeof(wc) );

    wc.cbSize = sizeof( WNDCLASSEX );
    wc.style = CS_CLASSDC;
    wc.lpfnWndProc = Window::MsgProc;
    wc.hInstance = GetModuleHandle( NULL );
    wc.lpszClassName = WND_CLASS;

    RegisterClassEx( &wc );

    hwnd = CreateWindow( WND_CLASS, WND_TITLE,
                           WS_OVERLAPPEDWINDOW, 100, 100, 600, 600,
                           NULL, NULL, wc.hInstance, NULL );
    if( hwnd == NULL )
    {
        unregister_class();
        throw WindowInitError();
    }
}

LRESULT WINAPI Window::MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
        case WM_DESTROY:
            PostQuitMessage( 0 );
            return 0;
    }

    return DefWindowProc( hWnd, msg, wParam, lParam );
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
    UnregisterClass( WND_CLASS, wc.hInstance );
}

Window::~Window()
{
    unregister_class();
}

