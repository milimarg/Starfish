#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <fstream>
#include <strstream>
#include "../../includes/core/engineCore.hpp"

bool Engine3D::loadObjectFromFile(std::string filename)
{
    std::ifstream f(filename);

    if (!f.is_open()) {
        std::cerr << "File couldn't be opened." << std::endl;
        return false;
    }
    Object object;
    std::vector<vector3> verts;
    char line[MAX_CONFIG_FILE_LINE_LENGTH];
    char trash;

    while (!f.eof()) {
        f.getline(line, MAX_CONFIG_FILE_LINE_LENGTH);
        std::strstream s;
        s << line;
        if (line[0] == 'v') {
            vector3 v;
            s >> trash >> v.x >> v.y >> v.z;
            verts.push_back(v);
        }
        if (line[0] == 'f') {
            int f[3];
            s >> trash >> f[0] >> f[1] >> f[2];
            triangle tri = {verts[f[0] - 1], verts[f[1] - 1], verts[f[2] - 1]};
            object.append(tri);
        }
    }
    this->object = object;
    return true;
}
