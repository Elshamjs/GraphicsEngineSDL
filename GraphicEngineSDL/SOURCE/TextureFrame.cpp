#include "Engine.h"

TextureFrame::TextureFrame(float xpos, float ypos, float width, float height, Assets::TEXTURE tex, LAYER object_layer) : VObject(xpos, ypos, width, height, tex, object_layer)
{
}

TextureFrame::TextureFrame(float xpos, float ypos, float width, float height, SDL_Texture* tex, LAYER object_layer) : VObject(xpos, ypos, width, height, tex, object_layer)
{
}


void TextureFrame::changeTexture(SDL_Texture* tex)
{
	normal_texure = tex;
}

void TextureFrame::changeTexture(Assets::TEXTURE new_texture)
{
	if (normal_texure != nullptr) SDL_DestroyTexture(normal_texure);
	normal_texure = Engine::loadTexture(Assets::getTexturePath(new_texture));
}

void TextureFrame::setHoverTexture(Assets::TEXTURE tex)
{
	if (hover_texture != nullptr) SDL_DestroyTexture(hover_texture);
	hover_texture = Engine::loadTexture(Assets::getTexturePath(tex));
}

void TextureFrame::setHoverTexture(SDL_Texture* tex)
{
	hover_texture = tex;
}

SDL_Texture* TextureFrame::getTexture()
{
	return normal_texure;
}

SDL_Texture* TextureFrame::getHoverTexture()
{
	return hover_texture;
}

float TextureFrame::getWidth()
{
	return *width;
}

float TextureFrame::getHeight()
{
	return *height;
}

void TextureFrame::setWidth(float w)
{
	*width = w;
}

void TextureFrame::setHeight(float h)
{
	*height = h;
}

float TextureFrame::getY()
{
	return *ypos;
}

float TextureFrame::getX()
{
	return *xpos;
}

void TextureFrame::setY(float y)
{
	*ypos = y;
}

void TextureFrame::setX(float x)
{
	*xpos = x;
}

bool TextureFrame::isHover()
{
	return hovered;
}

void TextureFrame::setVisible(bool v)
{
	visible = v;
}

void TextureFrame::setDisable(bool disable)
{
	this->disable = disable;
}

bool TextureFrame::isDisable()
{
	return disable;
}

bool TextureFrame::isVisible()
{
	return visible;
}

bool TextureFrame::isFocused()
{
	return (Engine::Scene_Manager->getCurrentScene()->getCurrentFocus() == this ? true : false);
}

bool TextureFrame::isMouseOver()
{
	return ((Engine::Scene_Manager->getMousePosition()->xpos > dest_rect->x && Engine::Scene_Manager->getMousePosition()->xpos < dest_rect->x + dest_rect->w) && (Engine::Scene_Manager->getMousePosition()->ypos > dest_rect->y && Engine::Scene_Manager->getMousePosition()->ypos < dest_rect->y + dest_rect->h));
}

bool TextureFrame::isMouseOver(int x, int y)
{
	static MousePosition mouse = MousePosition();
	mouse.xpos = x;
	mouse.ypos = y;
	return ((mouse.xpos > dest_rect->x && mouse.xpos < dest_rect->x + dest_rect->w) && (mouse.ypos > dest_rect->y && mouse.ypos < dest_rect->y + dest_rect->h));
}

void TextureFrame::translate(float x, float y)
{
	dest_rect->x = dest_rect->x + x;
	dest_rect->y = dest_rect->y + y;
}

LAYER TextureFrame::getLayer()
{
	return object_layer;
}

void TextureFrame::relocate(float new_x, float new_y)
{
	*xpos = new_x;
	*ypos = new_y;
}

void TextureFrame::resize(float w, float h)
{
	*width = w;
	*height = h;
}

void TextureFrame::setAccessibleText(string text)
{
	accessible_text = text;
}

string TextureFrame::getAccessibleText()
{
	return accessible_text;
}

function<void(VObject* sender, SDL_MouseButtonEvent e)> TextureFrame::getOnClickEvent()
{
	return on_click;
}

function<void(VObject* sender, SDL_MouseButtonEvent e)> TextureFrame::getOnDragStartEvent()
{
	return on_drag_start;

}

function<void(VObject* sender, SDL_MouseMotionEvent e)> TextureFrame::getOnDraggedEvent()
{
	return on_dragged;
}

function<void(VObject* sender, SDL_MouseButtonEvent e)> TextureFrame::getOnDragFinishEvent()
{
	return on_drag_finish;
}

function<void(VObject* sender, SDL_KeyboardEvent* e)> TextureFrame::getOnKeyEvent()
{
	return on_key;
}

void TextureFrame::setOnClickEvent(function<void(VObject* sender, SDL_MouseButtonEvent e)> on_click)
{
	this->on_click = on_click;
}

void TextureFrame::setOnDragStartEvent(function<void(VObject* sender, SDL_MouseButtonEvent e)> on_drag_start)
{
	this->on_drag_start = on_drag_start;
}

void TextureFrame::setOnDraggedEvent(function<void(VObject* sender, SDL_MouseMotionEvent e)> on_dragged)
{
	this->on_dragged = on_dragged;
}

void TextureFrame::setOnDragFinishEvent(function<void(VObject* sender, SDL_MouseButtonEvent e)> on_drag_finish)
{
	this->on_drag_finish = on_drag_finish;
}

void TextureFrame::setOnKeyPressedEvent(function<void(VObject* sender, SDL_KeyboardEvent* e)> on_key_pressed)
{
	this->on_key = on_key_pressed;
}

void TextureFrame::setOpacity(float opacity)
{
	this->opacity = (opacity > 1 ? 1 : (opacity < 0 ? 0 : opacity));
}

float TextureFrame::getOpacity()
{
	return opacity;
}

float TextureFrame::getScaleX()
{
	return scaleX;
}

float TextureFrame::getScaleY()
{
	return scaleY;
}

void TextureFrame::setScaleX(float scale)
{
	scaleX = (scale < 0 ? 0 : scale);
}

void TextureFrame::setScaleY(float scale)
{
	scaleY = (scale < 0 ? 0 : scale);
}

void TextureFrame::setRotationAxis(float x, float y, SDL_RendererFlip flip)
{
	rotation_axis->x = x;
	rotation_axis->y = y;
	this->flip = flip;
}

void TextureFrame::setRotation(double rotation)
{
	this->rotation = rotation;
}

double TextureFrame::getRotation()
{
	return rotation;
}