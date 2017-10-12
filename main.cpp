#include <stdio.h>
#include <SDL.h>

bool init(SDL_Window* window, SDL_Surface* surface) {
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
			SDL_WINDOW_OPENGL                  // flags - see below
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

bool loadMedia(SDL_Surface* image)
{
	//Loading success flag
	bool ret = true;

	//Load splash image
	image = SDL_LoadBMP("./hello_world.bmp");
	if (image == nullptr)
	{
		printf("Failed to load image");
		ret = false;
	}

	return ret;
}

void close(SDL_Surface* image, SDL_Window* window) {
	SDL_FreeSurface(image);
	image = nullptr;

	SDL_DestroyWindow(window);
	window = nullptr;

	SDL_Quit();
}

int main(int argc, char ** argv)
{
	SDL_Window *window = nullptr;
	SDL_Surface *surface = nullptr;
	SDL_Surface *image = nullptr;

	if (init(window,surface)) {
		SDL_BlitSurface(image,NULL,surface,NULL);
		while (1) {
			SDL_UpdateWindowSurface(window);
		}
	}
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