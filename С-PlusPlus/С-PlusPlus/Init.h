#pragma once
#include "Main.h"

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
Sprite sBackground, sBall, sPlayer, sEnemy, sEnemyText, sPlayerText;
Mix_Chunk* Pop = NULL;
Mix_Chunk* Score = NULL;
TTF_Font* Font = NULL;

bool init()
{
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) printf("Warning! Linear texture filtering not enable!\n");
		gWindow = SDL_CreateWindow("Sample Pong Game on C++", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			}
			else
			{
				SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags)&imgFlags))
				{
					printf("SDL image could not initialize! SDL Error: %s\n", IMG_GetError());
					success = false;
				}
				if (TTF_Init() == -1) 
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError()); 
					success = false;
				}
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) 
				{ 
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					success = false; 
				}
			}
		}
	}
	return success;
}

bool loadMedia()
{
	bool success = true;
	if (!sBackground.loadFromFile(aPath + "fancy-court.png"))
	{
		printf("Failed to load Background!\n");
		success = false;
	}
	if (!sBall.loadFromFile(aPath + "fancy-ball.png"))
	{
		printf("Failed to load Ball!\n");
		success = false;
	}
	if (!sPlayer.loadFromFile(aPath + "fancy-paddle-blue.png"))
	{
		printf("Failed to load Player!\n");
		success = false;
	}
	if (!sEnemy.loadFromFile(aPath + "fancy-paddle-green.png"))
	{
		printf("Failed to load Enemy!\n");
		success = false;
	}
	Pop = Mix_LoadWAV("assets/Pop.wav");
	if (Pop == NULL)
	{
		printf("Failed to load Pop sound! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}
	Score = Mix_LoadWAV("assets/Score.wav");
	if (Score == NULL)
	{
		printf("Failed to load Score sound! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}
	Font = TTF_OpenFont("assets/PressStart2P.ttf", 16);
	if (Font == NULL)
	{
		printf("Failed to load Font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	return success;
}

void close()
{
	sBackground.free();
	sBall.free();
	sPlayer.free();
	sEnemy.free();
	sPlayerText.free();
	sEnemyText.free();
	TTF_CloseFont(Font);
	Font = NULL;
	Mix_FreeChunk(Pop);
	Mix_FreeChunk(Score);
	Pop = NULL;
	Score = NULL;
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gRenderer = NULL;
	gWindow = NULL;
	TTF_Quit();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

bool checkCollision(SDL_Rect a, SDL_Rect b)
{
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;
	if (bottomA <= topB || topA >= bottomB || rightA <= leftB || leftA >= rightB)
	{
		return false;
	}
	return true;
}