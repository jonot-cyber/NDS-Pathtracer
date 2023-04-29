#include <nds.h>

#include "ray.h"

#define COLOR(r, g, b) ((r) | (g)<<5 | (b)<<10)
#define OFFSET(r, c, w) ((r)*(w)+(c))

struct Vector3 {
	float x;
	float y;
	float z;
};

void set_pixel(int row, int col, u16 color) {
	VRAM_A[OFFSET(row, col, SCREEN_WIDTH)] = color;
}

int main() {
	REG_DISPCNT = MODE_FB0;
	VRAM_A_CR = VRAM_ENABLE;

	while (1) {
		swiWaitForVBlank();
		for (int y = 0; y < SCREEN_HEIGHT; y++) {
			for (int x = 0; x < SCREEN_WIDTH; x++) {
				struct ray d = ray_for_pixel(y, x, 70);
				set_pixel(y, x, v3_to_color(d.dir));
			}
		}
	}
}
