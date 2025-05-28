#include "peon.h"
#include "textura.h"

Peon::Peon() {
    size = 1.0f;
}
Peon::~Peon() {}

bool Peon::mueve() {
    return true;
}
void Peon::dibuja() const {
    glPushMatrix();
    //TEXTURIZADO DEL PEON
    if (color == white) texturizado(posicion.x - 0.3, 5.01, posicion.z - 0.4, 0.6, 0.85, "imagenes/peonblanco.png", color.a);
    else texturizado(posicion.x + 0.34, 5.01, posicion.z + 0.4, -0.65, -0.85, "imagenes/peonnegro.png", color.a);

    glTranslatef(posicion.x, 0.4f, posicion.z);
    glColor4ub(color.r, color.g, color.b, color.a);
    GLUquadric* quad = getSharedQuadric();
    glRotatef(90, -1, 0, 0);
    gluDisk(quad, 0.0f, size * 0.28f, 8, 1);
    gluCylinder(quad, size * 0.28f, size * 0.28f, size * 0.07f, 8, 8);
    glTranslatef(0.0f, 0.0f, size * 0.07f);
    gluDisk(quad, 0.0f, size * 0.28f, 8, 1);
    gluCylinder(quad, size * 0.2275f, size * 0.2275f, size * 0.07f, 8, 8);
    glTranslatef(0.0f, 0.0f, size * 0.07f);
    gluDisk(quad, 0.0f, size * 0.2275f, 8, 1);
    gluCylinder(quad, size * 0.175f, size * 0.035f, size * 0.315f, 8, 8);
    glTranslatef(0.0f, 0.0f, size * 0.315f);
    gluDisk(quad, 0.0f, size * 0.0525f, 8, 1);
    glutSolidTorus(size * 0.0455f, size * 0.0875f, 10, 10);
    glTranslatef(0.0f, 0.0f, size * 0.105f);
    glutSolidSphere(size * 0.1155f, 6, 6);
    if (color == black) {
        glutSolidCone(size * 0.07f, size * 0.21f, 4, 4);
        glRotatef(45, 0, 1, 0);
        glutSolidCone(size * 0.0875f, size * 0.245f, 4, 4);
        glRotatef(90, 0, -1, 0);
        glutSolidCone(size * 0.0875f, size * 0.245f, 4, 4);
    }
    else {
        glTranslatef(0, 0, size * 0.175f);
        glutSolidTorus(size * 0.0175f, size * 0.077f, 10, 10);
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