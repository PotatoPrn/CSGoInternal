#ifndef CSGOINTERNAL_DRAW_CPP
#define CSGOINTERNAL_DRAW_CPP

#include "DX9Utils/Draw.h"

#include <sstream>


void DrawFilledRect(int x, int y, int w, int h, D3DCOLOR color)
{
	D3DRECT rect = { x, y, x + w, y + h };
	pDevice->Clear(1, &rect, D3DCLEAR_TARGET, color, 0, 0);
}

void DrawLine(int x1, int y1, int x2, int y2, int thickness, D3DCOLOR Color)
{
	D3DXCreateLine(pDevice, &HackClass.LineL);

	D3DXVECTOR2 Line[2];
	Line[0] = D3DXVECTOR2(x1, y1);
	Line[1] = D3DXVECTOR2(x2, y2);
	HackClass.LineL->SetWidth(thickness);
	HackClass.LineL->Draw(Line, 2, Color);
	HackClass.LineL->Release();
}

/// Drawline Wrapper
void DrawLine(Vec2 Src, Vec2 Dst, int Thickness, D3DCOLOR Color)
{
	DrawLine(Src.x, Src.y, Dst.x, Dst.y, Thickness, Color);
}

void DrawTextF(const char* Text, float x, float y, D3DCOLOR Color)
{
	RECT Rect;

	if (!HackClass.FontF) /// Keeps returning NULL... :/
		// Create Font
		D3DXCreateFont(pDevice, 14, 0, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
				DEFAULT_PITCH | FF_DONTCARE, "Arial", &HackClass.FontF);

	// Offset by 1 so we can read text
	SetRect(&Rect, x + 1, y + 1, x + 1, y + 1);
	HackClass.FontF->DrawTextA(NULL, Text, -1, &Rect, DT_CENTER | DT_NOCLIP, D3DCOLOR_ARGB(255, 0, 0, 0));

	SetRect(&Rect, x, y, x, y);
	HackClass.FontF->DrawText(NULL, Text, -1, &Rect, DT_CENTER | DT_NOCLIP, Color);
}

/// Draw Menu
void DrawMenu()
{
	int MenuOffX = WindowWidth / 2; // Centre
	int MenuOffY = 50;
	D3DCOLOR Enabled = D3DCOLOR_ARGB(255, 0, 255, 0);
	D3DCOLOR Disabled = D3DCOLOR_ARGB(255, 255, 0, 0);

	if (!THacks.T_ShowMenu)
		DrawTextF("ShowMenu (F1)", MenuOffX, MenuOffY, D3DCOLOR_ARGB(255, 255, 255, 255));
	else
	{
		/// MenuOffY + Index * Distance
		DrawTextF("F10/Shift TriggerBot Hack", MenuOffX, MenuOffY + 0 * 12, THacks.T_TrigBot ? Enabled : Disabled);
		DrawTextF("F9 BHop Hack", MenuOffX, MenuOffY + 1 * 12, THacks.T_BHop ? Enabled : Disabled);
		DrawTextF("F8 Glow Hack", MenuOffX, MenuOffY + 2 * 12, THacks.T_Glow ? Enabled : Disabled);
		DrawTextF("F7 Aimbot Hack", MenuOffX, MenuOffY + 3 * 12, THacks.T_AimBot ? Enabled : Disabled);
		DrawTextF("F6 Recoil Control Hack", MenuOffX, MenuOffY + 4 * 12, THacks.T_RCS ? Enabled : Disabled);
		DrawTextF("F5 ESP Hack", MenuOffX, MenuOffY + 5 * 12, THacks.T_ESP ? Enabled : Disabled);
	}
}


Vec2 CrossHair2D;
int CrossHairSize = 4;

void ESPHacks::DrawCrossHair()
{
	// Get Aim punch angle to determine where the next shot will land, thus moving the cross hair there
	Vec3 AimPunchAngle = OH::CalcOffset<Vec3>(HackClass.PlayerEntity, OffsetV.m_aimPunchAngle);
	CrossHair2D.x = WindowWidth / 2 - (WindowWidth / 90 * AimPunchAngle.y);
	CrossHair2D.y = WindowHeight / 2 + (WindowHeight / 90 * AimPunchAngle.x);


	Vec2 L, R, T, B;

	L = R = T = B = CrossHair2D;

	L.x -= CrossHairSize;
	R.x += CrossHairSize;
	B.y += CrossHairSize;
	T.y -= CrossHairSize;

	DrawLine(L, R, 2, D3DCOLOR_ARGB(255, 255, 255, 255));
	DrawLine(T, B, 2, D3DCOLOR_ARGB(255, 255, 255, 255));

}


void ESPHacks::DrawSnapLine()
{
	/// The view matrix is found by punching in the view angle into a 3d rotation converter then scanning it and looking for all matrixs
	/// https://guidedhacking.com/threads/how-to-get-started-with-learning-viewmatrix.13663/
	float ViewMatrix[16];
	memcpy(&ViewMatrix, (PBYTE)(HackClass.ClientBase + OffsetV.dwViewMatrix), sizeof(ViewMatrix));


	// 1 to skip the player
	for (unsigned int i = 1; i < 64; i++)
	{
		uintptr_t Entity = *(uintptr_t*)(HackClass.ClientBase + OffsetV.dwEntityList + i * 0x10);

		if (FPSUtils::VerifyEntity(Entity))
		{

			D3DCOLOR Color;
			if (!FPSUtils::SameTeamCheck(Entity))
			{
				Color = D3DCOLOR_ARGB(255, 255, 0, 0);
			}
			else
			{
				Color = D3DCOLOR_ARGB(255, 0, 255, 0);
			}

			Vec3 EntHeadPos3D = FPSUtils::GetBonePos(Entity, 8);
			EntHeadPos3D += 5;

			Vec2 EntPos2D, EntHead2D;
			Vec3 EntityPos = OH::CalcOffset<Vec3>(Entity, OffsetV.m_vecOrigin);

			if (FPSUtils::World2Screen(ViewMatrix, EntityPos, EntPos2D))
			{
				DrawLine(EntPos2D.x, EntPos2D.y, WindowWidth / 2, WindowHeight, 2, Color);

				if (FPSUtils::World2Screen(ViewMatrix, EntHeadPos3D, EntHead2D))
				{
					ESPHacks::DrawESPBox(EntPos2D, EntHead2D, 2, Color);
				}
			}

			std::stringstream s1, s2;
			s1 << OH::CalcOffset<int>(Entity, OffsetV.m_iHealth);
			std::string t1 = "HP: " + s1.str();
			char* HealthMsg = (char*)t1.c_str();

			DrawTextF(HealthMsg, EntPos2D.x, EntPos2D.y, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}
}

void ESPHacks::DrawESPBox(Vec2 Top, Vec2 Bot, int Thickness, D3DCOLOR Color)
{
	int Height = ABS(Top.y - Bot.y);

	// Top left & Top Right
	Vec2 TL, TR;
	TL.x = Top.x - Height / 4;
	TR.x = Top.x + Height / 4;
	TL.y = TR.y = Top.y;

	// Bottom Left & Bottom Right
	Vec2 BL, BR;
	BL.x = Bot.x - Height / 4;
	BR.x = Bot.x + Height / 4;
	BL.y = BR.y = Bot.y;

	DrawLine(TL, TR, Thickness, Color);
	DrawLine(TL, BL, Thickness, Color);
	DrawLine(TR, BR, Thickness, Color);
	DrawLine(BL, BR, Thickness, Color);

}

#endif //CSGOINTERNAL_DRAW_CPP