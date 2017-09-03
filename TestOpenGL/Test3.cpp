//#include <stdio.h>
//#include <string.h>
//#include <GL/glew.h>
//#include <GL/freeglut.h>
//#include <fstream>
//
//#include "Importer.hpp"
//#include "ogldev_util.h" //����Ҫ������ߵĹ��������ڶ�ȡ�ı��ļ�
//#include "ogldev_math_3d.h"
//#pragma comment(lib, "glew32.lib")
//using namespace std;
//
//GLuint VBO;
//
//// ����Ҫ��ȡ�Ķ�����ɫ���ű���Ƭ����ɫ���ű����ļ�������Ϊ�ļ���ȡ·���������Ļ�shader.vs��shader.fs�ļ�Ҫ�ŵ����̵ĸ�Ŀ¼�£���֤���涨������������ļ����ļ�·����
//const char* pVSFileName = "shader.vs";
//const char* pFSFileName = "shader.fs";
//
//static void RenderSceneCB()
//{
//	glClear(GL_COLOR_BUFFER_BIT);
//
//	glEnableVertexAttribArray(0);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
//
//	// ��Ȼ���ǻ���һ��������
//	glDrawArrays(GL_TRIANGLES, 0, 3);
//
//	glDisableVertexAttribArray(0);
//
//	glutSwapBuffers();
//}
//
//
//static void InitializeGlutCallbacks()
//{
//	glutDisplayFunc(RenderSceneCB);
//}
//
//static void CreateVertexBuffer()
//{
//	Vector3f Vertices[3];
//	Vertices[0] = Vector3f(-1.0f, -1.0f, 0.0f);
//	Vertices[1] = Vector3f(1.0f, -1.0f, 0.0f);
//	Vertices[2] = Vector3f(0.0f, 1.0f, 0.0f);
//
//	glGenBuffers(1, &VBO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
//}
//
//// ʹ��shader�ı�����shader���󣬲���shader���뵽��ɫ��������
//static void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
//{
//	// ����shader���Ͳ�����������shader����
//	GLuint ShaderObj = glCreateShader(ShaderType);
//	// ����Ƿ���ɹ�
//	if (ShaderObj == 0) {
//		fprintf(stderr, "Error creating shader type %d\n", ShaderType);
//		exit(0);
//	}
//
//	// ����shader�Ĵ���Դ
//	const GLchar* p[1];
//	p[0] = pShaderText;
//	GLint Lengths[1];
//	Lengths[0] = strlen(pShaderText);
//	glShaderSource(ShaderObj, 1, p, Lengths);
//	glCompileShader(ShaderObj);// ����shader����
//
//							   // ����shader��صĴ���
//	GLint success;
//	glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
//	if (!success) {
//		GLchar InfoLog[1024];
//		glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
//		fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
//		exit(1);
//	}
//
//	// ������õ�shader����󶨵�program object���������
//	glAttachShader(ShaderProgram, ShaderObj);
//}
//
//// ������ɫ������
//static void CompileShaders()
//{
//	// ������ɫ������
//	GLuint ShaderProgram = glCreateProgram();
//	// ����Ƿ񴴽��ɹ�
//	if (ShaderProgram == 0) {
//		fprintf(stderr, "Error creating shader program\n");
//		exit(1);
//	}
//
//	// �洢��ɫ���ı����ַ�������
//	string vs, fs;
//	// �ֱ��ȡ��ɫ���ļ��е��ı����ַ���������
//	if (!ReadFile(pVSFileName, vs)) {
//		exit(1);
//	};
//	if (!ReadFile(pFSFileName, fs)) {
//		exit(1);
//	};
//
//	// ��Ӷ�����ɫ����Ƭ����ɫ��
//	AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);
//	AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);
//
//	// ����shader��ɫ�����򣬲���������ش���
//	GLint Success = 0;
//	GLchar ErrorLog[1024] = { 0 };
//	glLinkProgram(ShaderProgram);
//	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);
//	if (Success == 0) {
//		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
//		fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
//		exit(1);
//	}
//
//	// �����֤�ڵ�ǰ�Ĺ���״̬�����Ƿ���Ա�ִ��
//	glValidateProgram(ShaderProgram);
//	glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
//	if (!Success) {
//		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
//		fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
//		exit(1);
//	}
//
//	// ���õ�������������ʹ������ɹ�������shader����
//	glUseProgram(ShaderProgram);
//}
//
//// ������
//int main(int argc, char** argv)
//{
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
//	glutInitWindowSize(1024, 768);
//	glutInitWindowPosition(100, 100);
//	glutCreateWindow("Tutorial 04");
//
//	InitializeGlutCallbacks();
//
//	// ������glut��ʼ����
//	GLenum res = glewInit();
//	if (res != GLEW_OK) {
//		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
//		return 1;
//	}
//
//	printf("GL version: %s\n", glGetString(GL_VERSION));
//
//	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
//
//	CreateVertexBuffer();
//
//	// ������ɫ��
//	CompileShaders();
//
//	glutMainLoop();
//
//	return 0;
//}