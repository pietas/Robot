#include <gl\glut.h>
#include <cmath>

//Boolean if left mouse button pressed.
bool leftMousePressed = false;
//Boolean if right mouse button pressed.
bool rightMousePressed = false;
//Boolean if middle mouse button pressed.
bool middleMousePressed = false;
//Fly mode/jump/height control.
float jump = 0.0f;
//pedal forwards and backwards into/out of scene boolean.
bool pedalUp = false;
bool pedalBack = false;
//Strafe booleans.
bool strafeLeft = false;
bool strafeRight = false;
//Y position booleans for ascend and descend.
bool ascend = false;
bool descend = false;

//KEYBOARD MOVEMENT VARIABLES-----------------------------
//Change in angle variable.
GLfloat changeInXAngle = 0.0f;
//Change in angle of y axis.
GLfloat changeInYAngle = 0.0f;
//Strafe value.
GLfloat strafeValue = 0.0f;
//Change in movement variable.
float changePositionInWorld = 0.0f;
//Original X value.
int initialX = 0;
//Original y value.
int initialY = 0;

//Normal key pressed method declaration.
void normalKeyPressed(unsigned char key, int x, int y);

//Normal key released method declaration.
void normalKeyReleased(unsigned char key, int x, int y);

//Special key pressed method declaration.
void specialKeyPressed(int key, int x, int y);

//Special key released method declaration.
void specialKeyReleased(int key, int x, int y);

//Mouse button action method declaration.
void mouseButtonAction(int button, int state, int x, int y);

//Mouse movement action method declaration.
void mouseMovementAction(int x, int y);

//Tracks movement of mouse passively.
void mousePassiveMovement(int x, int y);