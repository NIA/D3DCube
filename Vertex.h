#pragma once
#include "main.h"

// A structure for our custom vertex type
struct Vertex
{
    FLOAT x, y, z; // The position for the vertex
    DWORD color;   // The vertex color
};

extern D3DVERTEXELEMENT9 VERTEX_DECL_ARRAY[];
