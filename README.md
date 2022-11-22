# Venix Engine
<img src="https://forthebadge.com/images/badges/made-with-c-plus-plus.svg"> <img src="https://forthebadge.com/images/badges/60-percent-of-the-time-works-every-time.svg"><br><br>

## What is this?
The Venix Engine is a simple game engine made mainly for the PSP. As of now it only uses the CPU for rendering.<br><br>

## Usage:
Import the gfx.hpp and that's it!<br><br>

## Notes:
- If you are planning on doing something actually serious, Please don't use this.<br>
- This is in a very early alpha stage, so expect alot of changes and bugs.<br><br>

## Examples (untested):
Creating a moving image.
```c++
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <pspdisplay.h>
#include <gfx.h>

int x,y;
uint32_t* image;

int main() {
    VGE_init();
    pspDebugScreenInit();

    image = VGE_image_init("file.ppm");

    while (true) {
        VGE_image_draw(x++,y++,image);
    }
}
```

Creating a square.
```c++
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <pspdisplay.h>
#include <gfx.h>

int main() {
    VGE_init();
    pspDebugScreenInit();

    VGE_Rect rectangle = {10,10,20,50};

    while (true) {
        VGE_draw_rect(rectangle, 0xFFFFFFFF);
    }
}
```
