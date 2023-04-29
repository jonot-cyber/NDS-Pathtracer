#include "ray.h"

#define DEG2RAD(d) (M_PI*(d)/180)

struct ray ray_for_pixel(int y, int x, float fov) {
	fov = DEG2RAD(fov);
	float new_y = (float)(y - SCREEN_HEIGHT / 2) / SCREEN_WIDTH;
	float new_x = (float)(x - SCREEN_WIDTH / 2) / SCREEN_WIDTH;
	float back = sqrt(0.25*(cos(fov)+1)/(1-cos(fov)));

	struct v3 base = {
		.x = 0,
		.y = 0,
		.z = -back,
	};

	struct v3 head = {
		.x = new_x,
		.y = new_y,
		.z = 0,
	};

	struct ray ret = {
		.o = base,
		.dir = normalize(head),
	};
	return ret;
}
