#ifndef MATH_H
#define MATH_H
#include <cmath>

// @TODO namespace vs function-prefix
namespace Math
{
	template <typename T>
	T max(T a, T b)
	{
		return a > b ? a : b;
	}

	template <typename T>
	T min(T a, T b)
	{
		return a < b ? a : b;
	}

	template <typename T>
	T clamp(T a, T low, T high)
	{
		return max(low, min(a, high));
	}

	// @TODO specify both euler angle and quaternion
	// https://stackoverflow.com/questions/5724171/passing-an-array-by-reference
	void rotate2D(float (&mat)[2][2], float angle)
	{
		mat[0][0] = cos(angle);
		mat[0][1] = -sin(angle);
		mat[1][0] = sin(angle);
		mat[1][1] = cos(angle);
	}
}

#endif // MATH_H