#pragma once
#include "SceneMain.h"

void EngineStarter(SceneManager* manager)
{
	// manager->CreateScene("SceneMenu", SceneMenuInitializer);
	manager->CreateScene("SceneMain", SceneMainInitializer);

}

//void t6(Scene* parent)
//{
//	TextureFrame* tex = new TextureFrame(50, 300, 100, 100, Assets::TEXTURE::WALL, LAYER::LAYER_4);
//	Rectangle* opacity = new Rectangle(250, 300, 50, 50, Assets::COLOR::GREY, LAYER::LAYER_4);
//	opacity->setOnClickEvent([tex](VObject* sender, SDL_MouseButtonEvent e) -> void
//	{
//		cout << "click"<<endl;
//		(new ScaleTransition(tex, 5, 5, 0, 0, 15, 3000, []() -> void
//		{
//			cout << "TERMINO";
//		}))->play();
//	});
//	parent->getChildren()->add(tex);
//	parent->getChildren()->add(opacity);
// }
// void EngineStarter(SceneManager* manager)
// {
//	manager->CreateScene("main", ScenePruebaInitializer);
// };


//void ScenePruebaInitializer(Scene* parent)
//{
//	TextureFrame* tex = new TextureFrame(50, 300, 100, 100, Assets::TEXTURE::WALL, LAYER::LAYER_4);
//	Rectangle* opacity = new Rectangle(250, 300, 50, 50, Assets::COLOR::GREY, LAYER::LAYER_4);
//	opacity->setOnClickEvent([tex](VObject* sender, SDL_MouseButtonEvent e) -> void
//		{
//			cout << "click" << endl;
//			(new FadeTransition(tex, 1, 0, 15, 3000, []() -> void
//				{
//					cout << "TERMINO";
//				}))->play();
//		});
//	parent->getChildren()->add(tex);
//	parent->getChildren()->add(opacity);
//}



//void ScenePruebaInitializer(Scene* parent)
//{
//	TextureFrame* tex = new TextureFrame(50, 300, 100, 100, Assets::TEXTURE::WALL, LAYER::LAYER_4);
//	Rectangle* opacity = new Rectangle(250, 300, 50, 50, Assets::COLOR::GREY, LAYER::LAYER_4);
//	opacity->setOnClickEvent([tex](VObject* sender, SDL_MouseButtonEvent e) -> void
//		{
//			cout << "click" << endl;
//			(new RotationTransition(tex, 0, -360, 15, 3000, []() -> void
//				{
//					cout << "TERMINO";
//				}))->play();
//		});
//	parent->getChildren()->add(tex);
//	parent->getChildren()->add(opacity);
//}


//void ScenePruebaInitializer(Scene* parent)
//{
//	TextureFrame* tex = new TextureFrame(50, 300, 100, 100, Assets::TEXTURE::WALL, LAYER::LAYER_4);
//	Rectangle* opacity = new Rectangle(250, 300, 50, 50, Assets::COLOR::GREY, LAYER::LAYER_4);
//	Rectangle* rota = new Rectangle(320, 300, 50, 50, Assets::COLOR::GREEN, LAYER::LAYER_4);
//	Rectangle* scaX = new Rectangle(390, 300, 50, 50, Assets::COLOR::CIAN, LAYER::LAYER_4);
//	Rectangle* scaY = new Rectangle(470, 300, 50, 50, Assets::COLOR::BLUE, LAYER::LAYER_4);
//	Rectangle* scaXY = new Rectangle(540, 300, 50, 50, Assets::COLOR::ORANGE, LAYER::LAYER_4);
//	opacity->setOnDraggedEvent([opacity, tex](VObject* sender, SDL_MouseMotionEvent e) -> void
//		{
//			opacity->translate(0, e.yrel);
//			tex->setOpacity(tex->getOpacity() + (e.yrel / 100.0f));
//		});
//	rota->setOnDraggedEvent([rota, tex](VObject* sender, SDL_MouseMotionEvent e) -> void
//		{
//			rota->translate(0, e.yrel);
//			tex->setRotation(tex->getRotation() + e.yrel);
//		});
//	scaX->setOnDraggedEvent([scaX, tex](VObject* sender, SDL_MouseMotionEvent e) -> void
//		{
//			scaX->translate(0, e.yrel);
//			tex->setScaleX(tex->getScaleX() + (e.yrel / 100.0f));
//		});
//	scaY->setOnDraggedEvent([scaY, tex](VObject* sender, SDL_MouseMotionEvent e) -> void
//		{
//			scaY->translate(0, e.yrel);
//			tex->setScaleY(tex->getScaleY() + (e.yrel / 100.0f));
//		});
//	scaXY->setOnDraggedEvent([scaXY, tex](VObject* sender, SDL_MouseMotionEvent e) -> void
//		{
//			scaXY->translate(0, e.yrel);
//			tex->setScaleX(tex->getScaleX() + (e.yrel / 100.0f));
//			tex->setScaleY(tex->getScaleY() + (e.yrel / 100.0f));
//		});
//	parent->getChildren()->add(tex);
//	parent->getChildren()->add(opacity);
//	parent->getChildren()->add(rota);
//	parent->getChildren()->add(scaX);
//	parent->getChildren()->add(scaY);
//	parent->getChildren()->add(scaXY);
//
//}
//void EngineStarter(SceneManager* manager)
//{
//	manager->CreateScene("main", ScenePruebaInitializer);
//};