#ifndef CUBE_HPP
#define CUBE_HPP

#include <vector>

#include "glimac/common.hpp"

namespace glimac
{

    class Cube
    {
        private: 
        std::vector<ShapeVertex> m_Vertices;

        public:
        void build();
        Cube();

        const ShapeVertex* getDataPointer() const
        {
            return &m_Vertices[0];
        }

        GLsizei getVertexCount() const
        {
            return m_Vertices.size();
        }
    };

}

#endif