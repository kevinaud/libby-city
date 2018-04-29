#ifndef SKYBOX_H
#define SKYBOX_H

#include <iostream>
#include <cerrno>
#include "Shape.h"

GLuint back, front, left, right, up, down;

static GLuint texName;

bool initialized = false;

GLuint initTexture(const char * imagepath)
{
	int width = 2048, height = 2048;
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
    std::cout << texture << std::endl;
    glBindTexture  (GL_TEXTURE_2D, texture);
    glPixelStorei  (GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D   (GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, floorTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexEnvf      (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    free(floorTexture);

    return texture;
}

class Skybox : public Shape {
    public:
        Skybox() {
            std::cout << "construct" << std::endl;
        };
        ~Skybox() {};

        void setTexture(GLuint texture) {
            this->texture = texture; 
        }

        void draw() {
            std::cout << "draw" << std::endl;
            glEnable(GL_TEXTURE_2D);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            if (!initialized) {
                front = initTexture("/home/kevin/classes/graphics/libby-city/libby-city/src/shapes/SunSetFront2048.bmp");
                back = initTexture("/home/kevin/classes/graphics/libby-city/libby-city/src/img/SunSetBack2048.bmp");
                right = initTexture("/home/kevin/classes/graphics/libby-city/libby-city/src/img/SunSetRight2048.bmp");
                left = initTexture("/home/kevin/classes/graphics/libby-city/libby-city/src/img/SunSetLeft2048.bmp");
                up = initTexture("/home/kevin/classes/graphics/libby-city/libby-city/src/img/SunSetUp2048.bmp");
                down = initTexture("/home/kevin/classes/graphics/libby-city/libby-city/src/img/SunSetDown2048.bmp");
            }
            initialized = true;

            glPushMatrix(); { // +Z
                glRotatef(180, 0, 0, 1);
                drawCubeFace(front);
            }
            glPopMatrix();
            glPushMatrix(); { // +X
                glRotatef(90, 0, 1, 0);
                glRotatef(180, 1, 0, 0);
                drawCubeFace(left);
            }
            glPopMatrix();
            glPushMatrix(); { // -Z
                glRotatef(180, 0, 1, 0);
                glRotatef(180, 0, 0, 1);
                drawCubeFace(back);
            }
            glPopMatrix();
            glPushMatrix(); { // -X
                glRotatef(270, 0, 1, 0);
                glRotatef(180, 1, 0, 0);
                drawCubeFace(right);
            }
            glPopMatrix();
            glPushMatrix(); { // -Y
                glRotatef(270, 1, 0, 0);
                glRotatef(180, 0, 1, 0);
                drawCubeFace(down);
            }
            glPopMatrix();
            glPushMatrix(); { // +Y
                glRotatef(90, 1, 0, 0);
                glRotatef(180, 0, 1, 0);
                drawCubeFace(up);
            }
            glPopMatrix();
        };


        void drawNormal() {
            glPushMatrix(); {
                drawCubeFaceNormal();
            }
            glPopMatrix();
            glPushMatrix(); {
                glRotatef(90, 0, 1, 0);
                drawCubeFaceNormal();
            }
            glPopMatrix();
            glPushMatrix(); {
                glRotatef(180, 0, 1, 0);
                drawCubeFaceNormal();
            }
            glPopMatrix();
            glPushMatrix(); {
                glRotatef(270, 0, 1, 0);
                drawCubeFaceNormal();
            }
            glPopMatrix();
            glPushMatrix(); {
                glRotatef(270, 1, 0, 0);
                drawCubeFaceNormal();
            }
            glPopMatrix();
            glPushMatrix(); {
                glRotatef(90, 1, 0, 0);
                drawCubeFaceNormal();
            }
            glPopMatrix();
        };

    private:

        GLuint texture;

        void drawCubeFace(GLuint texture) {
            float width = 1.0f / (float)m_segmentsX;
            float height = 1.0f / (float)m_segmentsY;
            float size = 20.0f;

            glBindTexture(GL_TEXTURE_2D, texture);

            glBegin(GL_QUADS);
                glNormal3f(0.0, 0.0, 1.0);
                glTexCoord2f(0.0, 0.0); glVertex3f(-size,  size,  size);
                glTexCoord2f(1.0, 0.0); glVertex3f( size,  size,  size);
                glTexCoord2f(1.0, 1.0); glVertex3f( size, -size,  size);
                glTexCoord2f(0.0, 1.0); glVertex3f(-size, -size,  size);
            glEnd();
        }

        void drawCubeFaceNormal() {
            float width = 1.0f / (float)m_segmentsX;
            float height = 1.0f / (float)m_segmentsY;
            float startX = -0.5f;
            float startY = -0.5f;

            glBegin(GL_LINES);
            for (int i = 0; i < m_segmentsX; i++) {
                float xcoord = startX + (i*width);
                for (int j = 0; j < m_segmentsY; j++) {
                    float ycoord = startY + (j*height);
                    glVertex3d(xcoord, ycoord, 0); glVertex3d(xcoord, ycoord, 0.1); 
                    glVertex3d(xcoord + width, ycoord, 0); glVertex3d(xcoord + width, ycoord, 0.1);
                    glVertex3d(xcoord + width, ycoord + height, 0); glVertex3d(xcoord + width, ycoord + height, 0.1);

                    glVertex3d(xcoord + width, ycoord + height, 0); glVertex3d(xcoord + width, ycoord + height, 0.1);
                    glVertex3d(xcoord, ycoord + height, 0); glVertex3d(xcoord, ycoord + height, 0.1); 
                    glVertex3d(xcoord, ycoord, 0); glVertex3d(xcoord, ycoord, 0.1);
                }
            }
            glEnd();
        }
};

#endif
