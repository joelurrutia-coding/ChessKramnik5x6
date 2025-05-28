#include "plataforma.h"
#include "color.h"
#include <vector>
#include "losa.h"
#include <array>
#include "textura.h"

Plataforma::Plataforma(): 
color(border), limite({ 6, 7 }) 
{
	for (int j = 0; j < 6; ++j) {
		for (int i = 0; i < 5; ++i) {
			tiles[i][j].setPosicion(static_cast<float>(i), static_cast<float>(j));
			bool isBtile = (i + j) % 2 == 0; 
			if (isBtile) {
				tiles[i][j].setColor({ btile.r, btile.g, btile.b, btile.a });
			}
			else {
				tiles[i][j].setColor({ wtile.r, wtile.g, wtile.b, wtile.a });
			}
		}
	}
}
Plataforma::~Plataforma() {}

void Plataforma::dibuja() const {
	glPushMatrix();
	//TEXTURIZADO DEL SUELO
	texturizado(-10, 0, -10, 26, 26, "imagenes/suelo.png", color.a);

	glBegin(GL_QUADS);
	// Abajo
	glNormal3f(0.0f, -1.0f, 0.0f);
	glColor4ub(color.r, color.g, color.b, color.a);
	glVertex3f(0, 0, limite.z);
	glVertex3f(limite.x, 0, 0);
	glVertex3f(limite.x, 0, limite.z);
	glVertex3f(0, 0, limite.z);
	// Arriba
	glNormal3f(0.0f, 1.0f, 0.0f);
	glColor4ub(color.r+7, color.g+7, color.b+7, color.a);
	glVertex3f(0, 0.39f, 0);
	glVertex3f(limite.x, 0.39f, 0);
	glVertex3f(limite.x, 0.39f, limite.z);
	glVertex3f(0, 0.39f, limite.z);
	// Adelante
	glNormal3f(0.0f, 0.0f, 1.0f);
	glColor4ub(color.r-7, color.g-7, color.b-7, color.a);
	glVertex3f(0, 0, limite.z);
	glVertex3f(limite.x, 0, limite.z);
	glVertex3f(limite.x, 0.39f, limite.z);
	glVertex3f(0, 0.39f, limite.z);
	// Atras
	glNormal3f(0.0f, 0.0f, -1.0f);
	glColor4ub(color.r-7, color.g-7, color.b-7, color.a);
	glVertex3f(0, 0, 0);
	glVertex3f(limite.x, 0, 0);
	glVertex3f(limite.x, 0.39f, 0);
	glVertex3f(0, 0.39f, 0);
	// Izquierda
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glColor4ub(color.r-7, color.g-7, color.b-7, color.a);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, limite.z);
	glVertex3f(0, 0.39f, limite.z);
	glVertex3f(0, 0.39f, 0);
	// Derecha
	glNormal3f(1.0f, 0.0f, 0.0f);
	glColor4ub(color.r-7, color.g-7, color.b-7, color.a);
	glVertex3f(limite.x, 0, 0);
	glVertex3f(limite.x, 0, limite.z);
	glVertex3f(limite.x, 0.39f, limite.z);
	glVertex3f(limite.x, 0.39f, 0);
	glEnd();
	for (const auto& i : tiles) {
        for (const auto& tile : i) {
            tile.dibuja();
        }
    }	
	glPopMatrix();
}
void Plataforma::resetTileColors() {
	for (int j = 0; j < 6; ++j) {
		for (int i = 0; i < 5; ++i) {
			bool isBtile = (i + j) % 2 == 0;
			if (isBtile) {
				tiles[i][j].setColor({ btile.r, btile.g, btile.b, btile.a });
			}
			else {
				tiles[i][j].setColor({ wtile.r, wtile.g, wtile.b, wtile.a });
			}
		}
	}
}