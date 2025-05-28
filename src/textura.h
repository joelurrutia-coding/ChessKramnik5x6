#pragma once
#include "freeglut.h"
#include "ETSIDI.h"

//TEXTURIZADORGl
inline void texturizado(GLdouble dx, GLdouble dy, GLdouble dz, GLdouble size_x, GLdouble size_z, const char* PNGimagePath, unsigned char a) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture(PNGimagePath).id);
	glDisable(GL_LIGHTING);
	glBegin(GL_POLYGON);
	glColor4ub(255, 255, 255, a);
	glTexCoord3d(0, 1, 0); glVertex3d(dx, dy, dz);
	glTexCoord3d(1, 1, 0); glVertex3d(dx + size_x, dy, dz);
	glTexCoord3d(1, 0, 0); glVertex3d(dx + size_x, dy, dz + size_z);
	glTexCoord3d(0, 0, 0); glVertex3d(dx, dy, dz + size_z);
	glEnd();
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
}