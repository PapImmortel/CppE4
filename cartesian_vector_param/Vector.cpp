#include "Vector.hh"
#pragma once



#include "config.h"

    // Add suitable constructors
    Vector::Vector()
    {
        x = 0;
        y = 0;
#if (NDIM==3)
        z = 0;
#endif // 
         
    }
    Vector::Vector(const std::initializer_list<int> IL)
    {
        auto Val = std::data(IL);
        this->x = Val[0];
        this->y = Val[1];
#if NDIM==3
        this->z = Val[2];
#endif
    }
#if NDIM==2
    Vector::Vector(int px, int py)
    {
        this->x = px;
        this->y = py;
    }
#elif(NDIM==3)
    Vector::Vector(int px, int py, int pz)
    {
        this->x = px;
        this->y = py;
        this->z = pz;
    }
#endif
    // possibly more
    const int  Vector::getX() { return this->x; } 
    const int  Vector::getY() { return this->y; }
#if(NDIM==3)
    const int Vector::getZ() { return this->z; }
#endif
        // Public Member functions here
        Vector& Vector::operator+=(const Vector& rhs)
    {
        this->x += rhs.x;
        this->y += rhs.y;
#if(NDIM==3)
        this->z += rhs.z;
#endif
        return *this;
    }
    int Vector::operator*(const Vector Vec)
    {
        int res = this->x * Vec.x;
        res += this->y * Vec.y;
#if(NDIM==3)
        res += this->z * Vec.z;
#endif
        return res;
    }
    Vector Vector::operator*(int Nb)
    {
#if NDIM==2
        return Vector(this->x * Nb, this->y * Nb);
#elif NDIM == 3
        return Vector(this->x * Nb, this->y * Nb, this->z * Nb);
#endif
    }
    Vector& Vector::operator-=(const Vector& rhs)
    {
        this->x -= rhs.x;
        this->y -= rhs.y;
#if(NDIM==3)
        this->z -= rhs.z;
#endif
        return *this;
    }
    Vector& Vector::operator+=(const int nb)
    {
        this->x += nb;
        this->y += nb;
#if(NDIM==3)
        this->z += nb;
#endif
        return *this;
    }
    Vector& Vector::operator*=(const int nb)
    {
        this->x *= nb;
        this->y *= nb;
#if(NDIM==3)
        this->z *= nb;
#endif
        return *this;
    }
    /* Vector& operator*=(const Vector& rhs)
     {
 #if(NDIM==3)

 #endif
     }*/
    Vector Vector::operator+(const Vector rhs)
    {
        Vector res = rhs;
        res.x += this->x;
        res.y += this->y;
#if(NDIM==3)
        res.z += this->z;
#endif 
        return res;
    }
    Vector Vector::operator-(const Vector rhs)
    {
        Vector res = rhs;
        res.x -= this->x;
        res.y -= this->y;
#if(NDIM==3)
        res.z -= this->z;
#endif 
        return res;
    }

    int& Vector::operator[](size_t i)
    {
        if (i == 0) { int& a = (this->x); return a; }
        if (i == 1) { int& a = (this->y); return a; }
#if (NDIM==3)
        if (i == 2) { int& a = (this->z); return a; }
        int b = -1;
        int& a = b ;
        return a;
#endif
    // More to go
}

std::ostream &operator<<(std::ostream& os,  const Vector &rhs)
{
    Vector res = rhs;
    #if (NDIM==3)
        os << "(" << (std::to_string(res.getX())) + "," + std::to_string(res.getY()) + "," + std::to_string(res.getZ()) + ")"; 
        return os;
    #elif (NDIM==2)
        os << "(" << (std::to_string(res.getX())) + "," + std::to_string(res.getY()) + ')';
        return os;
    #endif

}
// Nonmember function operators go here