#include "main.h"
#include <windows.h>

GLuint firstTexture;

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
display(void)
{
	if (changePositionInWorld != 0)
	{
		changedPositionInWorld(changePositionInWorld);
	}
	if (strafeValue != 0)
	{
		changedPositionByStrafe(strafeValue);
	}
	if (jump != 0)
	{
		changeCameraHeight(jump);
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
	gluLookAt(cameraPositionX, cameraPositionY, cameraPositionZ,
		cameraPositionX + cameraDirectionX, cameraPositionY + cameraDirectionY, cameraPositionZ + cameraDirectionZ,
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

	variableRotation += 0.5f;
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
constructRobot()
{
	//Push global matrix onto stack.
	glPushMatrix();
	{
		//Position robot in world.
		glTranslatef(0.0f, 7.5f, -50.0f);
		//Scale robot if necessary. Initially populate the scale array.
		setScale(1.0f, 1.0f, 1.0f, scale);
		//Push robot position to stack.
		glPushMatrix();
		{
			//Draw waist.

			glPushMatrix();
			//glRotatef(variableRotation, 0.0f, 1.0f, 0.0f);
			constructWaist(scale);
			glPopMatrix();
		}
		//Pop robot position.
		glPopMatrix();

	}
	//Pop global matrix.
	glPopMatrix();

}

void
constructWaist(float scale[3])
{
	//Set scale for position.

	setScale(2.5f, 0.5f, 1.0f, scale);
	//Position waist.
	glScalef(scale[0], scale[1], scale[2]);
	//glScalef(2.5f, 0.5f, 1.0f);
	//Push positioned waist to stack.
	glPushMatrix();
	{
		float* waistScale = scale;
		//Draw waist.
		drawCube(0.0f, 0.0f, 0.0f);
		//Push waist in scene matrix.
		glPushMatrix();
		{
			constructLeftLeg(waistScale);
		}
		//Pop waist.
		glPopMatrix();
		//Push waist in scene matrix.
		glPushMatrix();
		{
			constructRightLeg(scale);
		}
		//Pop waist.
		glPopMatrix();
		//Push waist in scene matrix.
		glPushMatrix();
		{
			constructAbdomen(scale);
		}
		//Pop waist.
		glPopMatrix();

	}
	//Pop waist position.
	glPopMatrix();
}

void
constructLeftLeg(float waistScale[3])
{
	glScalef(0.4f, 2.0f, 1.0f);
	//Position left leg.
	glTranslatef(-1.5f, -2.0f - jointGap, 0.0f);
	glScalef(1.0f, 1.5f, 1.0f);
	//Push left leg position.
	glPushMatrix();
	{
		constructUpperLeg(waistScale);
	}
	//Pop left leg position.
	glPopMatrix();

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
constructUpperLeg(float waistScale[3])
{
	//Scale for leg
	//setScale(1.0f, 1.5f, 1.0f, scale);
	//Push leg scale.
	glPushMatrix();
	{
		//Draw upper leg.
		drawCube(0.5f, 0.0f, 0.0f);
		glTranslatef(0.0f, -2.0f - jointGap, 0.0f);
		glPushMatrix();
		{
			constructLowerLeg(waistScale);
		}
		glPopMatrix();
	}
	//Pop scale.
	glPopMatrix();
}

void
constructLowerLeg(float waistScale[3])
{
	glPushMatrix();
	{
		drawCube(1.0f, 1.0f, 1.0f);
		glScalef(1.0f, 0.8f, 1.0f);

		glTranslatef(0.0f, -1.75f - jointGap, 1.0f);

		glScalef(1.0f, 0.5f, 2.0f);
		constructFoot(waistScale);
	}
	glPopMatrix();
}

void
constructFoot(float lowerLegScale[3])
{
	glPushMatrix();
	{

		drawCube(1.0f, 0.0f, 0.0f);
	}
	glPopMatrix();
}

void
constructRightLeg(float waistScale[3])
{
	glScalef(0.4f, 2.0f, 1.0f);

	//Position left leg.
	glTranslatef(1.5f, -2.0f - jointGap, 0.0f);
	glScalef(1.0f, 1.5f, 1.0f);
	//Push left leg position.
	glPushMatrix();
	{
		constructUpperLeg(waistScale);
	}
	//Pop left leg position.
	glPopMatrix();
}

void
constructAbdomen(float waistScale[3])
{
	glScalef(1.0f, 2.0f, 1.0f);
	glTranslatef(0.0f, 1.5f + jointGap, 0.0f);

	//Push abdomen position.
	glPushMatrix();

	{
		//Draw abdomen.
		drawCube(0.0f, 0.5f, 0.0f);

		constructTorso(waistScale);


	}
	//Pop abdomen position.
	glPopMatrix();
}

void
constructTorso(float abdomenScale[3])
{

	glTranslatef(0.0f, 3.0f + jointGap, 0.0f);

	glScalef(1.0f, 2.0f, 1.0f);
	glPushMatrix();
	{
		//Draw torso.
		drawCube(0.0f, 1.0f, 0.0f);
		glPushMatrix();
		{
			constructLeftShoulder(abdomenScale);
		}
		glPopMatrix();
		glPushMatrix();
		{
			constructNeck(abdomenScale);
		}
		glPopMatrix();
		glPushMatrix();
		{
			constructRightShoulder(abdomenScale);
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void
constructNeck(float* torsoScale)
{
	glScalef(0.4f, 0.5f, 1.0f);
	glTranslatef(0.0f, 3.0f + jointGap, 0.0f);
	//Push neck position
	glPushMatrix();
	{
		//Draw neck.
		drawCube(0.0f, 0.0f, 0.5f);
		//Push neck for head reference.
		glPushMatrix();
		{
			constructHead(torsoScale);
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void
constructHead(float* neckScale)
{
	glTranslatef(0.0f, 3.0f + jointGap, 0.0f);
	glScalef(2.0f, 2.0f, 2.0f);
	//Push head position.
	glPushMatrix();
	{
		//Draw head.
		drawCube(0.0f, 0.0f, 1.0f);
	}
	glPopMatrix();
}

void
constructLeftShoulder(float* torsoScale)
{
	//Scale back to make it move 1:1:1 float
	glScalef(0.4f, 0.5f, 1.0f);
	glTranslatef(-2.5f - jointGap, 2.5f + jointGap, 0.0f);
	//Scale to 1.5:0.5:1 float
	glScalef(1.5f, 0.5f, 1.0f);
	//Push shoulder position.
	glPushMatrix();
	{
		//Draw shoulder.
		drawCube(0.5f, 0.5f, 0.0f);
		//Move to arm position.
		glScalef((2.0f / 3.0f), 2.0f, 1.0f);
		glTranslatef(-1.0f, -2.0f - jointGap, 0.0f);
		glPushMatrix();
		{
			//Set up upper arm.
			//Scale back from shoulder to make it 1:1:1

			constructUpperArm(torsoScale);
		}
		glPopMatrix();

	}
	glPopMatrix();

}

void
constructUpperArm(float* shoulderScale)
{

	glScalef(0.5f, 1.5f, 1.0f);
	//Push upper arm position
	glPushMatrix();
	{
		//Draw upper arm
		drawCube(0.5f, 1.0f, 0.0f);

		constructLowerArm(shoulderScale);
	}
	glPopMatrix();

}

void
constructLowerArm(float* upperArmScale)
{
	glScalef(1.0f, (2.0f / 3.0f), 1.0f);
	glTranslatef(0.0f, -3.0f - jointGap, 0.0f);
	glScalef(1.0f, 1.5f, 1.0f);
	//Push lower arm position.
	glPushMatrix();
	{
		//Draw lower arm.
		drawCube(0.5f, 0.5f, 0.5f);

		constructHand(upperArmScale);
	}
	glPopMatrix();
}

void
constructHand(float* lowerArmScale)
{
	glScalef(1.0f, (2.0f / 3.0f), 1.0f);
	glTranslatef(0.0f, -2.5f - jointGap, 0.0f);
	glScalef(0.75f, 1.0f, 1.0f);
	//Push hand position.
	glPushMatrix();
	{
		//Draw hand.
		drawCube(0.5f, 0.5f, 1.0f);
	}
	glPopMatrix();
}

void
constructRightShoulder(float* torsoScale)
{
	glScalef(0.4f, 0.5f, 1.0f);
	glTranslatef(2.5f + jointGap, 2.5f + jointGap, 0.0f);
	glScalef(1.5f, 0.5f, 1.0f);
	//Push shoulder position.
	glPushMatrix();
	{
		//Draw shoulder.
		drawCube(0.5f, 1.0f, 1.0f);

		glScalef((2.0f / 3.0f), 2.0f, 1.0f);
		glTranslatef(1.0f, -2.0f - jointGap, 0.0f);
		glPushMatrix();
		{
			//Set up upper arm.
			//Scale back from shoulder to make it 1:1:1

			constructUpperArm(torsoScale);
		}
		glPopMatrix();
	}
	glPopMatrix();
}


void
resetScale(float scale[3])
{
	scale[0] = 1 / scale[0];
	scale[1] = 1 / scale[1];
	scale[2] = 1 / scale[2];
	glScalef(scale[0], scale[1], scale[2]);
}

void
setScale(float scaleX, float scaleY, float scaleZ, float scale[3])
{
	scale[0] = scaleX;
	scale[1] = scaleY;
	scale[2] = scaleZ;
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

void
normalKeyPressed(unsigned char key, int x, int y)
{
	//Escape key.
	if (key == 27)
	{
		//Quits application.
		exit(0);
	}
	//W key.
	if (key == 119)
	{
		//Move into world.
		changePositionInWorld = 1.0f;
		pedalUp = true;
	}
	//S key.
	if (key == 115)
	{
		//Move out of world.
		changePositionInWorld = -1.0f;
		pedalBack = true;
	}
	//Q key.
	if (key == 113)
	{
		//Turn left in world.
		cameraXAngle -= 0.01f;
		angleOrientation(cameraXAngle);
	}
	//E key.
	if (key == 101)
	{
		//Turn right in world.
		cameraXAngle += 0.01f;
		angleOrientation(cameraXAngle);
	}
	//A key.
	if (key == 97)
	{
		//Strafe left in world.
		strafeValue = -1.0f;
		strafeLeft = true;
	}
	//D key.
	if (key == 100)
	{
		//Strafe right in world.
		strafeValue = 1.0f;
		strafeRight = true;
		
	}
	if (key == 32)
	{
		//Rise up.
		jump = 0.1f;
		ascend = true;
	}
	if (key == 120)
	{
		//Float down.
		jump = -0.1f;
		descend = true;
	}
}

void
normalKeyReleased(unsigned char key, int x, int y)
{
	if (key == 119)
	{
		changePositionInWorld = 0.0f;
	}
	if (key == 115)
	{
		changePositionInWorld = 0.0f;
	}
	if (key == 97)
	{
		strafeValue = 0.0f;
	}
	if (key == 100)
	{
		strafeValue = 0.0f;
	}
	if (key == 32)
	{
		jump = 0.0f;
	}
	if (key == 120)
	{
		jump = 0.0f;
	}
}

void
specialKeyPressed(int key, int x, int y)
{
	//TODO: Implement
}

void
specialKeyReleased(int key, int x, int y)
{
	//TODO: Implement
}

void
mouseButtonAction(int button, int state, int x, int y)
{
	//If left button pressed, rotate camera on x/y plane.
	if (button == GLUT_LEFT_BUTTON)
	{
		//Set initial values to be compared with in mouseMovementAction method.
		if (state == GLUT_DOWN)
		{
			initialX = x;
			initialY = y;
			leftMousePressed = true;
		}
		else
		{
			//Reset vales, and change camera angle.
			initialX = 0;
			initialY = 0;
			cameraXAngle += changeInXAngle;
			cameraYAngle += changeInYAngle;
			leftMousePressed = false;
		}
	}

	//Pans camera based on if button down.
	if (button == GLUT_RIGHT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			initialX = x;
			rightMousePressed = true;
		}
		else
		{
			initialX = 0;
			rightMousePressed = false;
		}
	}
}

void
mouseMovementAction(int x, int y)
{
	int initialDifference = x - initialX;

	//Test if left mouse button pressed or not.
	if (leftMousePressed)
	{
		//Updates change in camera angle.
		changeInXAngle = (x - initialX) * 0.001f;
		changeInYAngle = (y - initialY) * 0.001f;
		//Updates camera direction.
		cameraDirectionX = sin(cameraXAngle + changeInXAngle);
		cameraDirectionY = -sin(cameraYAngle + changeInYAngle);
		cameraDirectionZ = -cos(cameraXAngle + changeInXAngle);

	}

	//Test if right button pressed for strafing.
	if (rightMousePressed)
	{

		//changedPositionByStrafe(0.001f * x);
		if (xValueChange > initialDifference)
		{
			changedPositionByStrafe(1.0f);

		}
		else
		{
			changedPositionByStrafe(-1.0f);
		}
		xValueChange = initialDifference;
	}
}

void
changedPositionInWorld(float changeInPosition)
{
	//Changes position in world based on user input.
	cameraPositionX += changeInPosition * cameraDirectionX * 0.2f;
	cameraPositionZ += changeInPosition * cameraDirectionZ * 0.2f;
	
}

void
changeCameraHeight(float verticalMovement)
{
	if ((verticalMovement < 0 && cameraPositionY > 1.0f) || (verticalMovement > 0) )
	{
		cameraPositionY += verticalMovement;
	}
	
}

void
changedPositionByStrafe(float changeInPosition)
{
	//Strafes based on user input.
	cameraPositionX += changeInPosition * 0.3f * cos(cameraXAngle);
	cameraPositionZ += changeInPosition * 0.3f * sin(cameraXAngle);
}

void
angleOrientation(float theta)
{
	cameraDirectionX = sin(theta);
	cameraDirectionZ = -cos(theta);
	glLoadIdentity();
	gluLookAt(cameraPositionX, cameraPositionY, cameraPositionZ,
		cameraPositionX + cameraDirectionX, cameraPositionY + cameraDirectionY,
		cameraPositionZ + cameraDirectionZ, 0.0f, 1.0f, 0.0f);
}