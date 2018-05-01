#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "../util/bmpread.h"

#define NUM_WINDOWS 64
#define WINDOW_UNIT_SIZE 1.0/64.0

using namespace std;

enum BuildingLighting {
   SCATTER,
   STRIPED
};

void lightOnColor(GLubyte* windowColor);
void lightOffColor(GLubyte* windowColor);

GLubyte* generateBuildingTexture(BuildingLighting lighting);
GLuint getSideTexture(BuildingLighting lighting);

#endif
