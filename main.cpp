#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <pspdisplay.h>
#include <gfx.h>
#include <time.h>
#include <stdio.h>
#include <fstream>
#include <iostream>

PSP_MODULE_INFO("PSPProject",0,1,0);

double accumlator;
double lastTime;
double deltaTime;

/* int moveX = 5;
int moveY = 5;

VE2D_Rect rect1 = { 5,20,10,10 };
VE2D_Rect paddlemain;
VE2D_Rect paddleai; */
VE2D_Rect rectangle1 = {5,5,30,30};
VE2D_Rect rectangle2 = {40,5,30,30};
uint32_t* trollarr;

class Vector3D{
	public:
		float x;
		float y;
		float z;
};

float FOV = 150;
Vector3D RealCubeVectors[8] = {{40, 40, 40},  {-40, 40, 40},  {-40, -40, 40},  {40, -40, 40},{40, 40, -40}, {-40, 40, -40}, {-40, -40, -40}, {40, -40, -40}};
int edges[12][3] = {{7,6,5},{7,4,5},{6,5,1},{6,2,1},{2,1,0},{2,3,0},{3,4,0},{3,4,7},{3,6,7},{3,2,6},{0,1,5},{0,5,4}};
float theta = 0.04f;

void update(){
/* 	VE2D_clear(0xFF000000);
	
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

	VE2D_swap_buffers();
	VE2D_draw_line(10,10,20,20,0xFFFFFFFF);
	VE2D_draw_rect(rectangle1,0xFF000000);
	VE2D_fill_rect(rectangle2,0xFF000000);
	VE2D_image_draw(-2,0,trollarr); */

	VE2D_clear(0xFF0a0a0a);

	theta += 0.04f;

	Vector3D CubeVectors[8];
	for(int i = 0; i < 8; i++){
		CubeVectors[i] = RealCubeVectors[i];
	}

	float xMatrix[4] = {cos(theta), -sin(theta),
						sin(theta), cos(theta)};

	for(int i = 0; i < 8; i++){
		CubeVectors[i].x = (xMatrix[0]*RealCubeVectors[i].x)+(xMatrix[1]*RealCubeVectors[i].z);
		CubeVectors[i].z = (xMatrix[2]*RealCubeVectors[i].x)+(xMatrix[3]*RealCubeVectors[i].z);
	}
	
	for(int i = 0; i < 12; i++){
/* 		float projX1 = (FOV*CubeVectors[edges[i][0]].x)/(FOV+CubeVectors[edges[i][0]].z);
		float projY1 = (FOV*CubeVectors[edges[i][0]].y)/(FOV+CubeVectors[edges[i][0]].z);
		float projX2 = (FOV*CubeVectors[edges[i][1]].x)/(FOV+CubeVectors[edges[i][1]].z);
		float projY2 = (FOV*CubeVectors[edges[i][1]].y)/(FOV+CubeVectors[edges[i][1]].z);
		float projX3 = (FOV*CubeVectors[edges[i][2]].x)/(FOV+CubeVectors[edges[i][2]].z);
		float projY3 = (FOV*CubeVectors[edges[i][2]].y)/(FOV+CubeVectors[edges[i][2]].z); */
		Vector2D vector1 = {(FOV*CubeVectors[edges[i][0]].x)/(FOV+CubeVectors[edges[i][0]].z), (FOV*CubeVectors[edges[i][0]].y)/(FOV+CubeVectors[edges[i][0]].z)};
		Vector2D vector2 = {(FOV*CubeVectors[edges[i][1]].x)/(FOV+CubeVectors[edges[i][1]].z), (FOV*CubeVectors[edges[i][1]].y)/(FOV+CubeVectors[edges[i][1]].z)}; 
		Vector2D vector3 = {(FOV*CubeVectors[edges[i][2]].x)/(FOV+CubeVectors[edges[i][2]].z), (FOV*CubeVectors[edges[i][2]].y)/(FOV+CubeVectors[edges[i][2]].z)};  

		/* VE2D_draw_line(projX1, projY1, projX2, projY2,0xFFFFFFFF);
		VE2D_draw_line(projX2, projY2, projX3, projY3,0xFFFFFFFF);
		VE2D_draw_line(projX1, projY1, projX3, projY3,0xFFFFFFFF); */
		if(i % 2 == 0){
			VE2D_fill_triangle(vector1, vector2, vector3, 0xFF555599);
		}
		else{
			VE2D_fill_triangle(vector1, vector2, vector3, 0xFF559955);
		}
	}

/* 	VE2D_image_draw(0,0,trollarr); */

	sceDisplayWaitVblankStart();
}

int main() {
	VE2D_init();

	sceCtrlSetSamplingCycle(0);
	sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);

	SceCtrlData ctrlData;

	pspDebugScreenInit();

/* 	trollarr = VE2D_image_init("file.ppm"); */

	while (true) {
        deltaTime = clock() - lastTime;
        lastTime += deltaTime;
        accumlator += deltaTime;
        while (accumlator > 17) {
            update();
            accumlator -= 17;
        }
    }
}