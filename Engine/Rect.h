#pragma once
#include "Vec2.h"

template<typename T>
class Rect
{
public:
	Rect() = default;

	Rect(T left_in, T right_in, T top_in, T bottom_in)
		:
		left(left_in),
		right(right_in),
		top(top_in),
		bottom(bottom_in)
	{
	}

	Rect(const Vec2_<T>& topLeft, const Vec2_<T>& bottomRight)
		:
		Rect(topLeft.x, bottomRight.x, topLeft.y, bottomRight.y)
	{
	}

	Rect(const Vec2_<T>& topLeft, T width, T height)
		:
		Rect(topLeft, topLeft + Vec2_<T>(width, height))
	{
	}

	bool IsOverlappingWith(const Rect& other) const
	{
		return right > other.left && left < other.right
			&& bottom > other.top && top < other.bottom;
	}

	bool IsContainedBy(const Rect& other) const
	{
		return left >= other.left && right <= other.right &&
			top >= other.top && bottom <= other.bottom;
	}

	bool Contains(const Vec2_<T>& poT) const
	{
		return poT.x >= left && poT.x < right && poT.y >= top && poT.y < bottom;
	}

	Rect FromCenter(const Vec2_<T>& center, T halfWidth, T halfHeight)
	{
		const Vec2_<T> half(halfWidth, halfHeight);
		return Rect(center - half, center + half);
	}

	Rect GetExpanded(T offset) const
	{
		return Rect(left - offset, right + offset, top - offset, bottom + offset);
	}

	Vec2_<T> GetCenter() const
	{
		return Vec2_<T>((left + right) / T(2), (top + bottom) / T(2));
	}

	T GetWidth() const
	{
		return right - left;
	}

	T GetHeight() const
	{
		return bottom - top;
	}

	template<typename S>
	explicit Rect(const Rect<S>& src) 
		:
		left( (T)src.left),
		right( (T)src.right),
		top( (T)src.left),
		bottom( (T)src.bottom),
	{}

public:
	T left;
	T right;
	T top;
	T bottom;
};

typedef Rect<float> RectF;
typedef Rect<int> RectI;