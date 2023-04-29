#ifndef RAY_H
#define RAY_H

#include <math.h>
#include <nds.h>

#include "sphere.h"
#include "vector3.h"

struct ray {
	struct v3 o;
	struct v3 dir;
};

struct ray ray_for_pixel(int y, int x, float fov);

struct v3 ray_trace(struct ray ray, struct sphere* world, size_t len, int max_bounce, int bounce_count, struct sphere* ignore);

float ray_intersects_sphere(struct ray ray, struct sphere sphere);
#endif
