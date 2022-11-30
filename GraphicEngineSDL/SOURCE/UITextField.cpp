#include "Engine.h"

UITextField::UITextField(float x, float y, float width, float height, int char_max, bool wrap_text, Assets::FONT font, int font_size, Assets::COLOR text_color, LAYER l) : VObject(x, y, width, height, Assets::TEXTURE::NON_TEXTURE, l)
{
	this->char_count = 0;
	cursor_on = false;
	this->char_max = char_max;
	this->wrap_text = wrap_text;
	if (wrap_text)
	{
		lb_text = new UILabel(x + (float)(width / 2), y + (float)(height * 0.5) - (float)(font_size * 0.5), "", font, font_size, l, text_color);
	}
	else
	{
		lb_text = new UILabel(x + (float)(width * 0.06), y + (float)(height * 0.5) - (float)(font_size * 0.5), "", font, font_size, l, text_color);
	}
	in_line = new Line(x, lb_text->dest_rect->y+font_size, x + width, lb_text->dest_rect->y + font_size, 5, Assets::COLOR::BLACK, l);
	mayus = false;
	line_visibility = true;
}

UITextField::UITextField(float x, float y, float width, float height, int char_max, bool wrap_text, Assets::FONT font, int font_size, SDL_Color text_color, LAYER l) : VObject(x, y, width, height, Assets::TEXTURE::NON_TEXTURE, l)
{
	this->char_count = 0;
	cursor_on = false;
	this->char_max = char_max;
	this->wrap_text = wrap_text;
	if (wrap_text)
	{
		lb_text = new UILabel(x + (float)(width / 2), y + (float)(height * 0.5) - (float)(font_size * 0.5), "", font, font_size, l, text_color);
	}
	else
	{
		lb_text = new UILabel(x + (float)(width * 0.06), y + (float)(height * 0.5) - (float)(font_size * 0.5), "", font, font_size, l, text_color);
	}
	in_line = new Line(x, lb_text->dest_rect->y + lb_text->dest_rect->h, x + width, lb_text->dest_rect->y + lb_text->dest_rect->h, 5, Assets::COLOR::CIAN, l);
	mayus = false;
	line_visibility = true;
}

UITextField::~UITextField()
{
	delete lb_text;
	delete in_line;
}

string UITextField::getText()
{
	return text;
}

void UITextField::setText(string ss)
{
	text = ss;
	lb_text->setText(ss);
}

void UITextField::push(char c)
{
	if (c == 0)
	{
		return;
	}
	if (c == 8)
	{
		if (!isEmpty())
		{
			text.pop_back();
			lb_text->setText(text);
			if (wrap_text)
			{
				lb_text->setX(dest_rect->x + (dest_rect->w / 2) - (lb_text->getWidth() / 2));
			}
		}
		return;
	}
	else if (!(c == ' ' && isEmpty()) && !isFull())
	{
		text += c;
		lb_text->setText(text);
		if (wrap_text)
		{
			lb_text->setX((dest_rect->x + (dest_rect->w / 2) - (lb_text->getWidth() / 2)));
		}
	}
}

bool UITextField::isFull()
{
	return (text.length() == char_max);
}
bool UITextField::isEmpty()
{
	return (text.length() == 0);
}
void UITextField::setLineColor(SDL_Color color)
{
	in_line->setColor(color);
}
void UITextField::setLineColor(Assets::COLOR color)
{
	in_line->setColor(color);
}
SDL_Color UITextField::getLineColor()
{
	return in_line->getColor();
}
float UITextField::getLineWeight()
{
	return in_line->getWeight();
}
void UITextField::setLineWeight(float weight)
{
	in_line->setWeight(weight);
}
void UITextField::setTextColor(SDL_Color color)
{
	lb_text->setTextColor(color);
}
void UITextField::setTextColor(Assets::COLOR color)
{
	lb_text->setTextColor(color);
}
bool UITextField::getLineVisibility()
{
	return line_visibility;
}
void UITextField::setLineVisibility(bool visible)
{
	line_visibility = visible;
}
SDL_Color UITextField::getTextColor()
{
	return lb_text->getTextColor();
}
void UITextField::update()
{
	static Uint32 next_sec = SDL_GetTicks() + 400;
	static bool flag = false;
	if (Engine::Scene_Manager->getCurrentScene()->getCurrentFocus() != this)
	{
		if (!isEmpty() && lb_text->getText().back() == '|')
		{
			lb_text->setText(text);
		}
	}
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

		if (SDL_GetTicks() >= next_sec)
		{
			flag = flag ? false : true;
			if (Engine::Scene_Manager->getCurrentScene()->getCurrentFocus() == this)
			{
				if (flag)
				{
					lb_text->setText(text + '|');
					cursor_on = true;
				}
				else
				{
					lb_text->setText(text);
					cursor_on = false;
				}
			}
			next_sec = SDL_GetTicks() + 400;
		}
	}
}

void UITextField::render()
{
	if (visible)
	{
		if (normal_texure != nullptr)
		{
			if (hovered && hover_texture != nullptr)
			{
				SDL_RenderCopyF(Engine::renderer, hover_texture, nullptr, dest_rect);
			}
			else
			{
				SDL_RenderCopyF(Engine::renderer, normal_texure, nullptr, dest_rect);
			}
		}
		if (line_visibility) in_line->render();
		lb_text->render();
	}
}

void UITextField::handler(SDL_Event event)
{
	if(event.type == SDL_KEYUP)
	{
		if (event.key.keysym.sym == SDLK_RSHIFT || event.key.keysym.sym == SDLK_LSHIFT)
		{
			mayus = (mayus ? false : true);
		}
		return;
	}
	if (event.type != SDL_KEYDOWN) return;
	if (on_key != nullptr) on_key(this, &event.key);
	if (event.key.keysym.sym == SDLK_CAPSLOCK)
	{
		mayus = mayus ? false : true;
		return;
	}
	else if (event.key.keysym.sym == SDLK_RSHIFT || event.key.keysym.sym == SDLK_LSHIFT)
	{
		mayus = (mayus ? false : true);
		return;
	}
	else
	{
		push(getChar(event.key.keysym.sym));
	}
}

char UITextField::getChar(SDL_Keycode code)
{
	if (code == SDLK_BACKSPACE || code == ' ' || (code >= '0' && code <= '9'))
	{
		return code;
	}
	if ((code >= 'a' && code <= 'z'))
	{
		return mayus ? code - 32 : code;
	}
	return 0;
}

void UITextField::changeTexture(Assets::TEXTURE new_texture)
{
	if (normal_texure != nullptr) SDL_DestroyTexture(normal_texure);
	normal_texure = Engine::loadTexture(Assets::getTexturePath(new_texture));
}

void UITextField::setHoverTexture(Assets::TEXTURE tex)
{
	if (hover_texture != nullptr) SDL_DestroyTexture(hover_texture);
	hover_texture = Engine::loadTexture(Assets::getTexturePath(tex));
}

SDL_Texture* UITextField::getTexture()
{
	return normal_texure;
}

SDL_Texture* UITextField::getHoverTexture()
{
	return hover_texture;
}

float UITextField::getWidth()
{
	return *width;
}

float UITextField::getHeight()
{
	return *height;
}

void UITextField::setWidth(float w)
{
	in_line->setEndX(in_line->getEndX() + (w-(*width)));
	if (wrap_text)
	{
		lb_text->setX(dest_rect->x + (dest_rect->w / 2) - (lb_text->getWidth() / 2));
	}
	*width = w;
}

void UITextField::setHeight(float h)
{
	lb_text->setY(*ypos + (float)(h * 0.5) - (float)(lb_text->getFontSize() * 0.5));
	*height = h;
}

float UITextField::getY()
{
	return *ypos;
}

float UITextField::getX()
{
	return *xpos;
}

void UITextField::setY(float y)
{
	static float rel;
	rel = y - *ypos;
	lb_text->translate(0, rel);
	in_line->setIniY(in_line->getIniY() + rel);
	in_line->setEndY(in_line->getEndY() + rel);
	*ypos = y;
}

void UITextField::setX(float x)
{
	static float rel;
	rel = x - *xpos;
	lb_text->translate(rel, 0);
	in_line->setIniX(in_line->getIniX() + rel);
	in_line->setEndX(in_line->getEndX() + rel);
	*xpos = x;
}

bool UITextField::isHover()
{
	return hovered;
}

void UITextField::setVisible(bool v)
{
	visible = v;
}

void UITextField::setDisable(bool disable)
{
	this->disable = disable;
}

bool UITextField::isDisable()
{
	return disable;
}

bool UITextField::isVisible()
{
	return visible;
}

bool UITextField::isFocused()
{
	return (Engine::Scene_Manager->getCurrentScene()->getCurrentFocus() == this ? true : false);
}

bool UITextField::isMouseOver()
{
	return ((Engine::Scene_Manager->getMousePosition()->xpos > dest_rect->x && Engine::Scene_Manager->getMousePosition()->xpos < dest_rect->x + dest_rect->w) && (Engine::Scene_Manager->getMousePosition()->ypos > dest_rect->y && Engine::Scene_Manager->getMousePosition()->ypos < dest_rect->y + dest_rect->h));
}

bool UITextField::isMouseOver(int x, int y)
{
	static MousePosition mouse = MousePosition();
	mouse.xpos = x;
	mouse.ypos = y;
	return ((mouse.xpos > dest_rect->x && mouse.xpos < dest_rect->x + dest_rect->w) && (mouse.ypos > dest_rect->y && mouse.ypos < dest_rect->y + dest_rect->h));
}

void UITextField::translate(float x, float y)
{
	setX(getX() + x);
	setY(getY() + y);
}

LAYER UITextField::getLayer()
{
	return object_layer;
}

void UITextField::relocate(float new_x, float new_y)
{
	setX(new_x);
	setY(new_y);
}

void UITextField::resize(float w, float h)
{
	setWidth(w);
	setHeight(h);
}

void UITextField::setAccessibleText(string text)
{
	accessible_text = text;
}

string UITextField::getAccessibleText()
{
	return accessible_text;
}

function<void(VObject* sender, SDL_MouseButtonEvent e)> UITextField::getOnClickEvent()
{
	return on_click;
}

function<void(VObject* sender, SDL_MouseButtonEvent e)> UITextField::getOnDragStartEvent()
{
	return on_drag_start;

}

function<void(VObject* sender, SDL_MouseMotionEvent e)> UITextField::getOnDraggedEvent()
{
	return on_dragged;
}

function<void(VObject* sender, SDL_MouseButtonEvent e)> UITextField::getOnDragFinishEvent()
{
	return on_drag_finish;
}

function<void(VObject* sender, SDL_KeyboardEvent* e)> UITextField::getOnKeyEvent()
{
	return on_key;
}

void UITextField::setOnClickEvent(function<void(VObject* sender, SDL_MouseButtonEvent e)> on_click)
{
	this->on_click = on_click;
}

void UITextField::setOnDragStartEvent(function<void(VObject* sender, SDL_MouseButtonEvent e)> on_drag_start)
{
	this->on_drag_start = on_drag_start;
}

void UITextField::setOnDraggedEvent(function<void(VObject* sender, SDL_MouseMotionEvent e)> on_dragged)
{
	this->on_dragged = on_dragged;
}

void UITextField::setOnDragFinishEvent(function<void(VObject* sender, SDL_MouseButtonEvent e)> on_drag_finish)
{
	this->on_drag_finish = on_drag_finish;
}

void UITextField::setOnKeyPressedEvent(function<void(VObject* sender, SDL_KeyboardEvent* e)> on_key_pressed)
{
	this->on_key = on_key_pressed;
}

void UITextField::setOpacity(float opacity)
{
	this->opacity = (opacity > 1 ? 1 : (opacity < 0 ? 0 : opacity));
}

float UITextField::getOpacity()
{
	return opacity;
}

float UITextField::getScaleX()
{
	return scaleX;
}

float UITextField::getScaleY()
{
	return scaleY;
}

void UITextField::setScaleX(float scale)
{
	scaleX = (scale < 0 ? 0 : scale);
}

void UITextField::setScaleY(float scale)
{
	scaleY = (scale < 0 ? 0 : scale);
}

void UITextField::setRotationAxis(float x, float y, SDL_RendererFlip flip)
{
	rotation_axis->x = x;
	rotation_axis->y = y;
	this->flip = flip;
}

void UITextField::setRotation(double rotation)
{
	this->rotation = rotation;
}

double UITextField::getRotation()
{
	return rotation;
}