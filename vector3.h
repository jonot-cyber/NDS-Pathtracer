#ifndef V3_H
#define V3_H
#include <math.h>
#include <nds.h>

struct v3 {
	float x;
	float y;
	float z;
};

// normalize vector3 to be length 1
struct v3 normalize(struct v3 in);

// convert a vector3 to a color
u16 v3_to_color(struct v3 in);

// dot product
float dot(struct v3 a, struct v3 b);
#endif
