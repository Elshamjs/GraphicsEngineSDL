#include "ProgramMainExample.h"

int main(int argc, char* argv[])
{
	Engine::Start("Nombre de la Ventana", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1300, 800, EngineStarter);
	while (Engine::running->value)
	{
		Engine::clock->frame->frameStart();
		Engine::handleEvents();
		Engine::update();
		Engine::render();
		Engine::clock->frame->frameEnd();
	}
	Engine::close();
	return 0;
}