﻿// Is_Primme.cpp : définit le point d'entrée de l'application.


#include "is_prime_prog.h"
#include <string>
#include <cmath>

 

bool IsPrime(int n)
{
    if (n < 2)
    {
        return false;
    }
    if (n % 2 == 0)
    {
        if (n == 2) { return true; }
        else { return false; }
    }
    int d = 3;
    float m = sqrt(n);
    while (d <= m)
    {
        if (n % d == 0)
        {
            return false;
        }
        else
        {
            d = d + 2;
        }

    }
    return true;
}
int i;
int main()
{


    std::cout << "donne un chiffre " << std::endl;

    while (std::cin)
    {
        std::cin >> i;
        if (IsPrime(i))
        {
            std::string res = std::to_string(i);
            res = res + " is a Prime : True";
            std::cout << res << std::endl;
        }
        else
        {
            std::string res = std::to_string(i);
            res = res + " is a Prime : False";
            std::cout << res << std::endl;
        }

    }
}