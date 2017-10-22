#include <iostream>
#include <stdio.h>
#include <SDL.h>
#include <string>
#include "FontManager.h"
using namespace std;

bool init(SDL_Window*& window, SDL_Surface*& surface) {
	bool ret = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Failed to initialize SDL");
		ret = false;
	}
	else {
		window = SDL_CreateWindow(
			"An SDL2 window",                  // window title
			SDL_WINDOWPOS_UNDEFINED,           // initial x position
			SDL_WINDOWPOS_UNDEFINED,           // initial y position
			640,                               // width, in pixels
			480,                               // height, in pixels
			SDL_WINDOW_SHOWN                   // flags - see below
		);
		if (window == nullptr) {
			//printf("Failed to create window");
			ret = false;
		}
		else {
			surface = SDL_GetWindowSurface(window);
		}
	}
	return ret;
}

bool loadMedia(SDL_Surface*& image)
{
	//Loading success flag
	bool ret = true;

	//Load splash image
	image = SDL_LoadBMP("Fonts\\xenon2.bmp");
	if (image == nullptr)
	{
		printf("Failed to load image");
		ret = false;
	}

	return ret;
}

void close(SDL_Window*& window) {
	SDL_DestroyWindow(window);
	window = nullptr;

	SDL_Quit();
}

int main(int argc, char* args[])
{
	float time = 0;
	int count = 0;
	SDL_Window *window = nullptr;
	SDL_Surface *surface = nullptr;
	SDL_Surface *fontRed = nullptr;
	SDL_Surface *fontYellow = nullptr;
	SDL_Surface *fontBlue = nullptr;

	FontManager* FManager = new FontManager();

	if (!init(window, surface)) {
		printf("Failed to initialize");
	}
	else {
		FManager->loadFont(fontRed, "red", "Fonts\\lemred.bmp", "!\"#$%&`()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_´abcdefghijklmnopqrstuvwxyz(|)~ ", 8, 17);
		FManager->loadFont(fontYellow, "yellow", "Fonts\\lemyellow.bmp", "!\"#$%&`()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_´abcdefghijklmnopqrstuvwxyz(|)~ ", 8, 17);
		FManager->loadFont(fontBlue, "blue", "Fonts\\lemblue.bmp", "!\"#$%&`()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_´abcdefghijklmnopqrstuvwxyz(|)~ ", 8, 17);
		char* text = "Ohayooo";
		int x = 50;
		int y = 100;
		int incrementX = 1;
		int incrementY = 1;
		while (1) {
			SDL_FillRect(surface, NULL, 0x000000);
			FManager->print(surface, text, x, y, "red");
			//FManager->print(surface, "Desu neee!!", 50, 120, "blue");
			SDL_UpdateWindowSurface(window);

			//Bouncing effect
			if (time > 1) {
				x += incrementX;
				y += incrementY;
				if ((x + strlen(text) * FManager->getFontWidth("red") > 640) || (x < 0)) incrementX *= -1;
				if ((y + FManager->getFontHeight("red") > 480) || (y < 0)) incrementY *= -1;
				time = 0.f;
			}
			time += 0.1f;
		}
	}
	FManager->closeFontManager();
	close(window);
	return 0;
}