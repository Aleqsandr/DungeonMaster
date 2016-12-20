#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <string>
#include <fstream>
#include <glimac/Image.hpp>
#include <glimac/common.hpp>
#include <GL/glew.h>
#include <glimac/glm.hpp>
#include "../headers/monster.hpp"
#include <glimac/Sphere.hpp>


using namespace glimac;
using namespace glm;
using namespace std;

Monster::Monster(vec3 _position, int _vitesse, GLfloat radius, GLsizei discLat, GLsizei discLong):sphere(Sphere(radius, discLat, discLong)){
	position = _position;
	vitesse = _vitesse;
	

	//INITIALIZATION 
    unique_ptr<Image> monst = loadImage("assets/monster.jpg");
    

    // VBO
    GLuint vbomonster;
    glGenBuffers(1, &vbomonster);
    glBindBuffer(GL_ARRAY_BUFFER, vbomonster);
    glBufferData(GL_ARRAY_BUFFER, sphere.getVertexCount()*sizeof(ShapeVertex), sphere.getDataPointer(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // END VBO
    // START VAO

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    const GLuint VERTEX_POSITION_LOCATION = 0;
    const GLuint VERTEX_NORMAL_LOCATION = 1;
    const GLuint VERTEX_TEXTURE_LOCATION = 2;
    glEnableVertexAttribArray(VERTEX_POSITION_LOCATION);
    glEnableVertexAttribArray(VERTEX_NORMAL_LOCATION);
    glEnableVertexAttribArray(VERTEX_TEXTURE_LOCATION);
    glBindBuffer(GL_ARRAY_BUFFER, vbomonster);
    glVertexAttribPointer(VERTEX_POSITION_LOCATION, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*) 0);
    glVertexAttribPointer(VERTEX_NORMAL_LOCATION, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*) offsetof(ShapeVertex, normal));
    glVertexAttribPointer(VERTEX_TEXTURE_LOCATION, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*) offsetof(ShapeVertex, texCoords));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // END VAO

    // START TEXTURES

    GLuint monstertex;
    glGenTextures(1, &monstertex);
    glBindTexture(GL_TEXTURE_2D, monstertex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, monst->getWidth(), monst->getHeight(), 0, GL_RGBA, GL_FLOAT, monst->getPixels()); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    // END TEXTURES


    // END INITIALIZATION CODE

    vector<vec3> rotates;
    for (int i = 0; i < 32; i++)
    {
        rotates.push_back(sphericalRand(3.f));
    }
    vaomonster = vao;
    monstertexture = monstertex;
}

Sphere Monster::getSphere() {return sphere;}
vec3 Monster::getPosition() {return position;}
int Monster::getVitesse() {return vitesse;}
bool Monster::getKilled() {return kill;}
int Monster::getTouch(){return touch;}

void Monster::setPosition(vec3 value) {position = value;}
void Monster::setVitesse(int value) {vitesse = value;}
void Monster::setKilled(bool value) {kill = value;}

void Monster::drawMonster(GLuint locTexture)
{
// application loop :
    // START RENDERING CODE

    glBindVertexArray(vaomonster);
    
    glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, monstertexture);
        glUniform1i(locTexture, 0);
        glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());

    // END RENDERING CODE
}



bool Monster::isKilled()
{
	if(kill)
		return true;
	return false;
}
