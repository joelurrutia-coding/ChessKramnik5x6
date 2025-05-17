#include "reina.h"
#include "freeglut.h"

Reina::Reina() {
    size = 1.0f;
}
Reina::~Reina() {}

bool Reina::mueve() {
    return true;
}

void Reina::dibuja() const {
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
    gluCylinder(quad, size * 0.2f, size * 0.06f, size * 0.48f, 8, 8);
    glTranslatef(0.0f, 0.0f, size * 0.48f);
    gluDisk(quad, 0.0f, size * 0.06f, 8, 1);
    gluCylinder(quad, size * 0.06f, size * 0.16f, size * 0.24f, 8, 8);
    glutSolidTorus(size * 0.04f, size * 0.08f, 10, 10);
    glTranslatef(0.0f, 0.0f, size * 0.24f);
    gluDisk(quad, 0.0f, size * 0.16f, 8, 1);
    glutSolidTorus(size * 0.04f, size * 0.06f, 10, 10);
    glutSolidCone(size * 0.048f, size * 0.08f, 8, 8);
    glTranslatef(0.0f, 0.0f, size * 0.08f);
    glutSolidSphere(size * 0.028f, 6, 6);
    if ((color.r == black.r) && (color.g == black.g) && (color.b == black.b)) {
        glTranslatef(0, 0, -size * 0.14f);
        glRotatef(45, 0, 1, 0);
        glutSolidCone(size * 0.08f, size * 0.28f, 4, 4);
        glRotatef(90, 0, -1, 0);
        glutSolidCone(size * 0.08f, size * 0.28f, 4, 4);
        glRotatef(90, 0, -1, 0);
        glutSolidCone(size * 0.12f, size * 0.22f, 4, 4);
        glRotatef(90, 0, -1, 0);
        glutSolidCone(size * 0.12f, size * 0.22f, 4, 4);
    }
    else {
        glTranslatef(0, 0, size * 0.08f);
        glutSolidTorus(size * 0.016f, size * 0.088f, 10, 10);
        glTranslatef(0, 0, size * -0.5f);
        glRotatef(70, 0, -1, 0);
        glutSolidCone(size * 0.0875f, size * 0.315f, 4, 4);
        glTranslatef(size * -0.0525f, 0, 0);
        glutSolidCone(size * 0.0875f, size * 0.2625f, 4, 4);
        glTranslatef(size * -0.0525f, 0, 0);
        glutSolidCone(size * 0.0875f, size * 0.21f, 4, 4);
        glTranslatef(size * 0.105f, 0, 0);
        glRotatef(180, 1, 0, 0);
        glRotatef(40, 0, 1, 0);
        glutSolidCone(size * 0.0875f, size * 0.315f, 4, 4);
        glTranslatef(size * -0.0525f, 0, 0);
        glutSolidCone(size * 0.0875f, size * 0.2625f, 4, 4);
        glTranslatef(size * -0.0525f, 0, 0);
        glutSolidCone(size * 0.0875f, size * 0.21f, 4, 4);
    }
    glPopMatrix();
}