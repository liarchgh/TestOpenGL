#include <GL/freeglut.h>
#include <ctime>
#include <cmath>
#include <cstdio>
#include <vector>
using namespace std;

const int DESIRED_FPS = 30, mxv = 30;
int mxNumCircles = 20, mxRadius = 40, mnRadius = 3,
winWid = 800, winHei = 600;
struct circle {
	int x, y, radius;
	unsigned char color;
	struct {
		int x, y;
	}v;
	circle(int a, int b, int c, int d, int e, unsigned char f) {
		x = a, y = b, radius = c;
		v.x = d, v.y = e;
		color = f;
	}
	void move(int val) {
		x += v.x * val;
		y += v.y * val;
		if (x >= winWid) {
			x = winWid;
			v.x = -v.x;
		}
		else if (x <= 0) {
			x = 0;
			v.x = -v.x;
		}
		if (y >= winHei) {
			y = winHei;
			v.y = -v.y;
		}
		else if(y <= 0) {
			y = 0;
			v.y = -v.y;
		}
	}
};
vector<circle>circles;

void myReshape(int w, int h) {
	winWid = w;
	winHei = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, h, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void updateCircles(int val) {
	for (int i = 0; i < circles.size(); ++i) {
		circle& now = circles[i];
		now.move(val);
	}
	glutPostRedisplay();
	glutTimerFunc((1000.0) / DESIRED_FPS, updateCircles, 1);
}

void drawCircles() {
	for (int i = 0; i < circles.size(); ++i) {
		int radius = circles[i].radius, x = circles[i].x,
			y = circles[i].y;
		glColor3ub((char)rand() % 255, (char)rand() % 255, (char)rand() % 255);
		glBegin(GL_POLYGON);
		glVertex2f(0.0, 0.0);
		glVertex2f(0.0, 5.0);
		glVertex2f(5.0, 5.0);
		glEnd();
		glBegin(GL_TRIANGLE_FAN);
		for (double j = 0.0, stepRa = 0.1; j < 3.1 * 2; j += stepRa) {
			int tx = x + radius * cos(j),
				ty = y +  radius * sin(j);
			glVertex2f(tx, ty);
			//printf("--------%f %f %f\n", j, radius * cos(j), radius * sin(j));
			//printf("---%d %d\n", tx - x, ty - y);
		}
		//printf("--\n");
		glEnd();
	}
}

void myDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	drawCircles();
	glutSwapBuffers();
}

void myMouse(int btn, int state, int x, int y) {
	//while clicking left button of mouse
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (circles.size() < mxNumCircles) {
			int radius = rand() % mxRadius, vx = rand() % mxv - mxv/2, vy = rand() % mxv - mxv/2;
			circles.push_back(circle(x, y, radius, vx, vy,(char)rand() % 255));
			glutPostRedisplay();
		}
	}
	//for (int i = 0; i < circles.size(); ++i) {
	//	printf("--%d %d %d\n", circles[i].x, circles[i].y, circles[i].radius);
	//}
}

void myKey(unsigned char key, int x, int y) {
	if (key == 'q' || key == 'Q') {
		exit(0);
	}
}

void myInit() {
	glClearColor(0.0, 0.5, 0.0, 1.0);
	glShadeModel(GL_FLAT);
	srand((unsigned)time(NULL));
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Create circles");
	
	glutInitDisplayMode(GL_DOUBLE | GL_RGB);
	glutDisplayFunc(myDisplay);
	glutMouseFunc(myMouse);
	glutKeyboardFunc(myKey);
	glutReshapeFunc(myReshape);
	glutTimerFunc((1000.0) / DESIRED_FPS, updateCircles, 1);

	glutMainLoop();
	return 0;
}