#pragma once

#include <functional>

#ifndef TRANSITION_H
#define TRANSITION_H

// Base para las transiciones que se vayan a utilizar, similar a Java (en Java son hilos), están programadas para que hagan lo mismo sin tratarse de ser hilos
class Transition
{
public:
	~Transition();
protected:
	Transition(VObject* target, int duration, int delay_millis, function<void()> on_finish);
	void stop();
	void pause();
	void resume();
	bool isRunning();
	void setOnFinish(function<void()> on_finish);
	virtual void continue_process();
	bool isFinished();
	bool isPaused();
	void continue_pause();
	VObject* target;
	int duration;
	int delay_millis;
	bool finish;
	bool paused;
	bool running;
	Uint32 delay_cont;
	function<void()> on_finish;
	Uint32 end_time;
	
	friend class Engine;

};
#endif // !TRANSITION