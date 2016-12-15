#include <math.h>
#include <glimac/glm.hpp>
#include <glimac/FreeflyCamera.hpp>

namespace glimac {

    FreeflyCamera::FreeflyCamera() : m_Position(glm::vec3(0,0,0)), m_fTheta(0), m_fPhi(M_PI)
    {
        FreeflyCamera::computeDirectionVectors();
    }

    void FreeflyCamera::moveFront(float t)
    {
        m_Position += t * m_FrontVector;
    }

    void FreeflyCamera::moveLeft(float t)
    {
        m_Position += t * m_LeftVector;
    }

    void FreeflyCamera::rotateLeft(float degrees)
    {
        float radians = degrees / 180 * M_PI;
        m_fPhi += radians;
        FreeflyCamera::computeDirectionVectors();
    }

    void FreeflyCamera::rotateUp(float degrees)
    {
        float radians = degrees / 180 * M_PI;
        m_fTheta += radians;
        FreeflyCamera::computeDirectionVectors();
    }

    void FreeflyCamera::computeDirectionVectors()
    {
        m_FrontVector = glm::vec3(cos(m_fTheta) * sin(m_fPhi), sin(m_fTheta), cos(m_fTheta) * cos(m_fPhi));
        m_LeftVector = glm::vec3(sin(m_fPhi+(M_PI*0.5)), 0, cos(m_fPhi+(M_PI*0.5)));
        m_UpVector = glm::cross(m_FrontVector, m_LeftVector);

    }

    glm::mat4 FreeflyCamera::getViewMatrix() const
    {
        return glm::lookAt(m_Position, m_Position + m_FrontVector, m_UpVector);
    }

    void FreeflyCamera::moveTo(glm::vec3 position)
    {
        m_Position.x = position.x;
        m_Position.y = position.y;
        m_Position.z = position.z;
    }

}