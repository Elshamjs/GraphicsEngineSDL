#pragma once

#ifndef LINE_H
#define LINE_H

class Line : public VObject
{
private:
	float ini_x;
	float ini_y;
	float end_x;
	float end_y;
	float weight;
	SDL_Color color;
protected:
	void render();
	float getY();
	float getX();
	void setY(float y);
	void setX(float x);
	float getWidth();
	float getHeight();
	friend class UITextField;
public:
	Line(float ini_x, float ini_y, float end_x, float end_y, float weight, Assets::COLOR color, LAYER layer);
	Line(float ini_x, float ini_y, float end_x, float end_y, float weight, SDL_Color color, LAYER layer);
	void setIniX(float x);
	void setIniY(float y);
	void setEndX(float x);
	void setEndY(float y);
	float getIniX();
	float getIniY();
	float getEndX();
	float getEndY();
	void setWeight(float weight);
	float getWeight();
	void setColor(SDL_Color color);
	void setColor(Assets::COLOR color);
	SDL_Color getColor();

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

#endif // !LINE_H