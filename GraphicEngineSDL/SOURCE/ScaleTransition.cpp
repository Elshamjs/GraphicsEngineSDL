#include "Engine.h"

ScaleTransition::~ScaleTransition() {}

ScaleTransition::ScaleTransition(VObject* target, float from_scale_x, float from_scale_y, float to_scale_x, float to_scale_y, float duration_s) : Transition(target, (int)(duration_s * 1000.0f), 0, nullptr)
{
	this->from_scale_x = from_scale_x;
	this->from_scale_y = from_scale_y;
	this->to_scale_x = to_scale_x;
	this->to_scale_y = to_scale_y;
}

ScaleTransition::ScaleTransition(VObject* target, float from_scale_x, float from_scale_y, float to_scale_x, float to_scale_y, float duration_s, function<void()> on_finish) : Transition(target, (int)(duration_s * 1000.0f), 0, on_finish)
{
	this->from_scale_x = from_scale_x;
	this->from_scale_y = from_scale_y;
	this->to_scale_x = to_scale_x;
	this->to_scale_y = to_scale_y;
}


ScaleTransition::ScaleTransition(VObject* target, float from_scale_x, float from_scale_y, float to_scale_x, float to_scale_y, float duration_s, int delay_millis) : Transition(target, (int)(duration_s * 1000.0f), delay_millis, nullptr)
{
	this->from_scale_x = from_scale_x;
	this->from_scale_y = from_scale_y;
	this->to_scale_x = to_scale_x;
	this->to_scale_y = to_scale_y;
}

ScaleTransition::ScaleTransition(VObject* target, float from_scale_x, float from_scale_y, float to_scale_x, float to_scale_y, float duration_s, int delay_millis, function<void()> on_finish) : Transition(target, (int)(duration_s * 1000.0f), delay_millis, on_finish)
{
	this->from_scale_x = from_scale_x;
	this->from_scale_y = from_scale_y;
	this->to_scale_x = to_scale_x;
	this->to_scale_y = to_scale_y;
}

void ScaleTransition::play()
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
		target->setScaleX(from_scale_x);
		target->setScaleY(from_scale_y);
		running = true;
	}
}
void ScaleTransition::continue_process()
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
	act_time = SDL_GetTicks() + 2;
	if (target->getScaleX() == to_scale_x && target->getScaleY() == to_scale_y)
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
		target->setScaleX(to_scale_x);
		target->setScaleY(to_scale_y);
		return;
	}
	remaining_cycles = (float)((float)((float)(end_time - act_time) / (float)Engine::clock->frame->previous_duration));
	tempx = (float)((float)(to_scale_x - target->getScaleX()) / remaining_cycles);
	tempy = (float)((float)(to_scale_y - target->getScaleY()) / remaining_cycles);
	target->setScaleX(target->getScaleX()+ tempx);
	target->setScaleY(target->getScaleX() + tempy);
}

