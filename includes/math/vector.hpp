#ifndef INC_3DENGINE_VECTOR_HPP
    #define INC_3DENGINE_VECTOR_HPP
    #include <SFML/Graphics.hpp>
    #include <SFML/System.hpp>
    #include "matrix.hpp"

    class vector3 {
        public:
            struct {
                float x = 0;
                float y = 0;
                float z = 0;
                float w = 1;
            };
            struct {
                float yaw;
                float pitch;
                float roll;
            };
            float n[3] = {0};
            vector3();
            vector3(float x, float y, float z);
            float length();
            vector3 normal();
            float dotProduct(const vector3 &b);
            vector3 crossProduct(const vector3 &b);
            vector3 &operator+=(const vector3 &b);
            vector3 &operator-=(const vector3 &b);
            vector3 &operator*=(const float &b);
            vector3 &operator/=(const float &b);
            vector3 operator+(const vector3 &b);
            vector3 operator-(const vector3 &b);
            vector3 operator*(const float &b);
            vector3 operator/(const float &b);
            vector3 multiplyToMatrix(Matrix_4x4 &mat);
    };

    // move triangle-based stuff in another file
    // include that file just here

    struct triangle {
        vector3 points[3];
        sf::Color color;
    };

    namespace Math {
        void applyMatrixOnTriangle(triangle &tri, Matrix_4x4 &mat);
        void scaleTriangleToWindowSize(triangle &tri, sf::Vector2u &windowSize);
    }

#endif //INC_3DENGINE_VECTOR_HPP
