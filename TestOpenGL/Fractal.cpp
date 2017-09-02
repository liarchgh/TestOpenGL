//#include <cstdio>
//#include <GL/glut.h>
//
//GLfloat v[3][2] = { -1.0f, -0.58, 1.0, -0.58, 0.0, 1.7 };
//int n;
//
//void DrawTriangle(GLfloat* a, GLfloat* b, GLfloat* c) {
//	glVertex2fv(a);
//	glVertex2fv(b);
//	glVertex2fv(c);
//}
//
//void DivideTriangle(GLfloat * a, GLfloat* b, GLfloat* c, int m) {
//	GLfloat v0[2], v1[2], v2[2];
//	int j;
//	if (m > 0) {
//		for (int i = 0; i < 2; ++i) {
//			v0[i] = (a[i] + b[i]) / 2;
//		}
//		for (int i = 0; i < 2; ++i) {
//			v1[i] = (a[i] + c[i]) / 2;
//		}
//		for (int i = 0; i < 2; ++i) {
//			v2[i] = (b[i] + c[i]) / 2;
//		}
//		DivideTriangle(a, v0, v1, m - 1);
//		DivideTriangle(v0, b, v2, m - 1);
//		DivideTriangle(v1, v2, c, m - 1);
//	}
//	else {
//		DrawTriangle(a, b, c);
//	}
//}
//
//void MyDisplay() {
//	glClear(GL_COLOR_BUFFER_BIT);
//	glBegin(GL_TRIANGLES);
//	DivideTriangle(v[0], v[1], v[2], n);
//	glEnd();
//	glFlush();
//}
//
//void MyInit() {
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluOrtho2D(-2.0, 2.0, -2.0, 2.0); 
//	glMatrixMode(GL_MODELVIEW);
//	glClearColor(1.0, 1.0, 0.0, 0.0);
//	glColor3f(0.0, 0.0, 0.0);
//}
//
//int main(int argc, char ** argv) {
//	n = 3;
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
//	glutInitWindowPosition(100, 100);
//	glutInitWindowSize(1600, 900);
//	glutCreateWindow("Fractal");
//	glutDisplayFunc(MyDisplay);
//	MyInit();
//	glutMainLoop();
//	return 0;
//}