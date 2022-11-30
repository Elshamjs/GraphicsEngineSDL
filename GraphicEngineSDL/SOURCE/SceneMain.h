#pragma once

#include "Engine.h"

Line* ln;
TextureFrame* mapGraph;

void dirigidoClick(VObject* sender, SDL_MouseButtonEvent e) {


}

void dijkstraClick(VObject* sender, SDL_MouseButtonEvent e) {

}

void warshallClick(VObject* sender, SDL_MouseButtonEvent e) {

}

void noDirigidoClick(VObject* sender, SDL_MouseButtonEvent e) {

}

void kruskalClick(VObject* sender, SDL_MouseButtonEvent e) {

}

void primClick(VObject* sender, SDL_MouseButtonEvent e) {

}

void clearClick(VObject* sender, SDL_MouseButtonEvent e) {

}


void SceneMainInitializer(Scene* parent) 
{
	
	mapGraph = new TextureFrame(25, 15, 650, 775, Assets::TEXTURE::MAP, LAYER::LAYER_4);

	// hh->setOnDraggedEvent(dd);
	parent->getChildren()->add(mapGraph);
	parent->getChildren()->add(new UITextField(925, 225, 300, 60, 30, false, Assets::FONT::ARIAL, 20, Assets::loadColor(Assets::COLOR::BLACK), LAYER::LAYER_4));
	parent->getChildren()->add(new UIButton(925, 20, 200, 75, Assets::TEXTURE::DIRIGIDO, Assets::TEXTURE::DIRIGIDO_HOVER, LAYER::LAYER_4, dirigidoClick));
	parent->getChildren()->add(new UIButton(925, 125, 200, 75, Assets::TEXTURE::DIJKSTRA, Assets::TEXTURE::DIJKSTRA_HOVER, LAYER::LAYER_4, dijkstraClick));
	//parent->getChildren()->add(new UIButton(925, 225, 200, 75, Assets::TEXTURE::WARSHALL, Assets::TEXTURE::WARSHALL_HOVER, LAYER::LAYER_4, warshallClick));
	parent->getChildren()->add(new UIButton(925, 325, 200, 75, Assets::TEXTURE::NODIRIGIDO, Assets::TEXTURE::NODIRIGIDO_HOVER, LAYER::LAYER_4, noDirigidoClick));
	parent->getChildren()->add(new UIButton(925, 425, 200, 75, Assets::TEXTURE::KRUSKAL, Assets::TEXTURE::KRUSKAL_HOVER, LAYER::LAYER_4, kruskalClick));
	parent->getChildren()->add(new UIButton(925, 525, 200, 75, Assets::TEXTURE::PRIM, Assets::TEXTURE::PRIM_HOVER, LAYER::LAYER_4, primClick));
	parent->getChildren()->add(new UIButton(925, 625, 200, 75, Assets::TEXTURE::CLEAR, Assets::TEXTURE::CLEAR_HOVER, LAYER::LAYER_4, clearClick));
}