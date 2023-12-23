#include <cmath>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "../../includes/math/vector.hpp"
#include "../../includes/core/engineCore.hpp"

Engine3D::Engine3D(sf::RenderWindow &window) : window(window)
{
    windowSize = window.getSize();
    arrayFilled.setPrimitiveType(sf::PrimitiveType::Triangles);
    arrayWireframe.setPrimitiveType(sf::PrimitiveType::Lines);
    camera = vector3(0.0f, 0.0f, 0.0f);

    vision.near = 0.1f;
    vision.far = 1000.0f;
    vision.Fov = 90.0f;
    vision.aspectRatio = (float)windowSize.y / (float)windowSize.x;
    vision.FovRad = 1.0f / tanf(DEG_TO_RAD(vision.Fov * 0.5f));

    matTranslation.applyTranslation(0.0f, 0.0f, 10.0f);
    projectionMatrix.createProjection(vision);
}

void Engine3D::update()
{
    static sf::Clock clock;
    static Matrix_4x4 rotationX;
    static Matrix_4x4 rotationZ;
    float theta = clock.getElapsedTime().asSeconds();
    static sf::Vector3f move = {0.0f, 0.0f, 20.0f};
    Matrix_4x4 translation;

    window.clear();
    rotationZ.applyRotationZ(theta);
    rotationX.applyRotationX(theta);
    matWorld.createIdentity();
    matWorld = rotationZ.multiplyToMatrix(rotationX);

    // X MOVE

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        move.x -= 0.1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
        move.x += 0.1;
    }

    // Y MOVE

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        move.y -= 0.1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        move.y += 0.1;
    }

    // Z MOVE

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        move.z -= 0.1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
        move.z += 0.1;
    }
    translation.applyTranslation(move.x, move.y, move.z);
    matWorld = matWorld.multiplyToMatrix(translation);
}

void Engine3D::draw()
{
    arrayFilled.clear();
    arrayWireframe.clear();

    static std::vector<triangle> trianglesToSort;
    trianglesToSort.clear();

    for (auto &tri : object.mesh) {
        triangle triModified = tri;
        for (int j = 0; j < TRIANGLE_POINTS; j++) {
            triModified.points[j] = triModified.points[j].multiplyToMatrix(matWorld);
        }
        vector3 normal = Math::getNormalVectorOfTriangle(triModified).normal();

        vector3 cameraRay = triModified.points[0] - camera;
        if (normal.dotProduct(cameraRay) < 0.0f) {
            applyLightOnTriangle(normal, triModified);
            trianglesToSort.push_back(triModified);
        }
    }

    std::sort(trianglesToSort.begin(), trianglesToSort.end(), [](const triangle &t1, const triangle &t2) {
        float z1 = (t1.points[0].z + t1.points[1].z + t1.points[2].z) / 3.0f;
        float z2 = (t2.points[0].z + t2.points[1].z + t2.points[2].z) / 3.0f;
        return z1 > z2;
    });

    for (auto &tri : trianglesToSort) {
        static sf::Vector2f tris[3];

        this->object.displayWireframe = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);
        for (int i = 0; i < TRIANGLE_POINTS; i++) {
            tris[i] = sf::Vector2f(tri.points[i].x, tri.points[i].y);
            this->arrayFilled.append(sf::Vertex(tris[i], tri.color));
        }
        if (this->object.displayWireframe) {
            this->arrayWireframe.append(sf::Vertex(tris[0], sf::Color::Blue));
            this->arrayWireframe.append(sf::Vertex(tris[1], sf::Color::Blue));
            this->arrayWireframe.append(sf::Vertex(tris[1], sf::Color::Blue));
            this->arrayWireframe.append(sf::Vertex(tris[2], sf::Color::Blue));
            this->arrayWireframe.append(sf::Vertex(tris[2], sf::Color::Blue));
            this->arrayWireframe.append(sf::Vertex(tris[0], sf::Color::Blue));
        }
    }
    window.draw(arrayFilled);
    if (object.displayWireframe) {
        window.draw(arrayWireframe);
    }
    window.display();
}
