#ifndef CSGOINTERNAL_DIRECTX_CPP
#define CSGOINTERNAL_DIRECTX_CPP

#include "DX9Utils/DirectX.h"

// This list of function is to setup Directx9, grab the vtable offset for endscene (42), and then hook it

int WindowWidth, WindowLength;

BOOL CALLBACK EnumWind(HWND Handle, LPARAM lp)
{
	DWORD ProcID;
	GetWindowThreadProcessId(Handle, &ProcID);


	if (GetCurrentProcessId() != ProcID)
	{ /// Breaking here latest
		return TRUE;
	}

	if (Handle == GetConsoleWindow())
	{
		return TRUE;
	}

	Window = Handle;
	return FALSE;
}

HWND GetDeviceWindow()
{
	Window = NULL;

	EnumWindows(EnumWind, NULL);

	RECT Size;
	GetWindowRect(Window, &Size);
	WindowWidth = Size.right - Size.left;
	WindowLength = Size.bottom - Size.top;

	return Window;
}


bool InitD3D9(void** pTable, size_t Size)
{
	if (!pTable)
	{
		return false;
	}

	// Setup D3D Interface
	IDirect3D9* PD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (!PD3D)
		return false;

	IDirect3DDevice9* pDummyDevice = NULL;

	// Setup Direct X Struct and fill with information
	D3DPRESENT_PARAMETERS d3dpp = {};
	d3dpp.Windowed = false;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = GetDeviceWindow(); // Unable to retrieve the hDeviceWindow...
	//std::cout << WindowWidth << std::endl << WindowLength << std::endl;

	// Create Device Class with the information retrieved previously
	HRESULT DummyDevCreated = PD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pDummyDevice);
	if (DummyDevCreated != S_OK)
	{
		d3dpp.Windowed = !d3dpp.Windowed;
		HRESULT DummyDevCreated = PD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pDummyDevice);

		if (DummyDevCreated != S_OK)
		{
			PD3D->Release();
			return false;
		}
	}

	memcpy(pTable, *(void***)(pDummyDevice), Size);

	pDummyDevice->Release();
	PD3D->Release();
	return true;

}

#endif //CSGOINTERNAL_DIRECTX_CPP