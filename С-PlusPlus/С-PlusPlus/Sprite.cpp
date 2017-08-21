#include "Main.h"

Sprite::Sprite()
{
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

Sprite::~Sprite()
{
	free();
}

bool Sprite::loadFromFile(std::string path)
{
	free();
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), IMG_GetError());
	else
	{
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL) printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		else
		{
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}
	mTexture = newTexture;
	return mTexture != NULL;
}

void Sprite::free()
{
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void Sprite::render(int x, int y, Change* size, SDL_Rect * clip)
{
	SDL_Rect renderQuad = { x,y,mWidth,mHeight };
	if (size != NULL)
	{
		renderQuad.w = size->w;
		renderQuad.h = size->h;
	}
	SDL_RenderCopy(gRenderer, mTexture, clip, &renderQuad);
}

int Sprite::getWidth()
{
	return mWidth;
}

int Sprite::getHeight()
{
	return mHeight;
}

bool Sprite::loadFromRenderedText(std::string Text, SDL_Color color)
{
	free();
	SDL_Surface* textSurface = TTF_RenderText_Solid(Font, Text.c_str(), color);
	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_TTF Error: %s\n", TTF_GetError());
	}
	else
	{
		mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		if (mTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}
		SDL_FreeSurface(textSurface);
	}
	return mTexture != NULL;
}