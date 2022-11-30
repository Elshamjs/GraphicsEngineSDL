#include "Engine.h"

string Assets::getTexturePath(TEXTURE tex)
{
	switch (tex)
	{
	case TEXTURE::PLAYER: return "IMG/player.png";
	case TEXTURE::WALL: return "IMG/wall.png";
	case TEXTURE::MAP: return "IMG/map.png";
	case TEXTURE::DIJKSTRA: return "IMG/btn_dijkstra.png";
	case TEXTURE::WARSHALL: return "IMG/btn_warshall.png";
	case TEXTURE::PRIM: return "IMG/btn_prim.png";
	case TEXTURE::KRUSKAL: return "IMG/btn_kruskal.png";
	case TEXTURE::DIRIGIDO: return "IMG/dirigidos.png";
	case TEXTURE::NODIRIGIDO: return "IMG/nodirigidos.png";
	case TEXTURE::CLEAR: return "IMG/btn_clear.png";
	case TEXTURE::DIJKSTRA_HOVER: return "IMG/btn_dijkstra-hover.png";
	case TEXTURE::WARSHALL_HOVER: return "IMG/btn_warshall-hover.png";
	case TEXTURE::PRIM_HOVER: return "IMG/btn_prim-hover.png";
	case TEXTURE::KRUSKAL_HOVER: return "IMG/btn_kruskal-hover.png";
	case TEXTURE::DIRIGIDO_HOVER: return "IMG/dirigidos-hover.png";
	case TEXTURE::NODIRIGIDO_HOVER: return "IMG/nodirigidos-hover.png";
	case TEXTURE::CLEAR_HOVER: return "IMG/btn_clear-hover.png";
	default: return "";
	}
}

TTF_Font* Assets::loadFont(FONT font, int font_size)
{
	switch (font)
	{
	case FONT::ARIAL: return TTF_OpenFont("FONTS/arial.ttf", font_size);
	case FONT::ARIAL_B: return TTF_OpenFont("FONTS/arial_black.ttf", font_size);
	case FONT::ARIAL_I: return TTF_OpenFont("FONTS/arial_italic.ttf", font_size);
	case FONT::ARIAL_BI: return TTF_OpenFont("FONTS/arial_black_italic.ttf", font_size);
	case FONT::SHOWG: return TTF_OpenFont("FONTS/SHOWG.ttf", font_size);
	case FONT::TIMES_NEW_ROMAN: return TTF_OpenFont("FONTS/times_new_roman.ttf", font_size);
	case FONT::TIMES_NEW_ROMAN_B: return TTF_OpenFont("FONTS/times_new_roman_black.ttf", font_size);
	case FONT::TIMES_NEW_ROMAN_BI: return TTF_OpenFont("FONTS/times_new_roman_black_italic.ttf", font_size);
	case FONT::TIMES_NEW_ROMAN_I: return TTF_OpenFont("FONTS/times_new_roman_italic.ttf", font_size);
	default: return TTF_OpenFont("FONTS/arial.ttf", font_size);
	}
}

SDL_Color Assets::loadColor(COLOR color)
{
	switch (color)
	{
	case Assets::COLOR::BLACK: return SDL_Color{ 0,0,0,255 };
	case Assets::COLOR::WHITE: return SDL_Color{ 255,255,255,255 };
	case Assets::COLOR::GREEN: return SDL_Color{ 0,255,0,255 };
	case Assets::COLOR::RED: return SDL_Color{ 255,0,0,255 };
	case Assets::COLOR::BLUE: return SDL_Color{ 0,0,255,255 };
	case Assets::COLOR::YELLOW: return SDL_Color{ 255,255,0,255 };
	case Assets::COLOR::BROWN: return SDL_Color{ 102, 49, 21, 255 };
	case Assets::COLOR::GREY: return SDL_Color{ 60, 60, 60,255 };
	case Assets::COLOR::ORANGE: return SDL_Color{ 255, 90, 0, 255 };
	case Assets::COLOR::CIAN: return SDL_Color{ 0, 242, 242 , 255 };
	case Assets::COLOR::PURPLE: return SDL_Color{ 121, 0, 169 ,255 };
	case Assets::COLOR::PINK: return SDL_Color{ 242, 143, 206 , 255 };
	case Assets::COLOR::FUCHSIA: return SDL_Color{ 233, 0, 128 , 255 };
	case Assets::COLOR::COLOR_BG: return SDL_Color{ 21, 203, 215, 255 }; // Color de fondo, implementar
	default: return SDL_Color{ 0,0,0,255 };
	}
}

SDL_Texture* Assets::createTextureFromColor(SDL_Color color)
{
	static const int w=32, h=32;
	SDL_Texture* tile = SDL_CreateTexture(Engine::renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, w, h);
	unsigned char* bytes = nullptr;
	int pitch = 0;
	SDL_LockTexture(tile, nullptr, reinterpret_cast<void**>(&bytes), &pitch);
	unsigned char rgba[4] = { color.r,color.g,color.b,color.a };
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			memcpy(&bytes[(int)(int(y * 32) + x) * sizeof(rgba)], rgba, sizeof(rgba));
		}
	}
	SDL_UnlockTexture(tile);
	return tile;
}