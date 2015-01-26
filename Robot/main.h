#include "UserInterface.h"
#include <gl\glut.h>
#include "Controls.h"
#include "Materials.h"
#include "AssembleAndroid.h"

#include <iostream>
#include <fstream>

using namespace std;

//--------------------------------------------------------



//MISCELLANEOUS VARIABLES---------------------------------

//Width and height of screen.
int screenWidth = 500;
int screenHeight = 500;


//--------------------------------------------------------

//METHOD DECLARATIONS-------------------------------------
//Display method declaration.
void display(void);

//Construct robot method.
void constructRobot(void);

//Normal key pressed method declaration.
void normalKeyPressed(unsigned char, int x, int y);

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

//Reshape method declaration.
void reshapeDisplay(int width, int height);

//Idle method declaration.
void idleDisplay(void);

void setLighting(GLfloat* specular, GLfloat* diffuse, GLfloat* emission, bool specularBool, bool diffuseBool, bool emissionBool, GLfloat* shine);