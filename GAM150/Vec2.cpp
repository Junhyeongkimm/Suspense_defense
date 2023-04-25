#include "Vec2.h"

bool Vec2::operator==(const Vec2& v) {
	return (x == v.x) && (y = v.y);
}
bool Vec2::operator!=(const Vec2& v) {
	return (!(x == v.x) && (y = v.y));
}
Vec2 Vec2::operator+(const Vec2& v) {
	return { x + v.x, y + v.y };
}
Vec2& Vec2::operator+=(const Vec2& v) {
	x += v.x;
	y += v.y;
	return *this;
}

Vec2 Vec2::operator-(const Vec2& v) {
	return { x - v.x, y - v.y };
}
Vec2& Vec2::operator-=(const Vec2& v) {
	x -= v.x;
	y -= v.y;
	return *this;
}

Vec2 Vec2::operator*(double scale) {
	return { x * scale, y * scale };
}
Vec2& Vec2::operator*=(double scale) {
	x *= scale;
	y *= scale;
	return *this;
}

Vec2 Vec2::operator/(double divisor) {
	return { x / divisor, y / divisor };
}
Vec2& Vec2::operator/=(double divisor) {
	x /= divisor;
	y /= divisor;
	return *this;
}

bool iVec2::operator==(const iVec2& v) {
	return (x == v.x) && (y = v.y);
}
bool iVec2::operator!=(const iVec2& v) {
	return (!(x == v.x) && (y = v.y));
}
iVec2 iVec2::operator+(const iVec2& v) {
	return { x + v.x, y + v.y };
}
iVec2& iVec2::operator+=(const iVec2& v) {
	x += v.x;
	y += v.y;
	return *this;
}

iVec2 iVec2::operator-(const iVec2& v) {
	return { x - v.x, y - v.y };
}
iVec2& iVec2::operator-=(const iVec2& v) {
	x -= v.x;
	y -= v.y;
	return *this;
}

iVec2 iVec2::operator*(int scale) {
	return { x * scale, y * scale };
}
iVec2& iVec2::operator*=(int scale) {
	x *= scale;
	y *= scale;
	return *this;
}

iVec2 iVec2::operator/(int divisor) {
	return { x / divisor, y / divisor };
}
iVec2& iVec2::operator/=(int divisor) {
	x /= divisor;
	y /= divisor;
	return *this;
}