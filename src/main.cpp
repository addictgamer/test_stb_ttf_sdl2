
#include <iostream>
using std::cout;
using std::cerr;
#include <fstream>
using std::ifstream;
#include <string>
using std::string;
#include <cstdio>

#include <SDL2/SDL.h>
#include "sdl_stb/sdlStbFont.h"

size_t getFileSize(string filepath)
{
	ifstream file(filepath, std::ios::binary);
	if (!file)
	{
		printf("ERROR: Failed to load \"%s\"\n", filepath.c_str());
		return 0;
	}

	file.seekg(0, std::ios::end);
	return file.tellg();
}

struct FontFile
{
	size_t buffer_size;
	uint8_t* buffer;

	FontFile(size_t buffer_size, uint8_t* buffer)
		: buffer_size(buffer_size),
		buffer(buffer)
	{
	}

	~FontFile()
	{
		delete[] buffer;
	}
};

FontFile* loadFontFile(string filepath)
{
	size_t filesize = getFileSize(filepath);
	if (filesize == 0)
	{
		printf("ERROR: Skipping loading empty font file \"%s\"!\n");
		return nullptr;
	}

	ifstream file(filepath, std::ios::binary);
	if (!file)
	{
		printf("ERROR: Failed to load font file \"%s\"\n", filepath.c_str());
		return nullptr;
	}

	uint8_t* buffer = new uint8_t[filesize];
	if (!file.read(reinterpret_cast<char*>(buffer), filesize))
	{
		printf("ERROR: Failed to read file \"%s\" into buffer!\n");
		return nullptr;
	}

	return new FontFile(filesize, buffer);
}

int main()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;

		return 1;
	}

	SDL_Window *window = SDL_CreateWindow("STB TTF TEST", 100, 100, 608, 400, SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;

		SDL_Quit();

		return 1;
	}

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr)
	{
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;

		SDL_DestroyWindow(window);
		SDL_Quit();

		return 1;
	}

	SDL_Event event;
	bool quit = false;

	int width, height;
	SDL_Surface* image = SDL_LoadBMP("data/test.bmp");
	if (image == nullptr)
	{
		cout << "Boo! Failed to load image data/test.bmp!\n";
		return -1;
	}

	SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);

	string font_path = "data/SatellaRegular-ZVVaz.ttf";
	size_t font_filesize = getFileSize(font_path);
	cout << "Font filesize: " << font_filesize << "\n";

	FontFile *font_file = loadFontFile(font_path);
	if (!font_file)
	{
		cerr << "Failed to load font file, aborting!\n";
		return -1;
	}

	sdl_stb_font_cache fontcache;
	fontcache.faceSize = 24;
	fontcache.tabWidthInSpaces = 4;

	fontcache.loadFont(reinterpret_cast<char*>(font_file->buffer));
	fontcache.bindRenderer(renderer);

	while (!quit)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		SDL_RenderClear(renderer);

		// renderTextures
		SDL_RenderCopy(renderer, texture, nullptr, nullptr);

		SDL_SetRenderDrawColor(renderer, 125, 125, 125, 255);
		fontcache.drawText(20, 20, "This. Is. For. BARONY!!");

		SDL_RenderPresent(renderer);
	}

	delete font_file;

	return 0;
}
