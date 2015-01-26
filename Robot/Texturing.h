#ifndef TEXTURING_HEADER
#define TEXTURING_HEADER
#include <gl\glut.h>
//BITMAP TEXTURE VARIABLES--------------------------------

class Texturing
{
private:
	GLuint textures;
public:
	Texturing();
	GLuint getTexture();
	void setTexture(GLuint);
};

#endif