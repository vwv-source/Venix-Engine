#include <cstdint>
#include <math.h>

class VE2D_Rect {
    public:
        int x;
        int y;
        int w;
        int h;
};

class VE2D_Circle {
    public:
        int x;
        int y;
        int r;
};

class Vector2D{
	public:
		float x;
		float y;
};

void VE2D_init();
void VE2D_clear(uint32_t color);
void VE2D_swap_buffers();
void VE2D_draw_rect(VE2D_Rect rectangle, uint32_t color);
void VE2D_set_pixel(int x, int y, uint32_t color);
void VE2D_fill_rect(VE2D_Rect rectangle, uint32_t color);
void VE2D_draw_circle(VE2D_Circle circle, uint32_t color);
void VE2D_image_draw(int x, int y, uint32_t * pixelarray);
void VE2D_draw_line(float x, float y, float x1, float y1, uint32_t color);
void VE2D_fill_triangle(Vector2D v1, Vector2D v2, Vector2D v3, uint32_t color);
uint32_t * VE2D_image_init(char* filename);