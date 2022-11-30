#pragma once

#ifndef UIBUTTON_H
#define UIBUTTON_H

// Clase para los botones 
class UIButton : public VObject
{
	
public:
   /* 
    x: Coordenada 'x' en la escena actual
	y: Coordenada 'y' en la escena actual
	normal_tex: Textura principal del objeto
	hover_tex: Textura secundaria del objeto, se habilita cuando el mouse está encima del objeto
	l: Capa en la que el objeto será renderizado
	on_click: Función que será llamada cuando suceda el evento
	*/

	UIButton(float x, float y, float width, float height, Assets::TEXTURE normal_tex, Assets::TEXTURE hover_tex, LAYER l, function<void(VObject*, SDL_MouseButtonEvent)> on_click);

	// Cambia la textura del objecto
	void changeTexture(Assets::TEXTURE new_texture);

	// Cambia la textura secundaria del objeto
	void setHoverTexture(Assets::TEXTURE tex);

	// Obtiene la textura primaria
	SDL_Texture* getTexture();

	// Obtiene la textura secundaria
	SDL_Texture* getHoverTexture();
	
	// Obtiene el ancho real del objeto
	float getWidth();

	// Obtiene la altura real del objeto
	float getHeight();

	// Establece el ancho real del objeto
	void setWidth(float w);

	// Establece la altura real del objeto
	void setHeight(float h);

	// Obtiene la coordenada en 'y'
	float getY();

	// Obtiene la coordenada en 'x'
	float getX();

	// Establece la coordenada en 'y'
	void setY(float y);

	// Establece la coordenada en 'x'
	void setX(float x);

	// Devuelve verdadero si el mouse estaba encima de la figura en el frame anterior
	bool isHover();

	// Establece la visibilidad del objeto, el objecto simplemente no se renderizará, o sea nada más sera invisible pero seguira en el mismo lugar
	void setVisible(bool v);

	// Establece si el objeto activara eventos, esto quiere decir que cualquier accion del usuario sobre el objeto no importara
	void setDisable(bool disable);

	// Devuelve verdadero si el objeto esta desabilitado
	bool isDisable();

	// Devuelve verdadero si el objeto es visible
	bool isVisible();

	// Devuelve verdadero si el objeto es el enfoque actual en su escena padre. Cada escena solo puede tener un enfoque a la vez
	bool isFocused();

	// Devuelve verdadero si el mouse está encima del objeto en tiempo real, es la forma más precisa para obtener tal respuesta
	bool isMouseOver();

	// Devuelve verdadero si el punto en las coordenadas suministradas esta dentro de los márgenes reales de la figura. Para obtener las coordenadas del mouse, hay que utilizar la función Scene::getMousePosition()
	bool isMouseOver(int x, int y);

	// Mueve a la figura la cantidad en'x' y 'y' en los parámetros. Esta función llama a setX() y setY() de este objeto
	void translate(float x, float y);

	// Obtiene el nivel de capa en el que el objeto está siendo renderizado
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
#endif // !UIBUTTON_H