#include "Texturing.h"

Texturing::Texturing()
{

}

GLuint Texturing::getTexture()
{
	return textures;
}

void Texturing::setTexture(GLuint newValue)
{
	textures = newValue;
}