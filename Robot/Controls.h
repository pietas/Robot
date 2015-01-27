#include <gl\glut.h>
#include <cmath>
class Controls
{
private:
	//CAMERA ADJUSTMENT VARIABLES-----------------------------
	//Angle of camera in scene.
	GLfloat cameraXAngle = 0.0f;
	//Angle of camera in y direction.
	GLfloat cameraYAngle = 0.0f;
	//Angle of camera in Z direction.
	GLfloat cameraZAngle = 0.0f;
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
	//Change in x distance on screen.
	GLint xValueChange = 0;
	//Change in y distance on screen.
	GLint yValueChange = 0;
	//Change in z distance on screen.
	GLint zValueChange = 0;
	//Boolean if left mouse button pressed.
	GLboolean leftMousePressed = false;
	//Boolean if right mouse button pressed.
	GLboolean rightMousePressed = false;
	//Boolean if middle mouse button pressed.
	GLboolean middleMousePressed = false;
	//Fly mode/jump/height control.
	GLfloat jump = 0.0f;
	//pedal forwards and backwards into/out of scene boolean.
	GLboolean pedalUp = false;
	GLboolean pedalBack = false;
	//Strafe booleans.
	GLboolean strafeLeft = false;
	GLboolean strafeRight = false;
	//Y position booleans for ascend and descend.
	GLboolean ascend = false;
	GLboolean descend = false;
	//Modifiers for pedaling, strafing, and height.
	GLfloat pedalModifier = 1.0f;
	GLfloat strafeModifier = 1.0f;
	GLfloat heightModifier = 0.1f;

	//KEYBOARD MOVEMENT VARIABLES-----------------------------
	//Change in angle variable.
	GLfloat changeInXAngle = 0.0f;
	//Change in angle of y axis.
	GLfloat changeInYAngle = 0.0f;
	//Strafe value.
	GLfloat strafeValue = 0.0f;
	//Change in movement variable.
	GLfloat changePositionInWorld = 0.0f;
	//Original X value.
	GLint initialX = 0;
	//Original y value.
	GLint initialY = 0;

public:
	//Declare parameterized constructor at some point.
	Controls();
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

	//Tracks movement of mouse passively.
	void mousePassiveMovement(int x, int y);

	//Rotation of camera calculator.
	void angleOrientation(GLfloat theta);

	//Strafing position calculator.
	void changedPositionByStrafe(GLfloat);

	void changeCameraHeight(GLfloat);

	//Change camera position calculator
	void changedPositionInWorld(GLfloat changeInPosition);
	
	//Returns ascend boolean.
	GLboolean getAscend();
	
	//Sets ascend boolean.
	void setAscend(GLboolean);
	
	//Returns  the delta X angle.
	GLfloat getChangeInXAngle();
	
	//Sets the delta X angle.
	void setChangeInXAngle(GLfloat);
	
	//Returns the delta Y angle.
	GLfloat getChangeInYAngle();
	
	//Sets the delta Y angle.
	void setChangeInYAngle(GLfloat);
	
	//Returns the position in world.
	GLfloat getPositionInWorld();
	
	//Sets the position in the world.
	void setPositionInWorld(GLfloat);
	
	//Returns descend boolean.
	GLboolean getDescend();
	
	//Sets descend boolean.
	void setDescend(GLboolean);
	
	//Returns initial X value.
	GLint getInitialX();
	
	//Sets initial X value.
	void setInitialX(GLint);
	
	//Returns initial Y value.
	GLint getIntialY();
	
	//Sets initial Y value.
	void setInitialY(GLint);
	
	//Returns jump value.
	GLfloat getJump();
	
	//Sets jump value.
	void setJump(GLfloat);
	
	//Returns left mouse pressed boolean.
	GLboolean getLeftMousePressed();
	
	//Sets left mouse pressed boolean.
	void setLeftMousePressed(GLboolean);
	
	//Returns middle mouse pressed boolean.
	GLboolean getMiddleMousePressed();
	
	//Sets middle mouse pressed boolean.
	void setMiddleMousePressed(GLboolean);
	
	//Returns pedal back boolean.
	GLboolean getPedalBack();
	
	//Sets pedal back boolean.
	void setPedalBack(GLboolean);
	
	//Returns pedal up boolean.
	GLboolean getPedalUp();
	
	//Sets pedal up boolean.
	void setPedalUp(GLboolean);
	
	//Returns right mouse pressed boolean.
	GLboolean getRightMousePressed();
	
	//Sets right mouse pressed boolean.
	void setRightMousePressed(GLboolean);
	
	//Returns strafe left boolean.
	GLboolean getStrafeLeft();
	
	//Sets strafe left boolean.
	void setStrafeLeft(GLboolean);
	
	//Returns strafe right boolean.
	GLboolean getStrafeRight();
	
	//Sets strafe right boolean.
	void setStrafeRight(GLboolean);
	
	//Returns strafe value.
	GLfloat getStrafe();
	
	//Sets strafe value.
	void setStrafe(GLfloat);
	
	//Gets change in X direction on screen.
	GLint getXChange();
	
	//Sets change in X direction on screen.
	void setXChange(GLint);
	
	//Gets change in Y direction on screen.
	GLint getYChange();
	
	//Sets change in Y direction on screen.
	void setYChange(GLint);
	
	//Gets change in Z direction on screen.
	GLint getZChange();
	
	//Sets change in Z direction on screen.
	void setZChange(GLint);

	//-------------------------------------------------------
	//Gets camera's X angle.
	GLfloat getCameraXAngle();
	
	//Sets camera's X angle.
	void setCameraXAngle(GLfloat);

	//Gets camera's Y angle.
	GLfloat getCameraYAngle();

	//Sets camera's Y angle.
	void setCameraYAngle(GLfloat);

	//Gets camera's Z angle.
	GLfloat getCameraZAngle();

	//Sets camera's Z angle.
	void setCameraZAngle(GLfloat);

	//Gets camera's X direction.
	float getCameraXDirection();

	//Sets camera's X direction.
	void setCameraXDirection(float);

	//Gets camera's Y direction.
	float getCameraYDirection();

	//Sets camera's Y direction.
	void setCameraYDirection(float);

	//Gets camera's Z direction.
	float getCameraZDirection();

	//Sets camera's Z direction.
	void setCameraZDirection(float);

	//Gets camera's X position.
	float getCameraXPosition();

	//Sets camera's X position.
	void setCameraXPosition(float);

	//Gets camera's Y position.
	float getCameraYPosition();

	//Sets camera's Y position.
	void setCameraYPosition(float);

	//Gets camera's Z position.
	float getCameraZPosition();

	//Sets camera's Z position.
	void setCameraZPosition(float);

	GLfloat getFinalPedalValue();
	GLfloat getFinalStrafeValue();
	GLfloat getFinalHeightValue();
};