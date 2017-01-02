#ifndef	MONSTER_HPP
#define MONSTER_HPP

#include <vector>
#include <glimac/glm.hpp>
#include <glimac/Sphere.hpp>
#include "../headers/player.hpp"
#include "../headers/scene.hpp"
#include <GL/glew.h>


using namespace glimac;
using namespace glm;
using namespace std;

	//Pour les monstres, on crée des spheres
	class Monster
	{
		private:
		glimac::Sphere sphere;
		vec3 position;
		int vitesse; //vitesse de deplacement 
		int touch;//compteur pour avoir le nombre de fois où le joueur touche le monstre
		bool kill; //si tuer retourne true 
		GLuint vaomonster;
		GLuint monstertexture;

		public:
		Monster(vec3 _position, int _vitesse, GLfloat radius, GLsizei discLat, GLsizei discLong);

		glimac::Sphere getSphere();
		vec3 getPosition();
		int getVitesse();
		bool getKilled();
		int getTouch();

		void setPosition(vec3 value);
		void setVitesse(int value);
		void setKilled(bool value);

		void drawMonster(GLuint locTexture);

		bool isKilled();

	};


#endif