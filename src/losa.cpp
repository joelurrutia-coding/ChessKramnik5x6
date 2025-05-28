#include "losa.h"
#include "freeglut.h"

Losa::Losa():
    color(none),posicion({0,0}), size(1.0f)
{}
Losa::~Losa() {}

void Losa::dibuja() const {
    glPushMatrix();
    glColor4ub(color.r, color.g, color.b, color.a); 
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(posicion.x + 0.5f * size, 0.395f, posicion.z + 0.5f * size);
    glVertex3f(posicion.x + 1.5f * size, 0.395f, posicion.z + 0.5f * size);
    glVertex3f(posicion.x + 1.5f * size, 0.395f, posicion.z + 1.5f * size);
    glVertex3f(posicion.x + 0.5f * size, 0.395f, posicion.z + 1.5f * size);
    glNormal3f(0.0f, 1.0f, 0.0f);
    
    glVertex3f(posicion.x + 0.5f * size, 5.0f, posicion.z + 0.5f * size);
    glVertex3f(posicion.x + 1.5f * size, 5.0f, posicion.z + 0.5f * size);
    glVertex3f(posicion.x + 1.5f * size, 5.0f, posicion.z + 1.5f * size);
    glVertex3f(posicion.x + 0.5f * size, 5.0f, posicion.z + 1.5f * size);
    
    glEnd();
    glPopMatrix();
}