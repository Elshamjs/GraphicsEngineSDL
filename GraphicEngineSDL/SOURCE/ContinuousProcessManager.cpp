#include "Engine.h"

ContinuousProcessManager::ContinuousProcessManager(int param, function<bool(int)> continuous_process)
{
	this->continuous_process = continuous_process;
	finish = false;
	running = false;
	Engine::Scene_Manager->continuous_processes->set(this);
}

ContinuousProcessManager::~ContinuousProcessManager() {}

void ContinuousProcessManager::run()
{
	running = true;
}

bool ContinuousProcessManager::isRunning()
{ 
	return running;
}



void ContinuousProcessManager::process()
{
	finish = continuous_process(param);

}

bool ContinuousProcessManager::processHasEnded()
{
	return finish;
}

