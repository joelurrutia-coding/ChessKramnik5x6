#include "caballo.h"
#include "freeglut.h"

Caballo::Caballo() {
    size = 1.0f;
}
Caballo::~Caballo() {}

bool Caballo::mueve() {
    return true;
}

void Caballo::dibuja() const {
    glPushMatrix();
    glTranslatef(posicion.x, 0.4f, posicion.z);
    glColor4ub(color.r, color.g, color.b, color.a);
    GLUquadric* quad = getSharedQuadric();
    glRotatef(90, 0, -1, 0);
    glRotatef(90, -1, 0, 0);
    gluDisk(quad, 0.0f, size * 0.32f, 8, 1);
    gluCylinder(quad, size * 0.32f, size * 0.32f, size * 0.08f, 8, 8);
    glTranslatef(0.0f, 0.0f, size * 0.08f);
    gluDisk(quad, 0.0f, size * 0.32f, 8, 1);
    gluCylinder(quad, size * 0.26f, size * 0.26f, size * 0.08f, 8, 8);
    glTranslatef(0.0f, 0.0f, size * 0.08f);
    gluDisk(quad, 0.0f, size * 0.26f, 8, 1);
    gluCylinder(quad, size * 0.2f, size * 0.112f, size * 0.56f, 8, 8);
    glTranslatef(0.0f, 0.0f, size * 0.56f);
    gluDisk(quad, 0.0f, size * 0.112f, 8, 1);
    glRotatef(-90, -1, 0, 0);
    glRotatef(90, 0, 1, 0);
    glTranslatef(0.0f, 0.0f, -size * 0.04f);
    if ((color.r == black.r) && (color.g == black.g) && (color.b == black.b)) {
        glTranslatef(0.0f, 0.0f, size * 0.08f);
        glRotatef(180, 0, -1, 0);
    }
    glutSolidTorus(size * 0.08f, size * 0.056f, 4, 4);
    glutSolidTorus(size * 0.048f, size * 0.12f, 6, 6);
    gluDisk(quad, 0.0f, size * 0.16f, 8, 1);
    gluCylinder(quad, size * 0.16f, size * 0.06f, size * 0.28f, 3, 3);
    glTranslatef(0.0f, 0.0f, -size * 0.048f);
    glutSolidTorus(size * 0.04f, size * 0.14f, 10, 10);
    glTranslatef(0.0f, 0.0f, size * 0.328f);
    gluDisk(quad, 0.0f, size * 0.06f, 8, 1);
    glRotatef(90, -1, 0, 0);
    glutSolidTorus(size * 0.028f, size * 0.028f, 10, 10);
    glTranslatef(size * 0.1f, size * 0.32f, size * 0.08f);
    glRotatef(30, 0, 1, 0);
    glRotatef(30, -1, 0, 0);
    glutSolidCone(size * 0.08f, size * 0.18f, 4, 4);
    glRotatef(-30, -1, 0, 0);
    glRotatef(-30, 0, 1, 0);
    glTranslatef(-size * 0.2f, 0.0f, size * 0.0f);
    glRotatef(30, 0, -1, 0);
    glRotatef(30, -1, 0, 0);
    glutSolidCone(size * 0.08f, size * 0.18f, 4, 4);
    glPopMatrix();
}