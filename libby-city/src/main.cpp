#include <iostream>
#include <cmath>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glui.h>
#include "shapes/Shape.h"
#include "shapes/Cube.h"
#include "shapes/Cylinder.h"
#include "shapes/Cone.h"
#include "shapes/Sphere.h"
#include "camera/Camera.h"

GLuint back;
GLuint front;
GLuint left;
GLuint right;
GLuint up;
GLuint down;

enum OBJ_TYPE {
	SHAPE_CUBE = 0,
	SHAPE_CYLINDER = 1,
	SHAPE_CONE = 2,
	SHAPE_SPHERE = 3,
	SHAPE_SPECIAL1 = 4,
	SHAPE_SPECIAL2 = 5,
	SHAPE_SPECIAL3 = 6
};

int screenWidth = 500;
int screenHeight = 500;

/** These are the live variables passed into GLUI ***/
int  wireframe = 1;
int  fill = 1;
int  normal = 0;
int  segmentsX = 10;
int  segmentsY = 10;
int	 rotX = 0;
int	 rotY = 0;
int	 rotZ = 0;
int  scale = 50;

int	 camRotU = 0;
int	 camRotV = 0;
int	 camRotW = 0;
int  viewAngle = 45;
float eyeX = 2;
float eyeY = 2;
float eyeZ = 2;
float lookX = -2;
float lookY = -2;
float lookZ = -2;
float clipNear = 0.001;
float clipFar = 30;
float upX = 0.0;
float upY = 1.0;
float upZ = 0.0;

/**
 * keyboard and mouse movement variables
 */
// tracks which keys are being held down
GLboolean keysInUse[512]; 
// tracks if the camera is rotating in +/- x, +/- y direction (from camera perspective)
int rotationDirection[2] = { 0, 0 }; 

int  main_window;

/** these are the global variables used for rendering **/
OBJ_TYPE objType = SHAPE_CUBE;
Cube* cube = new Cube();
Cylinder* cylinder = new Cylinder();
Cone* cone = new Cone();
Sphere* sphere = new Sphere();
Shape* shape = cube;
Camera* camera = new Camera();

/***************************************** callback_obj() ***********/

void callback_obj(int id) {
	switch (objType) {
	case SHAPE_CUBE:
		shape = cube;
		break;
	case SHAPE_CYLINDER:
		shape = cylinder;
		break;
	case SHAPE_CONE:
		shape = cone;
		break;
	case SHAPE_SPHERE:
		shape = sphere;
		break;
	case SHAPE_SPECIAL1:
		shape = cube;
		break;
	default:
		shape = cube;
	}
}

/***************************************** myGlutIdle() ***********/

void myGlutIdle(void)
{
	/* According to the GLUT specification, the current window is
	undefined during an idle callback.  So we need to explicitly change
	it if necessary */
	if (glutGetWindow() != main_window)
		glutSetWindow(main_window);

	glutPostRedisplay();
}


/**************************************** myGlutReshape() *************/

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
    GLfloat cMovementSpeed = 0.0005;

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

}

void updateCameraLook(int deltaTime) {

}

int previousTime = 0;

int calcDeltaTime() {
    int current = glutGet(GLUT_ELAPSED_TIME);
    int deltaTime = current - previousTime;
    previousTime = current;
    return deltaTime;
}

/***************************************** myGlutDisplay() *****************/

void myGlutDisplay(void)
{
	/* glClearColor(.9f, .9f, .9f, 1.0f); */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	camera->SetViewAngle(viewAngle);
	camera->SetNearPlane(clipNear);
	camera->SetFarPlane(clipFar);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	Matrix projection = camera->GetProjectionMatrix();
	glMultMatrixd(projection.unpack());

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    int deltaTime = calcDeltaTime();
    updateCameraPos(deltaTime);
    updateCameraLook(deltaTime);

	Point eyeP(eyeX, eyeY, eyeZ);
	Vector lookV(lookX, lookY, lookZ);
	Vector upV(upX, upY, upZ);

	camera->Orient(eyeP, lookV, upV);
	camera->RotateV(camRotV);
	camera->RotateU(camRotU);
	camera->RotateW(camRotW);
	Matrix modelView = camera->GetModelViewMatrix();
	glMultMatrixd(modelView.unpack());

	//rotate object
	glRotatef(rotX, 1.0, 0.0, 0.0);
	glRotatef(rotY, 0.0, 1.0, 0.0);
	glRotatef(rotZ, 0.0, 0.0, 1.0);

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

	//scale object
	glScalef(scale / 50.0, scale / 50.0, scale / 50.0);

	shape->setSegments(segmentsX, segmentsY);
	
	if (normal) {
		glColor3f(1.0, 0.0, 0.0);
		shape->drawNormal();
	}

    glEnable(GL_LIGHTING);
	if (fill) {
		/* glEnable(GL_POLYGON_OFFSET_FILL); */
		/* glColor3f(0.5, 0.5, 0.5); */
		/* glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); */
		shape->draw();
	}
	
	if (wireframe) {
		glDisable(GL_POLYGON_OFFSET_FILL);
		glColor3f(0.0, 0.0, 0.0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		shape->draw();
	}

	camera->RotateV(-camRotV);
	camera->RotateU(-camRotU);
	camera->RotateW(-camRotW);

	glutSwapBuffers();
}

void onExit()
{
	delete cube;
	delete cylinder;
	delete cone;
	delete sphere;
}

GLuint loadBMP(const char * imagepath);

/**************************************** main() ********************/

int main(int argc, char* argv[])
{
	atexit(onExit);

	/****************************************/
	/*         Load Skybox Textures         */
	/****************************************/
    back = loadBMP("../img/SkyboxSet1/SunSet/SunSetBack2048.bmp"); 
    front = loadBMP("../img/SkyboxSet1/SunSet/SunSetFront2048.bmp"); 

    left = loadBMP("../img/SkyboxSet1/SunSet/SunSetLeft2048.bmp"); 
    right = loadBMP("../img/SkyboxSet1/SunSet/SunSetRight2048.bmp"); 

    up = loadBMP("../img/SkyboxSet1/SunSet/SunSetUp2048.bmp"); 
    down = loadBMP("../img/SkyboxSet1/SunSet/SunSetDown2048.bmp"); 

    cube->setTexture(front);

	/****************************************/
	/*   Initialize GLUT and create window  */
	/****************************************/

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

	/****************************************/
	/*       Set up OpenGL lighting         */
	/****************************************/


	    glClearColor (0.38, 0.38, 0.38, 0.0);
        glShadeModel (GL_SMOOTH);

        GLfloat light_pos0[] = {0.0f, 0.0f, 1.0f, 0.0f};
        GLfloat diffuse[] = {0.5f, 0.5f, 0.5f, 0.0f};
        GLfloat ambient[] = {0.1f, 0.1f, 0.1f, 1.0f};

        glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
        glLightfv(GL_LIGHT0, GL_POSITION, light_pos0);

        glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
        glEnable(GL_COLOR_MATERIAL);

        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_DEPTH_TEST);


	///****************************************/
	///*          Enable z-buferring          */
	///****************************************/

	glPolygonOffset(1, 1);

	/****************************************/
	/*         Here's the GLUI code         */
	/****************************************/

	GLUI *glui = GLUI_Master.create_glui("GLUI");

	GLUI_Panel *render_panel = glui->add_panel("Render");
	new GLUI_Checkbox(render_panel, "Wireframe", &wireframe);
	new GLUI_Checkbox(render_panel, "Fill", &fill);
	new GLUI_Checkbox(render_panel, "Normal", &normal);
	(new GLUI_Spinner(render_panel, "Segments X:", &segmentsX))
		->set_int_limits(3, 60);
	(new GLUI_Spinner(render_panel, "Segments Y:", &segmentsY))
		->set_int_limits(3, 60);

	GLUI_Panel *camera_panel = glui->add_panel("Camera");
	(new GLUI_Spinner(camera_panel, "RotateV:", &camRotV))
		->set_int_limits(-179, 179);
	(new GLUI_Spinner(camera_panel, "RotateU:", &camRotU))
		->set_int_limits(-179, 179);
	(new GLUI_Spinner(camera_panel, "RotateW:", &camRotW))
		->set_int_limits(-179, 179);
	(new GLUI_Spinner(camera_panel, "Angle:", &viewAngle))
		->set_int_limits(1, 179);

	GLUI_Spinner* eyex_widget = glui->add_spinner_to_panel(camera_panel, "EyeX:", GLUI_SPINNER_FLOAT, &eyeX);
	eyex_widget->set_float_limits(-5, 5);
	GLUI_Spinner* eyey_widget = glui->add_spinner_to_panel(camera_panel, "EyeY:", GLUI_SPINNER_FLOAT, &eyeY);
	eyey_widget->set_float_limits(-5, 5);
	GLUI_Spinner* eyez_widget = glui->add_spinner_to_panel(camera_panel, "EyeZ:", GLUI_SPINNER_FLOAT, &eyeZ);
	eyez_widget->set_float_limits(-5, 5);

	GLUI_Spinner* lookx_widget = glui->add_spinner_to_panel(camera_panel, "LookX:", GLUI_SPINNER_FLOAT, &lookX);
	lookx_widget->set_float_limits(-5, 5);
	GLUI_Spinner* looky_widget = glui->add_spinner_to_panel(camera_panel, "LookY:", GLUI_SPINNER_FLOAT, &lookY);
	looky_widget->set_float_limits(-5, 5);
	GLUI_Spinner* lookz_widget = glui->add_spinner_to_panel(camera_panel, "LookZ:", GLUI_SPINNER_FLOAT, &lookZ);
	lookz_widget->set_float_limits(-5, 5);

	GLUI_Spinner* clipN_widget = glui->add_spinner_to_panel(camera_panel, "Near:", GLUI_SPINNER_FLOAT, &clipNear);
	clipN_widget->set_float_limits(0, 10);
	GLUI_Spinner* clipF_widget = glui->add_spinner_to_panel(camera_panel, "Far:", GLUI_SPINNER_FLOAT, &clipFar);
	clipF_widget->set_float_limits(0, 100);

	glui->add_column(true);

	GLUI_Panel *obj_panel = glui->add_panel("Object Type");
	GLUI_RadioGroup *group1 =
		glui->add_radiogroup_to_panel(obj_panel, (int*)(&objType), 3, callback_obj);
	glui->add_radiobutton_to_group(group1, "Cube");
	glui->add_radiobutton_to_group(group1, "Cylinder");
	glui->add_radiobutton_to_group(group1, "Cone");
	glui->add_radiobutton_to_group(group1, "Sphere");
	glui->add_radiobutton_to_group(group1, "Special1");


	GLUI_Panel *object_panel = glui->add_panel("Object");
	(new GLUI_Spinner(object_panel, "Rotate X:", &rotX))
		->set_int_limits(0, 359);
	(new GLUI_Spinner(object_panel, "Rotate Y:", &rotY))
		->set_int_limits(0, 359);
	(new GLUI_Spinner(object_panel, "Rotate Z:", &rotZ))
		->set_int_limits(0, 359);
	(new GLUI_Spinner(object_panel, "Scale:", &scale))
		->set_int_limits(1, 100);

	glui->add_button("Quit", 0, (GLUI_Update_CB)exit);

	glui->set_main_gfx_window(main_window);

	/* We register the idle callback with GLUI, *not* with GLUT */
	GLUI_Master.set_glutIdleFunc(myGlutIdle);

	glutMainLoop();

	return EXIT_SUCCESS;
}

GLuint loadBMP(const char * imagepath) {

	GLuint texture;
	int width = 2048, height = 2048;
	unsigned char * data;

	FILE * file;
	file = fopen(imagepath, "rb");

	if (file == NULL) {
        return 0;
	}

	data = (unsigned char *)malloc( width * height * 3);
	//int size = fseek(file,);
	fread(data, width * height * 3, 1, file);
	fclose(file);

	for (int i = 0; i < width * height ; ++i) {
		int index = i*3;
		unsigned char B,R;
		B = data[index];
		R = data[index + 2];

		data[index] = R;
		data[index + 2] = B;
	}

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	/* glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE); */
	/* glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST); */


	/* glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR); */
	/* glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT); */
	/* glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT); */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_BGR, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	//gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height,GL_RGB, GL_UNSIGNED_BYTE, data);
	free(data);

	return texture;
}


