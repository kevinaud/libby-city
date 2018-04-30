#ifndef SKYBOX_H
#define SKYBOX_H

#include <iostream>
#include <cerrno>
#include "Shape.h"


class Skybox : public Shape {
    public:
        Skybox(
            char const * frontImgPath,
            char const * backImgPath,
            char const * rightImgPath,
            char const * leftImgPath,
            char const * upImgPath,
            char const * downImgPath
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
            /* glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); */
            /* glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); */
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
                /* glPushMatrix(); { // +X */
                /*     glRotatef(90, 0, 1, 0); */
                /*     drawCubeFace(left); */
                /* } */
                /* glPopMatrix(); */
                /* glPushMatrix(); { // -Z */
                /*     glRotatef(180, 0, 1, 0); */
                /*     drawCubeFace(back); */
                /* } */
                /* glPopMatrix(); */
                /* glPushMatrix(); { // -X */
                /*     glRotatef(270, 0, 1, 0); */
                /*     drawCubeFace(right); */
                /* } */
                /* glPopMatrix(); */
                /* glPushMatrix(); { // -Y */
                /*     glRotatef(270, 1, 0, 0); */
                /*     drawCubeFace(down); */
                /* } */
                /* glPopMatrix(); */
                /* glPushMatrix(); { // +Y */
                /*     glRotatef(90, 1, 0, 0); */
                /*     drawCubeFace(up); */
                /* } */
                /* glPopMatrix(); */
            glPopMatrix();
        };


        void drawNormal() {
        };

    private:

        GLuint back, front, left, right, up, down;
        char const * frontImgPath;
        char const * backImgPath;
        char const * rightImgPath;
        char const * leftImgPath;
        char const * upImgPath;
        char const * downImgPath;
        bool initialized = false;

        void drawCubeFace(GLuint texture) {
            float size = 2.0f;
            glBindTexture(GL_TEXTURE_2D, texture);
            glBegin(GL_QUADS);
                glNormal3f(0.0, 0.0, 1.0);
                glTexCoord2f(0.0, 0.0); glVertex3f(-size,  size,  size);
                glTexCoord2f(1.0, 0.0); glVertex3f( size,  size,  size);
                glTexCoord2f(1.0, 1.0); glVertex3f( size, -size,  size);
                glTexCoord2f(0.0, 1.0); glVertex3f(-size, -size,  size);
            glEnd();
        }

        GLuint initTexture(const char * imagepath) {
            int imgSize = 32;
            int width = imgSize, height = imgSize;
            unsigned char * data;

            FILE * file;
            file = fopen(imagepath, "rb");

            if (file == NULL) {
                std::cout << "fopen failed: " << std::strerror(errno) << std::endl;
                return 0;
            }

            data = (unsigned char *)malloc( width * height * 3);
            fread(data, width * height * 3, 1, file);
            fclose(file);

            GLubyte* floorTexture = new GLubyte[width * height * 3];//[width][height][3];
            GLubyte *loc;
            int s, t;

            /* Setup RGB image for the texture. */
            loc = (GLubyte*) floorTexture;
            for (t = 0; t < height; t++) {
                for (s = 0; s < width; s++) {
                    int index = ((t * height) + s) * 3;
                    loc[0] = data[index + 2]; // R
                    loc[1] = data[index + 1]; // G
                    loc[2] = data[index];     // B
                    loc += 3;
                }
            }

            free(data);

            GLuint texture;

            glGenTextures  (1, &texture);
            glBindTexture  (GL_TEXTURE_2D, texture);
            glPixelStorei  (GL_UNPACK_ALIGNMENT, 1);
            glTexImage2D   (GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, floorTexture);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexEnvf      (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
            free(floorTexture);

            return texture;
        }


};

#endif
