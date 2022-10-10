#include "Vector.hh"
#pragma once



#include "config.h"

    // Add suitable constructors
    Vector::Vector()
    {
        for (int i = 0; i < NDIM; i++)
        {
            this->coord[i] = 0;
        }
         
    }
    Vector::Vector(const std::initializer_list<int> IL)
    {
        auto Val = std::data(IL);
        for (int i=0; i < NDIM;i++)
        {
            this->coord[i] = Val[i];
        }
        
    }


    // possibly more
    
        // Public Member functions here
Vector& Vector::operator+=(const Vector& rhs)
{
    for (int i = 0; i < NDIM; i++)
    {
        this->coord[i] += rhs.coord[i];
    }
    return *this;
}
int Vector::operator*(const Vector Vec)
{
    int resultat = 0;
    for (int i = 0; i < NDIM; i++)
    {
        resultat += this->coord[i] * Vec.coord[i];
    }
    return resultat;
}
Vector Vector::operator*(int Nb)
{
    Vector newVec = Vector();
    for (int i = 0; i < NDIM; i++)
    {
        newVec.coord[i] = this->coord[i] * Nb;
    }
    return newVec;
}
Vector& Vector::operator-=(const Vector& rhs)
{
    for (int i = 0; i < NDIM; i++)
    {
        this->coord[i] -= rhs.coord[i];
    }
    return *this;
}
Vector& Vector::operator+=(const int nb)
{
    for (int i = 0; i < NDIM; i++)
    {
        this->coord[i] += nb;
    }
    return *this;
}
Vector& Vector::operator*=(const int nb)
{
    for (int i = 0; i < NDIM; i++)
    {
        this->coord[i] *= nb;
    }
    return *this;
}
    
Vector Vector::operator+(const Vector rhs)
{
    Vector newVec = Vector();
    for (int i = 0; i < NDIM; i++)
    {
        newVec.coord[i] =this->coord[i] + rhs.coord[i];
    }
    return newVec;
}
Vector Vector::operator-(const Vector rhs)
{
    Vector newVec = Vector();
    for (int i = 0; i < NDIM; i++)
    {
        newVec.coord[i] = this->coord[i] - rhs.coord[i];
    }
    return newVec;
}

int& Vector::operator[](size_t i)
{
    return this->coord[i];
}

std::ostream &operator<<(std::ostream& os, const Vector& rhs)
{
    os << "{";
    Vector newVec = Vector(rhs);
    for (int i = 0; i < NDIM-1; i++)
    {
        os << newVec[i]<<",";
    }
    os << newVec[NDIM - 1] << "}";
    return os;
}
// Nonmember function operators go here