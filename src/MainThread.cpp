#ifndef CSGOINTERNAL_MAINTHREAD_CPP
#define CSGOINTERNAL_MAINTHREAD_CPP

#include "MainThread.h"
#include "Utils/HelperUtils.h"
#include "DX9Utils/Draw.h"


void HackThread()
{
	// Setup Player Object Entity;
	//HackClass.PlayerEntity = *(PlayerObject**)(HackClass.ClientBase + OffsetV.dwLocalPlayer);
	HackClass.PlayerEntity = *(uintptr_t*)(HackClass.ClientBase + OffsetV.dwLocalPlayer);


	/// Not needed as since we are hooking, we will need to have this repatch with the original bytes
	/// DLL Detach Hotkey
	/*
	if (GetAsyncKeyState(VK_DELETE) & 1)
	{
		break;
	}*/

	// Check if Player Entity is null, if not, continue
	if (HackClass.PlayerEntity != NULL)
	{

		/// Open Hack Menu
		if (GetAsyncKeyState(VK_F1) & 1)
		{
			THacks.T_ShowMenu = !THacks.T_ShowMenu;
		}


		/// ESP
		if (GetAsyncKeyState(VK_F5) & 1)
		{
			THacks.T_ESP = !THacks.T_ESP;
		}

		/// Recoil Control
		if (GetAsyncKeyState(VK_F6) & 1)
		{
			THacks.T_RCS = !THacks.T_RCS;
		}


		/// Aimbot Hack Toggle
		if (GetAsyncKeyState(VK_F7) & 1)
		{
			THacks.T_AimBot = !THacks.T_AimBot;
		}

		/// Glow Hack Toggle
		if (GetAsyncKeyState(VK_F8) & 1)
		{
			GlowUtils::ModifyBrightness();
			THacks.T_Glow = !THacks.T_Glow;
		}

		/// BHop Related Hack Toggle
		if (GetAsyncKeyState(VK_F9) & 1)
		{
			THacks.T_BHop = !THacks.T_BHop;
		}


		/// Triggerbot Hack Toggle
		if (GetAsyncKeyState(VK_F10) & 1)
		{
			THacks.T_TrigBot = !THacks.T_TrigBot;
		}

		if (GetAsyncKeyState(VK_SHIFT) == KEYDOWN && !THacks.T_TrigBot2)
		{
			THacks.T_TrigBot = true;
			THacks.T_TrigBot2 = true;
		}

		if (GetAsyncKeyState(VK_SHIFT) == KEYUP && THacks.T_TrigBot2)
		{
			THacks.T_TrigBot = false;
			THacks.T_TrigBot2 = false;
		}


		/// Hack Function Loop
		if (THacks.T_ESP)
		{
			ESP();
		}

		if (THacks.T_RCS)
		{
			RCS();
		}

		if (THacks.T_TrigBot)
		{
			TriggerBot();
		}

		if (GetAsyncKeyState(VK_SPACE) && THacks.T_BHop)
		{
			BHop_Hack();
		}

		if (THacks.T_Glow)
		{
			Glow_Hack();
		}

		if (THacks.T_AimBot)
		{
			Aimbot();
		}
	}
}

#endif //CSGOINTERNAL_MAINTHREAD_CPP