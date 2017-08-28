#include <GL/freeglut.h>
#include <iostream>
#include <cstdio>
using namespace std;

GLfloat v[3][2] = { -0.5, -0.29,
	0.5, -0.29,
	0.0, 0.575};
int n;

void CalDS(GLfloat* a, GLfloat* b, GLfloat* c, GLfloat* v0, GLfloat* v1, GLfloat* v2) {
	for (int i = 0; i < 2; ++i) {
		v0[i] = (b[i] - a[i]) / 3 + a[i];
		v2[i] = (a[i] - b[i]) / 3 + b[i];
		GLfloat mid = (a[i] + b[i]) / 2;
		GLfloat t = mid + (mid - c[i]) / 3;
		v1[i] = t;
	}
}

void DrawTriangle(GLfloat* a, GLfloat* b, GLfloat* c) {
	glVertex2fv(a);
	glVertex2fv(b);
	glVertex2fv(c);
	//getchar();
}

void DivideSnow(GLfloat* a, GLfloat* b, GLfloat* c, int m) {
	if (m > 0) {
		GLfloat v0[2], v1[2], v2[2];
		GLfloat t0[2], t1[2], t2[2], t3[2], t4[2], t5[2];
		CalDS(a, b, c, v0, v1, v2);
		for (int i = 0; i < 2; ++i) {
			t0[i] = v0[i];
			t1[i] = v2[i];
		}
		DivideSnow(v0, v1, v2, m - 1);
		CalDS(b, c, a, v0, v1, v2);
		for (int i = 0; i < 2; ++i) {
			t2[i] = v0[i];
			t3[i] = v2[i];
		}
		DivideSnow(v0, v1, v2, m - 1);
		CalDS(c, a, b, v0, v1, v2);
		for (int i = 0; i < 2; ++i) {
			t4[i] = v0[i];
			t5[i] = v2[i];
		}
		DivideSnow(v0, v1, v2, m - 1);
		DivideSnow(a, t0, t5, m - 1);
		DivideSnow(b, t1, t2, m - 1);
		DivideSnow(c, t3, t4, m - 1);
	}
	//else{
		DrawTriangle(a, b, c);
		//cout << a << endl;
		//printf("%f %f %f\n", float(a), float(b), float(c));
	//}
}
void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_TRIANGLES);
	DivideSnow(v[0], v[1], v[2], n);
	glEnd();
	glFlush();
}

void MyInit() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-2.0, 2.0, -2.0, 2.0);
	glClearColor(1.0, 1.0, 0.0, 1.0);
	glColor3f(0.0, 0.0, 0.0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	n = 10;
	scanf_s("%d", &n);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("SnowFractal");
	glutDisplayFunc(MyDisplay);
	MyInit();
	glutMainLoop();
	return 0;
}