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
    zoom = 10.0f;

    visionData &vision = this->vision;
    vision.near = 0.1f; // *write down what that value represents*
    vision.far = 1000.0f; // *write down what that value represents*
    vision.Fov = 90.0f; // field of view in °
    vision.aspectRatio = (float)windowSize.y / (float)windowSize.x;
    vision.FovRad = 1.0f / std::tanf(DEG_TO_RAD(vision.Fov * 0.5f)); // *write down what that value represents*

    matrix_4x4 &mat = this->projectionMatrix;
    mat.data[0][0] = vision.aspectRatio * vision.FovRad;
    mat.data[1][1] = vision.FovRad;
    mat.data[2][2] = vision.far / (vision.far - vision.near);
    mat.data[3][2] = (-vision.far * vision.far) / (vision.far - vision.near);
    mat.data[2][3] = 1.0f;
    mat.data[3][3] = 0.0f;

    const float thetaX = 7.0f * 0.5f;
    matrix_4x4 &matRotX = this->rotationX;
    matRotX.data[0][0] = 1;
    matRotX.data[1][1] = cosf(thetaX);
    matRotX.data[1][2] = sinf(thetaX);
    matRotX.data[2][1] = -sinf(thetaX);
    matRotX.data[2][2] = cosf(thetaX);
    matRotX.data[3][3] = 1;
}

void Engine3D::update()
{
    static sf::Clock clock;
    static matrix_4x4 &matRotY = this->rotationY;
    float thetaY = clock.getElapsedTime().asSeconds() * 0.5f;
    static float zoomFactor = 0.5f;

    window.clear();

    matRotY.data[0][0] = cosf(thetaY);
    matRotY.data[2][0] = sinf(thetaY);
    matRotY.data[1][1] = 1;
    matRotY.data[0][2] = -sinf(thetaY);
    matRotY.data[2][2] = cosf(thetaY);
    matRotY.data[3][3] = 1;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) {
        this->zoom += zoomFactor;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X)) {
        this->zoom -= zoomFactor;
    }
}

void Engine3D::draw()
{
    arrayFilled.clear();
    arrayWireframe.clear();

    static std::vector<triangle> trianglesToRaster;
    trianglesToRaster.clear();

    for (auto &tri : object.mesh) {
        triangle triModified = tri;
        Math::applyMatrixOnTriangle(triModified, rotationX);
        Math::applyMatrixOnTriangle(triModified, rotationY);

        for (int i = 0; i < TRIANGLE_POINTS; i++) {
            triModified.points[i].y += 1.0f; // put object down on y
            triModified.points[i].z += this->zoom; // 3 = distance between me and the object
        }
        vector3 normal = Math::getNormalVectorOfTriangle(triModified).normal();

        if ((normal.x * (triModified.points[0].x - camera.x) +
            normal.y * (triModified.points[0].y - camera.y) +
            normal.z * (triModified.points[0].z - camera.z)) < 0.0f) {
            applyLightOnTriangle(normal, triModified);
            trianglesToRaster.push_back(triModified);
        }
    }

    std::sort(trianglesToRaster.begin(), trianglesToRaster.end(), [](const triangle &t1, const triangle &t2) {
        float z1 = (t1.points[0].z + t1.points[1].z + t1.points[2].z) / 3.0f;
        float z2 = (t2.points[0].z + t2.points[1].z + t2.points[2].z) / 3.0f;
        return z1 > z2;
    });

    for (auto &tri : trianglesToRaster) {
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
