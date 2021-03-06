#ifndef	SCENE_HPP
#define SCENE_HPP

#include <cstdlib>
#include <vector>
#include <glimac/glm.hpp>
#include "pixel.hpp"

class Scene
{
	private:
	std::vector<Pixel> pixels;
	float zones;
	int height;
	int width;

	public:

	Scene();
	std::vector<Pixel> getpixels();
	Pixel getpixel(int a);
	float getzones();
	int getwidth();
	int getheight();
	void loadmap();
	void drawmap();
	void print();

	glm::vec2 currentpixel;
	void pixelup();
	void pixeldown();
	void pixelright();
	void pixelleft();

};

#endif