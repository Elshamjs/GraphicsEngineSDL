#pragma once

#include <functional>

#ifndef CONTINUOUS_PROCESSMANAGER_H
#define CONTINUOUS_PROCESSMANAGER_H

// Funciona como un hilo, se le puede programar con cualquier c�digo que se desee que se ejecute durante el tiempo que se desee
class ContinuousProcessManager
{
private:
	bool running;
	int param; // Recoge un int al principio de la ejecuci�n si se requiere
	function<bool(int)> continuous_process; // Este es el c�digo programado, que se ejecutar� continuamente. Es importante programarle una condici�n de salida, de lo contrario s� quedar� en 'loop'
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