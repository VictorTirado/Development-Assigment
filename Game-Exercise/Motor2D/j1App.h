#ifndef __j1APP_H__
#define __j1APP_H__

#include "p2List.h"
#include "j1Module.h"
#include "j1PerfTimer.h"
#include "j1Timer.h"
#include "PugiXml\src\pugixml.hpp"

// Modules
class j1Window;
class j1Input;
class j1Render;
class j1Textures;
class j1Audio;
class j1Scene;
class j1Map;
class j1Collision;
class j1Fonts;
class j1Gui;
class j1FadeToBlack;
class j1Entities;
class j1PathFinding;
class j1Particles;
class j1Languages;
class MainMenu;
class Settings;

enum Entities
{
	PLAYER_ENTITY,
	NINJA_ENTITY,
	BAT_ENTITY,
	NONE_ENTITY,
};
enum Languages
{
	ENGLISH,
	ESPAÑOL,
};

class j1App
{
public:

	// Constructor
	j1App(int argc, char* args[]);

	// Destructor
	virtual ~j1App();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update();

	// Called before quitting
	bool CleanUp();

	// Add a new module to handle
	void AddModule(j1Module* module);

	// Exposing some properties for reading
	int GetArgc() const;
	const char* GetArgv(int index) const;
	const char* GetTitle() const;
	const char* GetOrganization() const;

	void LoadGame();
	void SaveGame() const;
	void GetSaveGames(p2List<p2SString>& list_to_fill) const;

	pugi::xml_node LoadEntities(pugi::xml_document&, Entities) const;

	pugi::xml_node LoadLanguages(pugi::xml_document&, Languages) const;

	p2SString language;

private:

	// Load config file
	pugi::xml_node LoadConfig(pugi::xml_document&) const;

	//Load player animations 
	

	// Call modules before each loop iteration
	void PrepareUpdate();

	// Call modules before each loop iteration
	void FinishUpdate();

	// Call modules before each loop iteration
	bool PreUpdate();

	// Call modules on each loop iteration
	bool DoUpdate();

	// Call modules after each loop iteration
	bool PostUpdate();

	// Load / Save
	bool LoadGameNow();
	bool SavegameNow() const;

public:

	// Modules
	j1Window*			win = nullptr;
	j1Input*			input = nullptr;
	j1Render*			render = nullptr;
	j1Textures*			tex = nullptr;
	j1Audio*			audio = nullptr;
	j1Fonts*            font = nullptr;
	j1Gui*              gui = nullptr;
	j1Scene*			scene = nullptr;
	j1Map*				map = nullptr;
	j1Collision*		collision = nullptr;
	j1FadeToBlack*		fade_to_black = nullptr;
	j1Entities*			entities = nullptr;
	j1PathFinding*		pathfinding = nullptr;
	j1Particles*		particles = nullptr;
	j1Languages*		languages = nullptr;
	MainMenu*			main_menu = nullptr;
	Settings*			settings = nullptr;

private:

	p2List<j1Module*>	modules;
	uint				frames = 0;
	float				dt = 0.0f;
	int					argc = 0;
	char**				args = nullptr;

	p2SString			title = nullptr;
	p2SString			organization = nullptr;

	mutable bool		want_to_save;
	bool				want_to_load;
	p2SString			load_game = nullptr;
	mutable p2SString	save_game = nullptr;

	j1PerfTimer			ptimer;
	j1PerfTimer         delay_ptimer;
	j1PerfTimer			perf_timer;
	uint64				frame_count = 0;
	j1Timer				startup_time;
	j1Timer				frame_time;

	j1Timer				last_sec_frame_time;
	uint32				last_sec_frame_count = 0;
	uint32				prev_last_sec_frame_count = 0;
	float               frame_cap_value = 0;
	p2SString			vsync_value;
	p2SString			cap_value;
	bool				cap = true;
	float				frame_delay;

};

extern j1App* App; // No student is asking me about that ... odd :-S

#endif