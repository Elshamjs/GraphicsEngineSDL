#pragma once

#include <functional>

#ifndef VOBJECT_H
#define VOBJECT_H

enum class LAYER { LAYER_0 = 0, LAYER_1, LAYER_2, LAYER_3, LAYER_4 };
//Clase base para objectos gráficos, cada instancia de sus subclases, se debe agregar a su respectiva Scene por medio de getChildren() para su posterior renderización
class VObject
{
public:
	~VObject();
protected:
	friend class Engine;
	friend class Scene;
	friend class Children;
	friend class Transition;
	friend class TranslateTransition;
	friend class RotationTransition;
	friend class FadeTransition;
	friend class ScaleTransition;
	SDL_FRect* dest_rect;
	float* width;
	float* height;
	float* xpos;
	float* ypos;
	SDL_Texture* normal_texure;
	SDL_Texture* hover_texture;
	LAYER object_layer;
	bool visible= true;
	bool hovered= false;
	bool disable = false;
	string accessible_text;
	function<void(VObject* sender, SDL_MouseButtonEvent e)>  on_click = nullptr;
	function<void(VObject* sender, SDL_MouseButtonEvent e)>  on_drag_start = nullptr;
	function<void(VObject* sender, SDL_MouseMotionEvent e)>  on_dragged = nullptr;
	function<void(VObject* sender, SDL_MouseButtonEvent e)>  on_drag_finish = nullptr;
	function<void(VObject* sender, SDL_KeyboardEvent* e)>  on_key = nullptr;

	float opacity;
	float scaleX;
	float scaleY;
	SDL_FPoint* rotation_axis;
	double rotation;
	SDL_RendererFlip flip;

	VObject(float xpos, float ypos, float width, float height, Assets::TEXTURE tex, LAYER object_layer);
	VObject(float xpos, float ypos, float width, float height, SDL_Texture* tex, LAYER object_layer);
	VObject(LAYER layer);

	virtual void render();
	virtual void handler(SDL_Event event);
	virtual void update();

	virtual void setOpacity(float opacity);
	virtual float getOpacity();
	virtual float getScaleX();
	virtual float getScaleY();
	virtual void setScaleX(float scale);
	virtual void setScaleY(float scale);
	virtual void setRotationAxis(float x, float y, SDL_RendererFlip flip);
	virtual void setRotation(double rotation);
	virtual double getRotation();

	virtual void changeTexture(SDL_Texture* tex);
	virtual void changeTexture(Assets::TEXTURE new_texture);
	virtual void setHoverTexture(Assets::TEXTURE tex);
	virtual void setHoverTexture(SDL_Texture* tex);
	virtual SDL_Texture* getTexture();
	virtual SDL_Texture* getHoverTexture();
	virtual float getY();
	virtual float getX();
	virtual void setY(float y);
	virtual void setX(float x);
	virtual float getWidth();
	virtual float getHeight();
	virtual void setWidth(float w);
	virtual void setHeight(float h);
	virtual bool isHover();
	virtual void setVisible(bool v);
	virtual void setDisable(bool disable);
	virtual bool isDisable();
	virtual bool isVisible();
	virtual bool isFocused();
	virtual bool isMouseOver();
	virtual bool isMouseOver(int x, int y);
	virtual void translate(float x, float y);
	virtual LAYER getLayer();
	virtual void relocate(float new_x, float new_y);
	virtual void resize(float w, float h);

	virtual void setAccessibleText(string text);
	virtual string getAccessibleText();

	virtual void setOnClickEvent(function<void(VObject* sender, SDL_MouseButtonEvent e)> on_click);
	virtual void setOnDragStartEvent(function<void(VObject* sender, SDL_MouseButtonEvent e)> on_drag_start);
	virtual void setOnDraggedEvent(function<void(VObject* sender, SDL_MouseMotionEvent e)> on_dragged);
	virtual void setOnDragFinishEvent(function<void(VObject* sender, SDL_MouseButtonEvent e)> on_drag_finish);
	virtual void setOnKeyPressedEvent(function<void(VObject* sender, SDL_KeyboardEvent* e)> on_key_pressed);

	virtual function<void(VObject* sender, SDL_MouseButtonEvent e)> getOnClickEvent();
	virtual function<void(VObject* sender, SDL_MouseButtonEvent e)> getOnDragStartEvent();
	virtual function<void(VObject* sender, SDL_MouseMotionEvent e)> getOnDraggedEvent();
	virtual function<void(VObject* sender, SDL_MouseButtonEvent e)> getOnDragFinishEvent();
	virtual function<void(VObject* sender, SDL_KeyboardEvent* e)> getOnKeyEvent();

	
};
#endif // !VOBJECT_H