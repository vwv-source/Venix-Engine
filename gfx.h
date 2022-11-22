#include <cstdint>
#include <math.h>

class VGE_Rect {
    public:
        int x;
        int y;
        int w;
        int h;
};

class VGE_Circle {
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

void VGE_init();
void VGE_clear(uint32_t color);
void VGE_swap_buffers();
void VGE_draw_rect(VGE_Rect rectangle, uint32_t color);
void VGE_set_pixel(int x, int y, uint32_t color);
void VGE_fill_rect(VGE_Rect rectangle, uint32_t color);
void VGE_draw_circle(VGE_Circle circle, uint32_t color);
void VGE_image_draw(int x, int y, uint32_t * pixelarray);
void VGE_draw_line(float x, float y, float x1, float y1, uint32_t color);
void VGE_fill_triangle(Vector2D v1, Vector2D v2, Vector2D v3, uint32_t color);
uint32_t * VGE_image_init(char* filename);