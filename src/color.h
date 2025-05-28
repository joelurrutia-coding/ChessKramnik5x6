#pragma once
#include "freeglut.h"

struct Color	//class Color { public: ... }
{
	unsigned char r, g, b, a;
	bool operator==(const Color& other) const {
		return r == other.r && g == other.g && b == other.b;
	}
};
const Color none = { 200, 200, 200, 255 };
/*
//PALETA v1
const Color white = { 252, 232, 140, 255 };
const Color black = { 172, 104, 36, 255 }; 
const Color border = { 80, 36, 17, 255 };
const Color wtile = { 254, 249, 223, 255 };
const Color btile = { 51, 19, 9, 255 };
*/
///*
//PALETA v2
const Color white = { 235, 245, 245, 255 };
const Color black = { 115, 125, 155, 255 };
const Color border = { 33, 52, 65, 255 };
const Color wtile = { 251, 251, 255, 255 };
const Color btile = { 5, 20, 40, 255 }; 
//*/
const Color valid = { 100, 250, 0, 255 };
const Color danger = { 250, 100, 0, 255 };
const Color dangerous = { 250, 250, 0, 255 };
const Color enroque = { 250, 0, 250, 255 };