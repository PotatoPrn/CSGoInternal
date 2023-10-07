#ifndef CSGOINTERNAL_HACKLIST_CPP
#define CSGOINTERNAL_HACKLIST_CPP

#include "HackList.h"
#include "Utils/HelperUtils.h"
#include "main.h"

void BHop_Hack()
{
	if (FPSUtils::IsPlayerMoving())
	{
		int JumpState = OH::CalcOffset<int>(HackClass.PlayerEntity, OffsetV.m_fFlag);

		static int FL_ONGROUND = 0b0000'0001; // Bitwise pattern for the player being on ground

		if (JumpState & FL_ONGROUND)
		{
			*(int*)(HackClass.ClientBase + OffsetV.dwForceJump) = 6;
		}
	}
}


void Glow_Hack()
{
	uintptr_t GlowObject = OH::CalcOffset<uintptr_t>(HackClass.ClientBase, OffsetV.dwGlowObjectManager);

	// 64 since the entity list for humanoids are below 64
	for (unsigned int i = 0; i < 64; i++)
	{
		uintptr_t Entity = *(uintptr_t*)(HackClass.ClientBase + OffsetV.dwEntityList + i * 0x10);

		if (FPSUtils::VerifyEntity(Entity))
		{
			int GlowIndex = OH::CalcOffset<int>(Entity, OffsetV.m_iGlowIndex);

			if (FPSUtils::SameTeamCheck(Entity))
			{
				// Draw Player Team
				GlowUtils::SetTeamGlow(GlowIndex, GlowObject);
				*(ClrRenderStruct*)(Entity + OffsetV.m_clrRender) = AllyTeamColor;
			}
			else
			{
				GlowUtils::SetEnemyGlow(Entity, GlowIndex, GlowObject);
				*(ClrRenderStruct*)(Entity + OffsetV.m_clrRender) = EnemyTeamColor;
				// Draw Enemy Team
			}
		}
	}
}


void TriggerBot()
{
	static size_t LastTime = 0;
	int CrosshairInfo = OH::CalcOffset<int>(HackClass.PlayerEntity, OffsetV.m_iCrosshairId);

	if (CrosshairInfo != 0 && CrosshairInfo < 64)
	{
		uintptr_t Entity = *(uintptr_t*)(HackClass.ClientBase + OffsetV.dwEntityList +
										 (CrosshairInfo - 1) * 0x10);

		// Great Thread Safety delay
		// https://www.mpgh.net/forum/showthread.php?t=1047609
		if (FPSUtils::VerifyEntity(Entity) && !FPSUtils::SameTeamCheck(Entity) && GetTickCount() > LastTime)
		{
			*(uintptr_t*)(HackClass.ClientBase + OffsetV.dwForceAttack) = 6;
			Vec3 PlayerPos = OH::CalcOffset<Vec3>(HackClass.PlayerEntity, OffsetV.m_vecOrigin);
			Vec3 EntPos = OH::CalcOffset<Vec3>(Entity, OffsetV.m_vecOrigin);
			LastTime = GetTickCount() + FPSUtils::DistanceDif(EntPos, PlayerPos) * 0.400;
		}
	}
}


void Aimbot()
{
	// Distance Vars
	float OldDistance = FLT_MAX;
	float NewDistance = 0;

	for (unsigned int i = 0; i < 64; i++)
	{
		// Get Entity List
		uintptr_t Entity = *(uintptr_t*)(HackClass.ClientBase + OffsetV.dwEntityList + i * 0x10);

		if (FPSUtils::VerifyEntity(Entity) && !FPSUtils::SameTeamCheck(Entity))
		{

			// Grab position...
			Vec3 PlayerPos = OH::CalcOffset<Vec3>(HackClass.PlayerEntity, OffsetV.m_vecOrigin);
			Vec3 EntityPos = OH::CalcOffset<Vec3>(Entity, OffsetV.m_vecOrigin);

			// Add TraceRay Function here...
			if (TraceRayFunction(Entity))
			{
				NewDistance = FPSUtils::DistanceDif(EntityPos, PlayerPos);

				if (NewDistance < OldDistance)
				{
					OldDistance = NewDistance;
					FPSUtils::CalculateAngle(FPSUtils::GetBonePos(Entity, 8));
					// Get Head Pos
				}
			}
		}
	}
}



/// ESP Hack
void ESP()
{
	ESPHacks::DrawCrossHair();

	ESPHacks::DrawSnapLine();


}

/// RCS Hack
Vec3 OPunch = { 0, 0, 0 };

void RCS() /// Doesnt work lmao
{
	Vec3* ViewAngle = (Vec3*)(*(uintptr_t*)(HackClass.EngineBase + OffsetV.dwClientState) + OffsetV.dwClientState_ViewAngles);

	int ShotsFired = OH::CalcOffset<int>(HackClass.PlayerEntity, OffsetV.m_iShotsFired);

	Vec3 AimPunchAngle = OH::CalcOffset<Vec3>(HackClass.PlayerEntity, OffsetV.m_aimPunchAngle);

	Vec3 PunchAngle = AimPunchAngle * 2;

	if (ShotsFired > 1)
	{
		Vec3 NewAngle = *ViewAngle + OPunch - PunchAngle;

		*ViewAngle = FPSUtils::NormaliseViewAngle(NewAngle);
	}

	OPunch = PunchAngle;
}

#endif //CSGOINTERNAL_HACKLIST_CPP