#include <cstdint>
#include <pspge.h>
#include <pspdisplay.h>
#include <psputils.h>
#include <pspdebug.h>
#include <math.h>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

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

class Vector2D{
	public:
		float x;
		float y;
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
        return;
    }
    if(y*512 > 512*272){
        return;
    }
    x += 480/2;
    y += 272/2;
    draw_buffer[x + (y * 512)] = color;
}

void VE2D_draw_rect(VE2D_Rect rectangle, uint32_t color){
    for (int i = 0; i <= rectangle.h; i++) {
        VE2D_set_pixel(rectangle.x + rectangle.w, rectangle.y + 1, color);
        VE2D_set_pixel(rectangle.x, rectangle.y++ + 1, color);
    }
    for (int i = 0; i <= rectangle.w; i++) {
        VE2D_set_pixel(rectangle.x, rectangle.y - rectangle.h, color);
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

int hexcolor(int r, int g, int b)
{
    return (r<<16) | (g<<8) | b;
}

uint32_t* VE2D_image_init(char* filename){
    std::ifstream image(filename);
    std::string str;
    uint32_t *pixelarray = new uint32_t[5000];
    int temp[3];
    int pixelarrcount;
    int count;
    while(std::getline(image, str, '\n')){
        if(count == 3){
            pixelarrcount++;
            pixelarray[pixelarrcount] = hexcolor(temp[3],temp[2],temp[1]);
            count = 0;
        }
        if(count == 0){temp[1] = std::atoi(str.c_str());}
        if(count == 1){temp[2] = std::atoi(str.c_str());}
        if(count == 2){temp[3] = std::atoi(str.c_str());}
        count++;
    }
    pixelarrcount = 0;
    image.close();
    
    return pixelarray;
}

void VE2D_image_draw(int x, int y, uint32_t* pixelarray){
    //image drawing magic
    int width = 48;
    int height = 71;
    int d = 0+x;
    int l = 0+y;
    int i = 0;

    for(i; i < height*width; i++){
        if(d >= width+x){
            d = 0+x;
            if(l >= height+y){
            }else{
                 l++; 
            }
        }
        d++;

        VE2D_set_pixel(d,l,pixelarray[i]);
    }
    i = 0;
}

void VE2D_draw_line(float x0, float y0, float x1, float y1, uint32_t color){

    float x{x1 - x0}, y{y1 - y0};
    const float max{std::max(std::fabs(x), std::fabs(y))};
    x /= max;
    y /= max;
    for (float n{0}; n < max; ++n)
    {
        VE2D_set_pixel(x0,y0,color);
        x0 += x; y0 += y;
    }
}

void VE2D_fill_triangle(Vector2D v1, Vector2D v2, Vector2D v3, uint32_t color){

    for(int i = 0; i < 40; i++){
        if(v1.x < 0){
            v1.x++;
        }else{ v1.x--; }

        if(v1.y < 0){
            v1.y++;
        }else{ v1.y--; }


        if(v2.x < 0){
            v2.x++;
        }else{ v2.x--; }

        if(v2.y < 0){
            v2.y++;
        }else{ v2.y--; }


        if(v3.x < 0){
            v3.x++;
        }else{ v3.x--; }

        if(v3.y < 0){
            v3.y++;
        }else{ v3.y--; }

        VE2D_draw_line(v1.x, v1.y, v2.x, v2.y,color);
        VE2D_draw_line(v2.x, v2.y, v3.x, v3.y,color);
        VE2D_draw_line(v1.x, v1.y, v3.x, v3.y,color);
    }
    
}