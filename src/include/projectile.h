#ifndef BANDCAMP_PROJECTILE_H_
#define BANDCAMP_PROJECTILE_H_

#include <algorithm>
#include <SDL.h>
#include <string>
#include <unordered_map>
#include <vector>

#include "breach.h"
#include "collision.h"
#include "object.h"
#include "randommap.h"
#include "utils.h"

class Projectile : public Object
{
	private:
		char projType;
		SDL_Rect projRect;
		SDL_Rect projDrawBox;
		bool up;
	    bool down;
	    bool left;
	    bool right;
		int playerXVel;
		int playerYVel;
		SDL_Renderer* rendererReference;
		int projNumber;
		bool projUsed;
		SDL_Texture* projImg;
		SDL_Rect projImgRect;

	public:
		void input(const Uint8* keystate);
		void init(SDL_Renderer *renderer);
		void update(std::unordered_map<std::string, Object*> &objectList, std::vector<std::vector<Tile*>> &grid, Uint32 ticks);
		std::string getInstanceName();
		SDL_Renderer* draw(SDL_Renderer *renderer, SDL_Rect cam);
		Projectile(char type, int playerX, int playerY);
        ~Projectile();
		Projectile();
		void checkProjOverlap(std::unordered_map<std::string, Object*> &objectList, std::vector<std::vector<Tile*>> &grid);
		SDL_Rect* getRect();
		void updatePosition(Uint32 ticks);
		bool isUsed();
};

#endif  //  BANDCAMP_PROJECTILE_H_