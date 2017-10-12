#include <stdio.h>
#include <SDL.h>

int main(int argc, char ** argv)
{
	SDL_Window *window = nullptr;
	SDL_Surface *surface = nullptr;


	SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2

										   // Create an application window with the following settings:
	window = SDL_CreateWindow(
		"An SDL2 window",                  // window title
		SDL_WINDOWPOS_UNDEFINED,           // initial x position
		SDL_WINDOWPOS_UNDEFINED,           // initial y position
		640,                               // width, in pixels
		480,                               // height, in pixels
		SDL_WINDOW_OPENGL                  // flags - see below
	);

	//Init Font Manager

	//SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
	close(surface, window);
	//End Font Manager

	return 0;
}

bool loadMedia(SDL_Surface* surface)
{
	//Loading success flag
	bool success = true;

	//Load splash image
	surface = SDL_LoadBMP("C:/Users/danielmt3/Documents/bitmaps/hello_world.bmp");
	if (surface == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", "02_getting_an_image_on_the_screen/hello_world.bmp", SDL_GetError());
		success = false;
	}

	return success;
}

void close(SDL_Surface* surface, SDL_Window* window) {
	SDL_FreeSurface(surface);
	surface = nullptr;

	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();
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