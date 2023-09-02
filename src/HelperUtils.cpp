#ifndef CSGOINTERNAL_HELPERUTILS_CPP
#define CSGOINTERNAL_HELPERUTILS_CPP

#include "HelperUtils.h"


/// FPS Helpers
bool FPSUtils::IsPlayerMoving()
{
	Vec3 PlayerAcceleration = HackClass.PlayerEntity->m_vecvelocity;
	int TotalAcceleration = PlayerAcceleration.X + PlayerAcceleration.Y + PlayerAcceleration.Z;

	if (TotalAcceleration != 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}


float FPSUtils::DistanceDif(Vec3 Dst, Vec3 Src)
{
	float Distance;

	Distance = sqrtf(
			pow(Dst.X - Src.X, 2) +
			pow(Dst.Y - Src.Y, 2) +
			pow(Dst.Z - Src.Z, 2));

	return Distance;
}


/// Glow Hack Helpers
void GlowUtils::SetTeamGlow(int GlowIndex, uintptr_t GlowObject)
{
	GlowStruct TGlow;

	TGlow = *(GlowStruct*)(GlowObject + (GlowIndex * 0x38));

	TGlow.Red = 0.0f;
	TGlow.Green = 0.0f;
	TGlow.Blue = 2.0f;
	TGlow.Alpha = 1.7f;
	TGlow.RenderWhenOcculeded = true;
	TGlow.RenderWhenUnoccluded = false;

	*(GlowStruct*)(GlowObject + (GlowIndex * 0x38)) = TGlow;
}

void GlowUtils::SetEnemyGlow(uintptr_t Entity, int GlowIndex, uintptr_t GlowObject)
{
	GlowStruct TGlow;

	TGlow = *(GlowStruct*)(GlowObject + (GlowIndex * 0x38));
	bool DefusingStatus = *(uintptr_t*)(Entity + PresetOffset::m_bIsDefusing);

	if (DefusingStatus)
	{
		TGlow.Red = 1.0f;
		TGlow.Green = 1.0f;
		TGlow.Blue = 1.0f;
	}
	else
	{
		int Health = *(uintptr_t*)(Entity + PresetOffset::m_iHealth);
		TGlow.Red = Health * -0.01 + 1;
		TGlow.Green = Health * 0.01;
		TGlow.Blue = 0.0f;
	}

	TGlow.Alpha = 1.7f;
	TGlow.RenderWhenOcculeded = true;
	TGlow.RenderWhenUnoccluded = false;

	*(GlowStruct*)(GlowObject + (GlowIndex * 0x38)) = TGlow;
}

void GlowUtils::ModifyBrightness()
{
	AllyTeamColor.Red = 0;
	AllyTeamColor.Green = 0;
	AllyTeamColor.Blue = 255;

	EnemyTeamColor.Red = 255;
	EnemyTeamColor.Green = 0;
	EnemyTeamColor.Blue = 0;

	float Brightness = 5.0f;

	int AmbientVal = *(uintptr_t*)(HackClass.EngineBase + PresetOffset::model_ambient_min);
	int XorPointer = *(int*)&Brightness ^ AmbientVal;

	*(uintptr_t*)(HackClass.EngineBase + PresetOffset::model_ambient_min) = XorPointer;
}


#endif //CSGOINTERNAL_HELPERUTILS_CPP