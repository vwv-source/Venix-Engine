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

VGE_Rect rectangle1 = {5,5,30,30};
VGE_Rect rectangle2 = {40,5,30,30};
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
	//Cleares the background.
	VGE_clear(0xFF0a0a0a);

	theta += 0.04f;

	//Copies the actual cube instead of modifying it directly.
	Vector3D CubeVectors[8];
	for(int i = 0; i < 8; i++){
		CubeVectors[i] = RealCubeVectors[i];
	}


	//Matrix Calculations.
	float xMatrix[4] = {cos(theta), -sin(theta),
						sin(theta), cos(theta)};

	for(int i = 0; i < 8; i++){
		CubeVectors[i].x = (xMatrix[0]*RealCubeVectors[i].x)+(xMatrix[1]*RealCubeVectors[i].z);
		CubeVectors[i].z = (xMatrix[2]*RealCubeVectors[i].x)+(xMatrix[3]*RealCubeVectors[i].z);
	}


	//Draws the cube
	for(int i = 0; i < 12; i++){
		Vector2D vector1 = {(FOV*CubeVectors[edges[i][0]].x)/(FOV+CubeVectors[edges[i][0]].z), (FOV*CubeVectors[edges[i][0]].y)/(FOV+CubeVectors[edges[i][0]].z)};
		Vector2D vector2 = {(FOV*CubeVectors[edges[i][1]].x)/(FOV+CubeVectors[edges[i][1]].z), (FOV*CubeVectors[edges[i][1]].y)/(FOV+CubeVectors[edges[i][1]].z)}; 
		Vector2D vector3 = {(FOV*CubeVectors[edges[i][2]].x)/(FOV+CubeVectors[edges[i][2]].z), (FOV*CubeVectors[edges[i][2]].y)/(FOV+CubeVectors[edges[i][2]].z)};  

		if(i % 2 == 0){
			VGE_fill_triangle(vector1, vector2, vector3, 0xFF555599);
		}
		else{
			VGE_fill_triangle(vector1, vector2, vector3, 0xFF559955);
		}
	}

	sceDisplayWaitVblankStart();
}

int main() {
	VGE_init();
	pspDebugScreenInit();

	//Game loop
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