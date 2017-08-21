#include "Main.h"

Player::Player(int pWidth, int pHeight)
{
	mPosY = (screenHeight - pHeight) / 2;
	mVelY = 0;
	mCollider.x = 0;
	mCollider.w = pWidth;
	mCollider.h = pHeight;
}

void Player::render()
{
	sPlayer.render(mCollider.x, mPosY);
}

void Player::handleEvent(SDL_Event & e)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: mVelY -= 5; break;
		case SDLK_DOWN: mVelY += 5; break;
		}
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: mVelY += 5; break;
		case SDLK_DOWN: mVelY -= 5; break;
		}
	}
}

void Player::move()
{
	mPosY += mVelY;
	mCollider.y = mPosY;
	if ((mPosY < 0) || (mPosY + mCollider.h > screenHeight))
	{
		mPosY -= mVelY;
		mCollider.y = mPosY;
	}
}