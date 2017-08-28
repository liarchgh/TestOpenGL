#include <GL/glut.h>
#include <cstdio>

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
	glVertex2f(0.0, 0.0);
	glVertex2f(0.5, 0.0);
	glVertex2f(0.0, -0.5);
	glVertex2f(0.5, -0.5);
	glEnd();
	glFlush();
}

int main() {
	glutCreateWindow("square");
	glutDisplayFunc(display);
	glutMainLoop();
}