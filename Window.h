#pragma once
#include <windows.h>
#include "main.h"

class Window
{
private:
    HWND hwnd;
    WNDCLASSEX wc;

    void unregister_class();
public:
    Window();
    void show();
    void update();
    static LRESULT WINAPI MsgProc( HWND, UINT, WPARAM, LPARAM );

    inline operator HWND() { return this->hwnd; }
    inline operator HWND() const { return this->hwnd; }
    ~Window();
};