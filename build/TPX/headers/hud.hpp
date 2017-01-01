#ifndef	HUD_HPP
#define HUD_HPP

#include "./cube.hpp"

class Hud
{
	private:
	int hp, keys, keysneeded;

	public:
	Hud();
	~Hud();
	void print();
};

#endif