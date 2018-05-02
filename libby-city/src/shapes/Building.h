#ifndef BUILDING_H
#define BUILDING_H

#include "BuildingPiece.h"
#include "Shape.h"
#include "../textures/textures.h"
#include <ctime>
#include <algorithm>
#include <vector>
#include <iostream>


#define WINDOW_SIZE 1
// int randNum = rand()%(max-min + 1) + min;

using namespace std;

class Building {
public:
	Building() {
	};

	Building(int floors_max, int columns_width_max, int columns_length_max, GLuint* lighting) {
		this->texture = lighting;
		this->floors_max = floors_max;
		this->columns_length_max = columns_length_max;
		this->columns_width_max = columns_width_max;

		createBuilding();
	};

	Building(int floors_max, GLuint* lighting) {
		this->texture = lighting;
		this->floors_max = rand() % (floors_max - (floors_max / 2) + 1) + (floors_max / 2);
		this->columns_length_max = 16;
		this->columns_width_max = 16;

		createBuilding();
	};

	~Building() {
	};

	virtual void draw() {};

private:
	GLuint* texture;
	int columns_length_max;
	int columns_width_max;
	int floors_max;


	virtual void createBuilding() {
	}
};

#endif
