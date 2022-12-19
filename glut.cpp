#ifndef GLUT_CPP

#include <GL/gl.h>
#include <GL/glut.h>

#define GLUT_CPP

void point(GLfloat x, GLfloat y, GLfloat z) {
	glVertex3f(x, y, z);
}

void color(GLfloat r, GLfloat g, GLfloat b) {
	glColor3f(r, g, b);
}

#endif
