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
    return std::sqrtf(this->product(*this));
}

vector3 vector3::normal()
{
    return *this / length();
}

float vector3::dot(const vector3 &b)
{
    // dot

    return 0.0f;
}

float vector3::product(const vector3 &b)
{
    return (x * b.x + y * b.y + z * b.z);
}

vector3 vector3::crossProduct(const vector3 &b)
{
    vector3 v;

    v.x = y * b.z - z * b.y;
    v.y = z * b.x - x * b.z;
    v.z = x * b.y - y * b.x;
    return v;
}

vector3 vector3::multiplyToMatrix(matrix_4x4 &mat)
{
    vector3 temp;
    temp.x = x * mat.data[0][0] + y * mat.data[1][0] + z * mat.data[2][0] + mat.data[3][0];
    temp.y = x * mat.data[0][1] + y * mat.data[1][1] + z * mat.data[2][1] + mat.data[3][1];
    temp.z = x * mat.data[0][2] + y * mat.data[1][2] + z * mat.data[2][2] + mat.data[3][2];
    float w = x * mat.data[0][3] + y * mat.data[1][3] + z * mat.data[2][3] + mat.data[3][3];

    if (w != 0.0f) {
        temp /= w;
    }
    return temp;
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
