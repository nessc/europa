#ifndef BANDCAMP_COLLISION_H_
#define BANDCAMP_COLLISION_H_

#include <iostream>
#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include "circle.h"
#include "tile.h"

namespace collision
{
    bool checkCol(SDL_Rect rect1, SDL_Rect rect2);
    bool checkCol(SDL_Rect rect, Circle circ);
    bool checkCol(Circle circ1, Circle circ2);
    bool checkColLeft(SDL_Rect rect, std::vector<std::vector<Tile*>> grid, int tilesize);
    bool checkColRight(SDL_Rect rect, std::vector<std::vector<Tile*>> grid, int tilesize);
    bool checkColTop(SDL_Rect rect, std::vector<std::vector<Tile*>> grid, int tilesize);
    bool checkColBottom(SDL_Rect rect, std::vector<std::vector<Tile*>> grid, int tilesize);
};
#endif