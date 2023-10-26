#ifndef INC_3DENGINE_ENGINECORE_HPP
    #define INC_3DENGINE_ENGINECORE_HPP
    #include "visionStruct.hpp"
    #include "../object/object.hpp"
    #include "../math/normalization.hpp"
    #define DEG_TO_RAD(deg) deg / 180.0f * 3.141592f
    #define MAX_CONFIG_FILE_LINE_LENGTH 128

    class Engine3D {
        public:
            Engine3D(sf::RenderWindow &window);
            void update();
            void draw();
            bool loadObjectFromFile(std::string filename);
        private:
            sf::VertexArray arrayFilled;
            sf::VertexArray arrayWireframe;
            Object object;
            visionData vision;
            Matrix_4x4 projectionMatrix;
            sf::Vector2u windowSize;
            sf::RenderWindow &window;
            Matrix_4x4 rotationX;
            Matrix_4x4 rotationZ;
            Matrix_4x4 matTranslation;
            Matrix_4x4 matWorld;
            vector3 camera;
            float zoom;
            void applyLightOnTriangle(vector3 &normal, triangle &tri);
    };

#endif //INC_3DENGINE_ENGINECORE_HPP
