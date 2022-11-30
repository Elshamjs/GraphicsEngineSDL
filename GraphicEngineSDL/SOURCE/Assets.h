#pragma once

#include <iostream>

#ifndef ASSETS
#define ASSETS

using namespace std;
class Assets
{
public:
	enum class TEXTURE { NON_TEXTURE = 525852, PLAYER, WALL, MAP, DIJKSTRA, WARSHALL, PRIM, KRUSKAL, DIRIGIDO, NODIRIGIDO, CLEAR, DIJKSTRA_HOVER, WARSHALL_HOVER, PRIM_HOVER, KRUSKAL_HOVER, DIRIGIDO_HOVER, NODIRIGIDO_HOVER, CLEAR_HOVER };
	enum class COLOR {BLACK= 6789, WHITE, GREEN, RED, BLUE, YELLOW, BROWN, GREY, ORANGE, CIAN, PURPLE, PINK, FUCHSIA, COLOR_BG };
	enum class FONT { ARIAL = 52452562, ARIAL_B, ARIAL_I, ARIAL_BI, SHOWG, TIMES_NEW_ROMAN, TIMES_NEW_ROMAN_I, TIMES_NEW_ROMAN_B, TIMES_NEW_ROMAN_BI };
	static string getTexturePath(TEXTURE tex);
	static TTF_Font* loadFont(FONT font, int font_size);
	static SDL_Color loadColor(COLOR color);
	static SDL_Texture* createTextureFromColor(SDL_Color color);
};
#endif // !ASSETS