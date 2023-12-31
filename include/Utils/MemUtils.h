#ifndef INTTEMPLATE_MEMUTILS_H
#define INTTEMPLATE_MEMUTILS_H

#include <Windows.h>
#include <Psapi.h>
#include <vector>

namespace Mem
{
	uintptr_t FindDMAAddy(uintptr_t AddrPtr, std::vector<unsigned int> MultiLevelOffset);

	char* PatternScanBasic(char* Base, size_t Size, char* Pattern, char* Mask);

	char* InternalScan(char* Begin, size_t Size, char* Pattern, char* Mask);

	uintptr_t InternalScanModule(bool IsRelative, char* Module, char* Pattern, char* Mask, unsigned int Offset, unsigned int Extra);
}


#endif //INTTEMPLATE_MEMUTILS_H
