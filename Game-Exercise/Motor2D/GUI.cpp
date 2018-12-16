#include "j1App.h"
#include "p2Log.h"
#include "j1Render.h"
#include "j1Scene.h"
#include "j1Input.h"
#include "GUI.h"
#include "GUI_button.h"
#include "j1Audio.h"
#include "Settings.h"

GUI::GUI(int x, int y, j1Module* callback,GUI* parent)
{
	/*screen_position.x = App->render->ScreenToWorld(x, y).x;
	screen_position.y = App->render->ScreenToWorld(x, y).y;*/
	this->parent = parent;
	this->callback = callback;
}

GUI::~GUI()
{
	animation2 = nullptr;
	texture = nullptr;
	parent = nullptr;
}

void GUI::Update()
{
	App->input->GetMousePosition(mouse_x, mouse_y);
	//LOG("%d, %d", mouse_x, mouse_y);
}

void GUI::Draw(SDL_Texture* sprites)
{
	if (type == LABEL && invisible == false)
	{
		App->render->Blit_UI(texture, position.x, position.y, &animation, 0);
	}
	else if(invisible == false)
	{
		App->render->Blit_UI(sprites, position.x, position.y,&animation,0);
	}
	if (App->gui->debug) {
		SDL_Rect tmp_rect{ position.x,position.y,animation.w,animation.h };
		App->render->DrawQuad(tmp_rect, 255, 0, 0, 255, false,false);
	}
	/*if(animation2 != nullptr && type != LABEL)
	App->render->Blit_UI(sprites, position.x, position.y, &(animation2->GetCurrentFrame()), 1);*/
	/*if(animation2== nullptr)
		App->render->Blit_UI(sprites, position.x, position.y, &animation, 0.0f);*/
}

bool GUI::MouseIn(GUI* element)
{
	GUI_Button*  ex2 = (GUI_Button*)element;

	if (element->type == BUTTON && App->settings->active == false) {
		if (mouse_x > element->position.x && mouse_x < element->position.x + element->animation.w && mouse_y > element->position.y && mouse_y < element->position.y + element->animation.h)
		{
			ex2->setAnimation(2);
		}
		if (mouse_x > element->position.x && mouse_x < element->position.x + element->animation.w && mouse_y > element->position.y && mouse_y < element->position.y + element->animation.h)
		{
			if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
			{
			
				App->audio->PlayFx(1);		
				ex2->setAnimation(3);
				element->callback->Interact(element);		
				return true;
			}
		}
		else
		{
			ex2->setAnimation(1);
			return false;
		}	
	}
	else if (element->type == BUTTON && App->settings->active == true ) {
		if (mouse_x > element->position.x && mouse_x < element->position.x + element->animation.w && mouse_y > element->position.y && mouse_y < element->position.y + element->animation.h)
		{
			ex2->setAnimation(2);
		}
		if (mouse_x > element->position.x && mouse_x < element->position.x + element->animation.w && mouse_y > element->position.y && mouse_y < element->position.y + element->animation.h)
		{
			if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT)
			{

				
				ex2->setAnimation(3);
				element->callback->Interact(element);
				return true;
			}
		}
		else
		{
			ex2->setAnimation(1);
			return false;
		}
	}
	
}

