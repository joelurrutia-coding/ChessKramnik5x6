#pragma once
#include "vector2D.h"
#include "color.h"
#include "losa.h"
#include <vector>
#include <array>

class Tablero
{
private:
	vector2D limite;
	Color color;
	std::array<std::array<Losa, 6>, 5> tiles;

public:
	Tablero();
	virtual ~Tablero();

	std::array<std::array<Losa, 6>, 5>& getTiles();
	void dibuja() const;
	void resetTileColors();
};