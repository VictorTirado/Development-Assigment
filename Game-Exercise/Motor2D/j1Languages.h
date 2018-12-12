#ifndef __j1LANGUAGES_H__
#define __j1LANGUAGES_H__

#include "j1Module.h"
#include "p2DynArray.h"

enum Language
{

	ENLGLISH,
	SPANISH

};
struct LanguageContent
{
	Language current;
	p2SString play;
	p2SString continue_;
	p2SString credits;
	p2SString exit;
};


class j1Languages : public j1Module
{

public:
	j1Languages();
	~j1Languages();

	bool Awake(pugi::xml_node&);
	bool Start();
	bool CleanUp();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();

	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;

	bool ChangeLanguage();
	bool LoadLanguage(Language);
	void DeleteLanguage();

public:
	LanguageContent English;
	LanguageContent current_language;
	
};


#endif // __j1ENTITIES_H__
