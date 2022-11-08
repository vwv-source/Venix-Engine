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

void VE2D_init();
void VE2D_clear(uint32_t color);
void VE2D_swap_buffers();
void VE2D_draw_rect(VE2D_Rect rectangle, uint32_t color);
void VE2D_set_pixel(int x, int y, uint32_t color);
void VE2D_fill_rect(VE2D_Rect rectangle, uint32_t color);
void VE2D_draw_circle(VE2D_Circle circle, uint32_t color);