//#include <cstdio>
//#include <GL/glut.h>
//using namespace std;
//
//int n = 10;
//
//GLfloat Tet[5][3] = { -0.5, -0.29, 0.0,
//	0.5, -0.29, 0.0,
//	0.0, 0.575, 0.0,
//	0.0, 0.0, -1.0
//};
//
//void DivideTetrahedra(GLfloat* a, GLfloat* b, GLfloat* c, int m) {
//}
//
//void MyDisplay() {
//	glClear(GL_COLOR_BUFFER_BIT);
//	glBegin(GL_TRIANGLES);
//	glColor3f(1.0, 0.0, 0.0);
//	DivideTetrahedra(Tet[0], Tet[1], Tet[2], n);
//	glColor3f(0.0, 1.0, 0.0);
//	DivideTetrahedra();
//	glColor3f(0.0, 0.0, 1.0);
//	DivideTetrahedra();
//	glColor3f(0.0, 0.0, 0.0);
//	DivideTetrahedra();
//	glEnd();
//}
//
//void MyInit() {
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
//	glClearColor(0.0, 0.0, 0.0, 0.0);
//	glColor3f(1.0, 1.0, 0.0);
//}
//
//int main1(int argc, char ** argv) {
//	glutInit(&argc, argv);
//	glutInitWindowSize(700, 700);
//	glutInitWindowPosition(100, 100);
//	glutCreateWindow("Fractal Tertrahedra");
//	glutDisplayFunc(MyDisplay);
//	MyInit();
//	glutMainLoop();
//	return 0;
//}