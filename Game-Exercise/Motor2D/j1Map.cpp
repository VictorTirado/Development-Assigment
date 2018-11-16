#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Map.h"
#include "Entity_Player.h"
#include "j1Scene.h"
#include "j1Entitites.h"
#include "Brofiler\Brofiler.h"
#include "j1Input.h"
#include <math.h>

j1Map::j1Map() : j1Module(), map_loaded(false)
{
	name.create("map");
}

// Destructor
j1Map::~j1Map()
{}

// Called before render is available
bool j1Map::Awake(pugi::xml_node& config)
{
	LOG("Loading Map Parser");
	bool ret = true;

	folder.create(config.child("folder").child_value());

	return ret;
}
void j1Map::Spawn()
{
	BROFILER_CATEGORY("MapSpawnFunction", Profiler::Color::MintCream);

	if (map_loaded == false)
		return;


	p2List_item<MapLayer*>* layers_list = this->data.map_layers.start;

	while (layers_list != NULL)
	{
		for (int i = 0; i < layers_list->data->width; i++)
		{
			for (int j = 0; j < layers_list->data->height; j++)
			{
				int tile_id = layers_list->data->Get(i, j);
				if (tile_id > 0)
				{

					TileSet* tileset = GetTilesetFromTileId(tile_id);
					if (tileset != nullptr)
					{

						if (layers_list->data->Get(i, j) != 0)
						{
							iPoint coords = MapToWorld(i, j);
							uint gid = Get_gid(coords.x, coords.y);

							if (layers_list->data->name == "Logic" && App->map->data.map_layers.end->data->data[gid] == 52)
							{
								App->entities->SpawnEntities(coords.x, coords.y, PLAYER);
							}
							if (layers_list->data->name == "Logic" && App->map->data.map_layers.end->data->data[gid] == 73)
							{
								App->entities->SpawnEntities(coords.x, coords.y, BOOK);
							}
							if (layers_list->data->name == "Logic" && App->map->data.map_layers.end->data->data[gid] == 74)
							{
								App->entities->SpawnEntities(coords.x, coords.y, BAT);
							}
							if (layers_list->data->name == "Logic" && App->map->data.map_layers.end->data->data[gid] == 46)
							{
								App->entities->SpawnEntities(coords.x, coords.y, NINJA);
							}
						}
					}
					tileset = nullptr;
				}	
			}
		}
		layers_list = layers_list->next;
	}
	layers_list = nullptr;

}

void j1Map::Draw()
{
	BROFILER_CATEGORY("MapDrawFunction", Profiler::Color::PaleTurquoise);

	if(map_loaded == false)
		return;


	p2List_item<MapLayer*>* layers_list = this->data.map_layers.start;
	
		while (layers_list != NULL)
		{
			for (int i = 0; i < layers_list->data->width; i++)
			{
				for (int j = 0; j < layers_list->data->height; j++)
				{
					int tile_id = layers_list->data->Get(i, j);
					if (tile_id > 0)
					{

						TileSet* tileset = GetTilesetFromTileId(tile_id);
						if (tileset != nullptr)
						{

							if (layers_list->data->Get(i, j) != 0)
							{
								SDL_Rect tile = tileset->GetTileRect(tile_id);
								iPoint coords = MapToWorld(i, j);
								
								if(layers_list->data->name !="Logic" && layers_list->data->name != "path_bat")
									App->render->Blit(tileset->texture, coords.x, coords.y, &tile, layers_list->data->parallax);
								
								else if (App->scene->collision_debug)
									App->render->Blit(tileset->texture, coords.x, coords.y, &tile, 1.0f);
								
							}
						}
					}
				}
			}
			layers_list = layers_list->next;
		}
}

int Properties_::Get(const char* value, int default_value) const
{
	p2List_item<Property*>* item = list.start;

	while (item)
	{
		if (item->data->name == value)
			return item->data->value;
		item = item->next;
	}

	return default_value;
}


iPoint j1Map::MapToWorld(int x, int y) const
{
	iPoint ret;

	ret.x = x * data.tile_width;
	ret.y = y * data.tile_height;

	return ret;
}
iPoint j1Map::WorldToMap(int x, int y) const
{
	iPoint ret(0, 0);

	if (data.type == MAPTYPE_ORTHOGONAL)
	{
		ret.x = x / data.tile_width;
		ret.y = y / data.tile_height;
	}
	else if (data.type == MAPTYPE_ISOMETRIC)
	{

		float half_width = data.tile_width * 0.5f;
		float half_height = data.tile_height * 0.5f;
		ret.x = int((x / half_width + y / half_height) / 2) - 1;
		ret.y = int((y / half_height - (x / half_width)) / 2);
	}
	else
	{
		LOG("Unknown map type");
		ret.x = x; ret.y = y;
	}

	return ret;
}

TileSet* j1Map::GetTilesetFromTileId(int id) const
{
	p2List_item<TileSet*>* item = data.tilesets.start;

	for (item; item != NULL; item = item->next)
	{
		if (item->next == nullptr || item->next->data->firstgid > id)
			return item->data;
	}

	return data.tilesets.start->data;
}

SDL_Rect TileSet::GetTileRect(int id) const
{
	int relative_id = id - firstgid;
	SDL_Rect rect;
	rect.w = tile_width;
	rect.h = tile_height;
	rect.x = margin + ((rect.w + spacing) * (relative_id % num_tiles_width));
	rect.y = margin + ((rect.h + spacing) * (relative_id / num_tiles_width));
	return rect;
}

// Called before quitting
bool j1Map::CleanUp()
{
	LOG("Unloading map");
	// Remove all tilesets
	p2List_item<TileSet*>* item;
	item = data.tilesets.start;

	while(item != NULL)
	{
		RELEASE(item->data);
		item = item->next;
	}
	data.tilesets.clear();

	// Remove all layers
	p2List_item<MapLayer*>* item2;
	item2 = data.map_layers.start;

	while (item2 != NULL)
	{
		RELEASE(item2->data);
		item2 = item2->next;
	}
	


	data.map_layers.clear();

	// Clean up the pugui tree
	map_file.reset();

	return true;
}

// Load new map
bool j1Map::Load(const char* file_name)
{
	BROFILER_CATEGORY("MapLoadFunction", Profiler::Color::SandyBrown);

	bool ret = true;
	p2SString tmp("%s%s", folder.GetString(), file_name);

	pugi::xml_parse_result result = map_file.load_file(tmp.GetString());

	if(result == NULL)
	{
		LOG("Could not load map xml file %s. pugi error: %s", file_name, result.description());
		ret = false;
	}

	// Load general info ----------------------------------------------
	if(ret == true)
	{
		ret = LoadMap();
	}

	// Load all tilesets info ----------------------------------------------
	pugi::xml_node tileset;
	for(tileset = map_file.child("map").child("tileset"); tileset && ret; tileset = tileset.next_sibling("tileset"))
	{
		TileSet* set = new TileSet();

		if(ret == true)
		{
			ret = LoadTilesetDetails(tileset, set);
		}

		if(ret == true)
		{
			ret = LoadTilesetImage(tileset, set);
		}

		data.tilesets.add(set);
	}
	pugi::xml_node properties;
	for (properties = map_file.child("map").child("properties"); properties && ret; properties = properties.next_sibling("properties"))
	{
		
		if (ret == true)
		{
			ret = LoadProperties(properties,prop);
		}
	}
	

	// TODO 4: Iterate all layers and load each of them
	// Load layer info ----------------------------------------------
	pugi::xml_node layer;
	for (layer = map_file.child("map").child("layer"); layer && ret; layer = layer.next_sibling("layer"))
	{
		MapLayer* set = new MapLayer();

		if (ret == true)
		{
			ret = LoadLayer(layer, set);
		}
		data.map_layers.add(set);
	}


	if(ret == true)
	{
		LOG("Successfully parsed map XML file: %s", file_name);
		LOG("width: %d height: %d", data.width, data.height);
		LOG("tile_width: %d tile_height: %d", data.tile_width, data.tile_height);

		p2List_item<TileSet*>* item = data.tilesets.start;
		while(item != NULL)
		{
			TileSet* s = item->data;
			LOG("Tileset ----");
			LOG("name: %s firstgid: %d", s->name.GetString(), s->firstgid);
			LOG("tile width: %d tile height: %d", s->tile_width, s->tile_height);
			LOG("spacing: %d margin: %d", s->spacing, s->margin);
			item = item->next;
		}

		// TODO 4: Add info here about your loaded layers
		// Adapt this vcode with your own variables
		
		p2List_item<MapLayer*>* item_layer = data.map_layers.start;
		while(item_layer != NULL)
		{
			MapLayer* l = item_layer->data;
			LOG("Layer ----");
			LOG("name: %s", l->name.GetString());
			LOG("tile width: %d tile height: %d",l->width,l->height);
			item_layer = item_layer->next;
		}
	}

	map_loaded = ret;

	return ret;
}

// Load map general properties
bool j1Map::LoadMap()
{
	BROFILER_CATEGORY("MapLoadMapFunction", Profiler::Color::Plum);

	bool ret = true;
	pugi::xml_node map = map_file.child("map");

	if(map == NULL)
	{
		LOG("Error parsing map xml file: Cannot find 'map' tag.");
		ret = false;
	}
	else
	{
		data.width = map.attribute("width").as_int();
		data.height = map.attribute("height").as_int();
		data.tile_width = map.attribute("tilewidth").as_int();
		data.tile_height = map.attribute("tileheight").as_int();
		p2SString bg_color(map.attribute("backgroundcolor").as_string());

		data.background_color.r = 0;
		data.background_color.g = 0;
		data.background_color.b = 0;
		data.background_color.a = 0;

		if(bg_color.Length() > 0)
		{
			p2SString red, green, blue;
			bg_color.SubString(1, 2, red);
			bg_color.SubString(3, 4, green);
			bg_color.SubString(5, 6, blue);

			int v = 0;

			sscanf_s(red.GetString(), "%x", &v);
			if(v >= 0 && v <= 255) data.background_color.r = v;

			sscanf_s(green.GetString(), "%x", &v);
			if(v >= 0 && v <= 255) data.background_color.g = v;

			sscanf_s(blue.GetString(), "%x", &v);
			if(v >= 0 && v <= 255) data.background_color.b = v;
		}

		p2SString orientation(map.attribute("orientation").as_string());

		if(orientation == "orthogonal")
		{
			data.type = MAPTYPE_ORTHOGONAL;
		}
		else if(orientation == "isometric")
		{
			data.type = MAPTYPE_ISOMETRIC;
		}
		else if(orientation == "staggered")
		{
			data.type = MAPTYPE_STAGGERED;
		}
		else
		{
			data.type = MAPTYPE_UNKNOWN;
		}
	}

	return ret;
}

bool j1Map::LoadTilesetDetails(pugi::xml_node& tileset_node, TileSet* set)
{
	bool ret = true;
	set->name.create(tileset_node.attribute("name").as_string());
	set->firstgid = tileset_node.attribute("firstgid").as_int();
	set->tile_width = tileset_node.attribute("tilewidth").as_int();
	set->tile_height = tileset_node.attribute("tileheight").as_int();
	set->margin = tileset_node.attribute("margin").as_int();
	set->spacing = tileset_node.attribute("spacing").as_int();
	pugi::xml_node offset = tileset_node.child("tileoffset");

	if(offset != NULL)
	{
		set->offset_x = offset.attribute("x").as_int();
		set->offset_y = offset.attribute("y").as_int();
	}
	else
	{
		set->offset_x = 0;
		set->offset_y = 0;
	}

	return ret;
}

bool j1Map::LoadTilesetImage(pugi::xml_node& tileset_node, TileSet* set)
{
	bool ret = true;
	pugi::xml_node image = tileset_node.child("image");

	if(image == NULL)
	{
		LOG("Error parsing tileset xml file: Cannot find 'image' tag.");
		ret = false;
	}
	else
	{
		set->texture = App->tex->Load(PATH(folder.GetString(), image.attribute("source").as_string()));
		int w, h;
		SDL_QueryTexture(set->texture, NULL, NULL, &w, &h);
		set->tex_width = image.attribute("width").as_int();

		if(set->tex_width <= 0)
		{
			set->tex_width = w;
		}

		set->tex_height = image.attribute("height").as_int();

		if(set->tex_height <= 0)
		{
			set->tex_height = h;
		}

		set->num_tiles_width = set->tex_width / set->tile_width;
		set->num_tiles_height = set->tex_height / set->tile_height;
	}

	return ret;
}

// TODO 3: Create the definition for a function that loads a single layer
bool j1Map::LoadLayer(pugi::xml_node& node, MapLayer* layer)
{
	layer->name = node.attribute("name").as_string();
	layer->width = node.attribute("width").as_uint();
	layer->height = node.attribute("height").as_uint();
	layer->parallax = node.child("properties").child("property").attribute("value").as_float();
	LoadProperties2(node, layer->properties);
	

	layer->data = new uint[layer->width*layer->height];
	memset(layer->data, 0, layer->width * layer->height * sizeof(uint));
	int i = 0;
	for (pugi::xml_node& gids = node.child("data").child("tile"); gids; gids = gids.next_sibling("tile"))
	{
		layer->data[i] = gids.attribute("gid").as_uint();
		i++;
	}
	return true;
}
bool j1Map::LoadProperties(pugi::xml_node& node, Properties* prop)
{
	for (pugi::xml_node& gids = node.child("property"); gids; gids = gids.next_sibling("property"))
	{
		prop->name = gids.attribute("name").as_string();

		if(prop->name == "gravity")
			prop->gravity = gids.attribute("value").as_int();

		if (prop->name == "jumping time")
			prop->jumping_time = gids.attribute("value").as_float();

		if (prop->name == "movement speed")
			prop->movement_speed = gids.attribute("value").as_int();

		if (prop->name == "player_positon_y0")
			prop->player_position_y0 = gids.attribute("value").as_int();

		if (prop->name == "tp_time")
			prop->tp_time = gids.attribute("value").as_float();

	
	}
	return true;
}
bool j1Map::LoadProperties2(pugi::xml_node& node, Properties_& properties)
{
	bool ret = false;

	pugi::xml_node data = node.child("properties");

	if (data != NULL)
	{
		pugi::xml_node prop;

		for (prop = data.child("property"); prop; prop = prop.next_sibling("property"))
		{
			Properties_::Property* p = new Properties_::Property();

			p->name = prop.attribute("name").as_string();
			p->value = prop.attribute("value").as_int();

			properties.list.add(p);
		}
	}

	return ret;
}

 uint MapLayer::Get(int x, int y)const
{
	 return data[width*y + x];
}

 uint j1Map::Get_gid(int x, int y) {
	 iPoint ret;
	 ret.x = x / data.tile_width;
	 ret.y = y / data.tile_height;
	 return data.map_layers.start->data->width*ret.y + ret.x;
 }

 bool j1Map::CreateWalkabilityMap(int& width, int& height, uchar** buffer) const
 {
	 BROFILER_CATEGORY("MapCreateWalkabilityMapFunction", Profiler::Color::Teal);
	 bool ret = false;
	 p2List_item<MapLayer*>* item;
	 item = data.map_layers.start;

	 for (item = data.map_layers.start; item != NULL; item = item->next)
	 {
		 MapLayer* layer = item->data;

		 if (layer->properties.Get("Navigation", 0) == 0)
			 continue;

		 uchar* map = new uchar[layer->width*layer->height];
		 memset(map, 1, layer->width*layer->height);

		 for (int y = 0; y < data.height; ++y)
		 {
			 for (int x = 0; x < data.width; ++x)
			 {
				 int i = (y*layer->width) + x;

				 int tile_id = layer->Get(x, y);
				 TileSet* tileset = (tile_id > 0) ? GetTilesetFromTileId(tile_id) : NULL;

				 if (tileset != NULL)
				 {
					 /*map[i] = (tile_id - tileset->firstgid) > 0 ? 0 : 1;*/
					 if (tile_id - tileset->firstgid > 0)
						 map[i] = 0;
					 else
						 map[i] = 1;
					
				 }
			 }
		 }

		 *buffer = map;
		 width = data.width;
		 height = data.height;
		 ret = true;

		 break;
	 }

	 return ret;
 }