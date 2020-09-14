/*
 * 2D/3D vector math implementation
 * 
 * Contains implementation for vectors useful to 
 * make a 2.5D game.
 *
 * Author: Marcos Lerones
 */
#pragma once

#include <math.h>

namespace shp
{
    struct Vector3
    {
        double x, y, z;

        // Constructors
        Vector3() : x(0), y(0), z(0) {}
        Vector3(const double x, const double y, const double z)
            : x(x), y(y), z(z) {}
        Vector3(const double angle)
            : x(cos(angle)), y(0), z(sin(angle)) {}

        // Basis Directions 
        const static Vector3 X;
        const static Vector3 Y;
        const static Vector3 Z;  

        // Null vector
        const static Vector3 ZEROV;      

        // Assignment
        inline Vector3& operator=(const Vector3& other)
        {
            if (this != &other) {
                x = other.x;
                y = other.y;
                z = other.z;
            }
            return *this;
        }
        
        // Addition
        inline Vector3& operator+=(const Vector3& rhs)
        {
            x += rhs.x;
            y += rhs.y;
            z += rhs.z;
            return *this;
        }
        inline friend Vector3 operator+(Vector3 lhs, const Vector3& rhs)
        {
            lhs += rhs;
            return lhs;
        }

        // Substraction
        inline Vector3& operator-=(const Vector3& rhs)
        {
            x -= rhs.x;
            y -= rhs.y;
            z -= rhs.z;
            return *this;
        }
        inline friend Vector3 operator-(Vector3 lhs, const Vector3& rhs)
        {
            lhs -= rhs;
            return lhs;
        }

        // Multiplication by a scalar
        inline Vector3& operator*=(const double rhs)
        {
            x *= rhs;
            y *= rhs;
            z *= rhs;
            return *this;
        }
        inline friend Vector3 operator*(Vector3 lhs, const double rhs)
        {
            lhs *= rhs;
            return lhs;
        }
        inline friend Vector3 operator*(const double lhs, Vector3 rhs)
        {
            rhs *= lhs;
            return rhs;
        }

        // Division by a scalar
        inline Vector3& operator/=(const double rhs)
        {
            x /= rhs;
            y /= rhs;
            z /= rhs;
            return *this;
        }
        inline friend Vector3 operator/(Vector3 lhs, const double rhs)
        {
            lhs /= rhs;
            return lhs;
        }

        // Dot product
        inline friend double operator*(const Vector3& lhs, const Vector3& rhs)
        {
            return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
        }

        // Equality
        inline bool operator==(const Vector3& rhs)
        {
            return x == rhs.x && y == rhs.y && z == rhs.z;
        }
        inline bool operator!=(const Vector3& rhs)
        {
            return !(*this == rhs);
        }
        inline bool isZero()
        {
            return x == 0 && y == 0 && z == 0;
        }

        // Get squared magnitude
        inline double squareNorm()
        {
            return (*this)*(*this);
        }

        // Get magnitude
        inline double norm()
        {
            return sqrt(squareNorm());
        }

        // Normalize vector
        inline void normalize()
        {
            double n = norm();
            if (n > 0) 
                (*this) /= n;
        }

        // Distance to another vector
        inline double distance(const Vector3& other)
        {
            return (*this - other).norm();
        }

        // 2D cross product (using x and z)
        inline double cross2D(const Vector3& other)
        {
            return x*other.z - z*other.x;
        }

        inline double orient2D(const Vector3& a, const Vector3& b)
        {
            return (a - (*this)).cross2D(b - (*this));
        }
    };
};