#ifndef CSGOINTERNAL_TRACERAYUTIL_CPP
#define CSGOINTERNAL_TRACERAYUTIL_CPP

#include "TraceRayUtil.h"
#include "Sdk/SDKFunctions.h"


bool TraceRayFunction(uintptr_t Ent)
{

	IEngineTrace* EngineTrace = (IEngineTrace*)GetInterface("engine.dll", "EngineTraceClient004");

	CGameTrace Trace;
	Ray_t Ray;
	CTraceFilter TraceFilter;
	TraceFilter.pSkip = (void*)HackClass.PlayerEntity;

	Vec3 PlayerEyePos = *(Vec3*)(HackClass.PlayerEntity + OffsetV.m_vecOrigin) + *(Vec3*)(HackClass.PlayerEntity + OffsetV.m_vecViewOffset);

	Vec3 EntityPos = FPSUtils::GetBonePos(Ent, 8);

	Ray.Init(PlayerEyePos, EntityPos);
	EngineTrace->TraceRay(Ray, MASK_SHOT | CONTENTS_GRATE, &TraceFilter, &Trace);

	//std::cout << "HitEntity Stuff > " << std::hex << Trace.hit_entity << "\n" << "Chosen Entity > " <<  Ent << std::endl;

	if (Trace.hit_entity == (void*)Ent)
	{
		return true;
	}
	return false;
}


#endif //CSGOINTERNAL_TRACERAYUTIL_CPP