#pragma once
class Vector2
{
public:
	Vector2(float x = 0, float y = 0);
	
	float Mag();
	
	//ToDo: Fix This Mess
	void RotateZ(Vector2 origin, float degrees);
	 
	Vector2 Normalize();

	float Dot(Vector2 vec);

	Vector2 operator + (const Vector2& rhs);
	Vector2 operator - (const Vector2& rhs);
	Vector2 operator * (const float& rhs);
	Vector2 operator / (const float& rhs);
	Vector2 operator += (const Vector2& rhs);
	Vector2 operator -= (const Vector2& rhs);

public:
	float x;
	float y;


};

