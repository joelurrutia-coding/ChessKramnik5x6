#include "torre.h"
#include "freeglut.h"

Torre::Torre() {
    size = 0.35f;
}
Torre::~Torre() {}

bool Torre::mueve() {
    return true;
}

void Torre::dibuja() const {
    glPushMatrix();
    glTranslatef(posicion.x, 0.4f, posicion.z);
    glColor4ub(color.r, color.g, color.b, color.a);
    GLUquadric* quad = getSharedQuadric();
    glPushMatrix();
    glRotatef(90, -1, 0, 0);
    gluDisk(quad, 0.0f, size * 0.8f, 8, 1);
    gluCylinder(quad, size * 0.8f, size * 0.8f, size * 0.2f, 8, 8);
    glTranslatef(0.0f, 0.0f, size * 0.2f);
    gluDisk(quad, 0.0f, size * 0.8f, 8, 1);
    gluCylinder(quad, size * 0.65f, size * 0.65f, size * 0.2f, 8, 8);
    glTranslatef(0.0f, 0.0f, size * 0.2f);
    gluDisk(quad, 0.0f, size * 0.65f, 8, 1);
    //gluQuadricDrawStyle(quad, GLU_LINE);  
    gluCylinder(quad, size * 0.5f, size * 0.35f, size * 1.3f, 8, 8);
    //gluQuadricDrawStyle(quad, GLU_FILL);
    glTranslatef(0.0f, 0.0f, size * 1.3f);
    gluDisk(quad, 0.0f, size * 0.4f, 8, 1);
    glTranslatef(0.0f, 0.0f, -size * 0.25f);
    glutSolidTorus(size * 0.13f, size * 0.35f, 10, 10);
    glTranslatef(0.0f, 0.0f, size * 0.22f);
    glutSolidTorus(size * 0.13f, size * 0.4f, 10, 10);
    glPopMatrix();
    for (int i = 0; i < 8; ++i) {
        float angle = 2.0f * 3.1415926535f * static_cast<float>(i) / 8.0f; // Radianes
        glPushMatrix();
        glTranslatef(cos(angle) * size * 0.4f, size * 1.85f, sin(angle) * size * 0.4f);
        glRotatef(angle * 180.0f / 3.1415926535f, 0, 1, 0);
        glutSolidCube(size * 0.2f);
        glPopMatrix();
    }
    glPopMatrix();
}