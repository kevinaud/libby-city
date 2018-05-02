#ifndef COMMONBUILDING_H
#define COMMONBUILDING_H

#include "BuildingPiece.h"
#include "Shape.h"
#include "../textures/textures.h"
#include <ctime>
#include <vector>

#define WINDOW_SIZE 1
// int randNum = rand()%(max-min + 1) + min;

using namespace std;

class CommonBuilding : public Shape {
public:
	CommonBuilding() {
	};

	CommonBuilding(int floors_max, int columns_width_max, int columns_length_max, GLuint* lighting) {
		this->texture = lighting;
		this->floors_max = floors_max;
		this->columns_length_max = columns_length_max;
		this->columns_width_max = columns_width_max;

		createBuilding();
	};

	CommonBuilding(int floors_max, GLuint* lighting) {
		this->texture = lighting;
		this->floors_max = rand() % (floors_max - (floors_max / 2) + 1) + (floors_max / 2);
		this->columns_length_max = 16;
		this->columns_width_max = 16;

		createBuilding();
	};

	~CommonBuilding() {
	};

	void draw() {
		pieces.at(0).draw();
		for (int i = 1; i < pieces.size(); i++) {
			glPushMatrix();
				glRotatef(rotations.at(i), 0, 1, 0);
				glTranslatef(pieces.at(i).getWidth() / 2.0, 0, 0);
				pieces.at(i).draw();
			glPopMatrix();
		}
		
	};

private:
	void createBuilding() {
		vector<int> possibleRotations = { 0, 90, 180, 270 };
		
		int mainLength = rand() % (columns_length_max - (columns_length_max/2)) + (columns_length_max/2);
		int mainWidth = rand() % (columns_width_max - (columns_width_max/2)) + (columns_width_max/2);
		int height = floors_max;

		pieces.push_back(BuildingPiece(height, mainWidth, mainLength, texture));
		rotations.push_back(0);

		int numTiers = 8;
		int rotationIndex = 0;

		int width = (mainWidth / 2);

		for (int i = 0; i < numTiers; i++) {
			int length = rand() % mainLength + 1;
			width = rand() % ((columns_width_max/2) - width + 1) + width;
			height = rand() % (floors_max - (floors_max/3) + 1) + (floors_max/3);
			int rotation = possibleRotations.at(rotationIndex);

			pieces.push_back(BuildingPiece(height, width, length, texture));
			rotations.push_back(rotation);

			if (rotationIndex == 3)
				rotationIndex = 0;
			else
				rotationIndex++;
		}
	}

	GLuint* texture;
	std::vector<BuildingPiece> pieces;
	std::vector<int>rotations;
	int columns_length_max;
	int columns_width_max;
	int floors_max;

};

#endif
