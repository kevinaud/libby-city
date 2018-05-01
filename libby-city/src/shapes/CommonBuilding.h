#ifndef COMMONBUILDING_H
#define COMMONBUILDING_H

#include "BuildingPiece.h"
#include "Shape.h"
#include <ctime>
#include <vector>

#define WINDOW_SIZE 1
// int randNum = rand()%(max-min + 1) + min;

using namespace std;

class CommonBuilding : public Shape {
public:
	CommonBuilding() {
		srand(time(0));
	};

	CommonBuilding(int floors_max, int columns_width_max, int columns_length_max, BuildingLighting lighting) {
		srand(time(0));
		this->texture = getSideTexture(lighting);
		this->floors_max = floors_max;
		this->columns_length_max = columns_length_max;
		this->columns_width_max = columns_width_max;

		createBuilding();

		/* pieces = new BuildingPiece[4]; */
		/* pieces[0] = BuildingPiece(24, 20, 20, texture); */
		/* pieces[1] = BuildingPiece(25, 1, 1, texture); */
		/* pieces[2] = BuildingPiece(10, 10, 7, texture); */
		/* pieces[3] = BuildingPiece(8, 6, 8, texture); */
	};

	~CommonBuilding() {
	};

	void draw() {
		pieces[0].draw();
		glPushMatrix(); 
			glTranslatef(-10, 0, -10);
			pieces[1].draw();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(15, 0, 0);
			pieces[2].draw();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(10, 0, 0);
			pieces[3].draw();
		glPopMatrix();
	};

private:
	void createBuilding() {
		float length = 0;
		float width = 0;
		float height = floors_max;

		while (height > 0) {

		}
	}

	GLuint texture;
	std::vector<BuildingPiece> pieces;
	float columns_length_max;
	float columns_width_max;
	float floors_max;

};

#endif
