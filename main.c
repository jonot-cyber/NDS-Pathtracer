#include <nds.h>
#include <time.h>

#include "ray.h"
#include "sphere.h"
#include "vector3.h"

#define COLOR(r, g, b) ((r) | (g)<<5 | (b)<<10)
#define OFFSET(r, c, w) ((r)*(w)+(c))
#define RANDF() ((float)(rand() % 1000000) / 1000000)

const int SPHERES = 256;

const float ASPECT_RATIO = (double)SCREEN_WIDTH / SCREEN_HEIGHT;
const float VIEWPORT_HEIGHT = 2.0;
const float VIEWPORT_WIDTH = ASPECT_RATIO * VIEWPORT_HEIGHT;
const float FOCAL_LENGTH = 1.0;

const float LLX = -VIEWPORT_WIDTH/2;
const float LLY = -VIEWPORT_HEIGHT/2;
const float LLZ = -FOCAL_LENGTH;

struct Vector3 {
	float x;
	float y;
	float z;
};

void set_pixel(int row, int col, u16 color) {
	VRAM_A[OFFSET(row, col, SCREEN_WIDTH)] = color;
}

void create_spheres(struct sphere* world, size_t len) {
	for (int i = 0; i < len; i++) {
		world[i].o.x = rand() % 100 - 50;
		world[i].o.y = rand() % 100 - 50;
		world[i].o.z = rand() % 100 - 50;
		world[i].r = rand() % 10;
		world[i].color.x = RANDF();
		world[i].color.y = RANDF();
		world[i].color.z = RANDF();
	}
}

int main() {
	srand(time(NULL));
	consoleDemoInit();
	// setup world
	struct sphere* world = malloc(SPHERES * sizeof(struct sphere));
	create_spheres(world, SPHERES);
	
	REG_DISPCNT = MODE_FB0;
	VRAM_A_CR = VRAM_ENABLE;

	swiWaitForVBlank();
	iprintf("Jonot's NDS Pathtracer");
	for (int y = 0; y < SCREEN_HEIGHT; y++) {
		for (int x = 0; x < SCREEN_WIDTH; x++) {
			float u = (float)x/(SCREEN_WIDTH-1);
			float v = (float)y/(SCREEN_HEIGHT-1);
			struct ray d = {
				.o = {
					.x = 0,
					.y = 0,
					.z = 0,
				},
				.dir = {
					.x = LLX + u*VIEWPORT_WIDTH,
					.y = LLY + v*VIEWPORT_HEIGHT,
					.z = LLZ,
				}
			};

			set_pixel(y, x, v3_to_color(ray_trace(d, world, SPHERES, 4, 0, NULL)));
		}
	}
	while (1) {}
	free(world);
}
