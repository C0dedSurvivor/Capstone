#ifndef ESPACE_H
#define ESPACE_H

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <SFML/Graphics.hpp>

class EncounterSpace {
public:
	int x, y, xL, yL, level;
	std::string area;

	EncounterSpace(int xP, int yP, int xLength, int yLength, std::string place, int l) {
		x = xP;
		y = yP;
		xL = xLength;
		yL = yLength;
		area = place;
		level = l;
	}
};

#endif