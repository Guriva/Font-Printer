#include <map>

class FontManager {

public:
	FontManager();
	~FontManager();

	bool loadFont();
	void print();

public:
	std::map<char, int> font;
};