#ifndef MATERIALS_HEADER
#define MATERIALS_HEADER
#include <gl\glut.h>

class Materials
{
private:
	//LIGHTING VARIABLES--------------------------------------
	GLfloat diffuseMaterial[3];
	GLfloat specularMaterial[3];
	GLfloat emissionMaterial[3];
	GLfloat noMaterial[3];
	GLfloat shineFactor[1];

public:
	Materials();

	GLfloat* getDiffuseMaterial();
	void setDiffuseMaterial(GLfloat*);
	GLfloat* getSpecularMaterial();
	void setSpecularMaterial(GLfloat*);
	GLfloat* getEmissionMaterial();
	void setEmissionMaterial(GLfloat*);
	GLfloat* getNoMaterial();
	void setNoMaterial(GLfloat*);
	GLfloat* getShineFactor();
	void setShineFactor(GLfloat*);
};
#endif