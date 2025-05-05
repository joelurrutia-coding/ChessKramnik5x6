#include "alfil.h"
#include "freeglut.h"

Alfil::Alfil() {
    size = 1.0f;
}
Alfil::~Alfil() {}

bool Alfil::mueve() {
    return true;
}

void Alfil::dibujaIndividual() const {
    glPushMatrix();
    glTranslatef(posicion.x, 0.4f, posicion.z);
    glColor4ub(color.r, color.g, color.b, color.a);
    GLUquadric* quad = getSharedQuadric();
    glRotatef(90, -1, 0, 0);
    gluDisk(quad, 0.0f, size * 0.32f, 8, 1);
    gluCylinder(quad, size * 0.32f, size * 0.32f, size * 0.08f, 8, 8);
    glTranslatef(0.0f, 0.0f, size * 0.08f);
    gluDisk(quad, 0.0f, size * 0.32f, 8, 1);
    gluCylinder(quad, size * 0.26f, size * 0.26f, size * 0.08f, 8, 8);
    glTranslatef(0.0f, 0.0f, size * 0.08f);
    gluDisk(quad, 0.0f, size * 0.26f, 8, 1);
    glutSolidCone(size * 0.2f, size * 0.76f, 8, 8);
    glTranslatef(0.0f, 0.0f, size * 0.488f);
    gluDisk(quad, 0.0f, size * 0.06f, 8, 1);
    glutSolidTorus(size * 0.04f, size * 0.06f, 10, 10);
    glTranslatef(0.0f, 0.0f, -size * 0.06f);
    glutSolidTorus(size * 0.04f, size * 0.088f, 10, 10);
    glTranslatef(0.0f, 0.0f, size * 0.176f);
    glutSolidSphere(size * 0.12f, 6, 6);
    glTranslatef(0.0f, 0.0f, size * 0.02f);
    glutSolidTorus(size * 0.02f, size * 0.104f, 6, 6);
    glTranslatef(0.0f, 0.0f, size * 0.072f);
    glutSolidCone(size * 0.068f, size * 0.12f, 6, 6);
    glTranslatef(0.0f, 0.0f, size * 0.144f);
    glutSolidSphere(size * 0.028f, 6, 6);
    glPopMatrix();
}