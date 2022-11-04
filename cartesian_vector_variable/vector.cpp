#include "Vector.hh"
#pragma once



#include "config.h"

// Add suitable constructors
Vector::Vector(size_t psize)
{
    this->size_ = psize;
    this->coord = std::make_unique<value[]>(psize);
    for (int i = 0; i <psize ; i++)
    {
        this->coord[i] = 0;
    }

}

Vector::Vector(std::initializer_list<value> IL)
{
    this->size_ = IL.size();
    this->coord = std::make_unique<value[]>(IL.size());
    auto Val = std::data(IL);
    for (int i = 0; i < IL.size(); i++)
    {
        this->coord[i] = Val[i];
    }

}
Vector::Vector(const Vector& v)
{
    this->size_ = v.size();
    this->coord = std::make_unique<value[]>(v.size());
    for (int i = 0; i < v.size(); i++)
    {
        this->coord[i] = v.coord[i];
    }
}
// possibly more

    // Public Member functions here

Vector& Vector::operator+=(Vector const& rhs)
{
    if (rhs.size() != this->size())
        throw std::runtime_error("Incompatible size");
    for (int i = 0; i < rhs.size(); i++)
    {
        this->coord[i] += rhs.coord[i];
    }
    return *this;
}
Vector& Vector::operator=(const Vector& V)
{
    this->size_ = V.size();
    this->coord = std::make_unique<value[]>(V.size());
    for (int i = 0; i < V.size(); i++)
    {
        this->coord[i] = V.coord[i];
    }
    return *this;
}
size_t Vector::size() const 
{
    return this->size_;
}
value Vector::operator*(const Vector& rhs) const
{
    if (rhs.size() != this->size())
        throw std::runtime_error("Incompatible size");
    value resultat = 0;
    for (int i = 0; i < this->size(); i++)
    {
        resultat += this->coord[i] * rhs.coord[i];
    }
    return resultat;
}
Vector Vector::operator*(value Nb) const
{
    Vector newVec = Vector(this->size());
    for (int i = 0; i < this->size(); i++)
    {
        newVec.coord[i] = this->coord[i] * Nb;
    }
    return newVec;
}
Vector& Vector::operator-=(Vector const& rhs)
{
    if (rhs.size() != this->size())
        throw std::runtime_error("Incompatible size");
    for (int i = 0; i < this->size(); i++)
    {
        this->coord[i] -= rhs.coord[i];
    }
    return *this;
}
Vector& Vector::operator+=(value nb)
{
    for (int i = 0; i < this->size(); i++)
    {
        this->coord[i] += nb;
    }
    return *this;
}
Vector& Vector::operator*=(value nb)
{
    for (int i = 0; i < this->size(); i++)
    {
        this->coord[i] *= nb;
    }
    return *this;
}
Vector Vector::operator+(value v) const
{
    Vector newVec = Vector(this->size());
    for (int i = 0; i < this->size(); i++)
    {
        newVec.coord[i] = this->coord[i] + v;
    }
    return newVec;
}
Vector Vector::operator+(const Vector& rhs) const
{
    if (rhs.size() != this->size())
        throw std::runtime_error("Incompatible size");
    
    Vector newVec = Vector(this->size());
    for (int i = 0; i < this->size(); i++)
    {
        newVec.coord[i] = this->coord[i] + rhs.coord[i];
    }
    return newVec;
}
/*Vector Vector::operator-(Vector& rhs) const
{
    if (rhs.size() != this->size())
        throw std::runtime_error("Incompatible size");
    Vector newVec = Vector(rhs.size());
    for (int i = 0; i < rhs.size(); i++)
    {
        newVec.coord[i] = this->coord[i] - rhs.coord[i];
    }
    return newVec;
}*/

value& Vector::operator[](size_t i)
{
    return this->coord[i];
}
value Vector::operator[](size_t i) const
{
    return this->coord[i];
}

std::ostream& operator<<(std::ostream& os, Vector const& rhs)
{
    os << "{";
    Vector newVec = Vector(rhs);
    for (int i = 0; i < rhs.size() - 1; i++)
    {
        os << newVec[i] << ",";
    }
    os << newVec[rhs.size() - 1] << "}";
    return os;
}
Vector operator*(const value& s, const Vector& v)
{
    Vector res = Vector(v.size());
    for (int i = 0; i < v.size(); i++)
    {
        res[i] = v[i] * s;
    }
    return res;
}
Vector operator+(const value& s, const Vector& v)
{
    Vector res = Vector(v.size());
    for (int i = 0; i < v.size(); i++)
    {
        res[i] = v[i] + s;
    }
    return res;
}