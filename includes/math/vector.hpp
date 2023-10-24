#ifndef INC_3DENGINE_VECTOR_HPP
    #define INC_3DENGINE_VECTOR_HPP
    #include <SFML/Graphics.hpp>
    #include <SFML/System.hpp>

    struct matrix_4x4 {
        float data[4][4] = {0};
    };

    class vector3 {
        public:
            struct {
                float x;
                float y;
                float z;
            };
            struct {
                float pitch;
                float yaw;
                float roll;
            };
            float n[3] = {0};
            vector3();
            vector3(float x, float y, float z);
            float length();
            vector3 normal();
            float dot(const vector3 &b);
            float product(const vector3 &b);
            vector3 crossProduct(const vector3 &b);
            vector3 multiplyToMatrix(matrix_4x4 &mat);
            vector3 &operator+=(const vector3 &b);
            vector3 &operator-=(const vector3 &b);
            vector3 &operator*=(const float &b);
            vector3 &operator/=(const float &b);
            vector3 operator+(const vector3 &b);
            vector3 operator-(const vector3 &b);
            vector3 operator*(const float &b);
            vector3 operator/(const float &b);
    };

    struct triangle {
        vector3 points[3];
        sf::Color color;
    };

    namespace Math {
        void applyMatrixOnTriangle(triangle &tri, matrix_4x4 &mat);
        void scaleTriangleToWindowSize(triangle &tri, sf::Vector2u &windowSize);
    }

#endif //INC_3DENGINE_VECTOR_HPP
