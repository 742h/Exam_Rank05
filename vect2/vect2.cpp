#include "vect2.hpp"

vect2::vect2() : x(0), y(0)
{
}

vect2::vect2(int num1, int num2) : x(num1), y(num2)
{
}

vect2::vect2(const vect2 &other)
{
	x = other.x;
	y = other.y;
}

vect2 &vect2::operator=(const vect2 &other)
{
	x = other.x;
	y = other.y;
	return (*this);
}

vect2::~vect2()
{
}

int &vect2::operator[](int index)
{
	if (index == 0)
		return (x);
	return (y);
}

int vect2::operator[](int index) const
{
	if (index == 0)
		return (x);
	return (y);
}

vect2 vect2::operator-() const
{
	return (vect2(-x, -y));
}

vect2 vect2::operator*(int num) const
{
	return (vect2(x * num, y * num));
}

vect2 &vect2::operator*=(int num)
{
	x *= num;
	y *= num;
	return (*this);
}

vect2 &vect2::operator+=(const vect2 &obj)
{
	x += obj.x;
	y += obj.y;
	return (*this);
}

vect2 &vect2::operator-=(const vect2 &obj)
{
	x -= obj.x;
	y -= obj.y;
	return (*this);
}

vect2 vect2::operator+(const vect2 &obj) const
{
	return (vect2(x + obj.x, y + obj.y));
}

vect2 vect2::operator-(const vect2 &obj) const
{
	return (vect2(x - obj.x, y - obj.y));
}

vect2 &vect2::operator++()
{
	x++;
	y++;
	return (*this);
}

vect2 vect2::operator++(int)
{
	vect2 temp(*this);

	x++;
	y++;

	return (temp);
}

vect2 &vect2::operator--()
{
	x--;
	y--;
	return (*this);
}

vect2 vect2::operator--(int)
{
	vect2 temp(*this);

	x--;
	y--;

	return (temp);
}

bool vect2::operator==(const vect2 &obj) const
{
	return (x == obj.x && y == obj.y);
}

bool vect2::operator!=(const vect2 &obj) const
{
	return (!(*this == obj));
}

vect2 operator*(int num, const vect2 &obj)
{
	return (obj * num);
}

std::ostream &operator<<(std::ostream &os, const vect2 &obj)
{
	os << "{" << obj[0] << ", " << obj[1] << "}";
	return (os);
}