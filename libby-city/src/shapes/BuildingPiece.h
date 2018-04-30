#ifndef BUILDINGPIECE_H
#define BUILDINGPIECE_H

#include "Shape.h"

#define WINDOW_SIZE 0.5


class BuildingPiece : public Shape {
public:
	BuildingPiece() {};
	~BuildingPiece() {};

	void draw() {
		glPushMatrix(); { // XY
			glTranslatef(0.0, 0.0, 0.5);
			drawCubeFace();
		}
		glPopMatrix();
		glPushMatrix(); { // -XY
			glTranslatef(0.0, 0.0, -0.5);
			glRotatef(180, 0, 1, 0);
			drawCubeFace();
		}
		glPopMatrix();
		glPushMatrix(); { // YZ
			glTranslatef(0.5, 0.0, 0.0);
			glRotatef(90, 0, 1, 0);
			drawCubeFace();
		}
		glPopMatrix();
		glPushMatrix(); { // -YZ
			glTranslatef(-0.5, 0.0, 0.0);
			glRotatef(270, 0, 1, 0);
			drawCubeFace();
		}
		glPopMatrix();
		glPushMatrix(); { // XZ
			glTranslatef(0, 0.5, 0.0);
			glRotatef(270, 1, 0, 0);
			drawCubeFace();
		}
		glPopMatrix();
		glPushMatrix(); { // -XZ
			glTranslatef(0.0, -0.5, 0.0);
			glRotatef(90, 1, 0, 0);
			drawCubeFace();
		}
		glPopMatrix();
	};


	void drawNormal() {
		glPushMatrix(); {
			glTranslatef(0.0, 0.0, 0.5);
			drawCubeFaceNormal();
		}
		glPopMatrix();
		glPushMatrix(); {
			glTranslatef(0.5, 0.0, 0.0);
			glRotatef(90, 0, 1, 0);
			drawCubeFaceNormal();
		}
		glPopMatrix();
		glPushMatrix(); {
			glTranslatef(0.0, 0.0, -0.5);
			glRotatef(180, 0, 1, 0);
			drawCubeFaceNormal();
		}
		glPopMatrix();
		glPushMatrix(); {
			glTranslatef(-0.5, 0.0, 0.0);
			glRotatef(270, 0, 1, 0);
			drawCubeFaceNormal();
		}
		glPopMatrix();
		glPushMatrix(); {
			glTranslatef(0, 0.5, 0.0);
			glRotatef(270, 1, 0, 0);
			drawCubeFaceNormal();
		}
		glPopMatrix();
		glPushMatrix(); {
			glTranslatef(0.0, -0.5, 0.0);
			glRotatef(90, 1, 0, 0);
			drawCubeFaceNormal();
		}
		glPopMatrix();
	};

private:
	enum FaceType { XY, YZ, XZ, _XY, _YZ, _XZ };
	struct Face {
		FaceType faceType;
		int floors;
		int columns;
		float height;
		float width;
		float textureCoordinates[4];
	};

	Face faces[6];

	void drawCubeFace(Face face) {
		float w = 1.0f / (float)m_segmentsX;
		float h = 1.0f / (float)m_segmentsY;
		float startX = -0.5f;
		float startY = -0.5f;

		glBegin(GL_TRIANGLES);
		for (int i = 0; i < m_segmentsX; i++) {
			float xcoord = startX + (i*w);
			for (int j = 0; j < m_segmentsY; j++) {
				float ycoord = startY + (j*height);
				glNormal3f(0, 0, 1);
				glVertex3d(xcoord, ycoord, 0);
				glVertex3d(xcoord + width, ycoord, 0);
				glVertex3d(xcoord + width, ycoord + height, 0);

				glNormal3f(0, 0, 1);
				glVertex3d(xcoord + width, ycoord + height, 0);
				glVertex3d(xcoord, ycoord + height, 0);
				glVertex3d(xcoord, ycoord, 0);
			}
		}
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
