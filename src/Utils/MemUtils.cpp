#include "Utils/MemUtils.h"
#include <iostream>
#include <sstream>


uintptr_t Mem::FindDMAAddy(uintptr_t AddrPtr, std::vector<unsigned int> MultiLevelOffset)
{
	uintptr_t AddressValue = AddrPtr;

	for (unsigned int i = 0; i < MultiLevelOffset.size(); i++)
	{
		AddressValue = *(uintptr_t*)AddressValue;
		AddressValue += MultiLevelOffset[i];
	}
	return AddressValue;
}


char* Mem::PatternScanBasic(char* Base, size_t Size, char* Pattern, char* Mask)
{
	size_t PatternLen = strlen(Mask);

	for (unsigned int i = 0; i < Size; i++)
	{
		bool Found = true;

		for (unsigned int j = 0; j < PatternLen; j++)
		{
			if (Mask[j] != '?' && Pattern[j] != *(char*)((intptr_t)Base + i + j))
			{
				Found = false;
				break;
			}
		}
		if (Found)
		{
			return (Base + i);
		}
	}
	return nullptr;
}


char* Mem::InternalScan(char* Begin, size_t Size, char* Pattern, char* Mask)
{
	char* Match{ nullptr };

	DWORD OldProc = 0;

	MEMORY_BASIC_INFORMATION mbi{};

	for (char* curr = Begin; curr < Begin + Size; curr += mbi.RegionSize)
	{
		if (!VirtualQuery(curr, &mbi, sizeof(mbi)) || mbi.State != MEM_COMMIT || mbi.Protect == PAGE_NOACCESS) continue;

		if (VirtualProtect(mbi.BaseAddress, mbi.RegionSize, PAGE_EXECUTE_READWRITE, &OldProc))
		{
			Match = Mem::PatternScanBasic(curr, mbi.RegionSize, Pattern, Mask);

			VirtualProtect(mbi.BaseAddress, mbi.RegionSize, OldProc, &OldProc);

			if (Match != nullptr)
			{
				break;
			}
		}
	}
	return Match;
}


uintptr_t* Mem::InternalScanModule(char* Module, char* Pattern, char* Mask, unsigned int Offset, unsigned int Extra)
{
	MODULEINFO moduleinfo = { 0 };
	HMODULE hmodule;
	hmodule = GetModuleHandle(Module);
	if (GetModuleInformation(GetCurrentProcess(), hmodule, &moduleinfo, sizeof(MODULEINFO)) == 0)
	{
		return 0;
	}

	char* Match = Mem::InternalScan((char*)moduleinfo.lpBaseOfDll, moduleinfo.SizeOfImage, Pattern, Mask);

	uintptr_t MatchOffset = (uintptr_t)Match + Offset;

	if (Extra > 0)
	{
		return *((uintptr_t**)MatchOffset) + Extra;
	}
	else
	{
		return *((uintptr_t**)MatchOffset);
	}

}

// Add function which converts hex to thingo...