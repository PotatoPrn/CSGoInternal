#ifndef CSGOINTERNAL_MAINTHREAD_CPP
#define CSGOINTERNAL_MAINTHREAD_CPP

#include "MainThread.h"
#include "Utils/HelperUtils.h"



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

		/// ESP
		if (GetAsyncKeyState(VK_F5) & 1)
		{
			THacks.T_ESP =!THacks.T_ESP;
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


		/// Temporary UI
		DbgPrint([F5] ESP Hack > , THacks.T_ESP);
		DbgPrint([F6] RCS Hack > , THacks.T_RCS);
		DbgPrint([F7] Aimbot Hack > , THacks.T_AimBot);
		DbgPrint([F8] Glow Hack > , THacks.T_Glow);
		DbgPrint([F9] Bhop Hack > , THacks.T_BHop);
		DbgPrint([F10] / [Shift] Triggerbot Hack > , THacks.T_TrigBot);

	}
	UI::ClearConsole();
}

#endif //CSGOINTERNAL_MAINTHREAD_CPP