#ifndef CSGOINTERNAL_HOOKUTIL_CPP
#define CSGOINTERNAL_HOOKUTIL_CPP

#include "Utils/HookUtil.h"

void Hook::Patch(BYTE* Dst, BYTE* Src, unsigned int Size)
{
	DWORD oProc;

	VirtualProtect(Dst, Size, PAGE_EXECUTE_READWRITE, &oProc);
	memcpy(Dst, Src, Size);
	VirtualProtect(Dst, Size, oProc, &oProc);
}

bool Hook::Hook(char* Src, char* Dst, int Len)
{
	if (Len < 5) return false;

	DWORD oProc;

	VirtualProtect(Src, Len, PAGE_EXECUTE_READWRITE, &oProc);

	memset(Src, 0x90, Len);

	uintptr_t RelAddy = uintptr_t(Dst - Src - 5);

	*Src = (char)0xE9;

	*(uintptr_t*)(Src + 1) = (uintptr_t)RelAddy;

	VirtualProtect(Src, Len, oProc, &oProc);

	return true;
}

char* Hook::TrampHook(char* Src, char* Dst, unsigned int Len)
{
	if (Len < 5) return 0;

	char* Gateway = (char*)VirtualAlloc(0, Len + 5, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

	memcpy(Gateway, Src, Len);

	uintptr_t GateRelAddy = (uintptr_t)(Src - Gateway - 5);

	*(Gateway + Len) = (char)0xE9;

	*(uintptr_t*)(Gateway + Len + 1) = GateRelAddy;

	if (Hook::Hook(Src, Dst, Len))
	{
		return Gateway;
	}
	else return nullptr;

}


#endif //CSGOINTERNAL_HOOKUTIL_CPP