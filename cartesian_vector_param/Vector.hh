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
    Vector(std::initializer_list<value> IL);

    // possibly more
// Public Member functions here
    Vector& operator+=(Vector const& rhs);
    value operator*(Vector Vec);
    Vector operator*(value Nb);
    Vector& operator-=(Vector const& rhs);
    Vector operator+(Vector rhs);
    Vector operator-(Vector rhs);
    Vector& operator+=(value nb);
    Vector& operator*=(value nb);
    value& operator[](size_t i);
    

    // More to go

private:
    // Private Member functions here
    value coord[NDIM];
    // Member variables are ALWAYS private, and they go here
};
std::ostream &operator<<(std::ostream& os, Vector const&rhs);
// Nonmember function operators go here