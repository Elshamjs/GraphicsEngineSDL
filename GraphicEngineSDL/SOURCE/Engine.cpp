#include "Engine.h"

#include <iostream>
using namespace std;

SceneManager* Engine::Scene_Manager = nullptr;
SDL_Window* Engine::window = nullptr;
SDL_Renderer* Engine::renderer = nullptr;
Clock* Engine::clock = new Clock();
Boolean* Engine::running = new Boolean();

SceneManager::SceneManager(SDL_Renderer* renderer)
{
	current_scene = nullptr;
	mouse_position = new MousePosition();
	continuous_processes = new ArrayList<ContinuousProcessManager*>();
	transitions = new ArrayList<Transition*>();
	this->renderer = renderer;
}

void SceneManager::CreateScene(string scene_name, function<void(Scene* sender)> initializer)
{
	scenes[scene_name] = new Scene(initializer);
	ChangeCurrentScene(scene_name);
}

void SceneManager::ChangeCurrentScene(string scene_name)
{
	current_scene = scenes[scene_name];
}

Scene* SceneManager::getCurrentScene()
{
	return current_scene;
}

Scene* SceneManager::getScene(string scene_name)
{
	return scenes[scene_name];
}

MousePosition* SceneManager::getMousePosition()
{
	static int a, b;
	SDL_GetMouseState(&a, &b);
	mouse_position->xpos = a;
	mouse_position->ypos = b;
	return mouse_position;
}

Scene::Scene(function<void(Scene* sender)> initializer)
{
	children = new Children();
	current_focus = nullptr;
	disable = false;
	initializer(this);
}

Scene::~Scene()
{
}

void Scene::setDisable(bool disable)
{
	this->disable = disable;
}

bool Scene::isDisable()
{
	return disable;
}

void Scene::allocateData(string data_id, any data)
{
	hashmap[data_id] = data;
}

Children* Scene::getChildren()
{
	return children;
}

void Scene::setFocus(VObject* object)
{
	current_focus = object;
}

VObject* Scene::getCurrentFocus()
{
	return current_focus;
}

void Engine::Start(const char* title, int xpos, int ypos, int width, int height, function<void(SceneManager* manager)> EngineStarter)
{
	running = new Boolean();
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		cout << "SDL: SISTEMAS INICIADOS" << endl;
		window = SDL_CreateWindow(title, xpos, ypos, width, height, 0);
		if (window != NULL)
		{
			cout << "SDL: VENTANA CREADA" << endl;
		}
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer != NULL)
		{
			cout << "SDL: RENDERER CREADO" << endl;
			if (SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255) != 0)
			{
				cout << "SDL: ERROR CON EL RENDERER" << endl;
			}
		}
		running->value = true;
	}
	else
	{
		cout << "SDL: FALLO AL INICIAR" << endl;
		running->value = false;
	}
	if (SDL_RenderClear(renderer) != 0)
	{
		cout << "ERROR CON EL RENDER CLEAR" << endl;
	}
	if (TTF_Init() == -1)
	{
		cout << "ERROR CON INICIAR TTF" << endl;
	}
	Scene_Manager = new SceneManager(renderer);
	EngineStarter(Scene_Manager);
}

SDL_Texture* Engine::loadTexture(string image_path)
{
	SDL_Surface* canvas= IMG_Load(image_path.c_str());
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, canvas);
	SDL_FreeSurface(canvas);
	return texture;
}
SDL_Texture* Engine::loadTexture(SDL_Surface* canvas)
{
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, canvas);
	SDL_FreeSurface(canvas);
	return texture;
}

Clock::Clock()
{
	laps = new ArrayList<Uint32>();
	frame = new Frame();
}

ArrayList<Uint32>* Clock::getLaps()
{
	return laps;
}

void Clock::lap()
{
	laps->set(SDL_GetTicks());
}


bool Clock::isTimeLapseCompleted(string time_lapse)
{
	return (SDL_GetTicks() >= time_lapses[time_lapse]);
}


void Clock::setTimeLapse(string name, float seconds)
{
	time_lapses[name] = SDL_GetTicks() + (int)(seconds * 1000);
}


void Engine::render()
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	if (Scene_Manager->getCurrentScene() != nullptr)
	{
		for (int i = 0; i < Scene_Manager->getCurrentScene()->getChildren()->layer0->getSize(); i++)
		{
			Scene_Manager->getCurrentScene()->getChildren()->layer0->get(i)->render();
		}
		for (int i = 0; i < Scene_Manager->getCurrentScene()->getChildren()->layer1->getSize(); i++)
		{
			Scene_Manager->getCurrentScene()->getChildren()->layer1->get(i)->render();
		}
		for (int i = 0; i < Scene_Manager->getCurrentScene()->getChildren()->layer2->getSize(); i++)
		{
			Scene_Manager->getCurrentScene()->getChildren()->layer2->get(i)->render();
		}
		for (int i = 0; i < Scene_Manager->getCurrentScene()->getChildren()->layer3->getSize(); i++)
		{
			Scene_Manager->getCurrentScene()->getChildren()->layer3->get(i)->render();
		}
		for (int i = 0; i < Scene_Manager->getCurrentScene()->getChildren()->layer4->getSize(); i++)
		{
			Scene_Manager->getCurrentScene()->getChildren()->layer4->get(i)->render();
		}
	}

	SDL_RenderPresent(renderer);
}
void Engine::handleEvents()
{
	static VObject* drag= nullptr;
	SDL_Event event;
	ArrayList<VObject*>* layer0 = Scene_Manager->getCurrentScene()->getChildren()->layer0;
	ArrayList<VObject*>* layer1 = Scene_Manager->getCurrentScene()->getChildren()->layer1;
	ArrayList<VObject*>* layer2 = Scene_Manager->getCurrentScene()->getChildren()->layer2;
	ArrayList<VObject*>* layer3 = Scene_Manager->getCurrentScene()->getChildren()->layer3;
	ArrayList<VObject*>* layer4 = Scene_Manager->getCurrentScene()->getChildren()->layer4;
	while (SDL_PollEvent(&event) == 1)
	{
		if (Engine::Scene_Manager->getCurrentScene()->isDisable()) continue;
		switch (event.type)
		{
			case SDL_QUIT:
			{
				running->value = false;
				return;
			}
			case SDL_MOUSEBUTTONDOWN:
			{
				Engine::Scene_Manager->getCurrentScene()->setFocus(nullptr);
				for (int i = 0; i < layer0->getSize(); i++)
				{
					if (layer0->get(i)->isDisable()) continue;
					if (layer0->get(i)->isMouseOver(event.button.x, event.button.y))
					{
						if (event.button.button == SDL_BUTTON_LEFT) Engine::Scene_Manager->getCurrentScene()->setFocus(layer0->get(i));
						if (layer0->get(i)->on_click != nullptr) layer0->get(i)->on_click(layer0->get(i), event.button);
					}
				}
				for (int i = 0; i < layer1->getSize(); i++)
				{
					if (layer1->get(i)->isDisable()) continue;
					if (layer1->get(i)->isMouseOver(event.button.x, event.button.y))
					{
						if (event.button.button == SDL_BUTTON_LEFT) Engine::Scene_Manager->getCurrentScene()->setFocus(layer1->get(i));
						if (layer1->get(i)->on_click != nullptr) layer1->get(i)->on_click(layer1->get(i), event.button);
					}
				}
				for (int i = 0; i < layer2->getSize(); i++)
				{
					if (layer2->get(i)->isDisable()) continue;
					if (layer2->get(i)->isMouseOver(event.button.x, event.button.y))
					{
						if (event.button.button == SDL_BUTTON_LEFT) Engine::Scene_Manager->getCurrentScene()->setFocus(layer2->get(i));
						if (layer2->get(i)->on_click != nullptr) layer2->get(i)->on_click(layer2->get(i), event.button);
					}
				}
				for (int i = 0; i < layer3->getSize(); i++)
				{
					if (layer3->get(i)->isDisable()) continue;
					if (layer3->get(i)->isMouseOver(event.button.x, event.button.y))
					{
						if (event.button.button == SDL_BUTTON_LEFT) Engine::Scene_Manager->getCurrentScene()->setFocus(layer3->get(i));
						if (layer3->get(i)->on_click != nullptr) layer3->get(i)->on_click(layer3->get(i), event.button);
					}
				}
				for (int i = 0; i < layer4->getSize(); i++)
				{
					if (layer4->get(i)->isDisable()) continue;
					if (layer4->get(i)->isMouseOver(event.button.x, event.button.y))
					{
						if (event.button.button == SDL_BUTTON_LEFT) Engine::Scene_Manager->getCurrentScene()->setFocus(layer4->get(i));
						if (layer4->get(i)->on_click != nullptr) layer4->get(i)->on_click(layer4->get(i), event.button);
					}
				}
				break;
			}
			case SDL_MOUSEMOTION:
			{
				if (Engine::Scene_Manager->getCurrentScene()->getCurrentFocus() == nullptr) break;
				if (drag != nullptr && drag->on_dragged!=nullptr)
				{
					drag->on_dragged(drag, event.motion);
					break;
				}
				if (event.motion.state == SDL_PRESSED && Engine::Scene_Manager->getCurrentScene()->getCurrentFocus()->isMouseOver(event.motion.x, event.motion.y))
				{
					drag = Engine::Scene_Manager->getCurrentScene()->getCurrentFocus();
					if (Engine::Scene_Manager->getCurrentScene()->getCurrentFocus()->on_drag_start != nullptr)
					{
						Engine::Scene_Manager->getCurrentScene()->getCurrentFocus()->on_drag_start(drag, event.button);
					}
				}
				break;
			}
			case SDL_MOUSEBUTTONUP:
			{
				if (drag != nullptr)
				{
					if (drag->on_drag_finish != nullptr)
					{
						drag->on_drag_finish(drag, event.button);
					}
					drag = nullptr;
				}
				break;
			}
			case SDL_KEYDOWN:
			{
				if(Scene_Manager->getCurrentScene()->getCurrentFocus()!=nullptr) Scene_Manager->getCurrentScene()->getCurrentFocus()->handler(event);
				break;
			}
			case SDL_KEYUP:
			{
				if (Scene_Manager->getCurrentScene()->getCurrentFocus() != nullptr) Scene_Manager->getCurrentScene()->getCurrentFocus()->handler(event);
				break;
			}
			default:
			{
				break;
			}
		}
	}
}
void Engine::update()
{
	if (Scene_Manager->getCurrentScene() != nullptr)
	{
		for (int i = 0; i < Scene_Manager->getCurrentScene()->getChildren()->layer0->getSize(); i++)
		{
			Scene_Manager->getCurrentScene()->getChildren()->layer0->get(i)->update();
		}
		for (int i = 0; i < Scene_Manager->getCurrentScene()->getChildren()->layer1->getSize(); i++)
		{
			Scene_Manager->getCurrentScene()->getChildren()->layer1->get(i)->update();
		}
		for (int i = 0; i < Scene_Manager->getCurrentScene()->getChildren()->layer2->getSize(); i++)
		{
			Scene_Manager->getCurrentScene()->getChildren()->layer2->get(i)->update();
		}
		for (int i = 0; i < Scene_Manager->getCurrentScene()->getChildren()->layer3->getSize(); i++)
		{
			Scene_Manager->getCurrentScene()->getChildren()->layer3->get(i)->update();
		}
		for (int i = 0; i < Scene_Manager->getCurrentScene()->getChildren()->layer4->getSize(); i++)
		{
			Scene_Manager->getCurrentScene()->getChildren()->layer4->get(i)->update();
		}
	}

	for (int i = 0; i < Scene_Manager->transitions->getSize(); i++)
	{
		if (Scene_Manager->transitions->get(i)->isFinished())
		{
			Scene_Manager->transitions->drop(i);
			i--;
		}
		else
		{
			if (Scene_Manager->transitions->get(i)->isPaused())
			{
				Scene_Manager->transitions->get(i)->continue_pause();
			}
			else if (Scene_Manager->transitions->get(i)->isRunning())
			{
				Scene_Manager->transitions->get(i)->continue_process();
			}
		}
	}


	for (int i = 0; i < Scene_Manager->continuous_processes->getSize(); i++)
	{
		if (Scene_Manager->continuous_processes->get(i)->isRunning())
		{
			Scene_Manager->continuous_processes->get(i)->process();
		}
		if (Scene_Manager->continuous_processes->get(i)->processHasEnded())
		{
			Scene_Manager->continuous_processes->drop(i);
		}
	}
}

Frame::Frame()
{
	this_start = 0;
	previous_duration = 0;
	previous_end = 0;
}

void Frame::frameStart()
{
	this_start = SDL_GetTicks();
}

void Frame::frameEnd()
{
	previous_duration = SDL_GetTicks() - this_start;
	if (frame_delay > previous_duration)
	{
		SDL_Delay(frame_delay - previous_duration);
	}
	previous_end = SDL_GetTicks();
	previous_duration = previous_end - this_start;
}

void Engine::close()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	running->value = false;
	cout << "SDL CERRADO" << endl;
}

