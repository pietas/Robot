#include <gl\glut.h>


//Gap distance between body parts.
float jointGap = 0.1f;

float variableRotation = 0.0f;


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