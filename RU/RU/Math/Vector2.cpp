#include "Vector2.h"
#include <math.h>
Vector2::Vector2(float x, float y)
	:x(x), y(y)
{
}

float Vector2::Mag()
{
	return sqrtf(x * x + y * y);
}

void Vector2::RotateZ(Vector2 origin, float degrees)
{
	
	float cos = cosf(degrees);
	float sin = sinf(degrees);

	float px = (x * cos - y * sin) - origin.x;
	float py = (x * sin + y * cos) - origin.y;

	x = px;
	y = py;
}

Vector2 Vector2::Normalize()
{
	float r = 1 / Mag();
	return Vector2(x * r, y * r);
}

float Vector2::Dot(Vector2 vec)
{
	return ((x * vec.x) + (y * vec.y));
}

Vector2 Vector2::operator+(const Vector2 &rhs)
{
	return Vector2(this->x + rhs.x, this->y + rhs.y);
}

Vector2 Vector2::operator-(const Vector2& rhs)
{
	return Vector2(this->x - rhs.x, this->y - rhs.y);
}

Vector2 Vector2::operator*(const float& rhs)
{
	return Vector2(this->x * rhs, this->y * rhs);
}

Vector2 Vector2::operator/(const float& rhs)
{
	return Vector2(this->x / rhs, this->y / rhs);
}

Vector2 Vector2::operator+=(const Vector2& rhs)
{
	this->x += rhs.x; this->y += rhs.y; return *this;
}

Vector2 Vector2::operator-=(const Vector2& rhs)
{
	this->x -= rhs.x; this->y -= rhs.y; return *this;
}
