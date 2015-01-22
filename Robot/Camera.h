#include <GL\glut.h>
#include <cmath>

//CAMERA ADJUSTMENT VARIABLES-----------------------------
//Angle of camera in scene.
GLfloat cameraXAngle = 0.0f;
//Angle of camera in y direction.
GLfloat cameraYAngle = 0.0f;
//X-axis direction vector.
float cameraDirectionX = 0.0f;
//Y-axis direction vector. 
float cameraDirectionY = 0.0f;
//Z-axis direction vector.
float cameraDirectionZ = -1.0f;
//X camera position.
float cameraPositionX = 1.0f;
//Y camera position.
float cameraPositionY = 1.0f;
//Z camera position.
float cameraPositionZ = 5.0f;