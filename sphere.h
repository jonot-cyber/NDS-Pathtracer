#ifndef SPHERE_H
#define SPHERE_H

#include <stdbool.h>
#include "vector3.h"

struct sphere {
	float r;
	struct v3 o;
	struct v3 color;
};

#endif
