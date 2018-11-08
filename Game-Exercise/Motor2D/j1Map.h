#ifndef __j1MAP_H__
#define __j1MAP_H__

#include "PugiXml/src/pugixml.hpp"
#include "p2List.h"
#include "p2Point.h"
#include "j1Module.h"

// TODO 1: Create a struct for the map layer
// ----------------------------------------------------
struct MapLayer{
	p2SString name = nullptr;
	uint width = 0;
	uint height = 0;
	float parallax = 0.0f;
	uint* data = 0;
	~MapLayer(){
		delete[]data;
	}
	inline uint Get(int x, int y)const;
};

	// TODO 6: Short function to get the value of x,y

struct Properties
{
	p2SString name;
	int gravity = 0;
	int player_position_y0 = 0;
	float jumping_time = 0.0f;
	float tp_time = 0.0f;
	int movement_speed = 0;
};

// ----------------------------------------------------
struct TileSet
{
	// TODO 7: Create a method that receives a tile id and returns it's Rectfind the Rect associated with a specific tile id
	SDL_Rect GetTileRect(int id) const;

	p2SString			name = nullptr;
	int					firstgid = 0;
	int					margin = 0;
	int					spacing = 0;
	int					tile_width = 0;
	int					tile_height = 0;
	SDL_Texture*		texture = nullptr;
	int					tex_width = 0;
	int					tex_height = 0;
	int					num_tiles_width = 0;
	int					num_tiles_height = 0;
	int					offset_x = 0;
	int					offset_y = 0;
};

enum MapTypes
{
	MAPTYPE_UNKNOWN = 0,
	MAPTYPE_ORTHOGONAL,
	MAPTYPE_ISOMETRIC,
	MAPTYPE_STAGGERED
};
// ----------------------------------------------------
struct MapData
{
	int					width = 0;
	int					height = 0;
	int					tile_width = 0;
	int					tile_height = 0;
	SDL_Color			background_color;
	MapTypes			type;
	p2List<TileSet*>	tilesets;
	p2List<MapLayer*>	map_layers;
	// TODO 2: Add a list/array of layers to the map!
};

// ----------------------------------------------------
class j1Map : public j1Module
{
public:

	j1Map();

	// Destructor
	virtual ~j1Map();

	// Called before render is available
	bool Awake(pugi::xml_node& conf);

	// Called each loop iteration
	void Draw();

	void Spawn();

	// Called before quitting
	bool CleanUp();

	// Load new map
	bool Load(const char* path);

	// TODO 8: Create a method that translates x,y coordinates from map positions to world positions
	iPoint MapToWorld(int x, int y) const;

private:

	bool LoadMap();
	bool LoadTilesetDetails(pugi::xml_node& tileset_node, TileSet* set);
	bool LoadTilesetImage(pugi::xml_node& tileset_node, TileSet* set);
	bool LoadLayer(pugi::xml_node& node, MapLayer* layer);

	bool LoadProperties(pugi::xml_node& node, Properties* prop);

	TileSet* GetTilesetFromTileId(int id) const;

public:
	Properties* prop = new Properties();
	MapData data;
	uint Get_gid(int x, int y);
	iPoint spawn;
	iPoint spawn_book;
	 p2List<iPoint*> coords_bat;
private:

	pugi::xml_document	map_file;
	p2SString			folder = nullptr;
	bool				map_loaded;
};

#endif // __j1MAP_H__