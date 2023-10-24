#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "../../includes/math/vector.hpp"
#include "../../includes/math/normalization.hpp"

vector3 Math::getNormalVectorOfTriangle(triangle &tri)
{
    vector3 line1 = tri.points[1] - tri.points[0];
    vector3 line2 = tri.points[2] - tri.points[0];
    vector3 normal = line1.crossProduct(line2);
    return (normal);
}
