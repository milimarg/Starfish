#ifndef INC_3DENGINE_OBJECT_HPP
    #define INC_3DENGINE_OBJECT_HPP
    #include <iostream>
    #define TRIANGLE_POINTS 3
    #include "../math/vector.hpp"

    class Object {
        public:
            std::vector<triangle> mesh;
            bool displayWireframe;
            void append(triangle &tri);
    };

#endif //INC_3DENGINE_OBJECT_HPP
