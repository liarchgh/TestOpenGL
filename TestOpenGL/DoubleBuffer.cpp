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
struct voc {
    float color[4] = { 1.0, 1.0, 1.0, 1.0 };
    float pos[3] = { 0,0,0 };

    void setPos(float a, float b, float c);
    void setColor(float a, float b, float c, float d);
    voc(float* vpos, float* vcol);
    voc();
};
struct square{
    voc* ver[4];
    void draw();
};

struct cube {
    //点的顺序固定 从上往下看，先是第一层的四个点逆时针方向存储，然后是下一层四个点也是逆时针存储
    voc vertex[8];
    square squares[6];

    //voc a, voc b, voc c, voc d, voc e, voc f, voc g, voc h
    cube(voc* vocs);
    cube() { setSquares(); }
    void setSquares();
};

vector<circle>circles;
vector<cube>cubes;

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

void drawCubes();

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
    if (choose == 0) {
        drawSquares();
        drawCircles();
    }
    if (choose == 1) {
        drawCubes();
    }
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
    printf("1: draw a cube\n");
    scanf_s("%d", &choose);
    switch (choose) {
        case 0:
            initDrawSquareCircle();
            break;
        case 1:
            voc vocs[8];
            vocs[0].setPos(5, 5, 5);
            vocs[1].setPos(5, 5, -5);
            vocs[2].setPos(-5, 5, -5);
            vocs[3].setPos(-5, 5, 5);
            vocs[4].setPos(5, -5, 5);
            vocs[5].setPos(5, -5, -5);
            vocs[6].setPos(-5, -5, -5);
            vocs[7].setPos(-5, -5, 5);
            cube aCube(vocs);
            cubes.push_back(aCube);
            initDrawSquareCircle();
            break;
        //default:
        //    printf("Nothin.");
        //    break;
    }
}

void initDrawSquareCircle() {
	glutInitDisplayMode(GL_DOUBLE | GL_RGB);
	glutDisplayFunc(myDisplay);
	glutMouseFunc(myMouse);
	glutKeyboardFunc(myKey);
	glutReshapeFunc(myReshape);
	glutTimerFunc((1000.0) / DESIRED_FPS, updateTime, 1);
	glutMainLoop();
}

void drawCubes() {
    for (int i = 0; i < cubes.size(); ++i) {
        cube& nCube = cubes[i];
        for (int j = 0; j < 6; ++j) {
            nCube.squares[j].draw();
        }
    }
}

void square::draw() {
    glBegin(GL_POLYGON);
    glColor4f(1.0, 0.0, 0.0, 1.0);
    for (int i = 0; i < 4; ++i) {
        ((ver[i])->setColor)(1.0, 0.0, 0.0, 1.0);
        glColor4f(((ver[i])->color)[0], ((ver[i])->color)[1], ((ver[i])->color)[2], ((ver[i])->color)[3]);
        glVertex3f(ver[i]->pos[0], ver[i]->pos[1], ver[i]->pos[2]);
    }
    glEnd();
}

void cube::setSquares() {
    for (int i = 0; i < 4; ++i) {
        squares[0].ver[i] = &vertex[i];
    }
    for (int i = 4; i < 8; ++i) {
        squares[1].ver[i] = &vertex[i];
    }
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 4; ++j) {
            squares[2 + j].ver[i] = &vertex[i + j];
            squares[2 + j].ver[i + 2] = &vertex[i + j + 4];
        }
    }
}

cube::cube(voc* vocs) {
    setSquares();
    for (int i = 0; i < 8; ++i) {
        vertex[i] = vocs[i];
    }
}

voc::voc(float* vpos, float* vcol) {
    for (int i = 0; i < 3; ++i){
        pos[i] = vpos[i];
    }
    for (int i = 0; i < 4; ++i) {
        color[i] = vcol[i];
    }
}

void voc::setPos(float a, float b, float c) {
    pos[0] = a;
    pos[1] = b;
    pos[2] = c;
}

void voc::setColor(float a, float b, float c, float d) {
    color[0] = a;
    color[1] = b;
    color[2] = c;
    color[3] = d;
}

voc::voc() {
    for (int i = 0; i < 4; ++i) {
        color[i] = 1.0f;
    }
    for (int i = 0; i < 3; ++i) {
        pos[i] = 1.0f;
    }
}
