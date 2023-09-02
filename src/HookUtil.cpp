#include "HookUtil.h"

bool Hook::Detour32(HookInfo HookClass)
{
	if (HookClass.Len < 5)
	{
		return false;
	}

	DWORD OldProc;

	if (VirtualProtect(HookClass.Src, HookClass.Len, PAGE_EXECUTE_READWRITE, &OldProc) == 0)
	{
		std::cout << "Detour32: VirtualProtect Error" << std::endl;
		return false;
	}

	// Calculate the relative address for the detour
	uintptr_t RelativeAddress = HookClass.Dst - HookClass.Src - 5;

	// Add Jmp Instruction
	*HookClass.Src = 0xE9;

	// Add Address after Jmp
	*(uintptr_t*)(HookClass.Src + 1) = RelativeAddress;


	if (VirtualProtect(HookClass.Src, HookClass.Len, OldProc, nullptr) == 0)
	{
		std::cout << "Detour32: VirtualProtect2 Error" << std::endl;
		return false;
	}
	return true;
}

BYTE* Hook::TrampHook32(HookInfo HookClass)
{
	if (HookClass.Len < 5) return 0;

	// Setup gateway
	HookClass.GatewayHook = (BYTE*)VirtualAlloc(0, HookClass.Len, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

	// Copy Stolen bytes to Gateway
	memcpy_s(HookClass.GatewayHook, HookClass.Len, HookClass.Src, HookClass.Len);

	// Copy Stolen bytes to Storage for recovery...
	memcpy_s(HookClass.BytesStorage, HookClass.Len, HookClass.Src, HookClass.Len);

	// Get Gateway to Destination Address
	uintptr_t GatewayRelativeAddress = HookClass.Src - HookClass.GatewayHook - 5;

	// Add Jump
	*(HookClass.GatewayHook + HookClass.Len) = 0xE9;

	//  Add Gateway Address After Jmp
	*(uintptr_t*)((uintptr_t)HookClass.GatewayHook + HookClass.Len) = GatewayRelativeAddress;

	Hook::Detour32(HookClass);

	return HookClass.GatewayHook;
}

bool Hook::EnableHook(char* ModuleName, char* FunctionName, BYTE* Functionhook, HookInfo HookClass)
{
	return true;
}

bool Hook::DisableHook(HookInfo HookClass)
{
	memcpy_s(HookClass.Dst, HookClass.Len, HookClass.BytesStorage, HookClass.Len);
	HookClass.IsHooked = true;

	return true;
}

