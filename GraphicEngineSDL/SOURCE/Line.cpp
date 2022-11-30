#include "Engine.h"
#include "tools.h"
#include <math.h>
static Uint32 rmask, gmask, bmask, amask;
void Line::render()
{
	static double m, degrees;
	static Uint32 rmask, gmask, bmask, amask;
	static SDL_FRect* render_destination= new SDL_FRect();
	if (visible)
	{
		m = (end_y - (ini_y)) / (end_x - (ini_x));
		degrees = (end_x<ini_x ? toDegrees(atan(m))+180 + rotation : toDegrees(atan(m)+rotation));
		render_destination->w = getWidth() * scaleX;
		render_destination->x = getX() - (render_destination->w - getWidth());
		render_destination->h = getHeight() * scaleY;
		render_destination->y = getY() - (render_destination->h - getHeight());
		SDL_SetTextureAlphaMod(normal_texure, ((int)(opacity * 255.0f)));
		SDL_RenderCopyExF(Engine::renderer, normal_texure, nullptr, render_destination, degrees, rotation_axis, flip);
	}
}

float Line::getY()
{
	return ini_y;
}

float Line::getX()
{
	return ini_x;
}

void Line::setY(float y)
{
	setIniY(y);
}

void Line::setX(float x)
{
	setIniX(x);
}

float Line::getWidth()
{
	return dest_rect->w;
}

float Line::getHeight()
{
	return dest_rect->h;
}

Line::Line(float ini_x, float ini_y, float end_x, float end_y, float weight, Assets::COLOR color, LAYER layer) : VObject(layer)
{
	this->ini_x = ini_x;
	this->ini_y = ini_y;
	this->end_x = end_x;
	this->end_y = end_y;
	this->weight = (weight < 0 ? weight * -1 : weight); 
	this->color = Assets::loadColor(color);
	dest_rect = new SDL_FRect{ ini_x, ini_y, (float)pythagorasC((double)end_y - (double)ini_y, (double)end_x - (double)ini_x), weight };
	normal_texure = Assets::createTextureFromColor(this->color);
	rotation = 0;
	rotation_axis = new SDL_FPoint{ 0,0 };
	opacity = 1;
	scaleX = 1;
	scaleY = 1;
	flip = SDL_RendererFlip::SDL_FLIP_NONE;
}

Line::Line(float ini_x, float ini_y, float end_x, float end_y, float weight, SDL_Color color, LAYER layer) : VObject(layer)
{
	this->ini_x = ini_x;
	this->ini_y = ini_y;
	this->end_x = end_x;
	this->end_y = end_y;
	this->weight = (weight < 0 ? weight * -1 : weight);
	this->color = color;
	dest_rect = new SDL_FRect{ ini_x, ini_y, (float)sqrt(pow((end_y - ini_y), 2) + pow((end_x - ini_x), 2)), weight };
	normal_texure = Assets::createTextureFromColor(this->color);
	rotation = 0;
	rotation_axis = new SDL_FPoint{ 0,0 };
	opacity = 1;
	scaleX = 1;
	scaleY = 1;
	flip = SDL_RendererFlip::SDL_FLIP_NONE;
}

void Line::setIniX(float x)
{
	ini_x = x;
	dest_rect->x = x;
	dest_rect->w = (float)pythagorasC(end_y - (double)ini_y, end_x - (double)ini_x);
}

void Line::setIniY(float y)
{
	ini_y = y;
	dest_rect->y = y;
	dest_rect->w = (float)pythagorasC(end_y - (double)ini_y, end_x - (double)ini_x);
}

void Line::setEndX(float x)
{
	end_x = x;
	dest_rect->w = (float)pythagorasC(end_y - (double)ini_y, end_x - (double)ini_x);
}

void Line::setEndY(float y)
{
	end_y = y;
	dest_rect->w = (float)pythagorasC(end_y - (double)ini_y, end_x - (double)ini_x);
}

float Line::getIniX()
{
	return ini_x;
}

float Line::getIniY()
{
	return ini_y;
}

float Line::getEndX()
{
	return end_x;
}

float Line::getEndY()
{
	return end_y;
}

void Line::setWeight(float weight)
{
	this->weight = abs(weight);
	dest_rect->h = abs(weight);
}

float Line::getWeight()
{
	return weight;
}


void Line::setColor(SDL_Color color)
{
	this->color = color;
	SDL_DestroyTexture(normal_texure);
	normal_texure = Assets::createTextureFromColor(color);
}

void Line::setColor(Assets::COLOR color)
{
	this->color = Assets::loadColor(color);
	SDL_DestroyTexture(normal_texure);
	normal_texure = Assets::createTextureFromColor(this->color);
}

SDL_Color Line::getColor()
{
	return color;
}

void Line::setOpacity(float opacity)
{
	this->opacity = (opacity > 1 ? 1 : (opacity < 0 ? 0 : opacity));
}

float Line::getOpacity()
{
	return opacity;
}

float Line::getScaleX()
{
	return scaleX;
}

float Line::getScaleY()
{
	return scaleY;
}

void Line::setScaleX(float scale)
{
	scaleX = (scale < 0 ? 0 : scale);
}

void Line::setScaleY(float scale)
{
	scaleY = (scale < 0 ? 0 : scale);
}

void Line::setRotationAxis(float x, float y, SDL_RendererFlip flip)
{
	rotation_axis->x = x;
	rotation_axis->y = y;
	this->flip = flip;
}

void Line::setRotation(double rotation)
{
	this->rotation = rotation;
}

double Line::getRotation()
{
	return rotation;
}
