#pragma once
#include <exception>

class RuntimeError : public std::exception
{
public:
    virtual const char *what() const { return "Runtime error!"; }
};

class WindowInitError : public RuntimeError
{
public:
    virtual const char *what() const { return "Error while creating window"; }
};

class D3DInitError : public RuntimeError 
{
public:
    virtual const char *what() const { return "Error while initializing D3D device"; }
};

class VertexDeclarationInitError : public RuntimeError 
{
public:
    virtual const char *what() const { return "Error while creating vertex declaration"; }
};

class VertexShaderAssemblyError : public RuntimeError 
{
public:
    virtual const char *what() const { return "Error while assembling vertex shader"; }
};

class VertexShaderInitError : public RuntimeError 
{
public:
    virtual const char *what() const { return "Error while creating vertex shader"; }
};
