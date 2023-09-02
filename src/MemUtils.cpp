#include "MemUtils.h"

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
