#include <GL/freeglut.h>
#include <ctime>
#include <cmath>
#include <cstdio>
#include <vector>
using namespace std;

const int DESIRED_FPS = 120, mxv = 10;
int mxNumCircles = 1000, mxRadius = 40, mnRadius = 3,
winWid = 800, winHei = 600,
choose;
struct circle {
	int x, y, radius;
	unsigned char color;
	struct {
		int x, y;
	}v;
    circle(int a, int b, int c, int d, int e, unsigned char f);
    void move(int val);
};
vector<circle>circles;

void myInit();
void myKey(unsigned char key, int x, int y);
void myMouse(int btn, int state, int x, int y);
void addCircle(int x, int y);
void myDisplay();
void drawCircles();
void myReshape(int w, int h);
void updateTime(int val);

void drawSquare();
void drawSquares();

void drawCube();

void initDrawSquareCircle();
void setOpenGL();

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("TestOpenGL");

    setOpenGL();
	return 0;
}

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

void updateTime(int val) {
	for (int i = 0; i < circles.size(); ++i) {
		circle& now = circles[i];
		now.move(val);
	}
	glutPostRedisplay();
	glutTimerFunc((1000.0) / DESIRED_FPS, updateTime, 1);
}

void drawCircles() {
	for (int i = 0; i < circles.size(); ++i) {
		int radius = circles[i].radius, x = circles[i].x,
			y = circles[i].y;
		glColor3ub((char)rand() % 255, (char)rand() % 255, (char)rand() % 255);
		glBegin(GL_TRIANGLE_FAN);
		for (double j = 0.0, stepRa = 0.1; j < 3.1 * 2; j += stepRa) {
			float tx = x + radius * cos(j),
				ty = y +  radius * sin(j);
			glVertex2f(tx, ty);
		}
		glEnd();
	}
}

void myDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    drawSquares();
	drawCircles();
	glutSwapBuffers();
}

void addCircle(int x, int y){
    if (circles.size() < mxNumCircles) {
        int radius = rand() % mxRadius, vx = rand() % mxv - mxv / 2, vy = rand() % mxv - mxv / 2;
        circles.push_back(circle(x, y, radius, vx, vy, (char)rand() % 255));
        printf("There are %d circles.\n", circles.size());
        glutPostRedisplay();
    }
}

void myMouse(int btn, int state, int x, int y) {
	//while clicking left button of mouse
	if (choose == 0 && btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        addCircle(x, y);
	}
	//for (int i = 0; i < circles.size(); ++i) {
	//	printf("--%d %d %d\n", circles[i].x, circles[i].y, circles[i].radius);
	//}
}

void myKey(unsigned char key, int x, int y) {
	if (key == 'q' || key == 'Q') {
		exit(0);
	}
    if (choose == 0 && key == 'C' || key == 'c') {
        circles.clear();
    }
}

void myInit() {
	glClearColor(0.0, 0.5, 0.0, 1.0);
	//glShadeModel(GL_FLAT);
	srand((unsigned)time(NULL));
}

circle::circle(int a, int b, int c, int d, int e, unsigned char f) {
    x = a, y = b, radius = c;
    v.x = d, v.y = e;
    color = f;
}
void circle::move(int val) {
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

void drawSquare() {
    glColor3f(1.0, 0.0, 0.0);
    double a = 20, ox = 50, oy = 50;
        //ox = winWid / 2 + 50, oy = winHei / 2 + 50;
    //printf("%lf\n", a);
    glBegin(GL_POLYGON);
        glVertex3d(ox+a, oy+a, 0.0);
        glVertex3d(ox+a, oy-a, 0.0);
        glVertex3d(ox-a, oy-a, 0.0);
        glVertex3d(ox-a, oy+a, 0.0);
    glEnd();
    //glBegin(GL_TRIANGLE_FAN);
    //    glVertex2f(a, a);
    //    glVertex2f(a, -a);
    //    glVertex2f(-a, -a);
    //    glVertex2f(-a, a);
    //glEnd();
}

void drawSquares() {
    double  ox = winWid/2, oy = winHei/2;
    for (int i = 0; i < 8; ++i) {
        glPushMatrix();
        glTranslated(ox, oy, 0.0);
        glRotated(i * 45.0, 0, 0, 1.0);
        //glScaled(0.5, 0.5, 0.5);
        drawSquare();
        glPopMatrix();
    }
}

void setOpenGL() {
    printf("Choose:\n");
    printf("0: draw squares and circles\n");
    scanf_s("%d", &choose);
    switch (choose) {
        case 0:
            initDrawSquareCircle();
            break;
        default:
            printf("Nothin.");
            break;
    }
}

void initDrawSquareCircle() {
	glutInitDisplayMode(GL_DOUBLE | GL_RGB);
	glutDisplayFunc(myDisplay);
	glutMouseFunc(myMouse);
	glutKeyboardFunc(myKey);
	glutReshapeFunc(myReshape);
	glutTimerFunc((1000.0) / DESIRED_FPS, updateTime, 1);
    glutMotionFunc(addCircle);
	glutMainLoop();
}
