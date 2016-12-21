#include "glm.hpp"

namespace glimac {


class FreeflyCamera {

public:
    FreeflyCamera();
    void moveFront(float t); 
	void moveLeft(float t);
    void rotateLeft(float degrees); 
    void rotateUp(float degrees);
    void computeDirectionVectors();
    glm::mat4 getViewMatrix() const;
    void moveTo(glm::vec3 position);
    glm::vec3 getPosition();
    void setPositionX(float a);
    void setPositionY(float a);
    void setPositionZ(float a);
	glm::vec3 m_FrontVector;
	float m_fPhi;
	float m_fTheta;
	float angle;

private:
	glm::vec3 m_Position;
	glm::vec3 m_LeftVector;
	glm::vec3 m_UpVector;
};
    
}