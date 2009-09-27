#pragma once
#include "main.h"
#include "Vertex.h"

class Model
{
private:
    IDirect3DDevice9        *device;

    unsigned    vertices_count;
    unsigned    primitives_count;

    D3DPRIMITIVETYPE        primitive_type;
    IDirect3DVertexBuffer9  *vertex_buffer;
    IDirect3DIndexBuffer9   *index_buffer;

    void init_buffers(  Vertex *vertices,
                        unsigned vertices_size,
                        D3DFORMAT index_format,
                        void *indices,
                        unsigned indices_size );
    void release_interfaces();

public:
    // Constructor for 16-bit indices
    Model(  IDirect3DDevice9 *device,
            D3DPRIMITIVETYPE primitive_type,
            Vertex *vertices,
            unsigned vertices_count,
            WORD *indices,
            unsigned indices_count,
            unsigned primitives_count );
    
    // Constructor for 32-bit indices
    Model(  IDirect3DDevice9 *device,
            D3DPRIMITIVETYPE primitive_type,
            Vertex *vertices,
            unsigned vertices_count,
            DWORD *indices,
            unsigned indices_count,
            unsigned primitives_count );

    virtual void draw();

    virtual ~Model();
};