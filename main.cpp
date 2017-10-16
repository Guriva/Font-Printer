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
			printf("Failed to create window");
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
	image = SDL_LoadBMP("D:/Descargas/xenon2.bmp");
	if (image == nullptr)
	{
		printf("Failed to load image");
		ret = false;
	}

	return ret;
}

void close(SDL_Surface*& image, SDL_Window*& window) {
	SDL_FreeSurface(image);
	image = nullptr;

	SDL_DestroyWindow(window);
	window = nullptr;

	SDL_Quit();
}

int main(int argc, char* args[])
{
	int count = 0;
	SDL_Window *window = nullptr;
	SDL_Surface *surface = nullptr;
	SDL_Surface *image = nullptr;

	FontManager* FManager = new FontManager();
	//string text = "NomNomNomNom";

	//example text on screen before mapping the font in FontManager
	SDL_Rect rectImage;
	rectImage.x = 37; rectImage.y = 0;
	rectImage.w = 15;
	rectImage.h = 23;
	SDL_Rect rectWindow;
	rectWindow.x = 640/2; rectWindow.y = 480/2;
	rectWindow.w = 15;
	rectWindow.h = 23;


	if (!init(window, surface)) {
		printf("Failed to initialize");
	}
	else {
		if (!loadMedia(image)) {
			printf("Failed to load media");
		}
		else {
			while (1) {
				SDL_FillRect(surface, NULL, 0x000000);
				SDL_BlitSurface(image, &rectImage, surface, &rectWindow);
				SDL_UpdateWindowSurface(window);
				if (count >= 5) {
					++rectWindow.x;
					count = 0;
				}
				if (rectWindow.x > 640)
					rectWindow.x = 0;
				++count;
			}
		}
	}
	close(image,window);
	return 0;
}

/*
Objective: hacer funcion print(font,x,y,"text")
Hacer update donde el texto se mueva por la pantalla horizontalmente en cada iteracion
Cada font sera una classe con su textura y la tabla de traduccion (nos llega una A y imprimimos la letra associada a la A)
FontManager: Carga todas las font en el Init, limpia espacio en el End
- Alloc/Create: const Font *pRed = Alloc("Red");
- print(pRed,x,y,"text");

try __FILE__, __LINE__ :
const Font *pRed = Alloc("Red",__FILE__,__LINE__);
*/