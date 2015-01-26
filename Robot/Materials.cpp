#include "Materials.h"

Materials::
Materials()
{
	for (int i = 0; i < 3; i++)
	{
		diffuseMaterial[i] = 1.0f;
		specularMaterial[i] = 1.0f;
		emissionMaterial[i] = 1.0f;
		noMaterial[i] = 1.0f;

	}
	shineFactor[0] = 1.0f;
}

GLfloat* Materials::
getDiffuseMaterial()
{
	return diffuseMaterial;
}

void Materials::
setDiffuseMaterial(GLfloat* newValue)
{
	for (int i = 0; i < 3; i++)
	{
		diffuseMaterial[i] = newValue[i];
	}
}

GLfloat* Materials::
getSpecularMaterial()
{
	return specularMaterial;
}

void Materials::
setSpecularMaterial(GLfloat* newValue)
{
	for (int i = 0; i < 3; i++)
	{
		specularMaterial[i] = newValue[i];
	}
}

GLfloat* Materials::
getEmissionMaterial()
{
	return emissionMaterial;
}

void Materials::
setEmissionMaterial(GLfloat* newValue)
{
	for (int i = 0; i < 3; i++)
	{
		emissionMaterial[i] = newValue[i];
	}
}

GLfloat* Materials::
getNoMaterial()
{
	return noMaterial;
}

void Materials::
setNoMaterial(GLfloat* newValue)
{
	for (int i = 0; i < 3; i++)
	{
		noMaterial[i] = newValue[i];
	}
}

GLfloat* Materials::
getShineFactor()
{
	return shineFactor;
}

void Materials::
setShineFactor(GLfloat* newValue)
{
	for (int i = 0; i < 3; i++)
	{
		shineFactor[i] = newValue[i];
	}
}