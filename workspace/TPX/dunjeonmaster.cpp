#include <glimac/SDLWindowManager.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Program.hpp>
#include <glimac/Image.hpp>
#include <glimac/Sphere.hpp>
#include <GL/glew.h>
#include <glimac/glm.hpp>
#include <cstddef>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>

#include "headers/scene.hpp"
#include "headers/pixel.hpp"
#include "headers/cube.hpp"
#include "headers/player.hpp"

using namespace glimac;
using namespace std;
using namespace glm;

int main(int argc, char** argv)
{
    // SDL INITIALIZATION + WINDOW OPENING

    SDLWindowManager windowManager(800, 600, "DUNJEON MASTER REHO/COUAVOUX");

    // GLEW INITIALIZATION FOR OPENGL3+ SUPPORT

    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    FilePath applicationPath(argv[0]);
    Program program =   loadProgram(applicationPath.dirPath() + "shaders/" + argv[1],
                        applicationPath.dirPath() + "shaders/" + argv[2]);
    program.use();

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    // START INITIALIZATION CODE

    Scene s = Scene();
    s.Scene::loadmap();
    Cube c = Cube();
    Sphere skybox = Sphere(1000, 32, 32);
    Player player = Player();
    player.camera.moveTo(vec3(20, 0, 0));

    unique_ptr<Image> img = loadImage("assets/texture.jpg");

    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->getWidth(), img->getHeight(), 0, GL_RGBA, GL_FLOAT, img->getPixels());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    unique_ptr<Image> sky = loadImage("assets/skybox.jpg");

    GLuint skytex;
    glGenTextures(1, &skytex);
    glBindTexture(GL_TEXTURE_2D, skytex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sky->getWidth(), sky->getHeight(), 0, GL_RGBA, GL_FLOAT, sky->getPixels());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

        // VBO
        
        GLuint vbo;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER,c.getVertexCount() * sizeof(ShapeVertex), c.getDataPointer(), GL_STATIC_DRAW);
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
        glEnableVertexAttribArray(VERTEX_TEXTURE_LOCATION);
        glEnableVertexAttribArray(VERTEX_NORMAL_LOCATION);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glVertexAttribPointer(VERTEX_POSITION_LOCATION, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*) 0);
        glVertexAttribPointer(VERTEX_NORMAL_LOCATION, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*) offsetof(ShapeVertex, normal));
        glVertexAttribPointer(VERTEX_TEXTURE_LOCATION, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*) offsetof(ShapeVertex, texCoords));
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        // END VAO

    GLint uMVPMatrix    = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
    GLint uMVMatrix     = glGetUniformLocation(program.getGLId(), "uMVMatrix");
    GLint uNormalMatrix = glGetUniformLocation(program.getGLId(), "uNormalMatrix");
    GLint locTexture    = glGetUniformLocation(program.getGLId(), "uTexture");

    glm::mat4 ProjMatrix, MVMatrix, NormalMatrix;
    ProjMatrix = perspective(radians(70.f), 800.f/600.f, 0.1f, 100.f);
    MVMatrix = mat4(1.f);
    MVMatrix = player.camera.getViewMatrix() * glm::translate(MVMatrix, vec3(0.f, 0.f, -5.f));
    NormalMatrix = transpose(inverse(MVMatrix));

    // END INITIALIZATION CODE

    glEnable(GL_DEPTH_TEST);
    float vitesseL = 0, vitesseF = 0, rotationL = 0;

    int i = 0;

    bool done = false;
    while(!done)
    {
        SDL_Event e;
        while(windowManager.pollEvent(e))
        {
            if (e.type == SDL_QUIT)
            {
                done = true; // Leave the loop after this iteration
            }
            // else if (e.type == SDL_MOUSEMOTION)
            // {
            //     if (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(SDL_BUTTON_LEFT))
            //     {
            //         player.camera.rotateLeft(-e.motion.xrel * 0.2);
            //         player.camera.rotateUp(-e.motion.yrel * 0.2);
            //     }
            // }
            else if (e.type == SDL_KEYDOWN)
            {
                switch(e.key.keysym.sym)
                {
                    case SDLK_z:
                        vitesseF = 0.02;
                        break;
                    case SDLK_q:
                        vitesseL = 0.02;
                        break;
                    case SDLK_s:
                        vitesseF = -0.02;
                        break;
                    case SDLK_d:
                        vitesseL = -0.02;
                        break;
                    case SDLK_a:
                        rotationL = 0.4;
                        break;
                    case SDLK_e:
                        rotationL = -0.4;
                        break;
                    default:
                        break;
                }

            }
            else if (e.type == SDL_KEYUP)
            {
                Uint8* keyState = SDL_GetKeyState(nullptr);
                switch(e.key.keysym.sym)
                {
                case SDLK_z:
                    if(!keyState[SDLK_s])
                        vitesseF = 0;
                    break;
                case SDLK_s:
                    if(!keyState[SDLK_w])
                        vitesseF = 0;
                    break;
                case SDLK_q:
                    if(!keyState[SDLK_d])
                        vitesseL = 0;
                    break;
                case SDLK_d:
                    if(!keyState[SDLK_a])
                        vitesseL = 0;
                    break;
                case SDLK_a:
                    if(!keyState[SDLK_e])
                        rotationL = 0;
                case SDLK_e:
                    if(!keyState[SDLK_a])
                        rotationL = 0;
                case SDLK_ESCAPE:
                    break;
                default:
                    break;
                }
            }
        }
        
        player.camera.moveFront(vitesseF);
        player.camera.moveLeft(vitesseL);
        player.camera.rotateLeft(rotationL);

        // START RENDERING CODE

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBindVertexArray(vao);

        ProjMatrix = perspective(glm::radians(70.f), 800.f/600.f, 0.1f, 100.f);

        for (int i = 0; i < s.getwidth(); i++)
        {
            for (int j = 0; j < s.getheight(); j++)
            {
                if (s.getpixel(s.getwidth()*j + i).getred() == 0 && s.getpixel(s.getwidth()*j + i).getgreen() == 0 && s.getpixel(s.getwidth()*j + i).getblue() == 0)
                {
                    MVMatrix = player.camera.getViewMatrix() * translate(mat4(1.f), vec3(2*i, 0, (-2*j)-5));
                    glUniformMatrix4fv(uMVPMatrix,    1, GL_FALSE, value_ptr(ProjMatrix * MVMatrix));
                    glUniformMatrix4fv(uMVMatrix,     1, GL_FALSE, value_ptr(MVMatrix));
                    glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, value_ptr(NormalMatrix));
                    glUniform1i(locTexture, 0);
                    glBindTexture(GL_TEXTURE_2D, tex);

                    glDrawArrays(GL_TRIANGLES, 0, c.getVertexCount());
                }
            }
        }

        glBindTexture(GL_TEXTURE_2D, 0);
        glBindVertexArray(0);

        windowManager.swapBuffers();

        // END RENDERING CODE
    }

    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    return EXIT_SUCCESS;
}
