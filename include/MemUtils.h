#ifndef INTTEMPLATE_MEMUTILS_H
#define INTTEMPLATE_MEMUTILS_H

#include "main.h"

namespace Mem
{
	uintptr_t FindDMAAddy(uintptr_t AddrPtr, std::vector<unsigned int> MultiLevelOffset);
}


#endif //INTTEMPLATE_MEMUTILS_H
