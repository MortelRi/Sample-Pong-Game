#include "Main.h"

Enemy::Enemy(int eWidth, int eHeight)
{
	mPosY = (screenHeight - eHeight) / 2;
	mCollider.x = screenWidth - eWidth;
	mCollider.w = eWidth;
	mCollider.h = eHeight;
}

void Enemy::render()
{
	sEnemy.render(mCollider.x,mPosY);
}

void Enemy::move(int ballCentre)
{
	enemyCentre = mPosY + (mCollider.h / 2);
	if (ballCentre > enemyCentre) mPosY += 5;
	if (ballCentre < enemyCentre) mPosY -= 5;
	if (mPosY <= 0) mPosY = 0;
	if (mPosY + mCollider.h >= screenHeight) mPosY = screenHeight - mCollider.h;
	mCollider.y = mPosY;
}