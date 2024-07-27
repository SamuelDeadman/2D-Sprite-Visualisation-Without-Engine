#pragma once
class Rectangle
{
public:
	int left, right, top, bottom;


	Rectangle(int l, int r, int t, int b) : 
		left(l), right(r), top(t), bottom(b) {}

	void Translate(int dx, int dy)
	{
		left += dx;
		right += dx;
		top += dy;
		bottom += dy;
	}

	void ClipTo(const Rectangle& other)
	{
		//left = std::max(left, other.left); (other way)

		if (right > other.right)
			right = other.right;

		if (bottom > other.bottom)
			bottom = other.bottom;

		if (left < other.left)
			left = other.left;

		if (top < other.top)
			top = other.top;
	}

	int Width() const
	{
		return right - left;
	}

	int Height() const
	{
		return bottom - top;
	}
};



