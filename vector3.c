#include "vector3.h"

#define COLOR(r, g, b) ((r) | (g)<<5 | (b)<<10)

struct v3 normalize(struct v3 in) {
	float len = sqrt(in.x*in.x + in.y*in.y + in.z * in.z);
	struct v3 ret = {
		.x = in.x / len,
		.y = in.y / len,
		.z = in.z / len,
	};
	return ret;
}

u16 v3_to_color(struct v3 in) {
	int r = 31 * in.x;
	int g = 31 * in.y;
	int b = 31 * in.z;
	return COLOR(r, g, b);
}

float dot(struct v3 a, struct v3 b) {
	return a.x*b.x + a.y*b.y + a.z*b.z;
}
