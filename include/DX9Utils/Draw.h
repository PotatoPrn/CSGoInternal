#ifndef CSGOINTERNAL_DRAW_H
#define CSGOINTERNAL_DRAW_H

#include "main.h"

void DrawFilledRect(int x, int y, int w, int h, D3DCOLOR color);

void DrawLine(int x1, int y1, int x2, int y2, int thickness, D3DCOLOR Color);
void DrawLine(Vec2 Src, Vec2 Dst, int Thickness, D3DCOLOR Color);

void DrawTextF(const char* Text, float x, float y, D3DCOLOR Color);

void DrawMenu();

namespace ESPHacks
{
	void DrawCrossHair();

	void DrawSnapLine();

	void DrawESPBox(Vec2 Top, Vec2 Bot, int Thickness, D3DCOLOR Color);
}



#endif //CSGOINTERNAL_DRAW_H