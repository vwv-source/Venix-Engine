#include <cstdint>
#include <pspge.h>
#include <pspdisplay.h>
#include <psputils.h>
#include <math.h>

uint32_t* draw_buffer;
uint32_t* disp_buffer;

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

void VE2D_init(){
    draw_buffer = static_cast<uint32_t*>(sceGeEdramGetAddr());
    //disp_buffer = (uint32_t*)sceGeEdramGetAddr() + (272 * 512 * 4);
    sceDisplaySetMode(0,512,272);
    sceDisplaySetFrameBuf(disp_buffer, 512, PSP_DISPLAY_PIXEL_FORMAT_8888, 0);
}

void VE2D_clear(uint32_t color){
    for(int i = 0; i<512 *272; i++){
        draw_buffer[i] = color;
    }
}

void VE2D_swap_buffers(){
    uint32_t* temp = disp_buffer;
    disp_buffer = draw_buffer;
    draw_buffer = temp;

    sceKernelDcacheWritebackInvalidateAll();
    sceDisplaySetFrameBuf(disp_buffer, 512, PSP_DISPLAY_PIXEL_FORMAT_8888, PSP_DISPLAY_SETBUF_IMMEDIATE);
}

void VE2D_set_pixel(int x, int y, uint32_t color){
    if(x > 512){
        x = 512;
    }
    if(y*512 > 512*272){
        y = 0;
    }
    draw_buffer[x + (y * 512)] = color;
}

void VE2D_draw_rect(VE2D_Rect rectangle, uint32_t color){
    for (int i = 0; i <= rectangle.h; i++) {
        VE2D_set_pixel(rectangle.x + rectangle.w, rectangle.y, color);
        VE2D_set_pixel(rectangle.x, rectangle.y++, color);
    }
    for (int i = 0; i <= rectangle.w; i++) {
        VE2D_set_pixel(rectangle.x, rectangle.y - rectangle.h - 1, color);
        VE2D_set_pixel(rectangle.x++, rectangle.y, color);
    }
}

void VE2D_fill_rect(VE2D_Rect rectangle, uint32_t color){
    for (int i = 0; i <= rectangle.h; i++) {
        int localRectX = rectangle.x;
        rectangle.y++;
        for (int i = 0; i <= rectangle.w; i++) {
            VE2D_set_pixel(localRectX++, rectangle.y, color);
        }
    }
}

void VE2D_draw_circle(VE2D_Circle circle, uint32_t color) {
    for (int i = -circle.r; i <= circle.r; i++) {
        VE2D_set_pixel(i + circle.x + circle.r, sqrt(pow(circle.r, 2) - pow(i, 2)) + circle.y + circle.r , color);
        VE2D_set_pixel(i + circle.x + circle.r, -sqrt(pow(circle.r, 2) - pow(i, 2)) + circle.y + circle.r, color);
    }
}