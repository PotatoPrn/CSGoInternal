#ifndef CSGOINTERNAL_DRAW_CPP
#define CSGOINTERNAL_DRAW_CPP

#include "DX9Utils/Draw.h"


void DrawFilledRect(int x, int y, int w, int h, D3DCOLOR color)
{
	D3DRECT rect = { x, y, x + w, y + h };
	pDevice->Clear(1, &rect, D3DCLEAR_TARGET, color, 0, 0);

}

#endif //CSGOINTERNAL_DRAW_CPP