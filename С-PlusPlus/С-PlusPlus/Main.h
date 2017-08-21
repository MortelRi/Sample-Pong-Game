#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <time.h>
#include <sstream>

const int screenWidth = 1280;
const int screenHeight = 720;
const std::string aPath = "assets/";

struct Change
{
	int w, h;
};
struct Vector2
{
	float x, y;
};

class Sprite
{
public:
	Sprite();
	~Sprite();
	bool loadFromFile(std::string path);
	bool loadFromRenderedText(std::string Text, SDL_Color color);
	void free();
	void render(int x, int y, Change* size = NULL, SDL_Rect* clip = NULL);
	int getWidth(), getHeight();
private:
	SDL_Texture* mTexture;
	int mWidth, mHeight;
};

class Ball
{
public:
	Ball(int bWidth, int bHeight);
	void move(SDL_Rect& pCol, SDL_Rect& eCol);
	void render();
	int getCentre();
	bool isPaused, isPop;
	int isHit;
private:
	float boost;
	void RandomLand();
	Vector2 velocity;
	int mPosX, mPosY, ballCentre;
	SDL_Rect mCollider;
	bool isStarted;
};

class Player
{
public:
	Player(int pWidth, int pHeight);
	void render();
	void handleEvent(SDL_Event &e);
	void move();
	int score = 0;
	SDL_Rect mCollider;
private:
	int mPosY, mVelY;
};

class Enemy
{
public:
	Enemy(int eWidth, int eHeight);
	void render();
	void move(int ballCentre);
	int score = 0;
	SDL_Rect mCollider;
private:
	int mPosY, enemyCentre;
};


bool init();
bool loadMedia();
void close();
void Timer(int& time, int& past, bool& pause, int& a);
bool checkCollision(SDL_Rect a, SDL_Rect b);
extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern Sprite sBackground, sBall, sPlayer, sEnemy, sEnemyText, sPlayerText;
extern Mix_Chunk* Pop;
extern Mix_Chunk* Score;
extern TTF_Font* Font;