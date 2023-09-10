#ifndef CSGOINTERNAL_HACKLIST_CPP
#define CSGOINTERNAL_HACKLIST_CPP

#include "HackList.h"
#include "Utils/HelperUtils.h"
#include "main.h"

#include <time.h>


void BHop_Hack()
{
	if (FPSUtils::IsPlayerMoving())
	{
		int JumpState = HackClass.PlayerEntity->m_fFlag;

		static int FL_ONGROUND = 0b0000'0001; // Bitwise pattern for the player being on ground

		if (JumpState & FL_ONGROUND)
		{
			*(OffsetV.m_Forcejump) = 6;
		}
	}
}


void Glow_Hack()
{
	int PlayerTeam = HackClass.PlayerEntity->m_iTeam;
	uintptr_t GlowObject = *(uintptr_t*)(HackClass.ClientBase + PresetOffset::dwGlowObjectManager);

	// 64 since the entity list for humanoids are below 64
	for (unsigned int i = 0; i < 64; i++)
	{
		uintptr_t EntityObject = *(uintptr_t*)(HackClass.ClientBase + PresetOffset::dwEntityList + i * 0x10);

		if (EntityObject != NULL)
		{
			int EntityTeam = *(uintptr_t*)(EntityObject + OffsetV.m_iTeamNum);
			int GlowIndex = *(uintptr_t*)(EntityObject + PresetOffset::m_iGlowIndex);

			if (EntityTeam == PlayerTeam)
			{
				// Draw Player Team
				GlowUtils::SetTeamGlow(GlowIndex, GlowObject);
				*(ClrRenderStruct*)(EntityObject + PresetOffset::m_clrRender) = AllyTeamColor;
			}
			else
			{
				GlowUtils::SetEnemyGlow(EntityObject, GlowIndex, GlowObject);
				*(ClrRenderStruct*)(EntityObject + PresetOffset::m_clrRender) = EnemyTeamColor;
				// Draw Enemy Team
			}
		}
	}
}


void TriggerBot()
{

	static size_t LastTime = 0;
	int CrosshairInfo = HackClass.PlayerEntity->m_CrosshairID;

	if (CrosshairInfo != 0 && CrosshairInfo < 64)
	{
		uintptr_t Entity = *(uintptr_t*)(HackClass.ClientBase + PresetOffset::dwEntityList +
										 (CrosshairInfo - 1) * 0x10);

		if (Entity != NULL)
		{
			int EntityHP = *(uintptr_t*)Entity + OffsetV.m_iHealth;

			// Great Thread Safety delay
			// https://www.mpgh.net/forum/showthread.php?t=1047609
			if (EntityHP > 0 && GetTickCount() > LastTime)
			{
				*(uintptr_t*)(HackClass.ClientBase + PresetOffset::dwForceAttack) = 6;
				Vec3 PlayerPos = HackClass.PlayerEntity->m_Vecorigin;
				Vec3 EntPos = *(Vec3*)(Entity + OffsetV.m_vecOrigin);
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
		uintptr_t Entity = *(uintptr_t*)(HackClass.ClientBase + PresetOffset::dwEntityList + i * 0x10);

		if (Entity != NULL)
		{
			bool m_bDormant = *(bool*)(Entity + PresetOffset::m_bDormant);
			int EntTeamVal = *(int*)(Entity + OffsetV.m_iTeamNum);

			int TeamValue = HackClass.PlayerEntity->m_iTeam;

			if (!m_bDormant && TeamValue != EntTeamVal)
			{
				// Grab Entity Health
				int EntHealth = *(int*)(Entity + OffsetV.m_iHealth);

				if (EntHealth > 0)
				{
					// Grab position...
					Vec3 PlayerPos = HackClass.PlayerEntity->m_Vecorigin;
					Vec3 EntityPos = *(Vec3*)(Entity + OffsetV.m_vecOrigin);

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


#endif //CSGOINTERNAL_HACKLIST_CPP