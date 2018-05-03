#ifndef PARK_CITY_BLOCK_H
#define PARK_CITY_BLOCK_H

#include "CityBlock.h"
#include "../shapes/Tree.h"
#include <vector>

using namespace std;

class ParkCityBlock : public CityBlock {
    public:
        ParkCityBlock();
		void draw();
	private:
        vector<Tree> trees;
		vector<float> xTranslations;
		vector<float> zTranslations;
		int numTrees;
};

#endif
