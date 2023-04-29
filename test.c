#include <nds.h>

#define COLOR(r, g, b) ((r) | (g)<<5 | (b)<<10)
#define OFFSET(r, c, w) ((r)*(w)+(c))

int main() {
	REG_DISPCNT = MODE_FB0;
	VRAM_A_CR = VRAM_ENABLE;

	while (1) {
		swiWaitForVBlank();
		for (int y = 0; y < SCREEN_HEIGHT; y++) {
			for (int x = 0; x < SCREEN_WIDTH; x++) {
				int r = 31 * x / SCREEN_WIDTH;
				int g = 31 * y / SCREEN_HEIGHT;
				set_pixel(y, x, COLOR(r, g, 0));
			}
		}
	}
}

void set_pixel(int row, int col, u16 color) {
	VRAM_A[OFFSET(row, col, SCREEN_WIDTH)] = color;
}
