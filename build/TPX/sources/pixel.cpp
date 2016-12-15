#include <iostream>
#include <string>
#include <fstream>

#include "../headers/pixel.hpp"

using namespace std;

Pixel::Pixel()
{
	red = 0;
	green = 0;
	blue = 0;
}

Pixel::Pixel(int r, int g, int b)
{
	red = r;
	green = g;
	blue = b;
}

int Pixel::getred(){return red;}
int Pixel::getgreen(){return green;}
int Pixel::getblue(){return blue;}
void Pixel::setred(int a){red = a;}
void Pixel::setgreen(int a){green = a;}
void Pixel::setblue(int a){blue = a;}

void Pixel::print()
{
	std::cout << "PIXEL VALUES : " << red << " " << green << " " << blue << "." << std::endl;
}