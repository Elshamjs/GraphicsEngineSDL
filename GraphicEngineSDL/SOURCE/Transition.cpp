#include <functional>
#include "Engine.h"


Transition::~Transition(){}

Transition::Transition(VObject* target, int duration, int delay_millis, function<void()> on_finish)
{
	this->target = target;
	this->duration = duration;
	this->delay_millis = delay_millis;
	running = false;
	this->on_finish = on_finish;
	finish = false;
	Engine::Scene_Manager->transitions->set(this);
}

void Transition::stop()
{
	if (!running)
	{
		cout << "\n\nEXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION\n\n";
		cout << "ESTA TRANSICION NO SE ESTABA EJECUTANDO AUN";
		cout << "\n\nEXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION\n\n";
		abort();
	}
	else
	{
		running = false;
	}
}

void Transition::pause()
{
	if (paused)
	{
		cout << "\n\nEXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION\n\n";
		cout << "ESTA TRANSICION NO SE PUEDE PAUSAR PORQUE YA ESTA PAUSADA";
		cout << "\n\nEXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION\n\n";
		abort();
	}
	else
	{
		paused = true;
	}

}

void Transition::resume()
{
	if (paused)
	{
		cout << "\n\nEXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION\n\n";
		cout << "ESTA TRANSICION NO SE PUEDE REANUDAR SI YA ESTA SIENDO EJECUTADA";
		cout << "\n\nEXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION\n\n";
		abort();
	}
	else
	{
		paused = false;
	}
}


bool Transition::isRunning()
{
	return running;
}

void Transition::setOnFinish(function<void()> on_finish)
{
	if (running)
	{
		cout << "\n\nEXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION\n\n";
		cout << "ESTA TRANSICION YA ESTA EJECUTANDOSE NO SE PUEDE ALTERAR MAS";
		cout << "\n\nEXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION\n\n";
		abort();
	}
	else
	{
		this->on_finish = on_finish;
	}
}

void Transition::continue_process() {}

bool Transition::isFinished()
{
	return finish;
}

bool Transition::isPaused()
{
	return paused;
}

void Transition::continue_pause()
{
	end_time = end_time + Engine::clock->frame->previous_duration;
}

