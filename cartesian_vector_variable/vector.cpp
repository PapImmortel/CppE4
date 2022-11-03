#include "Vector.hh"
#pragma once



#include "config.h"

Vector::Vector(const Vector&)
{

}

Vector::Vector(size_t N)
{
	this->sizeVector = N;
	this->coords = make_unique<value[]>(N);
	for (int i = 0; i < N; i++)
	{
		this->coords[i] = 0;
	}
}
Vector::Vector(std::initializer_list<value> l)
{

	auto Val = std::data(l);
	this->sizeVector = size(Val);
	this->coords = make_unique<value[]>(this->sizeVector);

	for (int i = 0; i < this->sizeVector; i++)
	{
		this->coords[i] = Val[i];
	}
}
size_t Vector::size() const
{
	return this->sizeVector;
}

Vector& Vector::operator+=(const Vector& rhs)
{
	if (this->sizeVector == rhs->sizeVector)
	{
		for (int i = 0; i < this->sizeVector; i++)
		{
			this->coord[i] += rhs.coord[i];
		}
		return *this;
	}
	throw std::runtime_error("Incompatible size");
	
}

Vector& Vector::operator-=(const Vector& rhs)
{
	if (this->sizeVector == rhs->sizeVector)
	{
		for (int i = 0; i < this->sizeVector; i++)
		{
			this->coord[i] -= rhs.coord[i];
		}
		return *this;
	}
	throw std::runtime_error("Incompatible size");
}

Vector& Vector::operator+=(value v)
{
	for (int i = 0; i < this->sizeVector; i++)
	{
		this->coord[i] += v;
	}
	return *this;
}

Vector& Vector::operator*=(value v)
{
	for (int i = 0; i < this->sizeVector; i++)
	{
		this->coord[i] *= v;
	}
	return *this;
}

Vector Vector::operator+(const Vector& rhs) const
{
	if (this->sizeVector == rhs->sizeVector)
	{
		Vector newVec = new Vector(this->sizeVector);
		for (int i = 0; i < this->sizeVector; i++)
		{
			newVec[i] = this->coords[i] + rhs.coord[i];
		}
		return newVec;
	}
	throw std::runtime_error("Incompatible size");
}
Vector Vector::operator+(value v) const
{
	Vector newVec = new Vector(this->sizeVector);
	for (int i = 0; i < this->sizeVector; i++)
	{
		newVec[i] = this->coords[i] +v;
	}
	return newVec;
}

value Vector::operator*(const Vector& rhs) const
{
	if (this->sizeVector == rhs->sizeVector)
	{
		value newVal = 0;
		for (int i = 0; i < this->sizeVector; i++)
		{
			newVal += this->coords[i] * rhs.coord[i];
		}
		return newVec;
	}
	throw std::runtime_error("Incompatible size");
}
Vector Vector::operator*(value v) const
{
	Vector newVec = new Vector(this->sizeVector);
	for (int i = 0; i < this->sizeVector; i++)
	{
		newVec[i] = this->coords[i] * v;
	}
	return newVec;
}

value& Vector::operator[](size_t idx)
{
	return this->coord[idx];
}

value Vector::operator[](size_t idx) const
{
	value valeur = this->coord[idx]
	return valeur;
}



Vector operator*(const value& s, const Vector& v)
{
	return v * s;
}

Vector operator+(const value& s, const Vector& v)
{
	return v + s;
}
std::ostream& operator<<(std::ostream& o, const Vector& v)
{
	o << "{";
	Vector newVec = Vector(v);
	for (int i = 0; i < v.size() - 1; i++)
	{
		o << newVec[i] << ",";
	}
	o << newVec[v.size()-1] << "}";
	return o;
}