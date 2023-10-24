#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "../../includes/math/vector.hpp"
#include "../../includes/object/object.hpp"

void Math::applyMatrixOnTriangle(triangle &tri, matrix_4x4 &mat)
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
