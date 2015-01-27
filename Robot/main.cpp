#include "main.h"
#include <windows.h>

//Same as one for AssembleAndroid.
GLuint firstTexture;
Controls cameraControls;
AssembleAndroid* assembleAndroid = new AssembleAndroid();
int
main(int argc, char **argv)
{
	//Initializes GLUT, creates window and places window.
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(screenWidth, screenHeight);
	//Title of window.

	window = glutCreateWindow("CS4204: Assignment Three");
	//CALLBACKS-------------------------------------------

	//GLUT initialization method.
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_TEXTURE_2D);


	//Display function callback.
	glutDisplayFunc(display);
	//Reshape function callback.
	glutReshapeFunc(reshapeDisplay);
	//Idle function callback.
	glutIdleFunc(display);
	//Normal keys pressed callback.
	glutKeyboardFunc(normalKeyPressed);
	//Normal keys released callback.
	glutKeyboardUpFunc(normalKeyReleased);
	//Special keys pressed callback.
	glutSpecialFunc(specialKeyPressed);
	//Special keys released callback.
	glutSpecialUpFunc(specialKeyReleased);
	//Mouse function callback.
	glutMouseFunc(mouseButtonAction);
	//Mouse movement callback.
	glutMotionFunc(mouseMovementAction);

	glutMainLoop();

	return 1;
}


void
normalKeyPressed(unsigned char key, int x, int y)
{
	cameraControls.normalKeyPressed(key, x, y);
}

void
normalKeyReleased(unsigned char key, int x, int y)
{
	cameraControls.normalKeyReleased(key, x, y);
}

void
specialKeyPressed(int key, int x, int y)
{
	cameraControls.specialKeyPressed(key, x, y);
}

void
specialKeyReleased(int key, int x, int y)
{
	cameraControls.specialKeyReleased(key, x, y);
}

void
mouseButtonAction(int button, int state, int x, int y)
{
	cameraControls.mouseButtonAction(button, state, x, y);
}

void
mouseMovementAction(int x, int y)
{
	cameraControls.mouseMovementAction(x, y);
}

void
display(void)
{
	cameraControls.changedPositionInWorld(cameraControls.getFinalPedalValue());

	cameraControls.changedPositionByStrafe(cameraControls.getFinalStrafeValue());
	
	cameraControls.changeCameraHeight(cameraControls.getFinalHeightValue());

	//Clears color and depth buffers.
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Load identity matrix.
	glLoadIdentity();
	//Set up white specular, blue diffuse, and black ambient lighting.
	float specularLight[] = { 1.0f, 1.0f, 1.0f };
	float ambientLight[] = { 0.0f, 0.0f, 0.0f };
	float diffuseLight[] = { 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	//Set camera.
	gluLookAt(cameraControls.getCameraXPosition(), cameraControls.getCameraYPosition(), cameraControls.getCameraZPosition(),
		cameraControls.getCameraXPosition() + cameraControls.getCameraXDirection(), cameraControls.getCameraYPosition() + cameraControls.getCameraYDirection(), cameraControls.getCameraZPosition() + cameraControls.getCameraZDirection(),
		0.0f, 1.0f, 0.0f);

	//Draw floor.
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-100.0f, 0.0f, -100.0f);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-100.0f, 0.0f, 100.0f);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(100.0f, 0.0f, 100.0f);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(100.0f, 0.0f, -100.0f);
	glEnd();
	float pos[] = { -1.0, 20.0, -2.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, pos);


	//DRAW ROBOT------------------------------------------

	assembleAndroid->constructRobot();

	if (value == 2)
	{
		return;
	}
	/*
		variableRotation += 0.5f;*/
	glutSwapBuffers();

}

void
reshapeDisplay(int width, int height)
{
	screenWidth = width;

	//Checks if resized height is less than or equal to zero.
	if (height <= 0)
	{
		height = 1;
	}
	screenHeight = height;
	//Aspect ratio of window.
	float aspectRatio = (1.0f * width) / height;
	//Load projection matrix.
	glMatrixMode(GL_PROJECTION);
	//Load identity matrix.
	glLoadIdentity();
	//Sets viewport to be entire size of window.
	glViewport(0, 0, width, height);
	//Set perspective
	gluPerspective(45.0f, aspectRatio, 0.1f, 1000.0f);
	//Reset to model view matrix.
	glMatrixMode(GL_MODELVIEW);
}

void
idleDisplay(void)
{
	//display();
}

