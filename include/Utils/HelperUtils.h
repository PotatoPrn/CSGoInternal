#ifndef CSGOINTERNAL_HELPERUTILS_H
#define CSGOINTERNAL_HELPERUTILS_H


#include "Sdk/Offsets.h"
#include <Windows.h>

#define PI 3.14159265f

/// FPS related helpers, mainly distance calc
namespace FPSUtils
{
	bool IsPlayerMoving();

	float DistanceDif(Vec3 Dst, Vec3 Src);

	Vec3 NormaliseViewAngle(Vec3 Angle);

	void CalculateAngle(Vec3 Angle);

	Vec3 GetBonePos(uintptr_t Entity, int BoneID);
}

/// Glow Related Stuff
namespace GlowUtils
{

	/// Set Enemy and Team Glow Outline
	void SetTeamGlow(int GlowIndex, uintptr_t GlowObject);

	void SetEnemyGlow(uintptr_t Entity, int GlowIndex, uintptr_t GlowObject);

	void ModifyBrightness();
}

struct ClrRenderStruct
{
	BYTE Red, Green, Blue;
};

extern ClrRenderStruct EnemyTeamColor;
extern ClrRenderStruct AllyTeamColor;

struct GlowStruct
{
	//https://www.unknowncheats.me/forum/counterstrike-global-offensive/223356-external-glow-struct.html
	BYTE dwBase[8]; // 0x00
	float Red; // 0x8
	float Green; // 0xc
	float Blue; // 0x10
	float Alpha; // 0x14
	BYTE Junk[4]; // 0x18
	float Flunk; // 0x1c
	float Bloom; // 0x20
	float Flunk1; // 0x24
	bool RenderWhenOcculeded; // 0x28
	bool RenderWhenUnoccluded; // 0x29
	bool FullBloomRender; // 0x30
	BYTE Junk1[1]; // 0x31
	int BloomStencilTestValue; // 0x35
	int GlowStyle; // 0x39
	int SplitScreenSlot; // 0x3D
	int NextFreeSlot; // 0x41
};


#endif //CSGOINTERNAL_HELPERUTILS_H