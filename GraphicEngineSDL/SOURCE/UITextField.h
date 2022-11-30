#pragma once
#ifndef UITEXTFIELD_H
#define UITEXTFIELD_H

class UITextField : public VObject
{
public:
	UITextField(float x, float y, float width, float height, int char_max, bool wrap_text, Assets::FONT font, int font_size, Assets::COLOR text_color, LAYER l);
	UITextField(float x, float y, float width, float height, int char_max, bool wrap_text, Assets::FONT font, int font_size, SDL_Color text_color, LAYER l);
	~UITextField();

	string getText();
	void setText(string ss);
	void setTextColor(SDL_Color color);
	void setTextColor(Assets::COLOR color);
	SDL_Color getTextColor();

	bool isFull();
	bool isEmpty();

	void setLineColor(SDL_Color color);
	void setLineColor(Assets::COLOR color);
	SDL_Color getLineColor();
	float getLineWeight();
	void setLineWeight(float weight);
	bool getLineVisibility();
	void setLineVisibility(bool visible);

	void changeTexture(Assets::TEXTURE new_texture);
	void setHoverTexture(Assets::TEXTURE tex);
	SDL_Texture* getTexture();
	SDL_Texture* getHoverTexture();
	float getWidth();
	float getHeight();
	void setWidth(float w);
	void setHeight(float h);
	float getY();
	float getX();
	void setY(float y);
	void setX(float x);
	bool isHover();
	void setVisible(bool v);
	void setDisable(bool disable);
	bool isDisable();
	bool isVisible();
	bool isFocused();
	bool isMouseOver();
	bool isMouseOver(int x, int y);
	void translate(float x, float y);
	LAYER getLayer();
	void relocate(float new_x, float new_y);
	void resize(float w, float h);

	void setAccessibleText(string text);
	string getAccessibleText();

	void setOnClickEvent(function<void(VObject* sender, SDL_MouseButtonEvent e)> on_click);
	void setOnDragStartEvent(function<void(VObject* sender, SDL_MouseButtonEvent e)> on_drag_start);
	void setOnDraggedEvent(function<void(VObject* sender, SDL_MouseMotionEvent e)> on_dragged);
	void setOnDragFinishEvent(function<void(VObject* sender, SDL_MouseButtonEvent e)> on_drag_finish);
	void setOnKeyPressedEvent(function<void(VObject* sender, SDL_KeyboardEvent* e)> on_key_pressed);

	function<void(VObject* sender, SDL_MouseButtonEvent e)> getOnClickEvent();
	function<void(VObject* sender, SDL_MouseButtonEvent e)> getOnDragStartEvent();
	function<void(VObject* sender, SDL_MouseMotionEvent e)> getOnDraggedEvent();
	function<void(VObject* sender, SDL_MouseButtonEvent e)> getOnDragFinishEvent();
	function<void(VObject* sender, SDL_KeyboardEvent* e)> getOnKeyEvent();

	void setOpacity(float opacity);
	float getOpacity();
	float getScaleX();
	float getScaleY();
	void setScaleX(float scale);
	void setScaleY(float scale);
	void setRotationAxis(float x, float y, SDL_RendererFlip flip);
	void setRotation(double rotation);
	double getRotation();
	

private:
	UILabel* lb_text;
	string text;
	int char_max;
	bool wrap_text;
	int char_count;
	bool cursor_on;
	Line* in_line;
	bool mayus;
	bool line_visibility;

	void push(char c);
	void update();
	void render();
	void handler(SDL_Event event);
	char getChar(SDL_Keycode code);
};

#endif // !UITEXTFIELD
