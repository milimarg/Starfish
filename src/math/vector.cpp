#include <cmath>
#include "../../includes/math/vector.hpp"

vector3::vector3()
{
    this->x = this->y = this->z = 0;
}

vector3::vector3(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

float vector3::length()
{
    return std::sqrtf(this->dotProduct(*this));
}

vector3 vector3::normal()
{
    return *this / length();
}

vector3 vector3::crossProduct(const vector3 &b)
{
    vector3 v;

    v.x = y * b.z - z * b.y;
    v.y = z * b.x - x * b.z;
    v.z = x * b.y - y * b.x;
    return v;
}

float vector3::dotProduct(const vector3 &b)
{
    return (x * b.x + y * b.y + z * b.z);
}

vector3 &vector3::operator+=(const vector3 &b)
{
    this->x += b.x;
    this->y += b.y;
    this->z += b.z;
    return *this;
}

vector3 &vector3::operator-=(const vector3 &b)
{
    this->x -= b.x;
    this->y -= b.y;
    this->z -= b.z;
    return *this;
}

vector3 &vector3::operator*=(const float &b)
{
    this->x *= b;
    this->y *= b;
    this->z *= b;
    return *this;
}

vector3 &vector3::operator/=(const float &b)
{
    this->x /= b;
    this->y /= b;
    this->z /= b;
    return *this;
}

vector3 vector3::operator+(const vector3 &b)
{
    vector3 r = {0, 0, 0};
    r.x = this->x + b.x;
    r.y = this->y + b.y;
    r.z = this->z + b.z;
    return r;
}

vector3 vector3::operator-(const vector3 &b)
{
    vector3 r = {0, 0, 0};
    r.x = this->x - b.x;
    r.y = this->y - b.y;
    r.z = this->z - b.z;
    return r;
}

vector3 vector3::operator*(const float &b)
{
    vector3 r = {0, 0, 0};
    r.x = this->x * b;
    r.y = this->y * b;
    r.z = this->z * b;
    return r;
}

vector3 vector3::operator/(const float &b)
{
    vector3 r = {0, 0, 0};
    r.x = this->x / b;
    r.y = this->y / b;
    r.z = this->z / b;
    return r;
}
