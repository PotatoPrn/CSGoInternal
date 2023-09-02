#ifndef INTTEMPLATE_HOOKUTIL_H
#define INTTEMPLATE_HOOKUTIL_H

#include "main.h"

struct HookInfo
{
	BYTE BytesStorage[10];
	BYTE* Dst; // Function to hook
	BYTE* Src; // Function you wish to attach to hook
	BYTE* GatewayHook; // Storage for stolen bytes & Detour
	unsigned int Len;
	bool IsHooked = false;
};


namespace Hook
{
	bool Detour32(HookInfo HookClass);

	BYTE* TrampHook32(HookInfo HookClass);

	bool EnableHook(char* ModuleName, char* FunctionName, BYTE* Functionhook, HookInfo HookClass);

	/*
	 * Hook Function...
	 * Depends on what graphics engine is used...
	 * Need Typecasted Hook Function Here
	 * BOOL __stdcall (opengl) HookBuffer(HDC hDc)
	 * std::cout << "hook" << std::endl;
	 * return Typecast Here
	 */

	bool DisableHook(HookInfo HookClass);

}

#endif //INTTEMPLATE_HOOKUTIL_H
