#include <stdio.h>
#include <vector>
#include <string>
#include <time.h>
#include <iostream>
#include <fstream>
#include <gl\glew.h>
#include <gl\glut.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "whiteroom2.h"
#include "crytek_sponza.h"
using namespace glm;
using namespace std;

const string title = "LightMap Demo";
int width;
int height;
int lastX, lastY;
float deltaTime = 0.f;

Scene* scene;

void CalcFPS(){
	static clock_t count = clock();
	static float acc = 0.f;
	static int num = 0;
	deltaTime = ((float)clock() - count) / CLOCKS_PER_SEC;
	acc += deltaTime;
	count = clock();
	++num;
	if (acc >= 1.f){
		char fps[50] = { 0 };
		sprintf_s(fps, " fps:[%d], diffuse[%s], lightmap[%s]", num, scene->showDiffuse ? "on" : "off", scene->showLightmap ? "on" : "off");
		string f = title + fps;
		glutSetWindowTitle(f.c_str());

		num = 0;
		acc = 0.f;
	}
}

static void display(void){
	CalcFPS();


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	scene->Draw(scene->bakeData);

	glutSwapBuffers();
	glutPostRedisplay();
}

static void keyboard(unsigned char key, int x, int y){
	float  speed = 400.f;
	vec3 forward = scene->camera.w;
	vec3 right = scene->camera.u;
	vec3 up = scene->camera.v;
	switch (key){
	case 'w':
		scene->camera.position += forward * -speed * deltaTime;
		break;
	case 's':
		scene->camera.position += forward * speed * deltaTime;
		break;
	case 'a':
		scene->camera.position += right * -speed * deltaTime;
		break;
	case 'd':
		scene->camera.position += right * speed * deltaTime;
		break;
	case 'e':
		scene->camera.position += up * -speed * deltaTime;
		break;
	case 'q':
		scene->camera.position += up * speed * deltaTime;
		break;
	case '[':
		scene->showDiffuse = !scene->showDiffuse;
		break;
	case ']':
		scene->showLightmap = !scene->showLightmap;
		break;
	}
}

static void mouse(int button, int state, int x, int y){
	lastX = x;
	lastY = y;
}

static void motion(int x, int y){
	vec3 u = scene->camera.u;
	vec3 v = scene->camera.v;
	vec3 w = scene->camera.w;
	mat4 r;
	float speed = 1.f;
	if (!false){
		if (x - lastX > 0)
			r = rotate(r, radians(-speed), v);
		else
			r = rotate(r, radians(speed), v);
	}

	if (!true){
		if (y - lastY > 0)
			r = rotate(r, radians(-speed), u);
		else
			r = rotate(r, radians(speed), u);
	}

	lastX = x; lastY = y;

	w = vec3(r*vec4(w, 0));

	scene->camera.Lookat(scene->camera.position,
		scene->camera.position - w, v);
}

void dumpGLInfo() {
	printf("Vendor: %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("Version: %s\n", glGetString(GL_VERSION));
	printf("GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
}

void InitScene(){
	scene->Init();
	width = scene->camera.resolution.x;
	height = scene->camera.resolution.y;
}

void InitGLUT(int argc, char**argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
	glutInitWindowSize(width, height);
	glutCreateWindow(title.c_str());

	glewInit();

	dumpGLInfo();

	glViewport(0, 0, width, height);

	glClearColor(0, 0, 0, 1);
	glClearDepth(1.f);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glEnable(GL_MULTISAMPLE);
}

void main(int argc, char**argv){
	if (argc < 2)
		return;

	int id = atoi(argv[1]);
	switch (id){
	case 0:
		scene = new WhiteroomScene();
		break;
	case 1:
		scene = new CrytekSponzaScene();
		break;
	default:
		scene = new CrytekSponzaScene();
	}

	width = scene->width;
	height = scene->height;

	InitGLUT(argc, argv);
	InitScene();

	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);

	glutMainLoop();

	return;
}