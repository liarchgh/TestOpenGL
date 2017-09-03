//#include <GL/glut.h>
//#include <cstdio>
//
//void init() {
//	glClearColor(0.0, 0.0, 0.0, 0.5);
//	glColor3f(1.0, 1.0, 0.0);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
//}
//
//void display() {
//	glClear(GL_COLOR_BUFFER_BIT);
//	glBegin(GL_POLYGON);
//	glVertex2f(0.0, 0.0);
//	glVertex2f(0.5, 0.0);
//	glVertex2f(0.0, -0.5);
//	glVertex2f(0.5, -0.5);
//	glEnd();
//	glFlush();
//}
//
//int main(int argc, char ** argv) {
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
//	glutInitWindowSize(1600, 900);
//	glutInitWindowPosition(100, 100);
//	glutCreateWindow("square");
//	glutDisplayFunc(display);
//	init();
//	glutMainLoop();
//}