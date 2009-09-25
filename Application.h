#pragma once
#include "main.h"
#include "Camera.h"
#include "Window.h"

class Application
{
private:
    IDirect3D9                  *d3d;           // used to create the D3DDevice
    IDirect3DDevice9            *device;        // our rendering device
    IDirect3DVertexDeclaration9 *vertex_decl;   // vertex declaration
    IDirect3DVertexShader9		*shader;        // vertex shader

    Window window;
    // Initialization steps:
    void init_device();
    void init_shader();

    // Deinitialization steps:
    void release_interfaces();

    void render();

public:
    Application();
    void run();
    ~Application();

};