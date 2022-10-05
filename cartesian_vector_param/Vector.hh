#pragma once

#include <ostream>
#include <initializer_list>
#include <string>
#include "config.h"

class Vector
{
public:
    // DO NOT CHANGE THIS
    Vector(const Vector&) = default;
    Vector& operator=(const Vector&) = default;
    ~Vector() = default;
    //

    // Add suitable constructors
    Vector();
    Vector(/*args*/std::initializer_list<int> IL);
#if NDIM==2
    Vector(int px, int py);

#elif NDIM==3

    Vector(int px, int py, int pz);

    // possibly more
#endif
// Public Member functions here
    Vector& operator+=(const Vector& rhs);
    int operator*(const Vector Vec);
    Vector operator*(int Nb);
    Vector& operator-=(const Vector& rhs);
    Vector operator+(const Vector rhs);
    Vector operator-(const Vector rhs);
    Vector& operator+=(const int nb);
    Vector& operator*=(const int nb);
    int& operator[](size_t i);
    const int  getX();
    const int  getY();
#if NDIM==3
    const int  getZ();
#endif

    // More to go

private:
    // Private Member functions here
    int x;
    int y;
#if NDIM==3
    int z;
#endif
    // Member variables are ALWAYS private, and they go here
};
std::ostream &operator<<(std::ostream& os, const Vector &rhs);
// Nonmember function operators go here