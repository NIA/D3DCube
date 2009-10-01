#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "Error.h"

inline void release_interface(IUnknown* iface)
{
    if( iface != NULL ) iface->Release();
}

inline unsigned triangles_count( unsigned indices_count )
{
    return indices_count/3;
}
