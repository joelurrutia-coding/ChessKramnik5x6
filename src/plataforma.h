#pragma once
#include "vector2D.h"
#include "color.h"
#include "losa.h"
#include <vector>
#include <array>

class Plataforma
{
private:
	vector2D limite;
	Color color;
	std::array<std::array<Losa, 6>, 5> tiles;

public:
	Plataforma();
	virtual ~Plataforma();

	inline std::array<std::array<Losa, 6>, 5>& getTiles() { return tiles; };
	void dibuja() const;
	void resetTileColors();
};