#include <math.h>
#include <nds.h>

struct v3 {
	float x;
	float y;
	float z;
};

// normalize vector3 to be length 1
struct v3 normalize(struct v3 in);

u16 v3_to_color(struct v3 in);
