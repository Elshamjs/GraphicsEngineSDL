#include <functional>
#include <math.h>
#include "Engine.h"


TranslateTransition::~TranslateTransition(){}

TranslateTransition::TranslateTransition(VObject* target, float from_x, float from_y, float to_x, float to_y, float duration_s) : Transition(target, (int)(duration_s * 1000.0f), 0, nullptr)
{
	this->from_x = from_x;
	this->from_y = from_y;
	this->to_x = to_x;
	this->to_y = to_y;
}

TranslateTransition::TranslateTransition(VObject* target, float from_x, float from_y, float to_x, float to_y, float duration_s, function<void()> on_finish) : Transition(target, (int)(duration_s * 1000.0f), 0, on_finish)
{
	this->from_x = from_x;
	this->from_y = from_y;
	this->to_x = to_x;
	this->to_y = to_y;
}


TranslateTransition::TranslateTransition(VObject* target, float from_x, float from_y, float to_x, float to_y, float duration_s, int delay_millis) : Transition(target, (int)(duration_s * 1000.0f), delay_millis, nullptr)
{
	this->from_x = from_x;
	this->from_y = from_y;
	this->to_x = to_x;
	this->to_y = to_y;
}

TranslateTransition::TranslateTransition(VObject* target, float from_x, float from_y, float to_x, float to_y, float duration_s, int delay_millis, function<void()> on_finish) : Transition(target, (int)(duration_s * 1000.0f), delay_millis, on_finish)
{
	this->from_x = from_x;
	this->from_y = from_y;
	this->to_x = to_x;
	this->to_y = to_y;
}

void TranslateTransition::play()
{
	if (running)
	{
		cout << "\n\nEXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION\n\n";
		cout << "ESTA TRANSICION YA SE ESTA EJECUTANDO NO SE PUEDE VOLVER A EJECUTAR";
		cout << "\n\nEXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION\n\n";
		abort();
	}
	else
	{
		delay_cont = 0;
		end_time = 0;
		target->relocate(from_x, from_y);
		running = true;
	}
}
void TranslateTransition::continue_process()
{
	static float remaining_cycles;
	static float tempx;
	static float tempy;
	static Uint32 act_time;
	if (delay_cont == 0)
	{
		delay_cont = SDL_GetTicks() + delay_millis;
	}
	if (end_time == 0)
	{
		end_time = SDL_GetTicks() + duration + delay_millis;
	}
	act_time = SDL_GetTicks()+2;
	if (target->getX() == to_x && target->getY() == to_y)
	{
		finish = true;
		paused = true;
		running = false;
		if (on_finish != nullptr)
		{
			on_finish();
		}
	}
	if (act_time <= delay_cont)
	{
		return;
	}
	if (act_time >= end_time)
	{
		target->setX(to_x);
		target->setY(to_y);
		return;
	}
	remaining_cycles = (float)((float)((float)(end_time - act_time) / (float)Engine::clock->frame->previous_duration));
	tempx = (float)((float)(to_x - target->getX()) / remaining_cycles);
	tempy = (float)((float)(to_y - target->getY()) / remaining_cycles);
	target->translate(tempx, tempy);
}

