#ifndef __VEC2_H__
#define __VEC2_H__

struct Vec2 {
	double x{ 0.0 };
	double y{ 0.0 };

	Vec2() = default;
	Vec2(double x, double y) : x(x), y(y) { }

    bool operator==(const Vec2& v);
    bool operator!=(const Vec2& v);

    Vec2 operator+(const Vec2& v);
    Vec2& operator+=(const Vec2& v);

    Vec2 operator-(const Vec2& v);
    Vec2& operator-=(const Vec2& v);

    Vec2 operator*(double scale);
    Vec2& operator*=(double scale);

    Vec2 operator/(double divisor);
    Vec2& operator/=(double divisor);
};

struct iVec2 {
    int x{ 0 };
    int y{ 0 };

    iVec2() = default;
    iVec2(int x, int y) : x(x), y(y) { }

    bool operator==(const iVec2& v);
    bool operator!=(const iVec2& v);

    iVec2 operator+(const iVec2& v);
    iVec2& operator+=(const iVec2& v);

    iVec2 operator-(const iVec2& v);
    iVec2& operator-=(const iVec2& v);

    iVec2 operator*(int scale);
    iVec2& operator*=(int scale);

    iVec2 operator/(int divisor);
    iVec2& operator/=(int divisor);
};

#endif