#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

#define K1 160
#define K2 5
#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 150

void calculate_surface(char *buffer, double x, double y, double z, double A, double B, double C, int normal){
	double sinA = sin(A), sinB = sin(B), sinC = sin(C);
	double cosA = cos(A), cosB = cos(B), cosC = cos(C);
       	double luminance;
	double rx = cosC * (x * cosB - sinB * (y * sinA + z * cosA)) - sinC * (y * cosA - z * sinA);
	double ry = sinC * (x * cosB - sinB * (y * sinA + z * cosA)) + cosC * (y * cosA - z * sinA);
	double rz = K2 + x * sinB + cosB * (y * sinA + z * cosA);
	int xp = (int) (SCREEN_WIDTH/2 + rx * K1 / rz);
	int yp = (int) (SCREEN_HEIGHT/2 + ry * K1 / rz);
	if (normal == 1) luminance = sinB;
	else if (normal == -1) luminance = -sinB;
	else if (normal == 2) luminance = sinA * cosB;
	else if (normal == -2) luminance = -sinA * cosB;
	else if (normal == 3) luminance = cosA * cosB;
	else luminance = -cosA * cosB;
	if (luminance < 0){
		int level = (int) (luminance * -11);
		buffer[xp + yp * SCREEN_WIDTH] = ".,-~:;=!*#$@"[level];
	}
}

void render_frame(double A, double B, double C){
	char buffer[SCREEN_WIDTH * SCREEN_HEIGHT];
	memset(buffer, ' ', SCREEN_WIDTH * SCREEN_HEIGHT);
	for (double i = -1; i <= 1; i += 0.01){
		for (double j = -1; j <= 1; j += 0.01){
			calculate_surface(buffer, i, j, 1, A, B, C, 3);
			calculate_surface(buffer, i, j, -1, A, B, C, -3);
			calculate_surface(buffer, i, 1, j, A, B, C, 2);
			calculate_surface(buffer, i, -1, j, A, B, C, -2);
			calculate_surface(buffer, 1, i, j, A, B, C, 1);
			calculate_surface(buffer, -1, i, j, A, B, C, -1);
		}
	}
	printf("\x1B[H");
	for (int i = 0; i < SCREEN_HEIGHT; i++){
		for (int j = 0; j < SCREEN_WIDTH; j++){
			putchar(buffer[j + i * SCREEN_WIDTH]);
		}
		putchar('\n');
	}
}

int main(){
	double A = 0, B = 0, C = 0;
	while (1){
		render_frame(A, B, C);
		A += 0.06;
		B += 0.07;
		C += 0.08;
		usleep(10000);
	}
	return 0;
}

