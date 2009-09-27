#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "Error.h"

#ifdef NDEBUG
#define CHECK(expr) do { if (FAILED(expr)) throw #expr; } while(0)
#else // #ifdef NDEBUG
#define CHECK(expr) expr
#endif // #ifdef NDEBUG

#define CHECK_OR_DO(code, expr) do {if (FAILED(expr)) {code;}} while(0)
#define CHECK_OR_FAIL(expr) CHECK_OR_DO(return E_FAIL, expr)

#define ARR_SIZE(arr) (sizeof(arr)/sizeof(arr[0]))

inline static void release_interface(IUnknown* iface)
{
    if( iface != NULL ) iface->Release();
}