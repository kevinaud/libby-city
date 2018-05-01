#ifndef ROAD_H
#define ROAD_H

using namespace std;

class Road {
    public:
        Road(int sizeX, int sizeY);
        void initialize();
        void draw();

    private:
        // dimensions
        int sizeX;
        int sizeY;

        bool initialized;
};

#endif
