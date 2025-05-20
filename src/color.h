#pragma once
#include "freeglut.h"

struct Color	//class Color { public: ... }
{
	unsigned char r, g, b, a;
	bool operator==(const Color& other) const {
		return r == other.r && g == other.g && b == other.b && a == other.a;
	}
};
const Color none = { 200, 200, 200, 250 };

/*
//PALETA v1
const Color white = { 252, 232, 140, 250 };
const Color black = { 172, 104, 36, 250 }; 
const Color border = { 80, 36, 17, 250 };
const Color wtile = { 254, 249, 223, 250 };
const Color btile = { 51, 19, 9, 250 };
*/
///*
//PALETA v2
const Color white = { 235, 245, 245, 250 };
const Color black = { 115, 125, 155, 250 };
const Color border = { 33, 52, 65, 250 };
const Color wtile = { 251, 251, 255, 250 };
const Color btile = { 5, 20, 40, 250 }; 
//*/
const Color valid = { 100, 250, 0, 250 };
const Color danger = { 250, 100, 0, 250 };
const Color dangerous = { 250, 250, 0, 250 };
const Color enroque = { 250, 0, 250, 250 };