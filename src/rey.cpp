#include "rey.h"
#include "textura.h"

Rey::Rey() {
    size = 1.0f;
}
Rey::~Rey() {}

bool Rey::mueve() {
    return true;
}

void Rey::dibuja() const {
    glPushMatrix();
    //TEXTURIZADO DEL ALFIL
    if (color == white) texturizado(posicion.x - 0.37, 5.01, posicion.z - 0.49, 0.75, 0.99, "imagenes/reyblanco.png", color.a);
    else texturizado(posicion.x + 0.4, 5.01, posicion.z + 0.49, -0.8, -0.99, "imagenes/reynegro.png", color.a);

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
    gluCylinder(quad, size * 0.2f, size * 0.1f, size * 0.52f, 8, 8);
    glTranslatef(0.0f, 0.0f, size * 0.52f);
    gluDisk(quad, 0.0f, size * 0.1f, 8, 1);
    gluCylinder(quad, size * 0.1f, size * 0.16f, size * 0.24f, 8, 8);
    glutSolidTorus(size * 0.04f, size * 0.12f, 10, 10);
    glTranslatef(0.0f, 0.0f, size * 0.24f);
    gluDisk(quad, 0.0f, size * 0.16f, 8, 1);
    glutSolidTorus(size * 0.04f, size * 0.04f, 10, 10);
    gluCylinder(quad, size * 0.032f, size * 0.032f, size * 0.24f, 4, 4);
    glTranslatef(0.0f, 0.0f, size * 0.24f);
    gluDisk(quad, 0.0f, size * 0.032f, 4, 1);
    glRotatef(90, 0, -1, 0);
    glTranslatef(-size * 0.1f, 0.0f, -size * 0.08f);
    gluCylinder(quad, size * 0.032f, size * 0.032f, size * 0.16f, 4, 4);
    gluDisk(quad, 0.0f, size * 0.032f, 4, 1);
    glTranslatef(0.0f, 0.0f, size * 0.16f);
    gluDisk(quad, 0.0f, size * 0.032f, 4, 1);
    glPopMatrix();
}
