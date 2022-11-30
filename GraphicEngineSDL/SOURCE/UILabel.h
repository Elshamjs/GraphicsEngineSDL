#pragma once

#ifndef UILABEL_H
#define UILABEL_H

// Clase para los labels
class UILabel : public VObject
{
private:
	string message;
	TTF_Font* lb_font;
	SDL_Color lb_color;
	Assets::FONT font;
	int font_size;
	void render();
	friend class UITextField;
public:
	UILabel(float x, float y, string message, Assets::FONT font, int size, LAYER l, SDL_Color rgb);
	UILabel(float x, float y, string message, Assets::FONT font, int size, LAYER l, Assets::COLOR rgb);
	~UILabel();

	void setText(string new_message);
	void setFontSize(int size);
	int getFontSize();
	void setTextColor(Assets::COLOR color);
	void setTextColor(SDL_Color color);
	SDL_Color getTextColor();
	string getText();
	void setOpacity(float opacity);
	float getOpacity();
	float getScaleX();
	float getScaleY();
	void setScaleX(float scale);
	void setScaleY(float scale);
	void setRotationAxis(float x, float y, SDL_RendererFlip flip);
	void setRotation(double rotation);
	double getRotation();

	SDL_Texture* getTexture();

	float getY();
	float getX();
	void setY(float y);
	void setX(float x);
	float getWidth();
	float getHeight();
	void setWidth(float w);
	void setHeight(float h);
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
};
#endif // !UILABEL_H