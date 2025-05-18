#include "vector2D.h"

vector2D::vector2D(float xi, float zi){
	x = xi;
	z = zi;
}
vector2D::~vector2D() {}

float vector2D::modulo() const{
	return (float)sqrt(x * x + z * z);
}
float vector2D::argumento() const{
	return (float)atan2(x, z);
}
vector2D vector2D::operator + (vector2D v) {
	return { x + v.x, z + v.z };
}
vector2D vector2D::operator - (vector2D v){
	return { x - v.x, z - v.z };
}
bool vector2D::operator==(const vector2D& other) const {
	return (x == other.x && z == other.z);
}