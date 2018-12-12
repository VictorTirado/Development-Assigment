#include "j1App.h"
#include "p2Log.h"
#include "j1Render.h"
#include "j1Scene.h"
#include "j1Input.h"
#include "GUI.h"
#include "GUI_button.h"

GUI::GUI(int x, int y,GUI* parent)
{
	screen_position.x = App->render->ScreenToWorld(x, y).x;
	screen_position.y = App->render->ScreenToWorld(x, y).y;
}

GUI::~GUI()
{
}

void GUI::Update()
{
	int mouse_x, mouse_y;
	App->input->GetMousePosition(mouse_x, mouse_y);
	//LOG("%d, %d", mouse_x, mouse_y);


}

void GUI::Draw(SDL_Texture* sprites)
{
	if (type == LABEL)
	{
		App->render->Blit_UI(texture, position.x, position.y, &animation, 1);
	}
	else if (type == BUTTON)
	{
		App->render->Blit_UI(sprites, position.x, position.y,&animation);
	}
	if(animation2 != nullptr && type != LABEL)
	App->render->Blit_UI(sprites, position.x, position.y, &(animation2->GetCurrentFrame()), 1);
	if(animation2 == nullptr && type != LABEL)
		App->render->Blit_UI(sprites, position.x, position.y, &animation, 0.0f);
}

