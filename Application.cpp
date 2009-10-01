#include "Application.h"

static const char * SHADER_FILE = "shader.vsh";

Application::Application() :
    d3d(NULL), device(NULL), vertex_decl(NULL), shader(NULL)
{
    try
    {
        init_device();
        init_shader();
    }
    catch(...)
    {
        release_interfaces();
        throw;
    }
}

void Application::init_device()
{
    d3d = Direct3DCreate9( D3D_SDK_VERSION );
    if( d3d == NULL )
        throw D3DInitError();

    // Set up the structure used to create the device
    D3DPRESENT_PARAMETERS present_parameters;
    ZeroMemory( &present_parameters, sizeof( present_parameters ) );
    present_parameters.Windowed = TRUE;
    present_parameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
    present_parameters.BackBufferFormat = D3DFMT_UNKNOWN;
    present_parameters.EnableAutoDepthStencil = TRUE;
    present_parameters.AutoDepthStencilFormat = D3DFMT_D16;
    // Create the device
    if( FAILED( d3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, window,
                                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                      &present_parameters, &device ) ) )
        throw D3DInitError();
    
    device->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
}

void Application::init_shader()
{
    if( FAILED( device->CreateVertexDeclaration(VERTEX_DECL_ARRAY, &vertex_decl) ) )
        throw VertexDeclarationInitError();

    ID3DXBuffer * shader_buffer = NULL;
    try
    {
        if( FAILED( D3DXAssembleShaderFromFileA( SHADER_FILE, NULL, NULL, NULL, &shader_buffer, NULL ) ) )
            throw VertexShaderAssemblyError();
        if( FAILED( device->CreateVertexShader( (DWORD*) shader_buffer->GetBufferPointer(), &shader ) ) )
            throw VertexShaderInitError();
    }
    catch(...)
    {
        release_interface(shader_buffer);
        throw;
    }
    release_interface(shader_buffer);
    
}

void Application::render()
{
    device->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB( 128, 128, 128 ), 1.0f, 0 );

    // Begin the scene
    if( SUCCEEDED( device->BeginScene() ) )
    {
        device->SetVertexDeclaration(vertex_decl);
        device->SetVertexShader(shader);
        device->SetVertexShaderConstantF(0, camera.get_matrix(), 4);

        for ( std::list<Model*>::iterator iter = models.begin(); iter != models.end(); iter++ )
            (*iter)->draw();

        // End the scene
        device->EndScene();
    }
    else
    {
        /* throw ...; */
    }

    // Present the backbuffer contents to the display
    device->Present( NULL, NULL, NULL, NULL );

}

IDirect3DDevice9 * Application::get_device()
{
    return device;
}

void Application::add_model(Model &model)
{
    models.push_back( &model );
}

void Application::remove_model(Model &model)
{
    models.remove( &model );
}

void Application::process_key(unsigned code)
{
    switch( code )
    {
    case VK_ESCAPE:
        PostQuitMessage( 0 );
        break;
    case VK_UP:
        camera.move_nearer();
        break;
    case VK_DOWN:
        camera.move_farther();
        break;
    case VK_PRIOR:
        camera.move_up();
        break;
    case VK_NEXT:
        camera.move_down();
        break;
    case VK_LEFT:
        camera.move_clockwise();
        break;
    case VK_RIGHT:
        camera.move_counterclockwise();
        break;
    }
}

void Application::run()
{
    window.show();
    window.update();

    // Enter the message loop
    MSG msg;
    ZeroMemory( &msg, sizeof( msg ) );
    while( msg.message != WM_QUIT )
    {
        if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
        {
            if( msg.message == WM_KEYDOWN )
            {
                process_key( (unsigned) msg.wParam );
            }

            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
        else
            render();
    }
}

void Application::release_interfaces()
{
    release_interface( d3d );
    release_interface( device );
    release_interface( vertex_decl );
    release_interface( shader );
}

Application::~Application()
{
    release_interfaces();
}