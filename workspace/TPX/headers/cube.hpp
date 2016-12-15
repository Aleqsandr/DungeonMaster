#ifndef CUBE_HPP
#define CUBE_HPP

#include <vector>

#include "glimac/common.hpp"

namespace glimac
{

    // cube centré en (0, 0, 0) dans le repère local
    // axe vertical (0, 1, 0) et axes transversaux (1, 0, 0) et (0, 0, 1)

    class Cube
    {
        void build();

        public:

        // constructeur - > alloue le tableau de données et construit les attributs des vertex
        Cube()
        {
            build(); // construction (voir le .cpp)
        }

        // renvoie le pointeur vers les données
        const ShapeVertex* getDataPointer() const
        {
            return &m_Vertices[0];
        }

        // renvoie le nombre de vertex
        GLsizei getVertexCount() const
        {
            return m_Vertices.size();
        }

        // void drawCube(int type, vec3, )

        private:
            
        std::vector<ShapeVertex> m_Vertices;
    };

}

#endif