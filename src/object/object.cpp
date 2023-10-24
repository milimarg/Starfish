#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "../../includes/object/object.hpp"

void Object::append(triangle &tri)
{
    mesh.push_back(tri);
}
