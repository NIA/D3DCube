#include <d3d9.h>
#pragma warning( disable : 4996 ) // disable deprecated warning 
#include <strsafe.h>
#pragma warning( default : 4996 )


#ifdef NDEBUG
#define CHECK(expr) do { if (FAILED(expr)) throw #expr; } while(0)
#else // #ifdef NDEBUG
#define CHECK(expr) expr
#endif // #ifdef NDEBUG

#define CHECK_OR_DO(code, expr) do {if (FAILED(expr)) {code;}} while(0)


//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
LPDIRECT3D9                  g_pD3D = NULL; // Used to create the D3DDevice
LPDIRECT3DDEVICE9            g_pd3dDevice = NULL; // Our rendering device
LPDIRECT3DVERTEXBUFFER9      g_pVB = NULL; // Buffer to hold vertices
LPDIRECT3DINDEXBUFFER9       g_pIB = NULL; // Buffer to hold indices
LPDIRECT3DVERTEXDECLARATION9 g_pDecl = NULL; // Vertex declaration

// A structure for our custom vertex type
struct CUSTOMVERTEX
{
    FLOAT x, y, z, rhw; // The transformed position for the vertex
    DWORD color;        // The vertex color
};

// Our custom FVF, which describes our custom vertex structure
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE)




//-----------------------------------------------------------------------------
// Name: InitD3D()
// Desc: Initializes Direct3D
//-----------------------------------------------------------------------------
HRESULT InitD3D( HWND hWnd )
{
    // Create the D3D object.
    if( NULL == ( g_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
        return E_FAIL;

    // Set up the structure used to create the D3DDevice
    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory( &d3dpp, sizeof( d3dpp ) );
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
    d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    // Create the D3DDevice
    CHECK_OR_DO(return E_FAIL, g_pD3D->CreateDevice(
									D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                    D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                    &d3dpp, &g_pd3dDevice ) );
				

    // Device state would normally be set here
    
    g_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
	
	D3DVERTEXELEMENT9 vertexDeclaration[] =
	{
		{0, 0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		{0, 16, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0},
		D3DDECL_END()
	};
	g_pd3dDevice->CreateVertexDeclaration(vertexDeclaration, &g_pDecl);
	g_pd3dDevice->SetVertexDeclaration(g_pDecl);
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: InitVB()
// Desc: Creates a vertex buffer and fills it with our vertices. The vertex
//       buffer is basically just a chuck of memory that holds vertices. After
//       creating it, we must Lock()/Unlock() it to fill it. For indices, D3D
//       also uses index buffers. The special thing about vertex and index
//       buffers is that they can be created in device memory, allowing some
//       cards to process them in hardware, resulting in a dramatic
//       performance gain.
//-----------------------------------------------------------------------------
HRESULT InitVB()
{
    CUSTOMVERTEX vertices[] =
    {
        {  50.0f, 50.0f,  0.5f, 1.0f, D3DCOLOR_XRGB(255,0,0), }, // x, y, z, rhw, color
        {  50.0f, 250.0f, 0.5f, 1.0f, D3DCOLOR_XRGB(0,255,255), },
        { 250.0f, 50.0f,  0.5f, 1.0f, D3DCOLOR_XRGB(0,255,0), },
        { 250.0f, 250.0f, 0.5f, 1.0f, D3DCOLOR_XRGB(255,255,0), },  // - a square

	    {  10.0f, 100.0f, 0.8f, 1.0f, D3DCOLOR_XRGB(255,255,255), },
        { 300.0f,  40.0f, 0.1f, 1.0f, D3DCOLOR_XRGB(255,255,255), }, // - a triangle
        { 230.0f,  80.0f, 0.8f, 1.0f, D3DCOLOR_XRGB(255,255,255), },
	};
	
	DWORD indices[] =
	{
		0, 1, 2, //  
		2, 1, 3, //  - a square
		4, 5, 6, // - a triangle
	};
	

    CHECK_OR_DO(return E_FAIL, g_pd3dDevice->CreateVertexBuffer(
												sizeof(vertices) /*5 * sizeof( CUSTOMVERTEX )*/,
                                                0, D3DFVF_CUSTOMVERTEX,
                                                D3DPOOL_DEFAULT, &g_pVB, NULL ) );
	

    CHECK_OR_DO(return E_FAIL, g_pd3dDevice->CreateIndexBuffer( sizeof(indices),
												 0, D3DFMT_INDEX32,
												 D3DPOOL_DEFAULT, &g_pIB, NULL ) );
				

    // fill the vertex buffer.
    VOID* pVertices;
    CHECK_OR_DO(return E_FAIL, g_pVB->Lock( 0, sizeof( vertices ), ( void** )&pVertices, 0 ) );
    memcpy( pVertices, vertices, sizeof( vertices ) );
    g_pVB->Unlock();

    // fill the index buffer.
	VOID* pIndices;
    CHECK_OR_DO(return E_FAIL, g_pIB->Lock( 0, sizeof( indices ), ( void** )&pIndices, 0 ) );
    memcpy( pIndices, indices, sizeof( indices ) );
    g_pIB->Unlock();

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: Cleanup()
// Desc: Releases all previously initialized objects
//-----------------------------------------------------------------------------
VOID Cleanup()
{
	if( g_pDecl != NULL )
        g_pDecl->Release();

    if( g_pIB != NULL )
        g_pIB->Release();

    if( g_pVB != NULL )
        g_pVB->Release();

    if( g_pd3dDevice != NULL )
        g_pd3dDevice->Release();

    if( g_pD3D != NULL )
        g_pD3D->Release();
}




//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Draws the scene
//-----------------------------------------------------------------------------
VOID Render()
{
    // Clear the backbuffer to a blue color
    g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB( 0, 0, 255 ), 1.0f, 0 );

    // Begin the scene
    if( SUCCEEDED( g_pd3dDevice->BeginScene() ) )
    {
        CHECK( g_pd3dDevice->SetStreamSource( 0, g_pVB, 0, sizeof( CUSTOMVERTEX ) ) );
        CHECK( g_pd3dDevice->SetFVF( D3DFVF_CUSTOMVERTEX ) );
        CHECK( g_pd3dDevice->SetIndices(g_pIB) );
        //CHECK( g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST , 0, 1 ) );
		CHECK( g_pd3dDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST , 0, 0, 7, 0, 3 ) );
 
        // End the scene
        CHECK( g_pd3dDevice->EndScene() );
    }

    // Present the backbuffer contents to the display
    g_pd3dDevice->Present( NULL, NULL, NULL, NULL );
}




//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: The window's message handler
//-----------------------------------------------------------------------------
LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
        case WM_DESTROY:
            Cleanup();
            PostQuitMessage( 0 );
            return 0;
    }

    return DefWindowProc( hWnd, msg, wParam, lParam );
}




//-----------------------------------------------------------------------------
// Name: wWinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
INT WINAPI wWinMain( HINSTANCE hInst, HINSTANCE, LPWSTR, INT )
{
	bool success = true;
    // Register the window class
    WNDCLASSEX wc =
    {
        sizeof( WNDCLASSEX ), CS_CLASSDC, MsgProc, 0L, 0L,
        GetModuleHandle( NULL ), NULL, NULL, NULL, NULL,
        L"Cube", NULL
    };
    RegisterClassEx( &wc );

    // Create the application's window
    HWND hWnd = CreateWindow( L"Cube", L"Cube",
                              WS_OVERLAPPEDWINDOW, 100, 100, 400, 300,
                              NULL, NULL, wc.hInstance, NULL );

    // Initialize Direct3D
    if( SUCCEEDED( InitD3D( hWnd ) ) )
    {
        // Create the vertex buffer
        if( SUCCEEDED( InitVB() ) )
        {
            // Show the window
            ShowWindow( hWnd, SW_SHOWDEFAULT );
            UpdateWindow( hWnd );

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
                    Render();
            }
        }
		else
		{
			success = false;
		}
    }
	else
	{
		success = false;
	}

    UnregisterClass( L"D3D Tutorial", wc.hInstance );
	if(success)
		return 0;
	else
		return 1;
}
