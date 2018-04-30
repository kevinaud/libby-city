#ifndef TEXTURED_CUBE_H
#define TEXTURED_CUBE_H

#include <string>
#include <ctime>
#include <cstdlib>
#include "Shape.h"
#include "../textures/textures.h"

class TexturedCube : public Shape {
public:
	TexturedCube() {
        this->textures = new GLuint[6]; 
        srand(time(0));
    };
	~TexturedCube() {};

	void draw() {
        if (!initialized) {
            initialize();
        }
        glEnable(GL_TEXTURE_2D);
		glPushMatrix(); {
            drawWindowedWall(4, 4);
			// drawCubeFace(textures[0]);
		}
		glPopMatrix();
		glPushMatrix(); {
			glRotatef(90, 0, 1, 0);
            drawWindowedWall(4, 4);
			// drawCubeFace(textures[1]);
		}
		glPopMatrix();
		glPushMatrix(); {
			glRotatef(180, 0, 1, 0);
            drawWindowedWall(4, 4);
			// drawCubeFace(textures[2]);
		}
		glPopMatrix();
		glPushMatrix(); {
			glRotatef(270, 0, 1, 0);
            drawWindowedWall(4, 4);
			// drawCubeFace(textures[3]);
		}
		glPopMatrix();
		glPushMatrix(); {
			glRotatef(270, 1, 0, 0);
            drawWindowedWall(4, 4);
			// drawCubeFace(textures[4]);
		}
		glPopMatrix();
		glPushMatrix(); {
			glRotatef(90, 1, 0, 0);
            drawWindowedWall(4, 4);
			// drawCubeFace(textures[5]);
		}
		glPopMatrix();
	};

    /**
     * - textures is an array of 6 initialized GL textures
     * 
     * textures[0] - FRONT
     * textures[1] - BACK
     * textures[2] - RIGHT
     * textures[3] - LEFT
     * textures[4] - TOP
     * textures[5] - BOTTOM
     */
    void setTextures(GLuint* textures) {
        this->textures = textures; 
    }

	void drawNormal() {
	};

private:
    GLuint* textures;
    bool initialized = false;
    float windowSize = 0.5f;

    void initialize() {
        this->textures[0] = getSideTexture(BuildingLighting::STRIPED);
        this->textures[1] = getSideTexture(BuildingLighting::STRIPED);
        this->textures[2] = getSideTexture(BuildingLighting::STRIPED);
        this->textures[3] = getSideTexture(BuildingLighting::STRIPED);
        this->textures[4] = getSideTexture(BuildingLighting::STRIPED);
        this->textures[5] = getSideTexture(BuildingLighting::STRIPED);
        std::cout << textures[0] << std::endl;
        initialized = true;
    }

	void drawCubeFace(GLuint texture = 0) {
        float size = 0.5;

        glBindTexture(GL_TEXTURE_2D, texture);
        glBegin(GL_QUADS);
            glNormal3f(0.0, 0.0, 1.0);
            glTexCoord2f(0.0, 0.0);glVertex3f(-size,  size,  size);
            glTexCoord2f(1.0, 0.0);glVertex3f( size,  size,  size);
            glTexCoord2f(1.0, 1.0);glVertex3f( size, -size,  size);
            glTexCoord2f(0.0, 1.0);glVertex3f(-size, -size,  size);
        glEnd();
	}

	void drawWindowedWall(GLuint numRows, GLuint numCols) {
        float size = 0.5;
        float width = numRows * windowSize;
        float height = numCols * windowSize;
        float windowTextureWidth = 1.0 / 64;
        float texWidth = numCols * windowTextureWidth;
        float texHeight = numRows * windowTextureWidth;

        int originX = rand() % (64 - numCols);
        int originY = rand() % (64 - numRows);

        float originXf = originX * windowTextureWidth;
        float originYf = originY * windowTextureWidth;

        glBindTexture(GL_TEXTURE_2D, textures[0]);
        glBegin(GL_QUADS);
            glNormal3f(0.0, 0.0, 1.0);
            glTexCoord2f(originX, originY);                        glVertex3f(-width,  height, 0);
            glTexCoord2f(originX + texWidth, originY);             glVertex3f( width,  height, 0);
            glTexCoord2f(originX + texWidth, originX + texHeight); glVertex3f( width, -height, 0);
            glTexCoord2f(originX, originX + texHeight);            glVertex3f(-width, -height, 0);
        glEnd();
	}

	void drawUntexturedCubeFace() {
        float size = 0.5;

        glBegin(GL_QUADS);
            glNormal3f(0.0, 0.0, 1.0);
            glVertex3f(-size,  size,  size);
            glVertex3f( size,  size,  size);
            glVertex3f( size, -size,  size);
            glVertex3f(-size, -size,  size);
        glEnd();
	}
};

#endif
