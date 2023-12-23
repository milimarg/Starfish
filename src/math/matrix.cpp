#include <SFML/System.hpp>
#include <math.h>
#include "../../includes/core/visionStruct.hpp"
#include "../../includes/math/vector.hpp"
#include "../../includes/object/object.hpp"

void Math::applyMatrixOnTriangle(triangle &tri, Matrix_4x4 &mat)
{
    triangle temp;

    for (int i = 0; i < TRIANGLE_POINTS; i++) {
        temp.points[i] = tri.points[i].multiplyToMatrix(mat);
    }
    tri = temp;
}

void Math::scaleTriangleToWindowSize(triangle &tri, sf::Vector2u &windowSize)
{
    for (int i = 0; i < TRIANGLE_POINTS; i++) {
        tri.points[i].x += 1.0f;
        tri.points[i].y += 1.0f;
        tri.points[i].x *= 0.5f * (float)windowSize.x;
        tri.points[i].y *= 0.5f * (float)windowSize.y;
    }
}

vector3 vector3::multiplyToMatrix(Matrix_4x4 &mat)
{
    vector3 temp;
    temp.x = x * mat.data[0][0] + y * mat.data[1][0] + z * mat.data[2][0] + w * mat.data[3][0];
    temp.y = x * mat.data[0][1] + y * mat.data[1][1] + z * mat.data[2][1] + w * mat.data[3][1];
    temp.z = x * mat.data[0][2] + y * mat.data[1][2] + z * mat.data[2][2] + w * mat.data[3][2];
    temp.w = x * mat.data[0][0] + y * mat.data[1][3] + z * mat.data[2][3] + w * mat.data[3][3];
    return temp;
}

Matrix_4x4::Matrix_4x4() {}

void Matrix_4x4::clear()
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            data[i][j] = 0;
        }
    }
}

void Matrix_4x4::createIdentity()
{
    data[0][0] = 1.0f;
    data[1][1] = 1.0f;
    data[2][2] = 1.0f;
    data[3][3] = 1.0f;
}

void Matrix_4x4::applyRotationX(float angle)
{
    data[0][0] = 1.0f;
    data[1][1] = cosf(angle);
    data[1][2] = sinf(angle);
    data[2][1] = -sinf(angle);
    data[2][2] = cosf(angle);
    data[3][3] = 1.0f;
}

void Matrix_4x4::applyRotationY(float angle)
{
    /*
    data[0][0] = cosf(angle);
    data[1][1] = sinf(angle);
    data[1][2] = -sinf(angle);
    data[2][1] = 1.0f;
    data[2][2] = cosf(angle);
    data[3][3] = 1.0f;
    */
    data[0][0] = cosf(angle);
    data[2][0] = sinf(angle);
    data[1][1] = 1.0f;
    data[0][2] = -sinf(angle);
    data[2][2] = cosf(angle);
    data[3][3] = 1.0f;
}

void Matrix_4x4::applyRotationZ(float angle)
{
    /*
     * data[0][0] = cosf(angle);
    data[1][1] = sinf(angle);
    data[1][2] = -sinf(angle);
    data[2][1] = cosf(angle);
    data[2][2] = 1.0f;
    data[3][3] = 1.0f;
    */
    data[0][0] = cosf(angle);
    data[1][0] = -sinf(angle);
    data[0][1] = sinf(angle);
    data[1][1] = cosf(angle);
    data[2][2] = 1.0f;
    data[3][3] = 1.0f;
}

void Matrix_4x4::applyTranslation(float x, float y, float z)
{
    this->createIdentity();
    data[3][0] = x;
    data[3][1] = y;
    data[3][2] = z;
}

void Matrix_4x4::createProjection(visionData &vision)
{
    data[0][0] = vision.aspectRatio * vision.FovRad;
    data[1][1] = vision.FovRad;
    data[2][2] = vision.far / (vision.far - vision.near);
    data[3][2] = (-vision.far * vision.far) / (vision.far - vision.near);
    data[2][3] = 1.0f;
    data[3][3] = 0.0f;
}

Matrix_4x4 Matrix_4x4::multiplyToMatrix(Matrix_4x4 &mat2)
{
    Matrix_4x4 temp;

    for (int col = 0; col < 4; col++) {
        for (int row = 0; row < 4; row++) {
            temp.data[row][col] = data[row][0] * mat2.data[0][col] + data[row][1] * mat2.data[1][col] + data[row][2] * mat2.data[2][col] + data[row][3] * mat2.data[3][col];
        }
    }
    return temp;
}
