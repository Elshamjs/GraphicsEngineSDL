#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "ArrayList.h"
#include "Assets.h"
#include "VObject.h"
#include "Line.h"
#include "Rectangle.h"
#include "ContinuousProcessManager.h"
#include "Transition.h"
#include "TranslateTransition.h"
#include "RotationTransition.h"
#include "FadeTransition.h"
#include "ScaleTransition.h"
#include "TextureFrame.h"
#include "UIButton.h"
#include "UILabel.h"
#include "UITextField.h"
#include "GrafoFile.h"
#include "Vertice.h"
#include <map>
#include <any>

using namespace std;

struct Boolean
{
	bool value = false;
};
struct Float
{
	float value = .0;
};
struct Integer
{
	int value = 0;
};

/// *Componente para aplicar rotaciones a texturas de instancias de VObject*/
// struct RotationComponent
// {
/// *Los grados de la rotacion, un valor entre 0 y 360*/
// double degrees = 0;
/// *El punto de eje de la rotacion*/
// /*SDL_Point* axis = new SDL_Point{0,0};*/
/// *Se refiere en que sentido se va a voltear la textura
// SDL_FLIP_NONE: Solo se aplicara una rotacion plana a la textura, no se volteara
// SDL_FLIP_HORIZONTAL: Se aplicara una rotacion volteando la textura horizontalmente
// SDL_FLIP_VERTICAL: Se aplicara una rotacion volteando la textura verticalmente*/
// /*SDL_RendererFlip flip = SDL_FLIP_VERTICAL;*/
// };

struct MousePosition
{
	int xpos = 0;
	int ypos = 0;
};

class Children
{
public:
	ArrayList<VObject*>* layer0 = nullptr;
	ArrayList<VObject*>* layer1 = nullptr;
	ArrayList<VObject*>* layer2 = nullptr;
	ArrayList<VObject*>* layer3 = nullptr;
	ArrayList<VObject*>* layer4 = nullptr;
	Children()
	{
		layer0 = new ArrayList<VObject*>();
		layer1 = new ArrayList<VObject*>();
		layer2 = new ArrayList<VObject*>();
		layer3 = new ArrayList<VObject*>();
		layer4 = new ArrayList<VObject*>();
	}
	void add(VObject* visual_object)
	{
		switch (visual_object->getLayer())
		{
		case LAYER::LAYER_0:
			layer0->set(visual_object);
			break;
		case LAYER::LAYER_1:
			layer1->set(visual_object);
			break;
		case LAYER::LAYER_2:
			layer2->set(visual_object);
			break;
		case LAYER::LAYER_3:
			layer3->set(visual_object);
			break;
		case LAYER::LAYER_4:
			layer4->set(visual_object);
			break;
		default:
			layer3->set(visual_object);
			break;
		}
	}
	bool remove(VObject* visual_object)
	{
		switch (visual_object->getLayer())
		{
		case LAYER::LAYER_0:
			return layer0->drop(visual_object);
		case LAYER::LAYER_1:
			return layer1->drop(visual_object);
		case LAYER::LAYER_2:
			return layer2->drop(visual_object);
		case LAYER::LAYER_3:
			return layer3->drop(visual_object);
		case LAYER::LAYER_4:
			return layer4->drop(visual_object);
		}
	}
};

class Scene
{
private:
	Children* children;
	VObject* current_focus;
	map<string, any> hashmap;
	function<void(Scene* sender)> initializer;
	bool disable;
public:
	Scene(function<void(Scene* sender)> initializer);
	~Scene();
	void setDisable(bool disable);
	bool isDisable();
	void allocateData(string data_id, any data);
	Children* getChildren();
	void setFocus(VObject* object);
	VObject* getCurrentFocus();
};

// Scenes del programa
class SceneManager
{
private:
	Scene* current_scene;
	SDL_Renderer* renderer;
	MousePosition* mouse_position;
	map<string, Scene*> scenes;
protected:
	ArrayList<ContinuousProcessManager*>* continuous_processes;
	ArrayList<Transition*>* transitions;
	friend class Engine;
	friend class ContinuousProcessManager;
	friend class Transition;
	friend class TranslateTransition;
public:
	SceneManager(SDL_Renderer* renderer);
	void CreateScene(string scene_name, function<void(Scene* parent)> initializer);
	void ChangeCurrentScene(string scene_name);
	Scene* getCurrentScene();
	Scene* getScene(string scene_name);
	MousePosition* getMousePosition();
};

class Frame
{
public:
	const int FPS = 60;
	const int frame_delay = 1000 / FPS;
	Frame();
	Uint32 this_start;
	Uint32 previous_end;
	int previous_duration;
	void frameStart();
	void frameEnd();
};

class Clock
{
private:
	map<string, Uint32> time_lapses;
	ArrayList<Uint32>* laps;
public:
	Clock();
	Frame* frame;
	void lap();
	void setTimeLapse(string name, float seconds);
	bool isTimeLapseCompleted(string time_lapse);
	ArrayList<Uint32>* getLaps();
};

class Engine
{
public:
	static void render();
	static void handleEvents();
	static void update();
	static void close();
	static SceneManager* Scene_Manager;
	static SDL_Renderer* renderer;
	static SDL_Window* window;
	static Boolean* running;
	static Clock* clock;
	static SDL_Texture* loadTexture(string image_path);
	static SDL_Texture* loadTexture(SDL_Surface* canvas);
	static void Start(const char* title, int xpos, int ypos, int width, int height, function<void(SceneManager* manager)> EngineStarter);
};