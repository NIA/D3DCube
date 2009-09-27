#pragma once
#include <exception>

#define DECLARE_ERROR(Error, Base, msg) \
    class Error : public Base \
    { \
    public: \
        virtual const char *what() const { return msg; } \
    }

DECLARE_ERROR(RuntimeError, std::exception, "Runtime Error!");
DECLARE_ERROR(WindowInitError, RuntimeError, "Error while creating window");
DECLARE_ERROR(D3DInitError, RuntimeError, "Error while initializing D3D device");
DECLARE_ERROR(VertexDeclarationInitError, RuntimeError, "Error while creating vertex declaration");
DECLARE_ERROR(VertexShaderAssemblyError, RuntimeError, "Error while assembling vertex shader");
DECLARE_ERROR(VertexShaderInitError, RuntimeError, "Error while creating vertex shader");
DECLARE_ERROR(VertexBufferInitError, RuntimeError, "Error while creating vertex buffer");
DECLARE_ERROR(IndexBufferInitError, RuntimeError, "Error while creating index buffer");
DECLARE_ERROR(VertexBufferFillError, RuntimeError, "Error while filling vertex buffer");
DECLARE_ERROR(IndexBufferFillError, RuntimeError, "Error while filling index buffer");
