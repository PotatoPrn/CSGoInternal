#ifndef CSGOINTERNAL_SDKFUNCTIONS_H
#define CSGOINTERNAL_SDKFUNCTIONS_H

#include <Windows.h>


/// CreateInterface Function
class IClientEntityList
{
public:
	// Get IClientNetworkable interface for specified entity
	virtual void* GetClientNetworkable(int entnum) = 0;

	virtual void* GetClientNetworkableFromHandle(int hEnt) = 0;

	virtual void* GetClientUnknownFromHandle(int hEnt) = 0;

	// NOTE: This function is only a convenience wrapper.
	// It returns GetClientNetworkable( entnum )->GetIClientEntity().
	virtual void* GetClientEntity(int entnum) = 0;

	virtual void* GetClientEntityFromHandle(int hEnt) = 0;

	// Returns number of entities currently in use
	virtual int NumberOfEntities(bool bIncludeNonNetworkable) = 0;

	// Returns highest index actually used
	virtual int GetHighestEntityIndex(void) = 0;

	// Sizes entity list to specified size
	virtual void SetMaxEntities(int maxents) = 0;

	virtual int GetMaxEntities() = 0;
};

typedef void* (__cdecl* _tCreateInterface)(const char* Name, int* ReturnCode);

void* GetInterface(const char* DLLName, const char* InterfaceName)
{
	_tCreateInterface CreateInterface = (_tCreateInterface)GetProcAddress(GetModuleHandle(DLLName), "CreateInterface");

	int ReturnCode = 0;
	void* Interface = CreateInterface(InterfaceName, &ReturnCode);

	return Interface;
}


/// NetVar Manager

class RecvProp;

class RecvTable
{
public:
	RecvProp* m_pProps;
	int m_nProps;
	void* m_pDecoder;
	const char* m_pNetTableName;    // The name matched between client and server.

public:
	bool m_bInitialized;
	bool m_bInMainList;
};


class RecvProp
{
public:
	const char* m_pVarName;
	void* m_RecvType;
	int m_Flags;
	int m_StringBufferSize;


public:
	bool m_bInsideArray;
	const void* m_pExtraData;
	RecvProp* m_pArrayProp;
	void* m_ArrayLengthProxy;
	void* m_ProxyFn;
	void* m_DataTableProxyFn;
	RecvTable* m_pDataTable;
	int m_Offset;
	int m_ElementStride;
	int m_nElements;
	const char* m_pParentArrayPropName;
};


class ClientClass
{
public:
	void* m_pCreateFn;
	void* m_pCreateEventFn;
	const char* m_pNetworkName;
	RecvTable* m_pRecvTable;
	ClientClass* m_pNext;
	int m_ClassID;
};


// https://guidedhacking.com/threads/how-to-find-dwgetallclasses-netvar-manager.14044/
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

class IBaseClientDLL
{
public:
	virtual void fn0() = 0;

	virtual void fn1() = 0;

	virtual void fn2() = 0;

	virtual void fn3() = 0;

	virtual void fn4() = 0;

	virtual void fn5() = 0;

	virtual void fn6() = 0;

	virtual void fn7() = 0;

	virtual ClientClass* GetAllClasses() = 0;
};

#endif //CSGOINTERNAL_SDKFUNCTIONS_H