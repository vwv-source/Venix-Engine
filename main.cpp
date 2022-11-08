#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <pspdisplay.h>
#include <gfx.h>
#include <time.h>
#include <stdio.h>

PSP_MODULE_INFO("PSPProject",0,1,0);

double accumlator;
double lastTime;
double deltaTime;

int moveX = 5;
int moveY = 5;

VE2D_Rect rect1 = { 5,20,10,10 };
VE2D_Rect paddlemain;
VE2D_Rect paddleai;

void update(){
	VE2D_clear(0xFF0A0A0A);
	
    paddlemain = {10,(rect1.y + 50)*0.2,10,60};
    paddleai = { 480-20,(rect1.y + 15)*0.75,10, 60 };
    if (rect1.x + moveX > 512 - rect1.w || rect1.x + moveX < 0) {
        moveX = -moveX;
    }

    if (rect1.y + moveY > 272 - rect1.h || rect1.y + moveY < 0) {
        moveY = -moveY;
    }

    if (rect1.y < paddlemain.y + paddlemain.h && rect1.h + rect1.y > paddlemain.y && rect1.x < paddlemain.x + paddlemain.w && rect1.x + rect1.w > paddlemain.x) {
        moveX = -moveX;
    }
    if (rect1.y < paddleai.y + paddleai.h && rect1.h + rect1.y > paddleai.y && rect1.x < paddleai.x + paddleai.w && rect1.x + rect1.w > paddleai.x) {
        moveX = -moveX;
    }
    rect1.y += moveY;
    rect1.x += moveX;

	VE2D_fill_rect(rect1,0xFF6EFF1A);
	VE2D_fill_rect(paddlemain,0xFF6EFF1A);
	VE2D_fill_rect(paddleai,0xFF6EFF1A);

	//VE2D_swap_buffers();
	sceDisplayWaitVblankStart();
}

int main() {
	VE2D_init();

	FILE* file2 = fopen("file.ppm","r");
	char arr[200] = {0};
	fread(arr, sizeof(char),200,file2);
	fclose(file2);

	sceCtrlSetSamplingCycle(0);
	sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);

	SceCtrlData ctrlData;

	pspDebugScreenInit();
	pspDebugScreenPrintf("%s", arr);

/* 	while (true) {
        deltaTime = clock() - lastTime;
        lastTime += deltaTime;
        accumlator += deltaTime;
        while (accumlator > 17) {
            update();
            accumlator -= 17;
        }
    } */

/* 	while(true){

		//Input Detection
		sceCtrlReadBufferPositive(&ctrlData,1);
		if(ctrlData.Buttons & PSP_CTRL_CROSS){
			pspDebugScreenPrintf("\nCross");
		}
		if(ctrlData.Buttons & PSP_CTRL_TRIANGLE){
			pspDebugScreenPrintf("\nTriangle");
		}
		if(ctrlData.Buttons & PSP_CTRL_SQUARE){
			pspDebugScreenPrintf("\nSquare");
		}

		if(ctrlData.Buttons & PSP_CTRL_CIRCLE){
			pspDebugScreenPrintf("\nCircle");
		}
	} */

	//Initializes the debug screen
/* 	pspDebugScreenInit();
	pspDebugScreenPrintf("%s", arr); */
}