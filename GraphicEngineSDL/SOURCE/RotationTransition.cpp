#include "Engine.h"

RotationTransition::~RotationTransition()
{
}

RotationTransition::RotationTransition(VObject* target, float from_rotation, float to_rotation, float duration_s) : Transition(target, ((int)duration_s * 1000.0f), 0, nullptr)
{
	this->from_rotation = from_rotation;
	this->to_rotation = to_rotation;
}

RotationTransition::RotationTransition(VObject* target, float from_rotation, float to_rotation, float duration_s, function<void()> on_finish) : Transition(target, ((int)duration_s * 1000.0f), 0, on_finish)
{
	this->from_rotation = from_rotation;
	this->to_rotation = to_rotation;
}

RotationTransition::RotationTransition(VObject* target, float from_rotation, float to_rotation, float duration_s, int delay_millis) : Transition(target, ((int)duration_s * 1000.0f), delay_millis, nullptr)
{
	this->from_rotation = from_rotation;
	this->to_rotation = to_rotation;
}

RotationTransition::RotationTransition(VObject* target, float from_rotation, float to_rotation, float duration_s, int delay_millis, function<void()> on_finish) : Transition(target, ((int)duration_s * 1000.0f), delay_millis, on_finish)
{
	this->from_rotation = from_rotation;
	this->to_rotation = to_rotation;
}

void RotationTransition::play()
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
		target->setRotation(from_rotation);
		running = true;
	}
}

void RotationTransition::continue_process()
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
	if (target->getRotation() == to_rotation)
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
		target->setRotation(to_rotation);
		return;
	}
	remaining_cycles = (double)((double)((double)(end_time - act_time) / (double)Engine::clock->frame->previous_duration));
	temp = (double)((double)(to_rotation - target->getRotation()) / remaining_cycles);
	target->setRotation(target->getRotation() + temp);
}


