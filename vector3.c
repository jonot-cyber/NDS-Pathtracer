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
	int r = 15 * (in.x + 1);
	int g = 15 * (in.y + 1);
	int b = 0;
	return COLOR(r, g, b);
}
