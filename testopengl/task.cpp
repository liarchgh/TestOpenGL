#include <ctime>
#include <GL/freeglut.h>
#include <iostream>
#include <ctime>
#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
using namespace std;

GLuint TextFont;

enum status {status_begin, status_run, status_end};

const GLfloat planetColor[] = {0.9, 0.6, 0.4};

// Car tyre color. 
const GLfloat tyreColor[] = {0.2, 0.2, 0.2};

// Material properties for all objects.
const GLfloat materialSpecular[] = {1.0, 1.0, 1.0, 1.0};
const GLfloat materialShininess[] = {100.0};
const GLfloat materialEmission[] = {0.0, 0.0, 0.0, 1.0};

// Light 0.
const GLfloat light0Ambient[] = {0.1, 0.1, 0.1, 1.0};
const GLfloat light0Diffuse[] = {0.7, 0.7, 0.7, 1.0};
const GLfloat light0Specular[] = {0.9, 0.9, 0.9, 1.0};
const GLfloat light0Position[] = {500.0, 0.0, -400.0, 0.0};

// Light 1.
const GLfloat light1Ambient[] = {0.1, 0.1, 0.1, 1.0};
const GLfloat light1Diffuse[] = {0.7, 0.7, 0.7, 1.0};
const GLfloat light1Specular[] = {0.9, 0.9, 0.9, 1.0};
const GLfloat light1Position[] = {-500.0, 0.0, -400.0, 0.0};


const int
	//FPSֵ
	DESIRED_FPS = 120;
int
	winWid = 800,
	winHei = 600;
float
	light0pos[4] = {300.0f, 0.0f, -400.0f , 0.0f},
	light1pos[4] = {-300.0f, 0.0f, -400.0f, 0.0f};

class object{
private:
	//��άλ������
    float pos[3];
	//��ά�ٶ�����
    float vel[3];
	//��ά���ٶ�����
    float acc[3];

public:
	//���Ƶ�ǰ����
    virtual void draw(){
        printf("draw\n");
    }
    virtual void update(int val);
    float length2(object x);
	//set get
    float getAcc(int in) { return acc[in]; }
    void setAcc(int in, float x) { acc[in] = x; }
    float getPos(int in)const{ return pos[in]; }
    void setPos(int in, float x) { pos[in] = x; }
	//��ȡ��ά��������
    float * getPosv() { return &pos[0]; }
    float getVel(int in) { return vel[in]; }
    void setVel(int in, float x) { vel[in] = x; }
};

class circle:public object{
private:
	//��İ뾶
    float radius;
	//�������ɫ
    unsigned char color;

public:
	//���Ƶ�ǰ���� ��д�麯��
    void draw();
	//construct
    circle();
    circle(float a, float b, float c, float d, float e, unsigned char f);
	//set get
    void setRadius(float x) { radius = x; }
    float getRadius()const{ return radius; }
};

class voc:public object{
private:
	//rgba��ɫ
    float color[4] = {1.0, 1.0, 1.0, 1.0};
public:
	//set get
    float getColor(int in) { return color[in]; }
	//��ȡrgba��ɫ����
    float * getColorv() { return &color[0]; }
    void setColor(int in, float x) { color[in] = x; }
    void setPoss(float a, float b, float c);
    void setColors(float a, float b, float c, float d);
	//construct
    voc(float* vpos, float* vcol);
    voc();
};

class square:public object{
private:
    voc* ver[4];
public:
    void setVer(int i, voc* x) { ver[i] = x; }
	//��ȡ��������
    voc * getVer(int i) { return ver[i]; }
	//����
    void draw();
	//��ʼ���ĸ�����ָ��
    void set();
	//construct
    square();
    square(float h);
	//�жϺ�Բ�Ƿ�Ӵ�
    bool judgeCircle(const circle & now);
};

class cube:public object{
private:
    //���˳��̶� �������¿������ǵ�һ����ĸ�����ʱ�뷽��洢��Ȼ������һ���ĸ���Ҳ����ʱ��洢
    voc vertex[8];
    square squares[6];
    float
		//��������ת�Ƕ�
        angle[3],
		//��������ת�ٶ�
		vAngle[3];
public:
	//contruct
    cube(voc* vocs);
    cube();
    cube(float hh);
	//set get
    void setSquares();
    void setVocs(voc* vocs);
	//����
    void draw();
	//�ж��Ƿ���԰��Ӵ�
    bool judgeCircle(const circle & now);
};

class sphere:public object{
private:
	//�Ƿ���ʾ�ֲ�������
	int showAxiss;
	//��ת�Ƕ�
	float angle[2],
		//��ת�ٶ�
		vAngle[2],
		//�뾶
		radius,
		//��������ɫ
		axissColor[3][4],
		color[4];
public:
	//set get
    void setRadius(float x) { radius = x; }
    float getRadius()const{ return radius; }
	void setColor(int in, float x);
	float getColor(int in);
	void setColorv(float * c);
	float * getColorv();
    void setAngle(float* a);
    void setAxissColor(float* c);
    void setVAngle(float* x);
    void setShowAxiss(bool x);
    void setPoss(float*p);
	//����������
    void drawAxiss(float length);
	//����
    void draw();
    sphere();
};


class player:public object {
private:
	//��ǰ��Ծ�ȼ� ���Ϊ2
    int countJump;
	//��ǰ��ɫΪ����
    sphere man;
	//����
    int score;
public:
	//����
    void draw();
	//������Ծ
    void jump();
	//construct
    player();
	//ÿ֡����
    void update(int val);
	//�ж��Ƿ����ϰ�����ײ
    bool judge();
};

class bar :public object {
private:
	//�ϰ���״
    cube s;
	//���߶�
    static float maxHeight;
public:
	//construct
    bar();
	//����
    void draw();
	//�ж��Ƿ��ָ������Ӵ�
    bool judgeSphere(const sphere & now);
};
float bar::maxHeight = 200.0f;

template <class T>
class objectSet:public object {
public:
	//�����е�����
    vector<T*>has;
	//���Ƽ����е�����
    virtual void draw();
	//ÿ֡����
    virtual void updateTime(int val);
};

class barSet:public objectSet<bar> {
private:
	//��¼�����ϴ�����ϰ���ʱ����
    int count;
public:
    bool judgeSphere(const sphere & now);
    void add();
	//set get
    int getCount() { return count; }
    void setCount(int x) { count = x; }
};

class playerSet:public objectSet<player> {
private:
	//���״̬
    status sta;
	//����
    int score;
public:
	//set get
    int getScore() { return score; }
    status getSta() { return sta; }
    void setSta(status x) { sta = x; }
	//�ж��Ƿ��������Ϸ����
    bool judge();
	//�����Ծ
    void jump(int no);
	//ÿ֡����
    void updateTime(int val);
	//construct
    playerSet();
	//����
    void draw();
};

//��ʾ����
class text:public object{
private:
	//��ͬ״̬��ʾ���ı�
    static char * begin;
    static char * end1;
    static char * end2;
public:
	//�ж���ʾʲô����
    void draw(status sta, int score);
	//��������
    void XPrintString(const char *s);
	//��ʾ����
    void showText(const char * ss);
};
char * text::begin = "Press 'A' to run this game.";
char * text::end1 = "Game Over!Your score:";
char * text::end2 = ".(Press 'Q' to quit)";

//�����ϰ�
barSet bars;
//������� ֮���������Ϊ��������һ���һ���˿��ƶ����ɫ
playerSet players;
//�ı���ʾ
text allText;

//vector<object*>all;

void myInit();
//��������
void myKey(unsigned char key, int x, int y);
//��괦��
void myMouse(int btn, int state, int x, int y);
//������Ļ
void myDisplay();
//���ڴ�С�������ı�
void myReshape(int w, int h);
//���³���
void updateTime(int val);

//����openGL������
void setOpenGL();
void init();

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Jump");

    setOpenGL();
    return 0;
}

void myReshape(int w, int h){
    winWid = w;
    winHei = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
        float depth1 = 400.0f, depth2 = 550.0f;
        glFrustum(-winWid / 2, winWid / 2, -winHei / 2, winHei / 2, depth1, depth2);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void updateTime(int val){
    if (players.getSta() == status_run) {
        bars.setCount(bars.getCount() + val);
        if (bars.getCount() > 300) {
            bars.add();
            bars.setCount(0);
        }
        bars.updateTime(val);
        players.updateTime(val);
    }
    glutPostRedisplay();
    glutTimerFunc((1000.0f) / DESIRED_FPS, updateTime, 1);
}

void myDisplay(){

    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    allText.draw(players.getSta(), players.getScore());
    if (players.getSta() != status_begin) {
        bars.draw();
        players.draw();
    }

    glutSwapBuffers();
}

void myMouse(int btn, int state, int x, int y){
}

void myKey(unsigned char key, int x, int y){
    if(key == 'q' || key == 'Q'){
        exit(0);
    }
    if (key == ' ') {
        players.jump(0);
    }
    if (key == 'a' || key == 'A') {
        if (players.getSta() == status_begin) {
            players.setSta(status_run);
        }
    }
}

void mySpecial(int key, int x, int y){
}

void myInit(){
    glClearColor(0.0, 0.5, 0.0, 1.0);
    srand((unsigned)time(NULL));
}

circle::circle(float a, float b, float c, float d, float e, unsigned char f){
    setPos(0, a);
    setPos(1, b);
    radius = c;
    setVel(0, d); 
    setVel(1, e);
    color = f;
}

circle::circle() {
    circle(0, 0, 50.0f, 20, 20, 0x0f);
}

void setOpenGL(){
    srand(unsigned(time(0)));
    players.has.push_back(new player());
    bars.has.push_back(new bar());

    TextFont = glGenLists(128);

    //��ÿ���ַ��Ļ������װ����Ӧ����ʾ�б���
    wglUseFontBitmaps(wglGetCurrentDC(), 0, 128, TextFont);

    init();
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

void square::draw(){
    glPushMatrix();
    glBegin(GL_POLYGON);
    for(int i = 0; i < 4; ++i){
        float * col = ver[i]->getColorv(),
            *pos = ver[i]->getPosv();
        glColor4f(col[0], col[1], col[2], col[3]);
        glVertex3f(pos[0], pos[1], pos[2]);
    }
    glEnd();
    glPopMatrix();
}

void cube::setSquares(){
    for(int i = 0; i < 4; ++i){
        squares[0].setVer(i, &vertex[i]);
        squares[1].setVer(i, &vertex[7 - i]);
    }
    //squares[5]���������
    for(int i = 0; i < 4; ++i){
        squares[i + 2].setVer(0, &vertex[i]);
        squares[i + 2].setVer(1, &vertex[i + 4]);
        squares[i + 2].setVer(2, &vertex[(i + 1) % 4 + 4]);
        squares[i + 2].setVer(3, &vertex[(i + 1) % 4]);
    }
    for(int i = 0; i < 3; ++i){
        angle[i] = vAngle[i] = 0.0f;
    }
}

cube::cube(voc* vocs){
    setSquares();
    setVocs(vocs);
}

void cube::setVocs(voc* vocs){
    for(int i = 0; i < 8; ++i){
        vertex[i] = vocs[i];
    }
}

voc::voc(float* vpos, float* vcol){
    for(int i = 0; i < 3; ++i){
        setPos(i, vpos[i]);
    }
    for(int i = 0; i < 4; ++i){
        color[i] = vcol[i];
    }
}

void voc::setColors(float a, float b, float c, float d){
    setColor(0, a);
    setColor(1, b);
    setColor(2, c);
    setColor(3, d);
}

voc::voc(){
    for(int i = 0; i < 4; ++i){
        color[i] = 1.0f;
    }
    for(int i = 0; i < 3; ++i){
        setPos(i, 1.0f);
    }
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
    //glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    //glLoadIdentity();
    //glTranslatef(x, y, z);
    //glRotatef(angle[0], 1.0, 0.0, 0.0);
    //glRotatef(angle[1], 0.0, 1.0, 0.0);
    //glRotatef(angle[2], 0.0, 0.0, 1.0);
    for(int i = 0; i < 6; ++i){
        squares[i].draw();
    }
    //glColor3fv(vertex[0].color);
    //glutSolidCube(vertex[0].pos[1]);
    glPopMatrix();
}

void init(){
    glutInitDisplayMode(GL_DOUBLE | GL_RGB | GL_DEPTH);
    glClearColor(0.0, 0.0, 0.0, 1.0); // Set black background color.
    glEnable(GL_DEPTH_TEST); // Use depth-buffer for hidden surface removal.
    glShadeModel(GL_SMOOTH);

    //=======================================================================
    // The rest of the code below sets up the lighting and 
    // the material properties of all objects.
    // You can just ignore this part.
    //=======================================================================

    // Set Light 0.
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0Ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0Specular);
    glEnable(GL_LIGHT0);

    // Set Light 1.
    glLightfv(GL_LIGHT1, GL_AMBIENT, light1Ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1Diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1Specular);
    glEnable(GL_LIGHT1);

    glEnable(GL_LIGHTING);

    // Set some global light properties.
    GLfloat globalAmbient[] = {0.1, 0.1, 0.1, 1.0};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);

    // Set the universal material properties.
    // The diffuse and ambient components can be changed using glColor*().
    glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, materialShininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_NORMALIZE); // Let OpenGL automatically renomarlize all normal vectors.

    glutDisplayFunc(myDisplay);
    glutMouseFunc(myMouse);
    glutKeyboardFunc(myKey);
    glutSpecialFunc(mySpecial);
    glutReshapeFunc(myReshape);

    glutTimerFunc((1000.0) / DESIRED_FPS, updateTime, 1);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
}

sphere::sphere(){
    float a[3] = {0.0, 0.0, 0.0},
        va[2] = {3.0, 3.0},
        c[4],
        cc[12] = {1.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 1.0, 1.0};
    for(int i = 0; i < 4; ++i){
        c[i] = rand() % 10000;
        c[i] /= 10000;
    }
    setShowAxiss(0);
    setAngle(a);
    setPoss(a);
    setColorv(c);
    setRadius(50.0f);
    setAxissColor(cc);
    setVAngle(va);

    //maxCars = max(0, in);
    //for(int i = 0; i < maxCars; ++i){
    //    car ac;
    //    float v[2] = {rand(), rand()};
    //    for(int i = 0; i < 2; ++i){
    //        v[i] = v[i] / 10000 - int(v[i] / 10000);
    //        v[i] = (v[i] - 0.5f) * 2;
    //    }
    //    ac.setVAngle(v);
    //    //for(int i = 0; i < 2; ++i){
    //    //    v[i] = rand() % 360;
    //    //}
    //    //ac.setAngle(v);
    //    cars.push_back(ac);
    //}
}

void sphere::setColorv(float *c){
    for(int i = 0; i < 4; ++i){
        setColor(i, c[i]);
    }
}

void sphere::draw(){
    //glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(getPos(0), getPos(1), getPos(2));
    //printf("rot %f\n", angle[0]);
    glColor3fv(getColorv());
    //MyInit();
    //InitCars();

    //printf("%d\n", cars.size());
    //glRotatef(angle[0], 1.0, 0.0, 0.0);
    //glRotatef(angle[1], 0.0, 1.0, 0.0);
    glutSolidSphere(radius, 100, 100);
    //if(showAxiss){
    //    drawAxiss(10000.0f);
    //}
    //if(!cars.size()){
    //    printf("has\n");
    //}
    //for(int i = 0; i < cars.size(); ++i){
    //    //printf("i is %d\n", i);
    //    cars[i].height = &radius;
    //    cars[i].draw();
    //    //printf("%d\n", cars.size());
    //}
    glPopMatrix();
}

void sphere::setAngle(float* a){
    for(int i = 0; i < 3; ++i){
        angle[i] = a[i];
    }
}
void sphere::setPoss(float* p){
    for(int i = 0; i < 3; ++i){
        setPos(i, p[i]);
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

cube::cube(){
    setSquares();
    float a = 100.0f, ox = 0.0, oy = 0.0, oz = 0.0;
    voc vocs[8];
    vocs[0].setPoss(a, a, a);
    vocs[1].setPoss(a, a, -a);
    vocs[2].setPoss(-a, a, -a);
    vocs[3].setPoss(-a, a, a);
    vocs[4].setPoss(a, -a, a);
    vocs[5].setPoss(a, -a, -a);
    vocs[6].setPoss(-a, -a, -a);
    vocs[7].setPoss(-a, -a, a);

    vocs[0].setColors(1.0, 0.0, 0.0, 1.0);
    vocs[1].setColors(0.0, 1.0, 0.0, 1.0);
    vocs[2].setColors(0.0, 0.0, 1.0, 1.0);
    vocs[3].setColors(1.0, 1.0, 0.0, 1.0);
    vocs[4].setColors(1.0, 0.0, 1.0, 1.0);
    vocs[5].setColors(0.0, 1.0, 1.0, 1.0);
    vocs[6].setColors(0.0, 0.0, 0.0, 1.0);
    vocs[7].setColors(1.0, 1.0, 1.0, 1.0);


    setVocs(vocs);
}

void sphere::setShowAxiss(bool x){
    if(x){
        showAxiss = 1;
    }
    else{
        showAxiss = 0;
    }
}

void player::draw() {
    glPushMatrix();
    glTranslatef(getPos(0), getPos(1), getPos(2));
    man.draw();
    glPopMatrix();
}

player::player():man() {
    for (int i = 0; i < 3; ++i) {
        setPos(i, 0.0f);
        setVel(i, 0.0f);
        setAcc(i, 0.0f);
        
        man.setPos(i, 0.0f);
        man.setVel(i, 0.0f);
        man.setAcc(i, 0.0f);
    }
    score = 0;
    setPos(2, -500.0f);
    setPos(0, -300.0f);
    countJump = 0;
    man.setRadius(20.0f);
    setAcc(1, -0.2f);
}

void circle::draw(){
    glColor3f(0.0f, 0.5f, 1.0f);
    glBegin(GL_TRIANGLE_FAN);
    for(double j = 0.0, stepRa = 0.1; j < 3.1 * 2; j += stepRa){
        float tx = getPos(0) + radius * cos(j),
            ty = getPos(1) + radius * sin(j);
        glVertex3f(tx, ty, getPos(2));
    }
    glEnd();
}

void bar::draw() {
    glPushMatrix();
    glTranslatef(getPos(0), getPos(1), getPos(2));
    s.draw();
    glPopMatrix();
}

bar::bar():s(maxHeight){
    for (int i = 0; i < 3; ++i) {
        setPos(i, 0.0f);
        setVel(i, 0.0f);
        setAcc(i, 0.0f);
    }
    setVel(0, -3.0f);
    setPos(2, -500.0f);
    setPos(1, 0.0f);
    setPos(0, 500.0f);
}

void square::set() {
    for (int i = 0; i < 4; ++i) {
        ver[i] = new voc();
        ver[i]->setPos(2, 0.0f);
        for (int j = 0; j < 4; ++j) {
            ver[i]->setColor(j, 1.0f);
        }
    }

    ver[0]->setPos(1, 100.0f);
    ver[3]->setPos(1, 100.0f);
    ver[0]->setPos(0, -30.0f);
    ver[1]->setPos(0, -30.0f);
    ver[1]->setPos(1, 0.0f);
    ver[2]->setPos(1, 0.0f);
    ver[2]->setPos(0, 30.0f);
    ver[3]->setPos(0, 30.0f);
}

template <typename T>
void objectSet<T>::draw() {
    for (int i = 0; i < has.size(); ++i) {
        has[i]->draw();
    }
}

template <typename T>
void objectSet<T>::updateTime(int val) {
    for(int i = 0; i < has.size(); ++i){
        has[i]->update(val);
    }
}

bool playerSet::judge() {
    for (int i = 0; i < has.size(); ++i) {
        if (!(has[i]->judge())) {
            sta = status_end;
            return false;
        }
    }
    return true;
}

void playerSet::jump(int no) {
    if (no < has.size()){
        has[no]->jump();
    }
}

void player::jump() {
    if (countJump < 2) {
        setVel(1, 8.0f);
        ++countJump;
    }
}

void object::update(int val) {
    for (int j = 0; j < 3; ++j) {
        vel[j] += acc[j] * val;
        pos[j] += vel[j] * val;
    }
}

void player::update(int val) {
    for (int j = 0; j < 3; ++j) {
        setVel(j, getVel(j) + getAcc(j) * val);
        setPos(j, getPos(j) + getVel(j) * val);
    }
    man.update(val);
}

void playerSet::updateTime(int val) {
    for (int i = 0; i < has.size(); ++i) {
        has[i]->update(val);
    }
    judge();
    score += val;
}

bool player::judge() {
    if (getPos(1) < 0.0f) {
        setPos(1, 0.0f);
        setVel(1, 0.0f);
        countJump = 0;
    }

    sphere jud = man;
    for (int i = 0; i < 3; ++i) {
        jud.setPos(i, getPos(i));
    }
    return bars.judgeSphere(jud);
}

bool barSet::judgeSphere(const sphere & now) {
    for (int i = 0; i < has.size(); ++i) {
        if (!(has[i]->judgeSphere(now))) {
            return false;
        }
    }
    return true;
}

bool bar::judgeSphere(const sphere & now) {
    circle x;
    x.setRadius(now.getRadius());
    for (int i = 0; i < 3; ++i) {
        x.setPos(i, now.getPos(i) - getPos(i));
    }
    return s.judgeCircle(x);
}

bool square::judgeCircle(const circle & now) {
    float maxx = ver[3]->getPos(0) + now.getRadius();
    float minx = ver[0]->getPos(0) - now.getRadius();
    float miny = ver[1]->getPos(1) - now.getRadius();
    float maxy = ver[0]->getPos(1) + now.getRadius();
    float smaxx = ver[3]->getPos(0);
    float sminx = ver[0]->getPos(0);
    float sminy = ver[1]->getPos(1);
    float smaxy = ver[0]->getPos(1);
    float x = now.getPos(0);
    float y = now.getPos(1);

    for (int i = 0; i < 4; ++i) {
        if (ver[i]->length2(now) < now.getRadius ()* now.getRadius()) {
            return false;
        }
    }
    if (x >= minx && x <= maxx
        && y >= sminy && y <= smaxy) {
        return false;
    }
    if (x >= sminx && x <= smaxx
        && y >= miny && y <= maxy) {
        return false;
    }
    return true;
}

float object::length2(object x) {
    float ans = 0.0f;
    for (int i = 0; i < 3; ++i) {
        float l = pos[i] - x.pos[i];
        ans += l * l;
    }
    return ans;
}

playerSet::playerSet() {
    sta = status_begin;
    score = 0;
}

void barSet::add() {
    has.push_back(new bar());
}

square::square() {
    set();
}

square::square(float h) {
    set();
    int r = rand();
    float hh = ((float)(r % 800+ 200) / 1000 * h);
    //cout << hh << endl;
    ver[0]->setPos(1, hh);
    ver[3]->setPos(1, hh);
}

void text::XPrintString(const char *s) {
    glPushAttrib(GL_LIST_BIT);

    //����ÿ���ַ���Ӧ����ʾ�б�����ÿ���ַ�
    for (; *s != '\0'; ++s)
        glCallList(TextFont + *s);

    glPopAttrib();
}


void text::showText(const char * ss) {
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -400.0f);
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos3f(0.5, 0.5, 0.0);
    XPrintString(ss);
    glPopMatrix();
}

void text::draw(status sta, int score) {
    if (sta == status_begin) {
        showText(begin);
    }
    else if (sta == status_run) {
    }
    else if(sta == status_end){
        int len = 0;
        for (int i = score; i > 0; ++len) {
            i /= 10;
        }
        int endLen1 = strlen(end1);
        int endLen2 = strlen(end2);
        char * sb = new char[len + 6 + endLen1 + endLen2];
        //char sb[20000];
        strcpy_s(sb, len + 6 + endLen1 + endLen2, end1);
        sprintf_s(sb + endLen1, len + 6, "%d", score);
        strcpy_s(sb + endLen1 + len, 6 + endLen2, end2);
        //sb[len + endLen] = '\0';
        showText(sb);
    }
}

void playerSet::draw() {
    for (int i = 0; i < has.size(); ++i) {
        has[i]->draw();
    }
    //allText.draw(sta, score);
}

cube::cube(float hh) {
    int r = rand();
    hh = ((float)(r % 800+ 200) / 1000 * hh);
    setSquares();
    float a = 30.0f;
    float z = 30.0f;
    voc vocs[8];
    vocs[0].setPoss(a, hh, a);
    vocs[1].setPoss(a, hh, -a);
    vocs[2].setPoss(-a, hh, -a);
    vocs[3].setPoss(-a, hh, a);
    vocs[4].setPoss(a, 0, a);
    vocs[5].setPoss(a, 0, -a);
    vocs[6].setPoss(-a, 0, -a);
    vocs[7].setPoss(-a, 0, a);

    vocs[0].setColors(1.0, 0.0, 0.0, 1.0);
    vocs[1].setColors(0.0, 1.0, 0.0, 1.0);
    vocs[2].setColors(0.0, 0.0, 1.0, 1.0);
    vocs[3].setColors(1.0, 1.0, 0.0, 1.0);
    vocs[4].setColors(1.0, 0.0, 1.0, 1.0);
    vocs[5].setColors(0.0, 1.0, 1.0, 1.0);
    vocs[6].setColors(0.0, 0.0, 0.0, 1.0);
    vocs[7].setColors(1.0, 1.0, 1.0, 1.0);

    setVocs(vocs);

    for (int i = 0; i < 3; ++i) {
        setPos(i, 0.0f);
        setVel(i, 0.0f);
    }
}

bool cube::judgeCircle(const circle & now) {
    return squares[5].judgeCircle(now);
}

void voc::setPoss(float a, float b, float c) {
    setPos(0, a);
    setPos(1, b);
    setPos(2, c);
}

float * sphere::getColorv(){
	return color;
}

void sphere::setColor(int in, float x){
	color[in] = x;
}
float sphere::getColor(int in){
	return color[in];
}
