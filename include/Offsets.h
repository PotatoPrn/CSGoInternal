#ifndef INTTEMPLATE_OFFSETS_H
#define INTTEMPLATE_OFFSETS_H

// Auto Padding
#define STR_MERGE_IMPL(a, b) a##b
#define STR_MERGE(a, b) STR_MERGE_IMPL(a, b)
#define MAKE_PAD(size) STR_MERGE(_pad, __COUNTER__)[size]
#define DEFINE_MEMBER_N(type, name, offset) struct {unsigned char MAKE_PAD(offset); type name;}


// Generic Structs
struct Vec3
{
	float X, Y, Z;
};


// Offsets Here

class PlayerEntity
{
public:
	union
	{

	};

};


#endif //INTTEMPLATE_OFFSETS_H
