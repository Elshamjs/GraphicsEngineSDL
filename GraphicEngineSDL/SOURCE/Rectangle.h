#pragma once

#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle : public VObject
{
private:
	SDL_Color color;
public:
	void setColor(SDL_Color color);
	void setColor(Assets::COLOR color);
	SDL_Color getColor();
	Rectangle(float x, float y, float width, float height, Assets::COLOR color, LAYER l);
	Rectangle(float x, float y, float width, float height, SDL_Color color, LAYER l);
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

	void setOpacity(float opacity);
	float getOpacity();
	float getScaleX();
	float getScaleY();
	void setScaleX(float scale);
	void setScaleY(float scale);
	void setRotationAxis(float x, float y, SDL_RendererFlip flip);
	void setRotation(double rotation);
	double getRotation();


};

#endif