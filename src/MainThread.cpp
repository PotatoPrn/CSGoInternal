#ifndef CSGOINTERNAL_MAINTHREAD_CPP
#define CSGOINTERNAL_MAINTHREAD_CPP

#include "MainThread.h"
#include "Utils/HelperUtils.h"



void HackThread()
{
	// Setup Player Object Entity;
	HackClass.PlayerEntity = *(PlayerObject**)(HackClass.ClientBase + PresetOffset::dwLocalPlayer);
	std::cout << OffsetV.dwGlowObjectManager << std::endl << std::hex << (uintptr_t*)(HackClass.ClientBase + PresetOffset::dwGlowObjectManager);
	//std::cout << OffsetV.m_bDormant << std::endl;

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
		std::cout << "[F7] Aimbot Hack > " << THacks.T_AimBot << "\n";
		std::cout << "[F8] Glow Hack > " << THacks.T_Glow << "\n";
		std::cout << "[F9] Bhop Hack > " << THacks.T_BHop << "\n";
		std::cout << "[F10] / [Shift] Triggerbot Hack > " << THacks.T_TrigBot << "\n";

	}
	UI::ClearConsole();
}

#endif //CSGOINTERNAL_MAINTHREAD_CPP