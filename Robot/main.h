#include "AndroidHead.h"
#include "AndroidLeftArm.h"
#include "AndroidLeftLeg.h"
#include "AndroidRightArm.h"
#include "AndroidRightLeg.h"
#include "AndroidTorso.h"
#include "AssembleAndroid.h"
#include "Camera.h"
#include "Materials.h"
#include "Texturing.h"
#include "UserInterface.h"
#include "Controls.h"

#include <iostream>
#include <fstream>

using namespace std;

//--------------------------------------------------------

//BODY ROTATION VARIABLES---------------------------------
//Head rotation angles.
GLfloat headXRotation = 0.0f;
GLfloat headYRotation = 0.0f;
GLfloat headZRotation = 0.0f;

//Neck rotation angles.
GLfloat neckXRotation = 0.0f;
GLfloat neckYRotation = 0.0f;
GLfloat neckZRotation = 0.0f;

//Torso rotation angles.
GLfloat torsoXRotation = 0.0f;
GLfloat torsoYRotation = 0.0f;
GLfloat torsoZRotation = 0.0f;

//Upper left arm rotation angles.
GLfloat upperLeftArmXRotation = 0.0f;
GLfloat upperLeftArmYRotation = 0.0f;
GLfloat upperLeftArmZRotation = 0.0f;

//Lower left arm rotation angles.
GLfloat lowerLeftArmXRotation = 0.0f;
GLfloat lowerLeftArmYRotation = 0.0f;
GLfloat lowerLeftArmZRotation = 0.0f;

//Left hand rotation angles.
GLfloat leftHandXRotation = 0.0f;
GLfloat leftHandYRotation = 0.0f;
GLfloat leftHandZRotation = 0.0f;

//Upper right arm rotation angles.
GLfloat upperRightArmXRotation = 0.0f;
GLfloat upperRightArmYRotation = 0.0f;
GLfloat upperRightArmZRotation = 0.0f;

//Lower right arm rotation angles.
GLfloat lowerRightArmXRotation = 0.0f;
GLfloat lowerRightArmYRotation = 0.0f;
GLfloat lowerRightArmZRotation = 0.0f;

//Right hand rotation angles.
GLfloat rightHandXRotation = 0.0f;
GLfloat rightHandYRotation = 0.0f;
GLfloat rightHandZRotation = 0.0f;

//Upper left leg rotation angles.
GLfloat upperLeftLegXRotation = 0.0f;
GLfloat upperLeftLegYRotation = 0.0f;
GLfloat upperLeftLegZRotation = 0.0f;

//Lower left leg rotation angles.
GLfloat lowerLeftLegXRotation = 0.0f;
GLfloat lowerLeftLegYRotation = 0.0f;
GLfloat lowerLeftLegZRotation = 0.0f;

//Left foot rotation angles.
GLfloat leftFootXRotation = 0.0f;
GLfloat leftFootYRotation = 0.0f;
GLfloat leftFootZRotation = 0.0f;

//Upper right leg rotation angles.
GLfloat upperRightLegXRotation = 0.0f;
GLfloat upperRightLegYRotation = 0.0f;
GLfloat upperRightLegZRotation = 0.0f;

//Lower right leg rotation angles.
GLfloat lowerRightLegXRotation = 0.0f;
GLfloat lowerRightLegYRotation = 0.0f;
GLfloat lowerRightLegZRotation = 0.0f;

//Right foot rotation angles.
GLfloat RightFootXRotation = 0.0f;
GLfloat RightFootYRotation = 0.0f;
GLfloat RightFootZRotation = 0.0f;

//MISCELLANEOUS VARIABLES---------------------------------
//Stores scale to be sent down pushMatrix pipeline when drawn.
float scale[] = { 1.0f, 1.0f, 1.0f };
//Width and height of screen.
int screenWidth = 500;
int screenHeight = 500;
//Change in x distance on screen.
int xValueChange = 0;

//--------------------------------------------------------

//METHOD DECLARATIONS-------------------------------------
//Display method declaration.
void display(void);

//Construct robot method.
void constructRobot(void);

//Draw cube method.
void drawCube(float red, float green, float blue);

//Reshape method declaration.
void reshapeDisplay(int width, int height);

//Idle method declaration.
void idleDisplay(void);

//Change camera position calculator
void changedPositionInWorld(float changeInPosition);

//Construct waist.
void constructWaist(float scale[3]);

//Sets scale of array that stores scale values
void setScale(float scaleX, float scaleY, float scaleZ, float scale[3]);

//Resets scale to be 1:1:1. Will create 1x1x1 cubes.
void resetScale(float*);

//Sets up creation of left leg. Requires scale of prior body part to calculate
//translation correctly since I will reset the scale inside each method.
void constructLeftLeg(float*);

//Sets up creation of right leg. Requires scale of prior body part to calculate
//translation correctly since I will reset the scale inside each method.
void constructRightLeg(float*);

//Sets up creation of abdomen. Requires scale of prior body part to calculate
//translation correctly since I will reset the scale inside each method.
void constructAbdomen(float*);

//Creates upper leg for either right or left depending on prior translation.
void constructUpperLeg(float*);

//Rotation of camera calculator.
void angleOrientation(float theta);

//Strafing position calculator.
void changedPositionByStrafe(float);

//Construct torso.

void changeCameraHeight(float);
void setLighting(GLfloat* specular, GLfloat* diffuse, GLfloat* emission, bool specularBool, bool diffuseBool, bool emissionBool, GLfloat* shine);