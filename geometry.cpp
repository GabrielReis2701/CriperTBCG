#ifndef GEOMETRY_CPP

#include "glut.h"
#include <math.h>

#define GEOMETRY_CPP

#define PI 3.1415926535897

void drawCircle(float radius, int solid) {
    float twoPI = 2 * PI;

        // GL_TRIANGLE_FAN | GL_POINTS
    glBegin(!solid ? GL_POINTS : GL_TRIANGLE_FAN);
        for (float i = 0.0; i <= twoPI; i += 0.001){
            point((sin(i)*radius), (cos(i)*radius), 0);
            point((sin(i)*radius), (cos(i)*radius), -0.003);
            }
    glEnd();
}

void drawCustomCircle(float startingAngle, float endingAngle, float radius, float spacing, int x, int y, int z, int solid) {
	// Must be in pairs of axes
	if(!(x & y) && !(x & z) && !(y & z)) return;

	// Must be in pairs of axes
	if(x & y & z) return;
	
	if(startingAngle > endingAngle) {
		float temp = startingAngle;
		startingAngle = endingAngle;
		endingAngle = temp;
		spacing *= -1;
	}

	// GL_TRIANGLE_FAN | GL_POINTS
  glBegin(!solid ? GL_POINTS : GL_TRIANGLE_FAN);
    for (float i = startingAngle; i <= endingAngle; i += spacing){
    	if(x & y) point(sin(i/180 * PI) * radius, cos(i/180 * PI) * radius, 0);
    	if(x & z) point(sin(i/180 * PI) * radius, 0, cos(i/180 * PI) * radius);
    	if(y & z) point(0, sin(i/180 * PI) * radius, cos(i/180 * PI) * radius);
		}
  glEnd();
}

void drawHalfSphere(float radius) {
	float twoPI = 2 * PI;
	float space = 1;
	float x, y, z;
	
	//GL_POINTS | GL_TRIANGLE_FAN
	glBegin(GL_POINTS);
		for (float theta = 0; theta <= 90 - space; theta += space) {
			for (float phi = 0; phi <= 360 - space; phi += space) {
				x = radius * sin(phi/180 * PI) * sin(theta/180 * PI);
				y = radius * cos(phi/180 * PI) * sin(theta/180 * PI);
				z = radius * cos(theta/180 * PI);
				point(x, y, z);
			}
		}
	glEnd();
}

void drawSphereSection(float startingTheta, float startingPhi, float endingTheta, float endingPhi, float radius, float space, int solid) {
	float x, y, z;
	
	//GL_POINTS | GL_TRIANGLE_FAN
	glBegin(!solid ? GL_POINTS : GL_TRIANGLE_FAN);
		for (float theta = startingTheta; theta <= endingTheta; theta += space) {
			for (float phi = startingPhi; phi <= endingPhi; phi += space) {
				x = radius * sin(phi/180 * PI) * sin(theta/180 * PI);
				y = radius * cos(phi/180 * PI) * sin(theta/180 * PI);
				z = radius * cos(theta/180 * PI);
				point(x, y, z);
			}
		}
	glEnd();
}

void drawRings(float radius, float gap) {
	float twoPI = 2 * PI;
	float space = 1;
	float x, y, z;
	
	//GL_POINTS | GL_TRIANGLE_FAN
	glBegin(GL_POINTS);
		for (float i = 0.0; i <= twoPI; i += 0.001){
    	point((sin(i)*radius), gap/2, (cos(i)*radius));
    	point((sin(i)*radius), -gap/2, (cos(i)*radius));
		}
	glEnd();
}
float rad(float angle) {
	return (angle / 180) * PI;
}
void drawCustomCylinder(float base, float top, float height, float startingAlpha, float endingAlpha) {
	glPopMatrix();
		glBegin(GL_LINE_LOOP);
			for (float alpha = rad(startingAlpha); alpha <= rad(endingAlpha); alpha += 0.001) {
				point(sin(alpha) * base, 0, cos(alpha) * base);
				point(sin(alpha) * top, height, cos(alpha) * top);
			}
		glEnd();
	glPushMatrix();
}

#endif
