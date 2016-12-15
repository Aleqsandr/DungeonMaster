#ifndef	PIXEL_HPP
#define PIXEL_HPP

class Pixel
{
	private:
	int red, green, blue;

	public:
	Pixel(int r, int g, int b);
	Pixel();
	int getred();
	int getgreen();
	int getblue();
	void setred(int a);
	void setgreen(int a);
	void setblue(int a);
	void print();
};

#endif