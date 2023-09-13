#ifndef CSGOINTERNAL_HELPERUTILS_CPP
#define CSGOINTERNAL_HELPERUTILS_CPP

#include <math.h>

#include "main.h"
#include "Utils/HelperUtils.h"
#include "Utils/MemUtils.h"

/// FPS Helpers
bool FPSUtils::IsPlayerMoving()
{
	Vec3 PlayerAcceleration = HackClass.PlayerEntity->m_vecvelocity;
	int TotalAcceleration = PlayerAcceleration.x + PlayerAcceleration.y + PlayerAcceleration.z;

	if (TotalAcceleration != 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/// Distance Calculation from one target to another
float FPSUtils::DistanceDif(Vec3 Dst, Vec3 Src)
{
	float Distance;

	Distance = sqrtf(
			pow(Dst.x - Src.x, 2) +
			pow(Dst.y - Src.y, 2) +
			pow(Dst.z - Src.z, 2));

	return Distance;
}

/// Normalise the view angle so the user doesn't get banned
Vec3 FPSUtils::NormaliseViewAngle(Vec3 Angle)
{
	if (Angle.x > 89)
	{
		Angle.x = 89;
	}

	if (Angle.x < -89)
	{
		Angle.x = -89;
	}

	if (Angle.y > 180)
	{
		Angle.y -= 360;
	}

	if (Angle.y < -180)
	{
		Angle.y += 360;
	}

	return Angle;
}

/// Get The bone Pos of an entity
Vec3 FPSUtils::GetBonePos(uintptr_t Entity, int BoneID)
{
	uintptr_t BoneMatrix = *(uintptr_t*)(Entity + OffsetV.m_dwBoneMatrix);
	Vec3 BonePos;

	BonePos.x = *(float*)(BoneMatrix + 0x30 * BoneID + 0x0c);
	BonePos.y = *(float*)(BoneMatrix + 0x30 * BoneID + 0x1c);
	BonePos.z = *(float*)(BoneMatrix + 0x30 * BoneID + 0x2c);

	return BonePos;
}

/// Aimbot Hack Angle Calculation
void FPSUtils::CalculateAngle(Vec3 Target)
{

	// Setup New View Angle Result
	Vec3 NewViewAngle;

	/// Grab the Player ViewAngle
	// Alternative to using dmaaddy
	uintptr_t ViewAngleAddress = *(uintptr_t*)OffsetV.dwClientState + OffsetV.dwClientState_ViewAngles;


	/// Get PLayer Position
	Vec3 PlayerPos = HackClass.PlayerEntity->m_Vecorigin;

	Vec3 ViewOffset = HackClass.PlayerEntity->m_VecViewOffset;

	Vec3 TruePlayerPos = (PlayerPos + ViewOffset);

	// Calculate the vector difference
	// Use it to get the Trig's Value (X = Distance Difference, Y = Horizontal Difference, Z = Height Difference)
	Vec3 DeltaVec = {Target.x - TruePlayerPos.x, Target.y - TruePlayerPos.y, Target.z - TruePlayerPos.z};

	float DeltaVecLen = sqrt(DeltaVec.x * DeltaVec.x + DeltaVec.y * DeltaVec.y + DeltaVec.z * DeltaVec.z);

	NewViewAngle.x = -asin(DeltaVec.z / DeltaVecLen) * (180 / PI);
	NewViewAngle.y = atan2f(DeltaVec.y, DeltaVec.x) * (180/PI);
	NewViewAngle.z = 0.0f;

	// Write New View Value
	*(Vec3*)ViewAngleAddress = FPSUtils::NormaliseViewAngle(NewViewAngle);
	// X = Pitch, Y = Yaw... bruh

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
	bool DefusingStatus = *(uintptr_t*)(Entity + OffsetV.m_bIsDefusing);

	if (DefusingStatus)
	{
		TGlow.Red = 1.0f;
		TGlow.Green = 1.0f;
		TGlow.Blue = 1.0f;
	}
	else
	{
		int Health = *(uintptr_t*)(Entity + OffsetV.m_iHealth);
		TGlow.Red = Health * -0.01 + 1;
		TGlow.Green = Health * 0.01;
		TGlow.Blue = 0.0f;
	}

	TGlow.Alpha = 1.7f;
	TGlow.RenderWhenOcculeded = true;
	TGlow.RenderWhenUnoccluded = false;

	*(GlowStruct*)(GlowObject + (GlowIndex * 0x38)) = TGlow;
}

/// Raise the brightness for glow hack
void GlowUtils::ModifyBrightness()
{
	AllyTeamColor.Red = 0;
	AllyTeamColor.Green = 0;
	AllyTeamColor.Blue = 255;

	EnemyTeamColor.Red = 255;
	EnemyTeamColor.Green = 0;
	EnemyTeamColor.Blue = 0;

	float Brightness = 5.0f;

	int AmbientVal = *(int*)OffsetV.model_ambient_min;
	int XorPointer = *(int*)&Brightness ^ AmbientVal;

	*OffsetV.model_ambient_min = XorPointer;
}


#endif //CSGOINTERNAL_HELPERUTILS_CPP