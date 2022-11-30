#include "Engine.h"


UIButton::UIButton(float x, float y, float width, float height, Assets::TEXTURE normal_tex, Assets::TEXTURE hover_tex, LAYER l, function<void(VObject*, SDL_MouseButtonEvent)> on_click)  : VObject(x, y, width, height, normal_tex, l)
{
	hover_texture = Engine::loadTexture(Assets::getTexturePath(hover_tex));
	this->on_click = on_click;
}


void UIButton::changeTexture(Assets::TEXTURE new_texture)
{
	if (normal_texure != nullptr) SDL_DestroyTexture(normal_texure);
	normal_texure = Engine::loadTexture(Assets::getTexturePath(new_texture));
}

void UIButton::setHoverTexture(Assets::TEXTURE tex)
{
	if (hover_texture != nullptr) SDL_DestroyTexture(hover_texture);
	hover_texture = Engine::loadTexture(Assets::getTexturePath(tex));
}

SDL_Texture* UIButton::getTexture()
{
	return normal_texure;
}

SDL_Texture* UIButton::getHoverTexture()
{
	return hover_texture;
}

float UIButton::getWidth()
{
	return *width;
}

float UIButton::getHeight()
{
	return *height;
}

void UIButton::setWidth(float w)
{
	*width = w;
}

void UIButton::setHeight(float h)
{
	*height = h;
}

float UIButton::getY()
{
	return *ypos;
}

float UIButton::getX()
{
	return *xpos;
}

void UIButton::setY(float y)
{
	*ypos = y;
}

void UIButton::setX(float x)
{
	*xpos = x;
}

bool UIButton::isHover()
{
	return hovered;
}

void UIButton::setVisible(bool v)
{
	visible = v;
}

void UIButton::setDisable(bool disable)
{
	this->disable = disable;
}

bool UIButton::isDisable()
{
	return disable;
}

bool UIButton::isVisible()
{
	return visible;
}

bool UIButton::isFocused()
{
	return (Engine::Scene_Manager->getCurrentScene()->getCurrentFocus() == this ? true : false);
}

bool UIButton::isMouseOver()
{
	return ((Engine::Scene_Manager->getMousePosition()->xpos > dest_rect->x && Engine::Scene_Manager->getMousePosition()->xpos < dest_rect->x + dest_rect->w) && (Engine::Scene_Manager->getMousePosition()->ypos > dest_rect->y && Engine::Scene_Manager->getMousePosition()->ypos < dest_rect->y + dest_rect->h));
}

bool UIButton::isMouseOver(int x, int y)
{
	static MousePosition mouse = MousePosition();
	mouse.xpos = x;
	mouse.ypos = y;
	return ((mouse.xpos > dest_rect->x && mouse.xpos < dest_rect->x + dest_rect->w) && (mouse.ypos > dest_rect->y && mouse.ypos < dest_rect->y + dest_rect->h));
}

void UIButton::translate(float x, float y)
{
	dest_rect->x = dest_rect->x + x;
	dest_rect->y = dest_rect->y + y;
}

LAYER UIButton::getLayer()
{
	return object_layer;
}

void UIButton::relocate(float new_x, float new_y)
{
	*xpos = new_x;
	*ypos = new_y;
}

void UIButton::resize(float w, float h)
{
	*width = w;
	*height = h;
}

void UIButton::setAccessibleText(string text)
{
	accessible_text = text;
}

string UIButton::getAccessibleText()
{
	return accessible_text;
}

function<void(VObject* sender, SDL_MouseButtonEvent e)> UIButton::getOnClickEvent()
{
	return on_click;
}

function<void(VObject* sender, SDL_MouseButtonEvent e)> UIButton::getOnDragStartEvent()
{
	return on_drag_start;

}

function<void(VObject* sender, SDL_MouseMotionEvent e)> UIButton::getOnDraggedEvent()
{
	return on_dragged;
}

function<void(VObject* sender, SDL_MouseButtonEvent e)> UIButton::getOnDragFinishEvent()
{
	return on_drag_finish;
}

function<void(VObject* sender, SDL_KeyboardEvent* e)> UIButton::getOnKeyEvent()
{
	return on_key;
}

void UIButton::setOnClickEvent(function<void(VObject* sender, SDL_MouseButtonEvent e)> on_click)
{
	this->on_click = on_click;
}

void UIButton::setOnDragStartEvent(function<void(VObject* sender, SDL_MouseButtonEvent e)> on_drag_start)
{
	this->on_drag_start = on_drag_start;
}

void UIButton::setOnDraggedEvent(function<void(VObject* sender, SDL_MouseMotionEvent e)> on_dragged)
{
	this->on_dragged = on_dragged;
}

void UIButton::setOnDragFinishEvent(function<void(VObject* sender, SDL_MouseButtonEvent e)> on_drag_finish)
{
	this->on_drag_finish = on_drag_finish;
}

void UIButton::setOnKeyPressedEvent(function<void(VObject* sender, SDL_KeyboardEvent* e)> on_key_pressed)
{
	this->on_key = on_key_pressed;
}

void UIButton::setOpacity(float opacity)
{
	this->opacity = (opacity > 1 ? 1 : (opacity < 0 ? 0 : opacity));
}

float UIButton::getOpacity()
{
	return opacity;
}

float UIButton::getScaleX()
{
	return scaleX;
}

float UIButton::getScaleY()
{
	return scaleY;
}

void UIButton::setScaleX(float scale)
{
	scaleX = (scale < 0 ? 0 : scale);
}

void UIButton::setScaleY(float scale)
{
	scaleY = (scale < 0 ? 0 : scale);
}

void UIButton::setRotationAxis(float x, float y, SDL_RendererFlip flip)
{
	rotation_axis->x = x;
	rotation_axis->y = y;
	this->flip = flip;
}

void UIButton::setRotation(double rotation)
{
	this->rotation = rotation;
}

double UIButton::getRotation()
{
	return rotation;
}