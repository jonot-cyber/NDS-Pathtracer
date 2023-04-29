#include <math.h>
#include <nds.h>

#include "vector3.h"

struct ray {
	struct v3 o;
	struct v3 dir;
};

struct ray ray_for_pixel(int y, int x, float fov);
