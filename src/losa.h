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

	inline void setColor(const Color& c) { color = c; }
	inline void setPosicion(float ix, float iz) { posicion = { ix, iz }; }
	void dibuja() const;
};