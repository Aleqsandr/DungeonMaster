#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <string>
#include <fstream>

#include "../headers/scene.hpp"
#include "../headers/pixel.hpp"

using namespace std;

Scene::Scene()
{

}

vector<Pixel> Scene::getpixels(){return pixels;}
Pixel Scene::getpixel(int a){return pixels[a];}
float Scene::getzones(){return zones;}

void Scene::loadmap()
{
	std::ifstream file("assets/ultimatemap.ppm");
    if (file)
    {
    	cout << "YES, the map has been loading successfully." << endl;
    	string content;
    	getline(file, content);
        getline(file, content);
        getline(file, content);
        int i = 0;
        string nbzones = "";
        while (content[i] != ' ')
        {
            nbzones += content[i];
            i++;
        }
        zones = stoi(nbzones);
        width = stoi(nbzones);
        height = width;
        getline(file, content);
        Pixel a = Pixel();
        for (int j = 0; j < zones * zones; j++)
        {
            getline(file, content);
            a.setred(stoi(content));
            getline(file, content);
            a.setgreen(stoi(content));
            getline(file, content);
            a.setblue(stoi(content));
            pixels.push_back(a);
        }
        file.close();
    }
    else cerr << "Impossible de lire de fichier." << endl;
}

void Scene::drawmap()
{

}

void Scene::print()
{
    for (int i = 0; i < pixels.size(); i++)
    {
        cout << pixels[i].getred() << " " << pixels[i].getgreen() << " " << pixels[i].getblue() << endl;
    }
}

int Scene::getwidth()
{
    return width;
}

int Scene::getheight()
{
    return height;
}