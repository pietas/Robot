#include "AssembleAndroid.h"

AssembleAndroid::
AssembleAndroid()
{
	scale[0] = 1.0f;
	scale[1] = 1.0f;
	scale[2] = 1.0f;
}

void AssembleAndroid::
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

void AssembleAndroid::
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

void AssembleAndroid::
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

void AssembleAndroid::
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
 
void AssembleAndroid::
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

void AssembleAndroid::
constructFoot(float lowerLegScale[3])
{
	glPushMatrix();
	{

		drawCube(1.0f, 0.0f, 0.0f);
	}
	glPopMatrix();
}

void AssembleAndroid::
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

void AssembleAndroid::
constructAbdomen(float waistScale[3])
{
	glScalef(1.0f, 2.0f, 1.0f);
	glTranslatef(0.0f, 1.5f + jointGap, 0.0f);

	//Push abdomen position.
	glPushMatrix();

	{
		//Draw abdomen.
		AssembleAndroid::drawCube(0.0f, 0.5f, 0.0f);

		constructTorso(waistScale);


	}
	//Pop abdomen position.
	glPopMatrix();
}

void AssembleAndroid::
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

void AssembleAndroid::
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

void AssembleAndroid::
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

void AssembleAndroid::
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

void AssembleAndroid::
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

void AssembleAndroid::
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

void AssembleAndroid::
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

void AssembleAndroid::
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

void AssembleAndroid::
resetScale(float scale[3])
{
	scale[0] = 1 / scale[0];
	scale[1] = 1 / scale[1];
	scale[2] = 1 / scale[2];
	glScalef(scale[0], scale[1], scale[2]);
}

void AssembleAndroid::
setScale(float scaleX, float scaleY, float scaleZ, float scale[3])
{
	scale[0] = scaleX;
	scale[1] = scaleY;
	scale[2] = scaleZ;
}
