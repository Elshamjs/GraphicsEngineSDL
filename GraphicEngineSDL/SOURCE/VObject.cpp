#include "Engine.h"

void VObject::render()
{
	static SDL_FRect* render_destination = new SDL_FRect();
	if (hovered && hover_texture != nullptr)
	{
		render_destination->w = (getWidth() * scaleX);
		render_destination->x = getX() - (((render_destination->w - getWidth()) / 2.0f));
		render_destination->h = (getHeight() * scaleY);
		render_destination->y = getY() - (((render_destination->h - getHeight()) / 2.0f));
		SDL_SetTextureAlphaMod(hover_texture, ((int)(opacity * 255.0f)));
		SDL_RenderCopyExF(Engine::renderer, hover_texture, nullptr, render_destination, rotation, rotation_axis, flip);
	}
	else
	{
		render_destination->w = (getWidth() * scaleX);
		render_destination->x = getX() - (((render_destination->w - getWidth()) / 2.0f));
		render_destination->h = (getHeight() * scaleY);
		render_destination->y = getY() - (((render_destination->h - getHeight()) / 2.0f));
		SDL_SetTextureAlphaMod(normal_texure, ((int)(opacity * 255.0f)));
		SDL_RenderCopyExF(Engine::renderer, normal_texure, nullptr, render_destination, rotation, rotation_axis, flip);
	}
}

void VObject::handler(SDL_Event event)
{
	if (on_key != nullptr) on_key(this, &event.key);
}

VObject::VObject(float xpos, float ypos, float width, float height, Assets::TEXTURE tex, LAYER object_layer)
{
	dest_rect = new SDL_FRect{xpos,ypos,width,height};
	this->width = &dest_rect->w;
	this->height = &dest_rect->h;
	this->xpos = &dest_rect->x;
	this->ypos = &dest_rect->y;
	normal_texure = (tex == Assets::TEXTURE::NON_TEXTURE ? nullptr : Engine::loadTexture(Assets::getTexturePath(tex)));
	hover_texture = nullptr;
	this->object_layer = object_layer;
	rotation_axis = new SDL_FPoint();
	rotation_axis->x = width / 2;
	rotation_axis->y = height / 2;
	rotation = 0;
	scaleX = 1;
	scaleY = 1;
	opacity = 1;
	flip = SDL_RendererFlip::SDL_FLIP_NONE;

}

VObject::VObject(float xpos, float ypos, float width, float height, SDL_Texture* tex, LAYER object_layer)
{
	dest_rect = new SDL_FRect{ xpos,ypos,width,height };
	this->width = &dest_rect->w;
	this->height = &dest_rect->h;
	this->xpos = &dest_rect->x;
	this->ypos = &dest_rect->y;
	normal_texure = tex;
	hover_texture = nullptr;
	this->object_layer = object_layer;
	rotation_axis = new SDL_FPoint();
	rotation_axis->x = width / 2;
	rotation_axis->y = height / 2;
	rotation = 0;
	scaleX = 1;
	scaleY = 1;
	opacity = 1;
	flip = SDL_RendererFlip::SDL_FLIP_NONE;
}

VObject::VObject(LAYER layer)
{
	this->width = &dest_rect->w;
	this->height = &dest_rect->h;
	this->xpos = &dest_rect->x;
	this->ypos = &dest_rect->y;
	normal_texure = nullptr;
	hover_texture = nullptr;
	dest_rect = nullptr;
	disable = false;
	object_layer = layer;
	visible = true;
	hovered = false;
	accessible_text = "";
}

VObject::~VObject()
{
	if (normal_texure != nullptr) SDL_DestroyTexture(normal_texure);
	if (hover_texture != nullptr) SDL_DestroyTexture(normal_texure);
	delete width;
	delete height;
	delete xpos;
	delete ypos;
	delete dest_rect;
}

void VObject::changeTexture(SDL_Texture* tex)
{
	if (normal_texure != nullptr) SDL_DestroyTexture(normal_texure);
	normal_texure = tex;
}

void VObject::changeTexture(Assets::TEXTURE new_texture)
{
	if (normal_texure != nullptr) SDL_DestroyTexture(normal_texure);
	normal_texure = Engine::loadTexture(Assets::getTexturePath(new_texture));
}

void VObject::setHoverTexture(Assets::TEXTURE tex)
{
	if (hover_texture != nullptr) SDL_DestroyTexture(hover_texture);
	hover_texture= Engine::loadTexture(Assets::getTexturePath(tex));
}

void VObject::setHoverTexture(SDL_Texture* tex)
{
	hover_texture = tex;
}

SDL_Texture* VObject::getTexture()
{
	return normal_texure;
}

SDL_Texture* VObject::getHoverTexture()
{
	return hover_texture;
}

void VObject::setOpacity(float opacity)
{
	this->opacity = (opacity > 1 ? 1 : (opacity < 0 ? 0 : opacity));
}

float VObject::getOpacity()
{
	return opacity;
}

float VObject::getScaleX()
{
	return scaleX;
}

float VObject::getScaleY()
{
	return scaleY;
}

void VObject::setScaleX(float scale)
{
	scaleX = (scale < 0 ? 0 : scale);
}

void VObject::setScaleY(float scale)
{
	scaleY = (scale < 0 ? 0 : scale);
}

void VObject::setRotationAxis(float x, float y, SDL_RendererFlip flip)
{
	rotation_axis->x = x;
	rotation_axis->y = y;
	this->flip = flip;
}

void VObject::setRotation(double rotation)
{
	this->rotation = rotation;
}

double VObject::getRotation()
{
	return rotation;
}

float VObject::getY()
{
	return *ypos;
}

float VObject::getX()
{
	return *xpos;
}

void VObject::setY(float y)
{
	*ypos = y;
}

void VObject::setX(float x)
{
	*xpos = x;
}


LAYER VObject::getLayer()
{
	return object_layer;
}

bool VObject::isHover()
{
	return hovered;
}

float VObject::getWidth()
{
	return *width;
}

float VObject::getHeight()
{
	return *height;
}


void VObject::setWidth(float w)
{
	*width = w;
}

void VObject::setHeight(float h)
{
	*height = h;
}


void VObject::setVisible(bool v)
{
	visible = v;
}

void VObject::setDisable(bool disable)
{
	this->disable = disable;
}

bool VObject::isDisable()
{
	return disable;
}

bool VObject::isVisible()
{
	return visible;
}

bool VObject::isFocused()
{
	return (Engine::Scene_Manager->getCurrentScene()->getCurrentFocus() == this ? true : false);
}


bool VObject::isMouseOver()
{
	return ((Engine::Scene_Manager->getMousePosition()->xpos > dest_rect->x && Engine::Scene_Manager->getMousePosition()->xpos < dest_rect->x + dest_rect->w) && (Engine::Scene_Manager->getMousePosition()->ypos > dest_rect->y && Engine::Scene_Manager->getMousePosition()->ypos < dest_rect->y + dest_rect->h));
}

bool VObject::isMouseOver(int x, int y)
{
	static MousePosition mouse= MousePosition();
	mouse.xpos = x;
	mouse.ypos = y;
	return ((mouse.xpos > dest_rect->x && mouse.xpos < dest_rect->x + dest_rect->w) && (mouse.ypos > dest_rect->y && mouse.ypos < dest_rect->y + dest_rect->h));
}

void VObject::translate(float x, float y)
{
	dest_rect->x = dest_rect->x + x;
	dest_rect->y = dest_rect->y + y;
}

void VObject::update()
{
	if (!disable)
	{
		if (isMouseOver())
		{
			hovered = true;
		}
		else
		{
			hovered = false;
		}
	}
}

void VObject::relocate(float new_x, float new_y)
{
	this->dest_rect->x = new_x;
	this->dest_rect->y = new_y;
}

void VObject::resize(float w, float h)
{
	dest_rect->w = w;
	dest_rect->h = h;
}

void VObject::setAccessibleText(string text)
{
	accessible_text = text;
}

string VObject::getAccessibleText()
{
	return accessible_text;
}

void VObject::setOnClickEvent(function<void(VObject* sender, SDL_MouseButtonEvent e)> on_click)
{
	this->on_click = on_click;
}

void VObject::setOnDragStartEvent(function<void(VObject* sender, SDL_MouseButtonEvent e)> on_drag_start)
{
	this->on_drag_start = on_drag_start;
}

void VObject::setOnDraggedEvent(function<void(VObject* sender, SDL_MouseMotionEvent e)> on_dragged)
{
	this->on_dragged = on_dragged;
}

void VObject::setOnDragFinishEvent(function<void(VObject* sender, SDL_MouseButtonEvent e)> on_drag_finish)
{
	this->on_drag_finish = on_drag_finish;
}

void VObject::setOnKeyPressedEvent(function<void(VObject* sender, SDL_KeyboardEvent* e)> on_key_pressed)
{
	this->on_key = on_key_pressed;
}

function<void(VObject* sender, SDL_MouseButtonEvent e)> VObject::getOnClickEvent()
{
	return on_click;
}

function<void(VObject* sender, SDL_MouseButtonEvent e)> VObject::getOnDragStartEvent()
{
	return on_drag_start;

}

function<void(VObject* sender, SDL_MouseMotionEvent e)> VObject::getOnDraggedEvent()
{
	return on_dragged;
}

function<void(VObject* sender, SDL_MouseButtonEvent e)> VObject::getOnDragFinishEvent()
{
	return on_drag_finish;
}

function<void(VObject* sender, SDL_KeyboardEvent* e)> VObject::getOnKeyEvent()
{
	return on_key;
}
