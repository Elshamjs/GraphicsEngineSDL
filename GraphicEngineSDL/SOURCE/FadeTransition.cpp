#include "Engine.h"

FadeTransition::FadeTransition(VObject* target, float from_fade, float to_fade, float duration_s) : Transition(target, ((int)duration_s * 1000.0f), 0, nullptr)
{
	this->from_fade = (from_fade > 1 ? 1 : (from_fade < 0 ? 0 : from_fade));
	this->to_fade = (to_fade > 1 ? 1 : (to_fade < 0 ? 0 : to_fade));
}

FadeTransition::FadeTransition(VObject* target, float from_fade, float to_fade, float duration_s, function<void()> on_finish) : Transition(target, ((int)duration_s * 1000.0f), 0, on_finish)
{
	this->from_fade = (from_fade > 1 ? 1 : (from_fade < 0 ? 0 : from_fade));
	this->to_fade = (to_fade > 1 ? 1 : (to_fade < 0 ? 0 : to_fade));
}

FadeTransition::FadeTransition(VObject* target, float from_fade, float to_fade, float duration_s, int delay_millis) : Transition(target, ((int)duration_s * 1000.0f), delay_millis, nullptr)
{
	this->from_fade = (from_fade > 1 ? 1 : (from_fade < 0 ? 0 : from_fade));
	this->to_fade = (to_fade > 1 ? 1 : (to_fade < 0 ? 0 : to_fade));
}

FadeTransition::FadeTransition(VObject* target, float from_fade, float to_fade, float duration_s, int delay_millis, function<void()> on_finish) : Transition(target, ((int)duration_s * 1000.0f), delay_millis, on_finish)
{
	this->from_fade = (from_fade > 1 ? 1 : (from_fade < 0 ? 0 : from_fade));
	this->to_fade = (to_fade > 1 ? 1 : (to_fade < 0 ? 0 : to_fade));
}

void FadeTransition::play()
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
		target->setOpacity(from_fade);
		running = true;
	}
}

void FadeTransition::continue_process()
{
	static float remaining_cycles;
	static float temp;
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
	if (target->getOpacity() == to_fade)
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
		target->setOpacity(to_fade);
		return;
	}
	remaining_cycles = (double)((double)((double)(end_time - act_time) / (double)Engine::clock->frame->previous_duration));
	temp = (double)((double)(to_fade - target->getOpacity()) / remaining_cycles);
	target->setOpacity(target->getOpacity() + temp);
}

FadeTransition::~FadeTransition()
{
}
