#include "FontManager.h"
#include <SDL.h>

FontManager::FontManager() {
}

FontManager::~FontManager() {

}

bool FontManager::loadFont(SDL_Surface*& font, const char* fontName, const char* path, const char* trad, const int w, const int h) {
	//Loading success flag
	bool ret = true;

	//Load splash image
	font = SDL_LoadBMP(path);
	if (font == nullptr)
	{
		printf("Failed to load image");
		ret = false;
	}
	else {
		//Initialize index table for each character
		map<char, int> indexTable;
		for (int i = 0; trad[i] != '\0'; ++i) {
			indexTable[trad[i]] = i;
		}

		//Create font
		Font f;
		f.font = font; f.indexTable = indexTable; f.w = w; f.h = h;

		//Add new font to table
		fontTable[fontName] = f;
	}

	return ret;
}

void FontManager::print(SDL_Surface* windSurface, const char* text, const int posx, const int posy, const char* fontName) {

	Font f = fontTable[fontName];

	SDL_Rect rectFont, rectWindow;
	rectFont.y = 0;
	rectFont.w = f.w; rectFont.h = f.h;
	rectWindow.x = posx; rectWindow.y = posy;
	rectWindow.w = f.w; rectWindow.h = f.h;

	for (int i = 0; text[i] != '\0'; ++i) {
		int index = f.indexTable[text[i]];
		rectFont.x = (f.w + 1)*index + 1;	//Each symbol is separated by one pixel
		rectWindow.x = posx + f.w*i;
		SDL_BlitSurface(f.font, &rectFont, windSurface, &rectWindow);
	}
}

int FontManager::getFontHeight(const char* fontName) {
	return fontTable[fontName].h;
}

int FontManager::getFontWidth(const char* fontName) {
	return fontTable[fontName].w;
}

void FontManager::closeFont(const char* fontName) {
	SDL_FreeSurface(fontTable[fontName].font);
	fontTable[fontName].font = nullptr;
	fontTable[fontName].indexTable.clear();
	fontTable.erase(fontName);
}

void FontManager::closeFontManager() {
	for (map<const char*, Font>::iterator it = fontTable.begin(); it != fontTable.end(); ++it) {
		SDL_FreeSurface(it->second.font);
		it->second.font = nullptr;
		it->second.indexTable.clear();
	}
	fontTable.clear();
}