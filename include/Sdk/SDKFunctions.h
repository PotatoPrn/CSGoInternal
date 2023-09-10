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

void* GetInterface(const char* DLLName, const char* InterfaceName);


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
intptr_t GetOffset(RecvTable* Table, const char* Tablename, const char* NetVarName);

intptr_t GetNetVarOffset(const char* Tablename, const char* NetVarName, ClientClass* clientclass);

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