#ifndef SKYBOX_H
#define SKYBOX_H

#include <iostream>
#include <string>
#include <cerrno>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "../util/bmpread.h"
#include "../textures/textures.h"
#include "Shape.h"

using namespace std;

class Skybox : public Shape {
    public:
        Skybox(
            std::string frontImgPath,
            std::string backImgPath,
            std::string rightImgPath,
            std::string leftImgPath,
            std::string upImgPath,
            std::string downImgPath
        ) {
            this->frontImgPath = frontImgPath;
            this->backImgPath = backImgPath;
            this->rightImgPath = rightImgPath;
            this->leftImgPath = leftImgPath;
            this->upImgPath = upImgPath;
            this->downImgPath = downImgPath;
        };
        ~Skybox() {};

        void draw() {
            glEnable(GL_TEXTURE_2D);
            if (!initialized) {
                front = initTexture(frontImgPath);
                back = initTexture(backImgPath);
                right = initTexture(rightImgPath);
                left = initTexture(leftImgPath);
                up = initTexture(upImgPath);
                down = initTexture(downImgPath);
            }
            initialized = true;

            glPushMatrix();
            glRotatef(180, 0, 0, 1);
                glPushMatrix(); { // +Z
                    drawCubeFace(front);
                }
                glPopMatrix();
                glPushMatrix(); { // +X
                    glRotatef(90, 0, 1, 0);
                    drawCubeFace(left);
                }
                glPopMatrix();
                glPushMatrix(); { // -Z
                    glRotatef(180, 0, 1, 0);
                    drawCubeFace(back);
                }
                glPopMatrix();
                glPushMatrix(); { // -X
                    glRotatef(270, 0, 1, 0);
                    drawCubeFace(right);
                }
                glPopMatrix();
                glPushMatrix(); { // -Y
                    glRotatef(270, 1, 0, 0);
                    drawCubeFace(down);
                }
                glPopMatrix();
                glPushMatrix(); { // +Y
                    glRotatef(90, 1, 0, 0);
                    drawCubeFace(up);
                }
                glPopMatrix();
            glPopMatrix();
        };


        void drawNormal() {
        };

    private:

        GLuint back, front, left, right, up, down;
        std::string frontImgPath;
        std::string backImgPath;
        std::string rightImgPath;
        std::string leftImgPath;
        std::string upImgPath;
        std::string downImgPath;
        bool initialized = false;

        void drawCubeFace(GLuint texture) {
            float size = 500.0f;
            glBindTexture(GL_TEXTURE_2D, texture);
            glBegin(GL_QUADS);
                glNormal3f(0.0, 0.0, 1.0);
                glTexCoord2f(0.0, 0.0); glVertex3f(-size,  size,  size);
                glTexCoord2f(1.0, 0.0); glVertex3f( size,  size,  size);
                glTexCoord2f(1.0, 1.0); glVertex3f( size, -size,  size);
                glTexCoord2f(0.0, 1.0); glVertex3f(-size, -size,  size);
            glEnd();
        }

        GLuint initTexture(const std::string imagePath) {
            GLuint texture;
            bmpread_t bitmap;

            if (!bmpread(imagePath.c_str(), 0, &bitmap)) {
                std::cout << "BMPRead failed, unable to load bitmap" << std::endl; 
            }

            glGenTextures  (1, &texture);
            glBindTexture  (GL_TEXTURE_2D, texture);
            glPixelStorei  (GL_UNPACK_ALIGNMENT, 1);
            glTexImage2D   (
                GL_TEXTURE_2D,
                0,
                GL_RGB,
                bitmap.width,
                bitmap.height,
                0,
                GL_RGB,
                GL_UNSIGNED_BYTE,
                bitmap.data
            );
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexEnvf      (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

            bmpread_free(&bitmap);

            return texture;
        }


};

#endif
