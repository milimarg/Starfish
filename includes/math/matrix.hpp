#ifndef INC_3DENGINE_MATRIX_HPP
    #define INC_3DENGINE_MATRIX_HPP
    #include "../core/visionStruct.hpp"

    class Matrix_4x4 {
        public:
            float data[4][4] = {0};
            Matrix_4x4();
            void clear();
            void createIdentity();
            void applyRotationX(float angle);
            void applyRotationY(float angle);
            void applyRotationZ(float angle);
            void applyTranslation(float x, float y, float z);
            void createProjection(visionData &vision);
            Matrix_4x4 multiplyToMatrix(Matrix_4x4 &mat);
    };

#endif //INC_3DENGINE_MATRIX_HPP
