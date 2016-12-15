#include <cmath>
#include <vector>
#include <iostream>
#include "glimac/common.hpp"
#include "../headers/cube.hpp"

namespace glimac {

    void Cube::build()
    {
        float vertices[] =
        {
            -1.0, -1.0, -1.0,   1.0, -1.0, -1.0,   1.0, 1.0, -1.0,     // Face 1
            -1.0, -1.0, -1.0,   -1.0, 1.0, -1.0,   1.0, 1.0, -1.0,     // Face 1

            1.0, -1.0, 1.0,   1.0, -1.0, -1.0,   1.0, 1.0, -1.0,       // Face 2
            1.0, -1.0, 1.0,   1.0, 1.0, 1.0,   1.0, 1.0, -1.0,         // Face 2

            -1.0, -1.0, 1.0,   1.0, -1.0, 1.0,   1.0, -1.0, -1.0,      // Face 3
            -1.0, -1.0, 1.0,   -1.0, -1.0, -1.0,   1.0, -1.0, -1.0,    // Face 3

            -1.0, -1.0, 1.0,   1.0, -1.0, 1.0,   1.0, 1.0, 1.0,        // Face 4
            -1.0, -1.0, 1.0,   -1.0, 1.0, 1.0,   1.0, 1.0, 1.0,        // Face 4

            -1.0, -1.0, -1.0,   -1.0, -1.0, 1.0,   -1.0, 1.0, 1.0,     // Face 5
            -1.0, -1.0, -1.0,   -1.0, 1.0, -1.0,   -1.0, 1.0, 1.0,     // Face 5

            -1.0, 1.0, 1.0,   1.0, 1.0, 1.0,   1.0, 1.0, -1.0,         // Face 6
            -1.0, 1.0, 1.0,   -1.0, 1.0, -1.0,   1.0, 1.0, -1.0        // Face 6
        };

        float coordTextureTmp[] =
        { 
            0, 0, 0,   1, 0, 0,    1, 1, 0,     // Face 1
            0, 0, 0,   0, 1, 0,    1, 1, 0,     // Face 1

            0, 0, 0,   1, 0, 0,    1, 1, 0,     // Face 2
            0, 0, 0,   0, 1, 0,    1, 1, 0,     // Face 2

            0, 0, 0,   1, 0, 0,    1, 1, 0,     // Face 3
            0, 0, 0,   0, 1, 0,    1, 1, 0,     // Face 3

            0, 0, 0,   1, 0, 0,    1, 1, 0,     // Face 4
            0, 0, 0,   0, 1, 0,    1, 1, 0,     // Face 4

            0, 0, 0,   1, 0, 0,    1, 1, 0,     // Face 5
            0, 0, 0,   0, 1, 0,    1, 1, 0,     // Face 5

            0, 0, 0,   1, 0, 0,    1, 1, 0,     // Face 6
            0, 0, 0,   0, 1, 0,    1, 1, 0      // Face 6
        };

        // construction des vertex

        for(GLsizei i = 0; i < 108 ; i+=3)
        {
            ShapeVertex vertex;

            vertex.texCoords.x = coordTextureTmp[i];
            vertex.texCoords.y = coordTextureTmp[i+1];

            vertex.normal.x = 0;
            vertex.normal.y = 0;
            vertex.normal.z = 0;

            vertex.position.x = vertices[i];
            vertex.position.y = vertices[i+1];
            vertex.position.z = vertices[i+2];

            m_Vertices.push_back(vertex);
        }
    }
}