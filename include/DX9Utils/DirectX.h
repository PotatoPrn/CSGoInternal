#ifndef CSGOINTERNAL_DIRECTX_H
#define CSGOINTERNAL_DIRECTX_H

#include "main.h"
#include <Windows.h>

typedef HRESULT(APIENTRY* tEndScene)(LPDIRECT3DDEVICE9 pDevice);

static HWND Window;

extern int WindowWidth, WindowHeight;

BOOL CALLBACK EnumWind(HWND Handle, LPARAM lp);

HWND GetDeviceWindow();

bool InitD3D9(void** pTable, size_t Size);

#endif //CSGOINTERNAL_DIRECTX_H