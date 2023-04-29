#include <stddef.h>
#include "ray.h"

#define DEG2RAD(d) (M_PI*(d)/180)

const float SENSOR_SIZE = 8;

struct ray ray_for_pixel(int y, int x, float fov) {
	// fov = DEG2RAD(fov);
	// float back = sqrt(SENSOR_SIZE/4*(cos(fov)+1)/(1-cos(fov)));

	struct v3 base = {
		.x = x,
		.y = y,
		.z = -10,
	};

	struct v3 head = {
		.x = x,
		.y = y,
		.z = 0,
	};

	struct ray ret = {
		.o = base,
		.dir = normalize(head),
	};
	return ret;
}

struct v3 ray_trace(struct ray ray, struct sphere* world, size_t len, int max_bounce, int bounce_count, struct sphere* ignore) {
	struct v3 ret = {
		.x = 1,
		.y = 1,
		.z = 1,
	};
	if (bounce_count > max_bounce)
		return ret;

	struct sphere* min_sphere = NULL;
	float min_distance = INFINITY;
	for (int i = 0; i < len; i++) {
		if (world+i == min_sphere)
			continue;
		float intersection = ray_intersects_sphere(ray, world[i]);
		if (intersection < min_distance) {
			min_distance = intersection;
			min_sphere = world+i;
		}
	}
	if (min_sphere == NULL)
		return ret;

	struct v3 origin = {
		.x = ray.o.x + min_distance * ray.dir.x,
		.y = ray.o.y + min_distance * ray.dir.y,
		.z = ray.o.z + min_distance * ray.dir.z,
	};

	struct v3 normal = {
		.x = origin.x - min_sphere->o.x,
		.y = origin.y - min_sphere->o.y,
		.z = origin.z - min_sphere->o.z,
	};
	normal = normalize(normal);

	struct ray other_ray = {
		.o = origin,
		.dir = normal,
	};

	struct v3 incoming = ray_trace(other_ray, world, len, max_bounce, bounce_count + 1, min_sphere);
	incoming.x *= min_sphere->color.x;
	incoming.y *= min_sphere->color.y;
	incoming.z *= min_sphere->color.z;
	return incoming;
}

float ray_intersects_sphere(struct ray ray, struct sphere sphere) {
	struct v3 O = {
		.x = ray.o.x - sphere.o.x,
		.y = ray.o.y - sphere.o.y,
		.z = ray.o.z - sphere.o.z,
	};
	float A = dot(ray.dir, ray.dir);
	float B = 2 * dot(O, ray.dir);
	float C = dot(O, O) - sphere.r * sphere.r;
	float discriminant = B*B-4*A*C;
	if (discriminant < 0)
		return INFINITY;
	float p1 = -B/(2*A);
	float p2 = sqrt(discriminant)/(2*A);
	float t1 = p1 + p2;
	float t2 = p1 - p2;
	if (t1 < 0 && t2 < 0)
		return INFINITY;
	return t2;
}
