#include "Engine.h"

float Rectangle::getWidth()
{
	return *width;
}

float Rectangle::getHeight()
{
	return *height;
}

void Rectangle::setWidth(float w)
{
	*width = w;
}

void Rectangle::setHeight(float h)
{
	*height = h;
}

void Rectangle::setColor(SDL_Color color)
{
	this->color = color;
}

void Rectangle::setColor(Assets::COLOR color)
{
	this->color = Assets::loadColor(color);
}

SDL_Color Rectangle::getColor()
{
	return color;
}

Rectangle::Rectangle(float x, float y, float width, float height, Assets::COLOR color, LAYER l) : VObject(x, y, width, height, nullptr, l)
{
	this->color = Assets::loadColor(color);
	normal_texure = Assets::createTextureFromColor(this->color);
}

Rectangle::Rectangle(float x, float y, float width, float height, SDL_Color color, LAYER l) : VObject(x, y, width, height, nullptr, l)
{
	this->color = color;
	normal_texure = Assets::createTextureFromColor(color);
}

float Rectangle::getY()
{
	return *ypos;
}

float Rectangle::getX()
{
	return *xpos;
}

void Rectangle::setY(float y)
{
	*ypos = y;
}

void Rectangle::setX(float x)
{
	*xpos = x;
}

bool Rectangle::isHover()
{
	return hovered;
}

void Rectangle::setVisible(bool v)
{
	visible = v;
}

void Rectangle::setDisable(bool disable)
{
	this->disable = disable;
}

bool Rectangle::isDisable()
{
	return disable;
}

bool Rectangle::isVisible()
{
	return visible;
}

bool Rectangle::isFocused()
{
	return (Engine::Scene_Manager->getCurrentScene()->getCurrentFocus() == this ? true : false);
}

bool Rectangle::isMouseOver()
{
	return ((Engine::Scene_Manager->getMousePosition()->xpos > dest_rect->x && Engine::Scene_Manager->getMousePosition()->xpos < dest_rect->x + dest_rect->w) && (Engine::Scene_Manager->getMousePosition()->ypos > dest_rect->y && Engine::Scene_Manager->getMousePosition()->ypos < dest_rect->y + dest_rect->h));
}

bool Rectangle::isMouseOver(int x, int y)
{
	static MousePosition mouse = MousePosition();
	mouse.xpos = x;
	mouse.ypos = y;
	return ((mouse.xpos > dest_rect->x && mouse.xpos < dest_rect->x + dest_rect->w) && (mouse.ypos > dest_rect->y && mouse.ypos < dest_rect->y + dest_rect->h));
}

void Rectangle::translate(float x, float y)
{
	dest_rect->x = dest_rect->x + x;
	dest_rect->y = dest_rect->y + y;
}

LAYER Rectangle::getLayer()
{
	return object_layer;
}

void Rectangle::relocate(float new_x, float new_y)
{
	*xpos = new_x;
	*ypos = new_y;
}

void Rectangle::resize(float w, float h)
{
	*width = w;
	*height = h;
}

void Rectangle::setAccessibleText(string text)
{
	accessible_text = text;
}

string Rectangle::getAccessibleText()
{
	return accessible_text;
}

function<void(VObject* sender, SDL_MouseButtonEvent e)> Rectangle::getOnClickEvent()
{
	return on_click;
}

function<void(VObject* sender, SDL_MouseButtonEvent e)> Rectangle::getOnDragStartEvent()
{
	return on_drag_start;

}

function<void(VObject* sender, SDL_MouseMotionEvent e)> Rectangle::getOnDraggedEvent()
{
	return on_dragged;
}

function<void(VObject* sender, SDL_MouseButtonEvent e)> Rectangle::getOnDragFinishEvent()
{
	return on_drag_finish;
}

function<void(VObject* sender, SDL_KeyboardEvent* e)> Rectangle::getOnKeyEvent()
{
	return on_key;
}

void Rectangle::setOnClickEvent(function<void(VObject* sender, SDL_MouseButtonEvent e)> on_click)
{
	this->on_click = on_click;
}

void Rectangle::setOnDragStartEvent(function<void(VObject* sender, SDL_MouseButtonEvent e)> on_drag_start)
{
	this->on_drag_start = on_drag_start;
}

void Rectangle::setOnDraggedEvent(function<void(VObject* sender, SDL_MouseMotionEvent e)> on_dragged)
{
	this->on_dragged = on_dragged;
}

void Rectangle::setOnDragFinishEvent(function<void(VObject* sender, SDL_MouseButtonEvent e)> on_drag_finish)
{
	this->on_drag_finish = on_drag_finish;
}

void Rectangle::setOnKeyPressedEvent(function<void(VObject* sender, SDL_KeyboardEvent* e)> on_key_pressed)
{
	this->on_key = on_key_pressed;
}

void Rectangle::setOpacity(float opacity)
{
	this->opacity = (opacity > 1 ? 1 : (opacity < 0 ? 0 : opacity));
}

float Rectangle::getOpacity()
{
	return opacity;
}

float Rectangle::getScaleX()
{
	return scaleX;
}

float Rectangle::getScaleY()
{
	return scaleY;
}

void Rectangle::setScaleX(float scale)
{
	scaleX = (scale < 0 ? 0 : scale);
}

void Rectangle::setScaleY(float scale)
{
	scaleY = (scale < 0 ? 0 : scale);
}

void Rectangle::setRotationAxis(float x, float y, SDL_RendererFlip flip)
{
	rotation_axis->x = x;
	rotation_axis->y = y;
	this->flip = flip;
}

void Rectangle::setRotation(double rotation)
{
	this->rotation = rotation;
}

double Rectangle::getRotation()
{
	return rotation;
}