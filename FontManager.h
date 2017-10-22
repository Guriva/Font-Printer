#include <map>
#include <list>
#include <SDL.h>
using namespace std;

struct Font {
	SDL_Surface* font;
	int w;
	int h;
	map<char, int> indexTable;
};

class FontManager {

public:
	FontManager();
	~FontManager();

	bool loadFont(SDL_Surface*& font, const char* fontName, const char* path, const char* trad, const int w, const int h);
	void print(SDL_Surface* windSurface, const char* text, const int posx, const int posy, const char* fontName);
	int getFontHeight(const char* fontName);
	int getFontWidth(const char* fontName);
	void closeFont(const char* fontName);
	void closeFontManager();

public:
	map<const char*, Font> fontTable;
};