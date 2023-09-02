#ifndef CSGOINTERNAL_HACKLIST_CPP
#define CSGOINTERNAL_HACKLIST_CPP

#include "HackList.h"


void BHop_Hack()
{
	if (FPSUtils::IsPlayerMoving())
	{
		int JumpState = HackClass.PlayerEntity->m_fFlag;

		static int FL_ONGROUND = 0b0000'0001; // Bitwise pattern for the player being on ground

		if (JumpState & FL_ONGROUND)
		{
			*(uintptr_t*)(HackClass.ClientBase + PresetOffset::dwForceJump) = 6;
		}
	}

}


void Glow_Hack()
{
	int PlayerTeam = HackClass.PlayerEntity->m_iTeam;
	uintptr_t GlowObject = *(uintptr_t*)(HackClass.ClientBase + PresetOffset::dwGlowObjectManager);


	for (unsigned int i = 0; i < 64; i++)
	{
		uintptr_t EntityObject = *(uintptr_t*)(HackClass.ClientBase + PresetOffset::dwEntityList + i * 0x10);

		if (EntityObject != NULL)
		{
			int EntityTeam = *(uintptr_t*)(EntityObject + PresetOffset::m_iTeamNum);
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
	int CrosshairInfo = HackClass.PlayerEntity->m_CrosshairID;

	if (CrosshairInfo != 0 && CrosshairInfo < 64)
	{
		uintptr_t Entity = *(uintptr_t*)(HackClass.ClientBase + PresetOffset::dwEntityList +
										 (CrosshairInfo - 1) * 0x10);

		if (Entity != NULL)
		{
			int EntityHP = *(uintptr_t*)Entity + PresetOffset::m_iHealth;
			if (EntityHP > 0)
			{
				*(uintptr_t*)(HackClass.ClientBase + PresetOffset::dwForceAttack) = 6;

				// Distance Vars
				Vec3 PlayerPos = HackClass.PlayerEntity->m_Vecorigin;
				Vec3 EntPos = *(Vec3*)(Entity + PresetOffset::m_vecOrigin);
				Sleep(FPSUtils::DistanceDif(EntPos, PlayerPos) * 0.333);
			}
		}
	}
}

#endif //CSGOINTERNAL_HACKLIST_CPP