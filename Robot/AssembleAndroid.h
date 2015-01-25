#include <gl\glut.h>

class AssembleAndroid
{
private:
	//Gap distance between body parts.
	float jointGap = 0.1f;

	float variableRotation = 0.0f;



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

public:
	//Draw cube method.
	void drawCube(float red, float green, float blue);
	void constructTorso(float*);
	void constructLowerLeg(float*);
	void constructRightShoulder(float*);
	void constructLeftShoulder(float*);
	void constructFoot(float*);
	void constructNeck(float*);
	void constructHead(float*);
	void constructUpperArm(float*);
	void constructLowerArm(float*);
	void constructHand(float*);
	void constructRobot();
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
};




