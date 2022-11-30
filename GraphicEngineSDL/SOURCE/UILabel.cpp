#include <iostream>
#include "Engine.h"
using namespace std;
static SDL_Point p = SDL_Point();
void UILabel::render()
{
	static SDL_FRect* render_destination = new SDL_FRect();
	if (visible)
	{
		render_destination->w = getWidth() * scaleX;
		render_destination->x -= render_destination->w - getWidth();
		render_destination->h = getHeight() * scaleY;
		render_destination->y -= render_destination->h - getHeight();
		SDL_SetTextureAlphaMod(normal_texure, ((int)(opacity * 255.0f)));
		SDL_RenderCopyExF(Engine::renderer, normal_texure, nullptr, render_destination, rotation, rotation_axis, flip);
	}
}
UILabel::UILabel(float x, float y, string message, Assets::FONT font, int size, LAYER l, SDL_Color rgb) : VObject(x, y, 0, 0, Assets::TEXTURE::NON_TEXTURE, l)
{
	this->font = font;
	font_size = size;
	lb_color = rgb;
	lb_font = Assets::loadFont(font, size);
	SDL_Surface* canvas = TTF_RenderText_Blended(lb_font, message.c_str(), lb_color);
	this->normal_texure = Engine::loadTexture(canvas);
	SDL_QueryTexture(this->normal_texure, nullptr, nullptr, &p.x, &p.y);
	dest_rect->w = (float)p.x;
	dest_rect->h = (float)p.y;
}
UILabel::UILabel(float x, float y, string message, Assets::FONT font, int size, LAYER l, Assets::COLOR rgb) : VObject(x, y, 0, 0, Assets::TEXTURE::NON_TEXTURE, l)
{
	this->font = font;
	font_size = size;
	lb_color = Assets::loadColor(rgb);
	lb_font = Assets::loadFont(font, size);
	SDL_Surface* canvas = TTF_RenderText_Blended(lb_font, message.c_str(), lb_color);
	this->normal_texure = Engine::loadTexture(canvas);
	SDL_QueryTexture(this->normal_texure, nullptr, nullptr, &p.x, &p.y);
	dest_rect->w = (float)p.x;
	dest_rect->h = (float)p.y;
}
UILabel::~UILabel()
{
}
void UILabel::setText(string new_message)
{
	message = new_message;
	SDL_Surface* canvas = TTF_RenderText_Blended(lb_font, message.c_str(), lb_color);
	SDL_DestroyTexture(this->normal_texure);
	this->normal_texure = Engine::loadTexture(canvas);
	SDL_QueryTexture(this->normal_texure, nullptr, nullptr, &p.x, &p.y);
	dest_rect->w = (float)p.x;
	dest_rect->h = (float)p.y;
}
void UILabel::setFontSize(int size)
{
	font_size = size;
	lb_font = Assets::loadFont(font, size);
	SDL_Surface* canvas = TTF_RenderText_Blended(lb_font, message.c_str(), lb_color);
	SDL_DestroyTexture(this->normal_texure);
	this->normal_texure = Engine::loadTexture(canvas);
	SDL_QueryTexture(this->normal_texure, nullptr, nullptr, &p.x, &p.y);
	dest_rect->w = (float)p.x;
	dest_rect->h = (float)p.y;
}
int UILabel::getFontSize()
{
	return font_size;
}
void UILabel::setTextColor(Assets::COLOR color)
{
	lb_color = Assets::loadColor(color);
	SDL_Surface* canvas = TTF_RenderText_Blended(lb_font, message.c_str(), lb_color);
	SDL_DestroyTexture(this->normal_texure);
	this->normal_texure = Engine::loadTexture(canvas);
}
void UILabel::setTextColor(SDL_Color color)
{
	lb_color = color;
	SDL_Surface* canvas = TTF_RenderText_Blended(lb_font, message.c_str(), lb_color);
	SDL_DestroyTexture(this->normal_texure);
	this->normal_texure = Engine::loadTexture(canvas);
}
SDL_Color UILabel::getTextColor()
{
	return lb_color;
}
string UILabel::getText()
{
	return message;
}

SDL_Texture* UILabel::getTexture()
{
	return normal_texure;
}

float UILabel::getWidth()
{
	return *width;
}

float UILabel::getHeight()
{
	return *height;
}

void UILabel::setWidth(float w)
{
	*width = w;
}

void UILabel::setHeight(float h)
{
	*height = h;
}

float UILabel::getY()
{
	return *ypos;
}

float UILabel::getX()
{
	return *xpos;
}

void UILabel::setY(float y)
{
	*ypos = y;
}

void UILabel::setX(float x)
{
	*xpos = x;
}

bool UILabel::isHover()
{
	return hovered;
}

void UILabel::setVisible(bool v)
{
	visible = v;
}

void UILabel::setDisable(bool disable)
{
	this->disable = disable;
}

bool UILabel::isDisable()
{
	return disable;
}

bool UILabel::isVisible()
{
	return visible;
}

bool UILabel::isFocused()
{
	return (Engine::Scene_Manager->getCurrentScene()->getCurrentFocus() == this ? true : false);
}

bool UILabel::isMouseOver()
{
	return ((Engine::Scene_Manager->getMousePosition()->xpos > dest_rect->x && Engine::Scene_Manager->getMousePosition()->xpos < dest_rect->x + dest_rect->w) && (Engine::Scene_Manager->getMousePosition()->ypos > dest_rect->y && Engine::Scene_Manager->getMousePosition()->ypos < dest_rect->y + dest_rect->h));
}

bool UILabel::isMouseOver(int x, int y)
{
	static MousePosition mouse = MousePosition();
	mouse.xpos = x;
	mouse.ypos = y;
	return ((mouse.xpos > dest_rect->x && mouse.xpos < dest_rect->x + dest_rect->w) && (mouse.ypos > dest_rect->y && mouse.ypos < dest_rect->y + dest_rect->h));
}

void UILabel::translate(float x, float y)
{
	dest_rect->x = dest_rect->x + x;
	dest_rect->y = dest_rect->y + y;
}

LAYER UILabel::getLayer()
{
	return object_layer;
}

void UILabel::relocate(float new_x, float new_y)
{
	*xpos = new_x;
	*ypos = new_y;
}

void UILabel::resize(float w, float h)
{
	*width = w;
	*height = h;
}

void UILabel::setAccessibleText(string text)
{
	accessible_text = text;
}

string UILabel::getAccessibleText()
{
	return accessible_text;
}

function<void(VObject* sender, SDL_MouseButtonEvent e)> UILabel::getOnClickEvent()
{
	return on_click;
}

function<void(VObject* sender, SDL_MouseButtonEvent e)> UILabel::getOnDragStartEvent()
{
	return on_drag_start;

}

function<void(VObject* sender, SDL_MouseMotionEvent e)> UILabel::getOnDraggedEvent()
{
	return on_dragged;
}

function<void(VObject* sender, SDL_MouseButtonEvent e)> UILabel::getOnDragFinishEvent()
{
	return on_drag_finish;
}

function<void(VObject* sender, SDL_KeyboardEvent* e)> UILabel::getOnKeyEvent()
{
	return on_key;
}

void UILabel::setOnClickEvent(function<void(VObject* sender, SDL_MouseButtonEvent e)> on_click)
{
	this->on_click = on_click;
}

void UILabel::setOnDragStartEvent(function<void(VObject* sender, SDL_MouseButtonEvent e)> on_drag_start)
{
	this->on_drag_start = on_drag_start;
}

void UILabel::setOnDraggedEvent(function<void(VObject* sender, SDL_MouseMotionEvent e)> on_dragged)
{
	this->on_dragged = on_dragged;
}

void UILabel::setOnDragFinishEvent(function<void(VObject* sender, SDL_MouseButtonEvent e)> on_drag_finish)
{
	this->on_drag_finish = on_drag_finish;
}

void UILabel::setOnKeyPressedEvent(function<void(VObject* sender, SDL_KeyboardEvent* e)> on_key_pressed)
{
	this->on_key = on_key_pressed;
}

void UILabel::setOpacity(float opacity)
{
	this->opacity = (opacity > 1 ? 1 : (opacity < 0 ? 0 : opacity));
}

float UILabel::getOpacity()
{
	return opacity;
}

float UILabel::getScaleX()
{
	return scaleX;
}

float UILabel::getScaleY()
{
	return scaleY;
}

void UILabel::setScaleX(float scale)
{
	scaleX = (scale < 0 ? 0 : scale);
}

void UILabel::setScaleY(float scale)
{
	scaleY = (scale < 0 ? 0 : scale);
}

void UILabel::setRotationAxis(float x, float y, SDL_RendererFlip flip)
{
	rotation_axis->x = x;
	rotation_axis->y = y;
	this->flip = flip;
}

void UILabel::setRotation(double rotation)
{
	this->rotation = rotation;
}

double UILabel::getRotation()
{
	return rotation;
}