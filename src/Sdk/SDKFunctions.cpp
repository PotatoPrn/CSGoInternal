#ifndef CSGOINTERNAL_SDKFUNCTIONS_CPP
#define CSGOINTERNAL_SDKFUNCTIONS_CPP

#include "Sdk/SDKFunctions.h"
#include <Windows.h>

void* GetInterface(const char* DLLName, const char* InterfaceName)
{
	_tCreateInterface CreateInterface = (_tCreateInterface)GetProcAddress(GetModuleHandle(DLLName), "CreateInterface");

	int ReturnCode = 0;
	void* Interface = CreateInterface(InterfaceName, &ReturnCode);

	return Interface;
}


intptr_t GetOffset(RecvTable* Table, const char* Tablename, const char* NetVarName)
{
	for (unsigned int i = 0; i < Table->m_nProps; i++)
	{
		RecvProp Prop = Table->m_pProps[i];

		// Compare Netvar name against what was retrieved, if not search through the link list to find the correct offset
		if (!_stricmp(Prop.m_pVarName, NetVarName))
		{
			return Prop.m_Offset;
		}

		if (Prop.m_pDataTable)
		{
			// recursivly search for correct netvar name
			intptr_t Offset = GetOffset(Prop.m_pDataTable, Tablename, NetVarName);

			if (Offset)
			{
				return Offset + Prop.m_Offset;
			}
		}
	}
	return 0;
}

intptr_t GetNetVarOffset(const char* Tablename, const char* NetVarName, ClientClass* clientclass)
{
	// Search the client class for the netvar name, pretty much the getoffset wrapper...
	for (auto Currnode = clientclass; Currnode; Currnode = Currnode->m_pNext)
	{
		if (!_stricmp(Tablename, Currnode->m_pRecvTable->m_pNetTableName))
		{
			return GetOffset(Currnode->m_pRecvTable, Tablename, NetVarName);
		}
	}
	return 0;
}


#endif //CSGOINTERNAL_SDKFUNCTIONS_CPP