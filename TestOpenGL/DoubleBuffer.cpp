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
float eyeDistance = 400.0f, planeDepth = 200.0f,
light0pos[4] = {0.0f, 600.0f, 0.0f , 0.0f},
light1pos[4] = {300.0f, 200.0f, 400.0f, 0.0f};

struct circle{
    int x, y, radius;
    unsigned char color;
    struct{
        int x, y;
    }v;
    circle(int a, int b, int c, int d, int e, unsigned char f);
    void move(int val);
};
struct voc{
    float color[4] = {1.0, 1.0, 1.0, 1.0};
    float pos[3] = {0,0,0};

    void setPos(float a, float b, float c);
    void setColor(float a, float b, float c, float d);
    voc(float* vpos, float* vcol);
    voc();
};
struct square{
    voc* ver[4];
    void draw();
};

struct cube{
    //点的顺序固定 从上往下看，先是第一层的四个点逆时针方向存储，然后是下一层四个点也是逆时针存储
    voc vertex[8];
    square squares[6];
    float x, y, z, length,
        angle[3], vAngle[3];

    //voc a, voc b, voc c, voc d, voc e, voc f, voc g, voc h
    cube(voc* vocs);
    cube(){ setSquares(); }
    void setSquares();
    void setOrigin(float a, float b, float c);
    void setLength(float a);
    void draw();
};

struct car{
    void draw();
};

struct sphere{
    static int ifShowAxiss;
    float pos[3], angle[2], vAngle[2], radius,
        color[4], axissColor[3][4];
    vector<car>cars;

    void drawAxiss(float length);
    void draw();
    void setRadius(float x);
    void setColor(float *c);
    void setAngle(float* a);
    void setPos(float* p);
    void setAxissColor(float* c);
    void setVAngle(float* x);
    sphere();
};
int sphere::ifShowAxiss = 1;

vector<circle>circles;
vector<cube>cubes;
vector<sphere>spheres;

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
void initDrawCubes();
void setOpenGL();

void initDrawCars();
void drawCars();

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 600);
    glutCreateWindow("TestOpenGL");

    setOpenGL();
    return 0;
}

void myReshape(int w, int h){
    winWid = w;
    winHei = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(choose == 0){
        gluOrtho2D(0, w, h, 0);
    }
    if(choose == 1){
        float depth1 = 200.0f, depth2 = 600.0f;
        glFrustum(-winWid / 2, winWid / 2, -winHei / 2, winHei / 2, depth1, depth2);
        //glOrtho(-w / 2, w / 2, -h / 2, h / 2, depth1, depth2);
    }
    if(choose == 2){
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void updateTime(int val){
    if(choose == 0){
        for(int i = 0; i < circles.size(); ++i){
            circle& now = circles[i];
            now.move(val);
        }
    }
    if(choose == 1){
        for(int i = 0; i < cubes.size(); ++i){
            for(int j = 0; j < 3; ++j){
                cubes[i].angle[j] += cubes[i].vAngle[j] * val;
            }
        }
        //printf("%f\n", cubes[0].vAngle[1]);
    }
    //printf("time func val is %d\n", val);
    glutPostRedisplay();
    glutTimerFunc((1000.0) / DESIRED_FPS, updateTime, 1);
}

void drawCircles(){
    for(int i = 0; i < circles.size(); ++i){
        int radius = circles[i].radius, x = circles[i].x,
            y = circles[i].y;
        glColor3ub((char)rand() % 255, (char)rand() % 255, (char)rand() % 255);
        glBegin(GL_TRIANGLE_FAN);
        for(double j = 0.0, stepRa = 0.1; j < 3.1 * 2; j += stepRa){
            float tx = x + radius * cos(j),
                ty = y + radius * sin(j);
            glVertex2f(tx, ty);
        }
        glEnd();
    }
}

void myDisplay(){
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    if(choose == 0){
        drawSquares();
        drawCircles();
    }
    if(choose == 1){
        drawCubes();
    }
    if(choose == 2){
        drawCars();
    }
    glutSwapBuffers();
}

void addCircle(int x, int y){
    if(circles.size() < mxNumCircles){
        int radius = rand() % mxRadius, vx = rand() % mxv - mxv / 2, vy = rand() % mxv - mxv / 2;
        circles.push_back(circle(x, y, radius, vx, vy, (char)rand() % 255));
        printf("There are %d circles.\n", circles.size());
        glutPostRedisplay();
    }
}

void myMouse(int btn, int state, int x, int y){
    //while clicking left button of mouse
    if(choose == 0 && btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        addCircle(x, y);
    }
    if(choose == 1){
        if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
            for(int i = 0; i < cubes.size(); ++i){
                cubes[i].vAngle[0] = 1.0f;
                cubes[i].vAngle[1] = 0.0f;
                cubes[i].vAngle[2] = 0.0f;
            }
        }
        if(btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
            for(int i = 0; i < cubes.size(); ++i){
                cubes[i].vAngle[0] = 0.0f;
                cubes[i].vAngle[1] = 1.0f;
                cubes[i].vAngle[2] = 0.0f;
            }
        }
        //for (int i = 0; i < cubes.size(); ++i) {
        //    printf("%f %f %f\n", cubes[i].vAngle[0], cubes[i].vAngle[1], cubes[i].vAngle[2]);
        //}
    }
    //for (int i = 0; i < circles.size(); ++i) {
    //	printf("--%d %d %d\n", circles[i].x, circles[i].y, circles[i].radius);
    //}
}

void myKey(unsigned char key, int x, int y){
    if(key == 'q' || key == 'Q'){
        exit(0);
    }
    if(choose == 0 && key == 'C' || key == 'c'){
        circles.clear();
    }
}

void mySpecial(int key, int x, int y){
    //printf("+%d\n", key);
    if(choose == 2){
        //printf("++%d\n", choose);
        if(key == GLUT_KEY_UP){
            //printf("+++up\n");
            for(int i = 0; i < spheres.size(); ++i){
                spheres[i].angle[0] += spheres[i].vAngle[0];
            }
        }
    }
}

void myInit(){
    glClearColor(0.0, 0.5, 0.0, 1.0);
    //glShadeModel(GL_FLAT);
    srand((unsigned)time(NULL));
}

circle::circle(int a, int b, int c, int d, int e, unsigned char f){
    x = a, y = b, radius = c;
    v.x = d, v.y = e;
    color = f;
}
void circle::move(int val){
    x += v.x * val;
    y += v.y * val;
    if(x >= winWid){
        x = winWid;
        v.x = -v.x;
    }
    else if(x <= 0){
        x = 0;
        v.x = -v.x;
    }
    if(y >= winHei){
        y = winHei;
        v.y = -v.y;
    }
    else if(y <= 0){
        y = 0;
        v.y = -v.y;
    }
}

void drawSquare(){
    glColor3f(1.0, 0.0, 0.0);
    double a = 20, ox = 50, oy = 50;
    //ox = winWid / 2 + 50, oy = winHei / 2 + 50;
    //printf("%lf\n", a);
    glBegin(GL_POLYGON);
    glVertex3d(ox + a, oy + a, 0.0);
    glVertex3d(ox + a, oy - a, 0.0);
    glVertex3d(ox - a, oy - a, 0.0);
    glVertex3d(ox - a, oy + a, 0.0);
    glEnd();
    //glBegin(GL_TRIANGLE_FAN);
    //    glVertex2f(a, a);
    //    glVertex2f(a, -a);
    //    glVertex2f(-a, -a);
    //    glVertex2f(-a, a);
    //glEnd();
}

void drawSquares(){
    double  ox = winWid / 2, oy = winHei / 2;
    for(int i = 0; i < 8; ++i){
        glPushMatrix();
        glTranslated(ox, oy, 0.0);
        glRotated(i * 45.0, 0, 0, 1.0);
        //glScaled(0.5, 0.5, 0.5);
        drawSquare();
        glPopMatrix();
    }
}

void setOpenGL(){
    printf("Choose:\n");
    printf("0: draw squares and circles\n");
    printf("1: draw a cube\n");
    printf("2: draw circles and cars\n");
    scanf_s("%d", &choose);
    switch(choose){
        case 0:
            initDrawSquareCircle();
            break;
        case 1:
        {
            float a = 100.0f, ox = 0.0, oy = 0.0, oz = -400;
            voc vocs[8];
            vocs[0].setPos(a, a, a);
            vocs[1].setPos(a, a, -a);
            vocs[2].setPos(-a, a, -a);
            vocs[3].setPos(-a, a, a);
            vocs[4].setPos(a, -a, a);
            vocs[5].setPos(a, -a, -a);
            vocs[6].setPos(-a, -a, -a);
            vocs[7].setPos(-a, -a, a);

            vocs[0].setColor(1.0, 0.0, 0.0, 1.0);
            vocs[1].setColor(0.0, 1.0, 0.0, 1.0);
            vocs[2].setColor(0.0, 0.0, 1.0, 1.0);
            vocs[3].setColor(1.0, 1.0, 0.0, 1.0);
            vocs[4].setColor(1.0, 0.0, 1.0, 1.0);
            vocs[5].setColor(0.0, 1.0, 1.0, 1.0);
            vocs[6].setColor(0.0, 0.0, 0.0, 1.0);
            vocs[7].setColor(1.0, 1.0, 1.0, 1.0);

            cube aCube(vocs);
            aCube.setLength(a);
            aCube.setOrigin(ox, oy, oz);
            //for (int i = 0; i < 8; ++i) {
            //    float* pp = (aCube.vertex)[i].color;
            //    printf("%f %f %f %f %f\n", pp[0], pp[1], pp[2], pp[3]);
            //}
            //for (int i = 0; i < 6; ++i) {
            //    for (int j = 0; j < 4; ++j) {
            //        float* pp = aCube.squares[i].ver[j]->color;
            //        printf("%f %f %f %f %f\n", pp[0], pp[1], pp[2], pp[3]);
            //    }
            //}
            cubes.push_back(aCube);
            initDrawCubes();
            break;
        }
        case 2:
        {
            sphere s;
            spheres.push_back(s);
            initDrawCars();
            break;
        }
        //default:
        //    printf("Nothin.");
        //    break;
    }
}

void initDrawSquareCircle(){
    glutInitDisplayMode(GL_DOUBLE | GL_RGB);
    glutDisplayFunc(myDisplay);
    glutMouseFunc(myMouse);
    glutKeyboardFunc(myKey);
    glutSpecialFunc(mySpecial);
    glutReshapeFunc(myReshape);
    glutTimerFunc((1000.0) / DESIRED_FPS, updateTime, 1);
    glutMainLoop();
}

void drawCubes(){
    for(int i = 0; i < cubes.size(); ++i){
        cubes[i].draw();
    }
}

void square::draw(){
    glBegin(GL_POLYGON);
    for(int i = 0; i < 4; ++i){
        float* col = (*(ver[i])).color,
            *pos = (*(ver[i])).pos;
        glColor4f(col[0], col[1], col[2], col[3]);
        //(ver[i])->setColor(1.0, 0.0, 0.0, 1.0);
        glVertex3f(pos[0], pos[1], pos[2]);
    }
    glEnd();
}

void cube::setSquares(){
    for(int i = 0; i < 4; ++i){
        squares[0].ver[i] = &vertex[i];
        squares[1].ver[i] = &vertex[7 - i];
    }
    for(int i = 0; i < 4; ++i){
        squares[i + 2].ver[0] = &vertex[i];
        squares[i + 2].ver[1] = &vertex[i + 4];
        squares[i + 2].ver[2] = &vertex[(i + 1) % 4 + 4];
        squares[i + 2].ver[3] = &vertex[(i + 1) % 4];
    }
    for(int i = 0; i < 3; ++i){
        angle[i] = vAngle[i] = 0.0f;
    }
}

cube::cube(voc* vocs){
    setSquares();
    for(int i = 0; i < 8; ++i){
        vertex[i] = vocs[i];
    }
}

voc::voc(float* vpos, float* vcol){
    for(int i = 0; i < 3; ++i){
        pos[i] = vpos[i];
    }
    for(int i = 0; i < 4; ++i){
        color[i] = vcol[i];
    }
}

void voc::setPos(float a, float b, float c){
    pos[0] = a;
    pos[1] = b;
    pos[2] = c;
}

void voc::setColor(float a, float b, float c, float d){
    color[0] = a;
    color[1] = b;
    color[2] = c;
    color[3] = d;
}

voc::voc(){
    for(int i = 0; i < 4; ++i){
        color[i] = 1.0f;
    }
    for(int i = 0; i < 3; ++i){
        pos[i] = 1.0f;
    }
}

void cube::setOrigin(float a, float b, float c){
    x = a;
    y = b;
    z = c;
}

void cube::setLength(float a){
    length = a;
}

void initDrawCubes(){
    glutInitDisplayMode(GL_DOUBLE | GL_RGB | GL_DEPTH);
    glutDisplayFunc(myDisplay);
    glutMouseFunc(myMouse);
    glutKeyboardFunc(myKey);
    glutSpecialFunc(mySpecial);
    glutReshapeFunc(myReshape);
    glutTimerFunc((1000.0) / DESIRED_FPS, updateTime, 1);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
}

void cube::draw(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(x, y, z);
    glRotatef(angle[0], 1.0, 0.0, 0.0);
    glRotatef(angle[1], 0.0, 1.0, 0.0);
    glRotatef(angle[2], 0.0, 0.0, 1.0);
    for(int i = 0; i < 6; ++i){
        squares[i].draw();
    }
    glPopMatrix();
}

void initDrawCars(){
    glutInitDisplayMode(GL_DOUBLE | GL_RGB | GL_DEPTH);
    glutDisplayFunc(myDisplay);
    glutMouseFunc(myMouse);
    glutKeyboardFunc(myKey);
    glutSpecialFunc(mySpecial);
    glutReshapeFunc(myReshape);
    glutTimerFunc((1000.0) / DESIRED_FPS, updateTime, 1);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
}

void drawCars(){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)winWid / winHei, eyeDistance - planeDepth, eyeDistance + planeDepth);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0f, 0.0f, eyeDistance, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    glLightfv(GL_LIGHT0, GL_POSITION, light0pos);
    glLightfv(GL_LIGHT1, GL_POSITION, light1pos);
    for(int i = 0; i < spheres.size(); ++i){
        spheres[i].draw();
    }
}

void sphere::setRadius(float x){
    radius = x;
}

sphere::sphere(){
    float a[3] = {0.0, 0.0, 0.0},
        va[2] = {10.0, 10.0},
        c[4] = {0.0, 0.5, 0.5, 1.0},
        cc[12] = {1.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 1.0, 1.0};
    setAngle(a);
    setPos(a);
    setColor(c);
    setRadius(100.0f);
    setAxissColor(cc);
    setVAngle(a);
}

void sphere::setColor(float *c){
    for(int i = 0; i < 4; ++i){
        color[i] = c[i];
    }
}

void sphere::draw(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(pos[0], pos[1], pos[2]);
    glRotatef(angle[1], 1.0, 0.0, 0.0);
    glRotatef(angle[0], 0.0, 1.0, 0.0);
    glColor3fv(color);
    glutSolidSphere(radius, 100, 100);
    if(ifShowAxiss){
        drawAxiss(10000.0f);
    }
    glPopMatrix();
}

void sphere::setAngle(float* a){
    for(int i = 0; i < 3; ++i){
        angle[i] = a[i];
    }
}
void sphere::setPos(float* p){
    for(int i = 0; i < 3; ++i){
        pos[i] = p[i];
    }
}

void sphere::setAxissColor(float* c){
    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 4; ++j){
            axissColor[i][j] = *(c + i * 4 + j);
        }
    }
}

void sphere::drawAxiss(float length){
    glMatrixMode(GL_MODELVIEW);
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glDisable(GL_LIGHTING);
    glLineWidth(50.0);

    glBegin(GL_LINES);
    glColor3fv(axissColor[0]);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(length, 0.0, 0.0);
    glColor3fv(axissColor[1]);
    //printf("%f %f %f\n", axissColor[1][0], axissColor[1][1], axissColor[1][2]);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, length, 0.0);
    glColor3fv(axissColor[2]);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, length);
    glEnd();
    glEnable(GL_LIGHTING);
    glPopAttrib();
}

void sphere::setVAngle(float* x){
    for(int i = 0; i < 2; ++i){
        vAngle[i] = x[i];
    }
}