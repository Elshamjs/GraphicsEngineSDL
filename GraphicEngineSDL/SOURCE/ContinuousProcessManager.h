#pragma once

#include <functional>

#ifndef CONTINUOUS_PROCESSMANAGER_H
#define CONTINUOUS_PROCESSMANAGER_H

// Funciona como un hilo, se le puede programar con cualquier código que se desee que se ejecute durante el tiempo que se desee
class ContinuousProcessManager
{
private:
	bool running;
	int param; // Recoge un int al principio de la ejecución si se requiere
	function<bool(int)> continuous_process; // Este es el código programado, que se ejecutará continuamente. Es importante programarle una condición de salida, de lo contrario sé quedará en 'loop'
	bool finish;
public:
	ContinuousProcessManager(int param, function<bool(int)> continuous_process);
	~ContinuousProcessManager();
	void run();
	bool isRunning();
	void process();
	bool processHasEnded();
};
#endif // !CONTINUOUS_PROCESSMANAGER_H