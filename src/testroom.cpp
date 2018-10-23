/* Team Bandcamp
 * Class function: 
 * 
*/

#include <SDL.h>
#include <algorithm>
#include <string>

#include "include/object.h"
#include "include/player.h"
#include "include/spritesheet.h"
#include "include/HUD.h"
#include "include/testroom.h"
#include "include/game.h"
#include "include/ooze.h"

constexpr int UPDATE_MAX = 100;
int updateCount = 1;
int oldTemp = 100;
int oldO2 = 100;

HUD h;
Player p;
Ooze o;

TestRoom::TestRoom(int* roomNumber){
	start = false;
	std::unordered_map<std::string, Object*> objectList;
	roomReference = roomNumber;
}

void TestRoom::init(SDL_Renderer* reference){
	rendererReference = reference;
	SDL_Rect player_box = {screen_w/2, screen_h/4, tile_s, tile_s};
	p = Player(player_box);
	SDL_Rect ooze_box = {screen_w/2, 3*screen_h/4, 30, 30};
	o = Ooze(ooze_box, &p, &h);
    
	h.init(reference);
	p.init(reference);
	o.init(reference);
	
	//Player and HUD in the Room
	objectList["player"] = &p;
	objectList["hud"] = &h;
	objectList["ooze"] = &o;
}

void TestRoom::update(Uint32 ticks){
	if (h.currentTemp > oldTemp || h.currentOxygen > oldO2) movePickup(rendererReference);
	oldTemp = h.currentTemp;
	oldO2 = h.currentOxygen;
	std::unordered_map<std::string, Object*>::iterator it = objectList.begin();
	while(it != objectList.end()){
		it->second->update(&objectList, ticks);
		if(it->second->isUsed()) {
			it = objectList.erase(it);
		}
		it++;
	}
	if (updateCount == 0) {
		h.currentTemp = std::max(0, h.currentTemp-5);
		h.currentOxygen = std::max(0, h.currentOxygen-5);
		if (h.currentTemp == 0) {
			h.currentHealth = std::max(0, h.currentHealth-5);
		}
		if (h.currentOxygen == 0) {
			h.currentHealth = std::max(0, h.currentHealth-5);
		}
	}
	updateCount = (updateCount+1)%UPDATE_MAX;
}

void TestRoom::movePickup(SDL_Renderer* reference) {
		int pickupX = std::max(tile_s, rand()%(screen_w-tile_s));
		int pickupY = std::max(tile_s, rand()%(screen_h-tile_s));
		SDL_Rect pickupBox = {pickupX, pickupY, tile_s, tile_s};
		
		int pickupValue = rand()%25+25;
		
		int pickupType = rand()%2;
		char type;
		
		if (pickupType == 0)
			type = 'e';
		else
			type = 'o';
		
		Pickup *newP  = new Pickup(pickupBox, type, pickupValue, &p, &h);
		objectList[newP->getInstanceName()] = newP;
		newP->init(reference);
}

void TestRoom::input(const Uint8* keystate){
	std::unordered_map<std::string, Object*>::iterator it = objectList.begin();
	while(it != objectList.end()){
		it->second->input(keystate);
		it++;
	}
}

SDL_Renderer* TestRoom::draw(SDL_Renderer *renderer){
	std::unordered_map<std::string, Object*>::iterator it = objectList.begin();
	while(it != objectList.end()){
		renderer = it->second->draw(renderer);
		it++;
	}
	return renderer;
}
