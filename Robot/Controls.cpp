#include "Camera.h"
#include "Controls.h"
#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <stdio.h>

Controls::Controls()
{

}

void Controls::
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
		pedalUp = true;
	}
	//S key.
	if (key == 115)
	{
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
		strafeLeft = true;
	}
	//D key.
	if (key == 100)
	{
		strafeRight = true;

	}
	if (key == 32)
	{
		ascend = true;
	}
	if (key == 120)
	{
		descend = true;
	}
}

void Controls::
normalKeyReleased(unsigned char key, int x, int y)
{
	if (key == 119)
	{
		pedalUp = false;
	}
	if (key == 115)
	{
		pedalBack = false;
	}
	if (key == 97)
	{
		strafeLeft = false;
	}
	if (key == 100)
	{
		strafeRight = false;
	}
	if (key == 32)
	{
		ascend = false;
	}
	if (key == 120)
	{
		descend = false;
	}
}

void Controls::
specialKeyPressed(int key, int x, int y)
{
	//TODO: Implement
}

void Controls::
specialKeyReleased(int key, int x, int y)
{
	//TODO: Implement
}

void Controls::
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
			cameraXAngle += changeInXAngle;
			cameraYAngle += changeInYAngle;
		}
		else
		{
			//Reset vales, and change camera angle.
			initialX = 0;
			initialY = 0;


			leftMousePressed = false;
		}
	}

	////Pans camera based on if button down.
	//if (button == GLUT_RIGHT_BUTTON)
	//{

	//}
}

void Controls::
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

	////Test if right button pressed for strafing.
	//if (rightMousePressed)
	//{

	//}
}

void Controls::
changedPositionInWorld(float changeInPosition)
{
	//Changes position in world based on user input.
	cameraPositionX += changeInPosition * cameraDirectionX * 0.2f;
	cameraPositionZ += changeInPosition * cameraDirectionZ * 0.2f;

}

void Controls::
changeCameraHeight(float verticalMovement)
{
	if ((verticalMovement < 0 && cameraPositionY > 1.0f) || (verticalMovement > 0))
	{
		cameraPositionY += verticalMovement;
	}

}

void Controls::
changedPositionByStrafe(float changeInPosition)
{

	//Strafes based on user input.
	cameraPositionX += changeInPosition * 1.0f * cos(cameraXAngle);
	cameraPositionZ += changeInPosition * 1.0f * sin(cameraXAngle);
}

void Controls::
angleOrientation(float theta)
{
	cameraDirectionX = sin(theta);
	cameraDirectionZ = -cos(theta);
	glLoadIdentity();
	gluLookAt(cameraPositionX, cameraPositionY, cameraPositionZ,
		cameraPositionX + cameraDirectionX, cameraPositionY + cameraDirectionY,
		cameraPositionZ + cameraDirectionZ, 0.0f, 1.0f, 0.0f);
}

GLboolean Controls::
getAscend()
{
	return ascend;
}

void Controls::
setAscend(GLboolean newValue)
{
	ascend = newValue;
}

GLfloat Controls::
getChangeInXAngle()
{
	return changeInXAngle;
}

void Controls::
setChangeInXAngle(GLfloat newValue)
{
	changeInXAngle = newValue;
}

GLfloat Controls::
getChangeInYAngle()
{
	return changeInYAngle;
}

void Controls::
setChangeInYAngle(GLfloat newValue)
{
	changeInYAngle = newValue;
}

GLfloat Controls::
getPositionInWorld()
{
	return changePositionInWorld;
}

void Controls::
setPositionInWorld(GLfloat newValue)
{
	changePositionInWorld = newValue;
}

GLboolean Controls::
getDescend()
{
	return descend;
}

void Controls::
setDescend(GLboolean newValue)
{
	descend = newValue;
}

GLint Controls::
getInitialX()
{
	return initialX;
}

void Controls::
setInitialX(GLint newValue)
{
	initialX = newValue;
}

GLint Controls::
getIntialY()
{
	return initialY;
}

void Controls::
setInitialY(GLint newValue)
{
	initialY = newValue;
}

GLfloat Controls::
getJump()
{
	return jump;
}

void Controls::
setJump(GLfloat newValue)
{
	jump = newValue;
}

GLboolean Controls::
getLeftMousePressed()
{
	return leftMousePressed;
}

void Controls::
setLeftMousePressed(GLboolean newValue)
{
	leftMousePressed = newValue;
}

GLboolean Controls::
getMiddleMousePressed()
{
	return middleMousePressed;
}

void Controls::
setMiddleMousePressed(GLboolean newValue)
{
	middleMousePressed = newValue;
}

GLboolean Controls::
getPedalBack()
{
	return pedalBack;
}

void Controls::
setPedalBack(GLboolean newValue)
{
	pedalBack = newValue;
}

GLboolean Controls::
getPedalUp()
{
	return pedalUp;
}

void Controls::
setPedalUp(GLboolean newValue)
{
	pedalUp = newValue;
}

GLboolean Controls::
getRightMousePressed()
{
	return rightMousePressed;
}

void Controls::
setRightMousePressed(GLboolean newValue)
{
	rightMousePressed = newValue;
}

GLboolean Controls::
getStrafeLeft()
{
	return strafeLeft;
}

void Controls::
setStrafeLeft(GLboolean newValue)
{
	strafeLeft = newValue;
}

GLboolean Controls::
getStrafeRight()
{
	return strafeRight;
}

void Controls::
setStrafeRight(GLboolean newValue)
{
	strafeRight = newValue;
}

GLfloat Controls::
getStrafe()
{
	return strafeValue;
}

void Controls::
setStrafe(GLfloat newValue)
{
	strafeValue = newValue;
}

GLint Controls::
getXChange()
{
	return xValueChange;
}
void Controls::
setXChange(GLint newValue)
{
	xValueChange = newValue;
}

GLint Controls::
getYChange()
{
	return yValueChange;
}

void Controls::
setYChange(GLint newValue)
{
	yValueChange = newValue;
}

GLint Controls::
getZChange()
{
	return zValueChange;
}

void Controls::
setZChange(GLint newValue)
{
	zValueChange = newValue;
}

GLfloat Controls::
getCameraXAngle()
{
	return cameraXAngle;
}

void Controls::
setCameraXAngle(GLfloat newValue)
{
	cameraXAngle = newValue;
}

GLfloat Controls::
getCameraYAngle()
{
	return cameraYAngle;
}

void Controls::
setCameraYAngle(GLfloat newValue)
{
	cameraYAngle = newValue;
}

GLfloat Controls::
getCameraZAngle()
{
	return cameraZAngle;
}

void Controls::
setCameraZAngle(GLfloat newValue)
{
	cameraZAngle = newValue;
}

float Controls::
getCameraXDirection()
{
	return cameraDirectionX;
}

void Controls::
setCameraXDirection(float newValue)
{
	cameraDirectionX = newValue;
}

float Controls::
getCameraYDirection()
{
	return cameraDirectionY;
}

void Controls::
setCameraYDirection(float newValue)
{
	cameraDirectionY = newValue;
}

float Controls::
getCameraZDirection()
{
	return cameraDirectionZ;
}

void Controls::
setCameraZDirection(float newValue)
{
	cameraDirectionZ = newValue;
}

float Controls::
getCameraXPosition()
{
	return cameraPositionX;
}

void Controls::
setCameraXPosition(float newValue)
{
	cameraPositionX = newValue;
}

float Controls::
getCameraYPosition()
{
	return cameraPositionY;
}

void Controls::
setCameraYPosition(float newValue)
{
	cameraPositionY = newValue;
}

float Controls::
getCameraZPosition()
{
	return cameraPositionZ;
}

void Controls::
setCameraZPosition(float newValue)
{
	cameraPositionZ = newValue;
}

GLfloat Controls::
getFinalPedalValue()
{
	return (pedalUp - pedalBack) * pedalModifier;
}

GLfloat Controls::
getFinalStrafeValue()
{
	return (strafeRight - strafeLeft) * strafeModifier;
}

GLfloat Controls::
getFinalHeightValue()
{
	return (ascend - descend) * heightModifier;
}