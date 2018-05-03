#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "../util/bmpread.h"

#define NUM_WINDOWS 64
#define WINDOW_UNIT_SIZE 1.0/64.0

using namespace std;

/**
 * data types
 */
struct GlobalTextures {
    struct BuildingTextures {
        GLuint scatter;
        GLuint striped;
        GLuint yellowScatter;
        GLuint yellowStriped;
    };
    
    BuildingTextures building;
    bool initialized;
};

enum BuildingLighting {
   SCATTER,
   STRIPED
};

/**
 * global variables
 */
extern GlobalTextures textures;
extern bool texturesInitialized;

/**
 * function definitions
 */
void initTextures();

GLubyte* generateBuildingTextureData(GLubyte* baseColor, BuildingLighting lighting, bool noise);
GLuint getBuildingTexture(GLubyte* baseColor, BuildingLighting lighting, bool noise);

void lightOnColor(GLubyte* baseColor, GLubyte* windowColor);
void lightOffColor(GLubyte* windowColor);


#endif
