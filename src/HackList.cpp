#ifndef CSGOINTERNAL_HACKLIST_CPP
#define CSGOINTERNAL_HACKLIST_CPP

#include "HackList.h"
#include "Utils/HelperUtils.h"
#include "main.h"
#include "DX9Utils/Draw.h"

#include <time.h>





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
	int PlayerTeam = *(int*)(HackClass.PlayerEntity + OffsetV.m_iTeamNum);
	uintptr_t GlowObject = OH::CalcOffset<uintptr_t>(HackClass.ClientBase, OffsetV.dwGlowObjectManager);

	// 64 since the entity list for humanoids are below 64
	for (unsigned int i = 0; i < 64; i++)
	{
		uintptr_t EntityObject = *(uintptr_t*)(HackClass.ClientBase + OffsetV.dwEntityList + i * 0x10);

		if (EntityObject != NULL)
		{
			//int EntityTeam = *(uintptr_t*)(EntityObject + OffsetV.m_iTeamNum);
			int EntityTeam = OH::CalcOffset<int>(EntityObject,
					OffsetV.m_iTeamNum); // Convert all offset calcs to use this
			int GlowIndex = OH::CalcOffset<int>(EntityObject, OffsetV.m_iGlowIndex);

			if (EntityTeam == PlayerTeam)
			{
				// Draw Player Team
				GlowUtils::SetTeamGlow(GlowIndex, GlowObject);
				*(ClrRenderStruct*)(EntityObject + OffsetV.m_clrRender) = AllyTeamColor;
			}
			else
			{
				GlowUtils::SetEnemyGlow(EntityObject, GlowIndex, GlowObject);
				*(ClrRenderStruct*)(EntityObject + OffsetV.m_clrRender) = EnemyTeamColor;
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

		if (Entity != NULL)
		{
			int EntityHP = OH::CalcOffset<int>(Entity, OffsetV.m_iHealth);

			// Great Thread Safety delay
			// https://www.mpgh.net/forum/showthread.php?t=1047609
			if (EntityHP > 0 && GetTickCount() > LastTime)
			{
				*(uintptr_t*)(HackClass.ClientBase + OffsetV.dwForceAttack) = 6;
				Vec3 PlayerPos = OH::CalcOffset<Vec3>(HackClass.PlayerEntity, OffsetV.m_vecOrigin);
				Vec3 EntPos = OH::CalcOffset<Vec3>(Entity, OffsetV.m_vecOrigin);
				LastTime = GetTickCount() + FPSUtils::DistanceDif(EntPos, PlayerPos) * 0.400;
			}
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

		if (Entity != NULL)
		{
			bool m_bDormant = OH::CalcOffset<bool>(Entity, OffsetV.m_bDormant);
			int EntTeamVal = OH::CalcOffset<int>(Entity, OffsetV.m_iTeamNum);

			int TeamValue = OH::CalcOffset<int>(HackClass.PlayerEntity, OffsetV.m_iTeamNum);

			if (!m_bDormant && TeamValue != EntTeamVal)
			{
				// Grab Entity Health
				int EntHealth = OH::CalcOffset<int>(Entity, OffsetV.m_iHealth);

				if (EntHealth > 0)
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
	}
}

/// ESP Hack
void ESP()
{
	/// The view matrix is found by punching in the view angle into a 3d rotation converter then scanning it and looking for all matrixs
	/// https://guidedhacking.com/threads/how-to-get-started-with-learning-viewmatrix.13663/
	float ViewMatrix[16];
	/// Causing crashing...
	memcpy(&ViewMatrix, (PBYTE)(HackClass.ClientBase + OffsetV.dwViewMatrix), sizeof(ViewMatrix));

	// 1 to skip the player
	for (unsigned int i = 1; i < 64; i++)
	{
		uintptr_t Entity = *(uintptr_t*)(HackClass.ClientBase + OffsetV.dwEntityList + i * 0x10);

		if (Entity != NULL)
		{
			bool m_bDormant = OH::CalcOffset<bool>(Entity, OffsetV.m_bDormant);
			int EntTeamVal = OH::CalcOffset<int>(Entity, OffsetV.m_iTeamNum);
			int EntHealth = OH::CalcOffset<int>(Entity, OffsetV.m_iHealth);

			int TeamValue = OH::CalcOffset<int>(HackClass.PlayerEntity, OffsetV.m_iTeamNum);

			if (!m_bDormant && EntHealth > 0)
			{
				D3DCOLOR Color;
				if (TeamValue != EntTeamVal)
				{
					Color = D3DCOLOR_ARGB(255, 255, 0, 0);
				}
				else
				{
					Color = D3DCOLOR_ARGB(255, 0, 255, 0);
				}

				Vec2 EntPos2D;
				Vec3 EntityPos = OH::CalcOffset<Vec3>(Entity, OffsetV.m_vecOrigin);

				if (FPSUtils::World2Screen(ViewMatrix, EntityPos, EntPos2D))
				{
					DrawLine(EntPos2D.x, EntPos2D.y, WindowWidth / 2, WindowLength / 2, 2, Color);
				}
			}
		}
	}
}

/// RCS Hack
void RCS() /// Doesnt work lmao
{
	// ViewAngle
	uintptr_t ViewAngleAddress =
			OH::CalcOffset<uintptr_t>(HackClass.EngineBase, OffsetV.dwClientState) + OffsetV.dwClientState_ViewAngles;
	Vec3 ViewAngle = *(Vec3*)ViewAngleAddress;
	// ShotsFired
	int ShotsFired = OH::CalcOffset<int>(HackClass.PlayerEntity, OffsetV.m_iShotsFired);
	// AimPunch
	Vec3 AimPunchAngle = OH::CalcOffset<Vec3>(HackClass.PlayerEntity, OffsetV.m_aimPunchAngle);

	Vec3 OPunch = { 0, 0, 0 };

	if (ShotsFired > 1)
	{
		Vec3 NewPunch = {AimPunchAngle.x - OPunch.x, AimPunchAngle.y - OPunch.y, 0};

		ViewAngle.x -= NewPunch.x * 2.0f;
		ViewAngle.y -= NewPunch.y * 2.0f;
		ViewAngle.z = 0;

		*(Vec3*)ViewAngleAddress = ViewAngle;
		OPunch = AimPunchAngle;
	}
	else
	{
		OPunch = {0, 0, 0};
	}
}

#endif //CSGOINTERNAL_HACKLIST_CPP