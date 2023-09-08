#ifndef CSGOINTERNAL_HOOKUTIL_H
#define CSGOINTERNAL_HOOKUTIL_H

#include "main.h"

namespace Hook
{
	void Patch(BYTE* Dst, BYTE* Src, unsigned int Size);

	bool Hook(char* Src, char* Dst, int Len);

	char* TrampHook(char* Src, char* Dst, unsigned int Len);
}



#endif //CSGOINTERNAL_HOOKUTIL_H