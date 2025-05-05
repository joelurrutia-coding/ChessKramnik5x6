#pragma once
#include "vector2D.h"
#include "color.h"

class Losa
{
private:
	float size;
	Color color;
	vector2D posicion;

public:
	Losa();
	virtual~Losa();

	void setColor(const Color& c);
	void setPosicion(float ix, float iz);
	void dibuja() const;
};