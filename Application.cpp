#include "Application.h"

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
    if( NULL == ( d3d = Direct3DCreate9( D3D_SDK_VERSION ) ) )
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
	D3DVERTEXELEMENT9 vertex_decl_array[] =
	{
		{0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		{0, 12, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0},
		D3DDECL_END()
	};
	if( FAILED( device->CreateVertexDeclaration(vertex_decl_array, &vertex_decl) ) )
        throw VertexDeclarationInitError();

	ID3DXBuffer * shader_buffer = NULL;
	if( FAILED( D3DXAssembleShaderFromFileA( "shader.vsh", NULL, NULL, NULL, &shader_buffer, NULL ) ) )
        throw VertexShaderAssemblyError();
	if( FAILED( device->CreateVertexShader( (DWORD*) shader_buffer->GetBufferPointer(), &shader ) ) )
        throw VertexShaderInitError();
}

void Application::render()
{
    device->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB( 128, 128, 128 ), 1.0f, 0 );

    // Begin the scene
    if( SUCCEEDED( device->BeginScene() ) )
    {
		device->SetVertexDeclaration(vertex_decl);
        device->SetVertexShader(shader);

        // TODO: Here we call draw() at each model
        // device->SetStreamSource( 0, g_pVB, 0, sizeof( CUSTOMVERTEX ) );
        // device->SetIndices(g_pIB);
		// device->DrawIndexedPrimitive( D3DPT_TRIANGLELIST , 0, 0, 7, 0, 3 );
 
        // End the scene
        device->EndScene();
    }

    // Present the backbuffer contents to the display
    device->Present( NULL, NULL, NULL, NULL );

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