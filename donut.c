#include <stdio.h>
#include <math.h>
#include <string.h>
#include <unistd.h>

#define SCREEN_HEIGHT 30
#define SCREEN_WIDTH 100
#define K1 15
#define K2 5
#define R1 1
#define R2 2

void render_frame(double A, double B){
	char buffer[SCREEN_HEIGHT * SCREEN_WIDTH];
       	memset(buffer, ' ', SCREEN_HEIGHT * SCREEN_WIDTH);
	double sinA = sin(A), sinB = sin(B);
	double cosA = cos(A), cosB = cos(B);
	for (double theta = 0; theta < 2 * M_PI; theta += 0.04){
		double sintheta = sin(theta), costheta = cos(theta);
		for (double phi = 0; phi < 2 * M_PI; phi += 0.05){
			double sinphi = sin(phi), cosphi = cos(phi);
			double x = cosB * cosphi * (R2 + R1 * costheta) - sinB * (cosA * R1 * sintheta - sinA * sinphi * 					(R2 + R1 * costheta));
			double y = sinB * cosphi * (R2 + R1 * costheta) + cosB * (cosA * R1 * sintheta - sinA * sinphi *                                        (R2 + R1 * costheta));
			double z = K2 + sinA * R1 * sintheta + cosA * sinphi * (R2 + R1 * costheta);
			int xp = (int) (50 + ((x * K1) / z));
        		int yp = (int) (15 + ((y * K1) / z));
			double luminance = sinA * sintheta + cosA * sinphi * costheta;
			if (luminance < 0){
				int level = (int) (luminance * -11);
				buffer[xp + (yp * SCREEN_WIDTH)] = ".,-~:;=!*#$@"[level];
			}
		}
	}
	printf("\x1B[H");
	for (int i = 0; i < SCREEN_HEIGHT; i++){
		for (int j = 0; j < SCREEN_WIDTH; j++){
			putchar(buffer[j + (i * SCREEN_WIDTH)]);
		}
		putchar('\n');
	}
}

int main(){
        double A = 0, B = 0;
        while(1){
                render_frame(A, B);
                A += 0.06;
                B += 0.07;
		usleep(10000);
        }
        return 0;
}
