#include "main.h"
#include <windows.h>


GLuint firstTexture;
Controls cameraControls;

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
	if (cameraControls.getPositionInWorld() != 0)
	{
		cameraControls.changedPositionInWorld(cameraControls.getPositionInWorld());
	}
	if (cameraControls.getStrafe() != 0)
	{
		cameraControls.changedPositionByStrafe(cameraControls.getStrafe());
	}
	if (cameraControls.getJump() != 0)
	{
		cameraControls.changeCameraHeight(cameraControls.getJump());
	}
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
	glBindTexture(GL_TEXTURE_2D, firstTexture);
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

	constructRobot();

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
setLighting(GLfloat* specular, GLfloat* diffuse, GLfloat* emission, bool specularBool, bool diffuseBool, bool emissionBool, GLfloat* shine)
{
	//If specular requested or not, set material according.
	if (specularBool)
	{
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shine);
	}
	else
	{
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, noMaterial);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, noMaterial);
	}
	if (diffuseBool)
	{
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	}
	else
	{
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, noMaterial);
	}

	if (emissionBool)
	{
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
	}
	else
	{
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, noMaterial);
	}

}



void
drawCube(float red, float green, float blue)
{
	//printf("Current diffuse color: %f, %f, %f\n", red, green, blue);
	diffuseMaterial[0] = red;
	diffuseMaterial[1] = green;
	diffuseMaterial[2] = blue;
	glBindTexture(GL_TEXTURE_2D, firstTexture);
	glBegin(GL_QUADS);
	{
		setLighting(specularMaterial, diffuseMaterial, emissionMaterial, true, true, false, shineFactor);



		//TOP FACE

		//Back top right
		glTexCoord2f(0, 1);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, -1.0f);

		//Back top left
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(0, 1);
		glVertex3f(-1.0f, 1.0f, -1.0f);

		//front top left
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(0, 1);
		glVertex3f(-1.0, 1.0f, 1.0f);

		//Front top right
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(0, 1);
		glVertex3f(1.0f, 1.0f, 1.0f);



		//FRONT FACE

		//Front top right
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(1, 1);
		glVertex3f(1.0f, 1.0f, 1.0f);

		//Front top left
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0, 1);
		glVertex3f(-1.0f, 1.0f, 1.0f);

		//Front bottom left
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0, 0);
		glVertex3f(-1.0f, -1.0f, 1.0f);

		//Front bottom right
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(1, 1);
		glVertex3f(1.0f, -1.0f, 1.0f);



		//BOTTOM FACE

		//Front bottom right
		glNormal3f(0.0f, -1.0f, 0.0f);
		glTexCoord2f(0, 1);
		glVertex3f(1.0f, -1.0f, 1.0f);

		//Front bottom left
		glNormal3f(0.0f, -1.0f, 0.0f);
		glTexCoord2f(1, 0);
		glVertex3f(-1.0f, -1.0f, 1.0f);

		//Back bottom left
		glNormal3f(0.0f, -1.0f, 0.0f);
		glTexCoord2f(0, 0);
		glVertex3f(-1.0f, -1.0f, -1.0f);

		//Back bottom right
		glNormal3f(0.0f, -1.0f, 0.0f);
		glTexCoord2f(1, 1);
		glVertex3f(1.0f, -1.0f, -1.0f);


		//LEFT FACE

		//Front top left
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0, 1);
		glVertex3f(-1.0f, 1.0f, 1.0f);

		//Back top left
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(1, 0);
		glVertex3f(-1.0f, 1.0f, -1.0f);

		//Back bottom left
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0, 0);
		glVertex3f(-1.0f, -1.0f, -1.0f);

		//Front bottom left
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(1, 1);
		glVertex3f(-1.0f, -1.0f, 1.0f);


		//RIGHT FACE

		//Back top right
		glNormal3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(0, 1);
		glVertex3f(1.0f, 1.0f, -1.0f);

		//Front top right
		glNormal3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(1, 0);
		glVertex3f(1.0f, 1.0f, 1.0f);

		//Front bottom right
		glNormal3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(0, 0);
		glVertex3f(1.0f, -1.0f, 1.0f);

		//Back bottom right
		glNormal3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(1, 1);
		glVertex3f(1.0f, -1.0f, -1.0f);

		//BACK FACE

		//Back top right
		glNormal3f(0.0f, 0.0f, -1.0f);
		glTexCoord2f(1, 0);
		glVertex3f(1.0f, 1.0f, -1.0f);

		//Back top left
		glNormal3f(0.0f, 0.0f, -1.0f);
		glTexCoord2f(0, 1);
		glVertex3f(-1.0f, 1.0f, -1.0f);

		//Back bottom left
		glNormal3f(0.0f, 0.0f, -1.0f);
		glTexCoord2f(0, 0);
		glVertex3f(-1.0f, -1.0f, -1.0f);

		//Back bottom right
		glNormal3f(0.0f, 0.0f, -1.0f);
		glTexCoord2f(1, 1);
		glVertex3f(1.0f, -1.0f, -1.0f);
		//Reset lighting.
		setLighting(specularMaterial, diffuseMaterial, emissionMaterial, false, false, false, shineFactor);
	}
	glEnd();
}



void
idleDisplay(void)
{
	//display();
}

