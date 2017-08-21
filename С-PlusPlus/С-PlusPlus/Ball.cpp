#include "Main.h"

Ball::Ball(int bWidth, int bHeight)
{
	isPop = false;
	isHit = 0;
	isPaused = true;
	isStarted = true;
	velocity = { 0,0 };
	mPosX = (screenWidth - bWidth) / 2;
	mPosY = (screenHeight - bHeight) / 2;
	mCollider.w = bWidth;
	mCollider.h = bHeight;
	boost = 1;
}

void Ball::move(SDL_Rect& pCol, SDL_Rect& eCol)
{
	if (isStarted && !isPaused)
	{
		RandomLand();
		isStarted = false;
	}

	ballCentre = mPosY + (mCollider.h / 2);

	if (checkCollision(mCollider, pCol) || checkCollision(mCollider, eCol))
	{
		boost += 0.2f;
		velocity.x = -velocity.x * boost;
		velocity.y *= boost;
		isPop = true;
	}

	mPosX += velocity.x;
	mPosY += velocity.y;

	if ((mPosX <= -100) || (mPosX + mCollider.w >= screenWidth + 100))
	{
		if (mPosX <= -100)
			isHit = 2;
		if (mPosX + mCollider.w >= screenWidth + 100)
			isHit = 1;
		mPosX = (screenWidth - mCollider.w) / 2;
		mPosY = (screenHeight - mCollider.h) / 2;
		boost = 1;
		isPaused = true;
		isStarted = true;
		velocity = { 0,0 };
	}

	if ((mPosY < 0) || (mPosY + mCollider.h > screenHeight))
	{
		velocity.y = -velocity.y;
	}

	mCollider.x = mPosX;
	mCollider.y = mPosY;
}

void Ball::render()
{
	sBall.render(mPosX, mPosY);
}

void Ball::RandomLand()
{
	srand(time(NULL));
	int random = rand() % 4;
	if (random == 0)
	{
		velocity.x = 3;
		velocity.y = 3;
	}
	if (random == 1)
	{
		velocity.x = -3;
		velocity.y = 3;
	}
	if (random == 2)
	{
		velocity.x = -3;
		velocity.y = -3;
	}
	if (random == 3)
	{
		velocity.x = 3;
		velocity.y = -3;
	}
}

int Ball::getCentre()
{
	return ballCentre;
}