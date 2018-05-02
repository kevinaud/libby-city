// LIBARIES
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glui.h>

// CITY
#include "city/City.h"

// CAMERA
#include "camera/Camera.h"

// CONFIG
#include "config/config.h"

using namespace std;

int screenWidth = 1000;
int screenHeight = 1000;

int wireframe = 1;
int filled = 1;
int normal = 0;
int segmentsX = 10;
int segmentsY = 10;
int	rotX = 0, rotY = 0, rotZ = 0;

int viewAngle = 45;
int	camRotU = 0, camRotV = 0, camRotW = 0;

float eyeX = 0, eyeY = 5, eyeZ = 0;
float lookX = 0, lookY = 0, lookZ = -1;
float upX = 0.0, upY = 1.0, upZ = 0;

float clipNear = 0.001;
float clipFar = 10000;

// tracks which keys are being held down
GLboolean keysInUse[512]; 

// tracks if the camera is rotating in +/- x, +/- y direction 
// (from camera perspective)
int rotationDirection[2] = { 0, 0 }; 

int  main_window;

/** these are the global variables used for rendering **/
City* city;
Camera* camera = new Camera();

int previousTime = 0;

/********************************************************
 * Function Definitions
 *******************************************************/

// Camera movement functions
void mouseMoveHandler(int x, int y);
void keyPressHandler(unsigned char key, int x, int y);
void keyReleaseHandler(unsigned char key, int x, int y);
void updateCameraPos(int deltaTime);
int calcDeltaTime();

void drawAxes();

// Glut callbacks
void myGlutDisplay(void);
void myGlutIdle(void);
void myGlutReshape(int x, int y);

// city initialization
void initCity();

// opengl initialization
void initGLUT(int argc, char* argv[]);
void initLighting();
void initGLUI();

// teardown
void onExit();

/**
 * MAIN
 */
int main(int argc, char* argv[]) {
	srand(time(0));
	atexit(onExit);

    // set up all the glut / opengl / glui stuff
    initGLUT(argc, argv);

    // set up city
    initCity();

	glutMainLoop();

	return EXIT_SUCCESS;
}

void initCity() {
    city = new City(24, 8);
    city->setSkybox(new Skybox(
        project_dir + "libby-city/src/img/SunSetFront2048.bmp",
        project_dir + "libby-city/src/img/SunSetBack2048.bmp",
        project_dir + "libby-city/src/img/SunSetRight2048.bmp",
        project_dir + "libby-city/src/img/SunSetLeft2048.bmp",
        project_dir + "libby-city/src/img/SunSetUp2048.bmp",
        project_dir + "libby-city/src/img/SunSetDown2048.bmp"
    ));
}

void myGlutDisplay(void)
{
	glClearColor(.9f, .9f, .9f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    int deltaTime = calcDeltaTime();
    updateCameraPos(deltaTime);

    glEnable(GL_LIGHTING);
	if (filled) {
		glEnable(GL_POLYGON_OFFSET_FILL);
		glColor3f(1, 1, 1);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		city->draw();
	}
	
	if (wireframe) {
		glDisable(GL_POLYGON_OFFSET_FILL);
		glColor3f(0.0, 0.0, 0.0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        city->draw();
	}

	camera->RotateV(-camRotV);
	camera->RotateU(-camRotU);
	camera->RotateW(-camRotW);

	glutSwapBuffers();
}

void myGlutIdle(void)
{
	/* According to the GLUT specification, the current window is
	undefined during an idle callback.  So we need to explicitly change
	it if necessary */
	if (glutGetWindow() != main_window)
		glutSetWindow(main_window);

	glutPostRedisplay();
}

void myGlutReshape(int x, int y)
{
	glViewport(0, 0, x, y);

    screenWidth = x;
    screenHeight = y;
	camera->SetScreenSize(x, y);

	glutPostRedisplay();
}

void mouseMoveHandler(int x, int y) {
    if ((screenWidth - x) > (0.75 * screenWidth)) {        // rotate left
        rotationDirection[0] = 1;
    } else if ((screenWidth - x) < (0.25 * screenWidth)) { // rotate right
        rotationDirection[0] = -1;
    } else {                                              // dont rotate left or right
        rotationDirection[0] = 0;
    }

    if ((screenHeight - y) > (0.75 * screenHeight)) {        // rotate up
        rotationDirection[1] = -1;
    } else if ((screenHeight - y) < (0.25 * screenHeight)) { // rotate down
        rotationDirection[1] = 1;
    } else {                                              // dont rotate up or down
        rotationDirection[1] = 0;
    }
}

void keyPressHandler(unsigned char key, int x, int y) {
    if (key >= 0 && key < 512) {
        keysInUse[key] = true;
    }
    /* camera->keyPressHandler(key, x, y); */
}

void keyReleaseHandler(unsigned char key, int x, int y) {
    if (key >= 0 && key < 512) {
        keysInUse[key] = false;
    }
    /* camera->keyReleaseHandler(key, x, y); */
}

void updateCameraPos(int deltaTime) {

	camera->SetViewAngle(viewAngle);
	camera->SetNearPlane(clipNear);
	camera->SetFarPlane(clipFar);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	Matrix projection = camera->GetProjectionMatrix();
	glMultMatrixd(projection.unpack());

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	Point eyeP(eyeX, eyeY, eyeZ);

	Vector look = camera->GetLookVector();

    Vector dirX(look[0], 0, 0);
    Vector dirY(0, look[1], 0);
    Vector dirZ(0, 0, look[2]);

    // Alter position in the appropriate direction
    Vector fMovement(0.0, 0.0, 0.0);

    if (keysInUse['w'])  // forward
        fMovement = fMovement + dirZ;

    if (keysInUse['s'])  // backward
        fMovement = fMovement - dirZ;

    if (keysInUse['a'])  // left
        fMovement = fMovement + dirX;

    if (keysInUse['d'])  // right
        fMovement = fMovement - dirX;

    if (keysInUse['e'])  // vertical up
        fMovement = fMovement - dirY;

    if (keysInUse['q'])  // vertical down
        fMovement = fMovement + dirY;

    fMovement = camera->getCamera2WorldMatrix() * fMovement;
    GLfloat cMovementSpeed = 0.000005; // !!

    // Trick to balance PC speed with movement
    GLfloat velocity = cMovementSpeed * deltaTime;

    // Update camera position using the appropriate velocity
    eyeP = eyeP + fMovement * velocity;

    eyeX = eyeP[0];
    eyeY = eyeP[1];
    eyeZ = eyeP[2];

    if (rotationDirection[0] != 0) {
        Matrix rotMat = rotY_mat(3.142 /180 * rotationDirection[0]);
        Matrix cam2World = camera->getCamera2WorldMatrix();

        Vector look(0.0, 0.0, -1.0);
        look = rotMat * look;
        look = cam2World * look;

        lookX = look[0];
        lookY = look[1];
        lookZ = look[2];
    }

    if (rotationDirection[1] != 0) {

        float cs = cos(3.142 /180 * rotationDirection[1]);
        float sn = sin(3.142 /180 * rotationDirection[1]);

        Vector look1(0.0, 0.0, -1.0);
        Vector up(0.0, 1.0, 0.0);

        Vector old = look1;

        Vector u(cs*old[0] - sn*up[0], cs*old[1] - sn*up[1], cs*old[2] - sn*up[2]);
        Vector v(sn*old[0] + cs*up[0], sn*old[1] + cs*up[1], sn*old[2] + cs*up[2]) ;

        Matrix transform = camera->getCamera2WorldMatrix();

        u = transform * u;
        v = transform * v;
        
        lookX = u[0];
        lookY = u[1];
        lookZ = u[2];

        upX = v[0];
        upY = v[1];
        upZ = v[2];
    }

	eyeP = Point(eyeX, eyeY, eyeZ);
	Vector lookV(lookX, lookY, lookZ);
	Vector upV(upX, upY, upZ);

	camera->Orient(eyeP, lookV, upV);
	camera->RotateV(camRotV);
	camera->RotateU(camRotU);
	camera->RotateW(camRotW);

	Matrix modelView = camera->GetModelViewMatrix();
	glMultMatrixd(modelView.unpack());

}

int calcDeltaTime() {
    int current = glutGet(GLUT_ELAPSED_TIME);
    int deltaTime = current - previousTime;
    previousTime = current;
    return deltaTime;
}

void drawAxes() {
	//drawing the axes
    glDisable(GL_LIGHTING);
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0, 0, 0); glVertex3f(1.0, 0, 0);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0, 0, 0); glVertex3f(0.0, 1.0, 0);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0, 0, 0); glVertex3f(0, 0, 1.0);
	glEnd();
}


/****************************************/
/*   Initialize GLUT and create window  */
/****************************************/
void initGLUT(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(screenWidth, screenHeight);

	main_window = glutCreateWindow("CSI 4341: Assignment 2");
	glutDisplayFunc(myGlutDisplay);
	glutReshapeFunc(myGlutReshape);

    // register keyboard handlers
    glutKeyboardFunc(keyPressHandler);
    glutKeyboardUpFunc(keyReleaseHandler);
    
    // register mouse handlers
    glutPassiveMotionFunc(mouseMoveHandler);

    initLighting();

    // enable z-buffering
	glPolygonOffset(1, 1);

    initGLUI();
}

/****************************************/
/*       Set up OpenGL lighting         */
/****************************************/
void initLighting() {
    glClearColor (0.38, 0.38, 0.38, 0.0);
    glShadeModel (GL_SMOOTH);
    GLfloat light_ambient     [] = { 0.0f, 0.0f, 0.0f, 1.0f };  /* default value */
    GLfloat light_diffuse     [] = { 1.0f, 1.0f, 1.0f, 1.0f };  /* default value */
    GLfloat light_specular    [] = { 1.0f, 1.0f, 1.0f, 1.0f };  /* default value */
    GLfloat light_position    [] = { 1.0f, 1.0f, 1.0f, 0.0f };  /* NOT default value */
    GLfloat lightModel_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };  /* default value */
    GLfloat material_specular [] = { 1.0f, 1.0f, 1.0f, 1.0f };  /* NOT default value */
    GLfloat material_emission [] = { 1.0f, 1.0f, 1.0f, 1.0f };  /* default value */

    glLightfv (GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv (GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv (GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv (GL_LIGHT0, GL_POSITION, light_position);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lightModel_ambient);
    glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
    glMaterialfv(GL_FRONT, GL_EMISSION, material_emission);
    glMaterialf(GL_FRONT, GL_SHININESS, 10.0);               /* NOT default value	*/

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
}

/****************************************/
/*         Here's the GLUI code         */
/****************************************/
void initGLUI() {
	GLUI *glui = GLUI_Master.create_glui("GLUI");

	glui->add_button("Quit", 0, (GLUI_Update_CB)exit);

	glui->set_main_gfx_window(main_window);

	/* We register the idle callback with GLUI, *not* with GLUT */
	GLUI_Master.set_glutIdleFunc(myGlutIdle);
}

void onExit()
{
	delete city;
}

