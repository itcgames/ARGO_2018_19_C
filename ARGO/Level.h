#pragma once

#include "SDL.h"
#include <string>
#include <vector>

#include <iostream>
#include <algorithm>
#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>
#include <map>

typedef int gid;

// Stores information about an individual tile to be
// displayed.

struct tileProp
{
	SDL_Texture* tset;

	int tx, ty;
	int width, height;

	tileProp(SDL_Texture* tset, int tx = 0, int ty = 0, int width = 0, int height = 0);
};

struct tile {
	
	SDL_Texture * sheet;
	// x coordinate in the world
	int x;
	// y coordinate in the world
	int y;
	int tx, ty, width, height;

	tileProp *model;
	
	tile( int x, int y, tileProp *tp);
	void draw(SDL_Renderer* ren);
};

struct MapObjects {
	int x;
	int y;
	int width;
	int height;

	MapObjects(float x = 0, float y = 0, float width = 0, float height = 0);
};

class level {
public:
	level(const std::string& name);
	void load(const std::string& path, SDL_Renderer* ren);
	void draw(SDL_Renderer* ren);
	// All of the tiles we will draw to the screen.
	std::vector<tile> tiles;
	std::vector<MapObjects> m_wall;
	std::vector<MapObjects>m_ceiling;
	std::vector<MapObjects> m_killTiles;
	std::vector<MapObjects> m_teleport;
private:
	std::string name;
	// Think of the dimensions as a 2D array (after all, that's what our
	// Tiled map is)
	// The rows variable is the number of tiles from top to bottom (Y axis).
	int rows;
	// The cols variable is the number of tiles from left to right (X axis).
	tileProp * tpPointer;
	int cols;
	int tile_width;
	int tile_height;
	// All of the tilesets used by our Tiled map.
	std::map<gid, SDL_Texture*> tilesets;
};
