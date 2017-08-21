#include "Main.h"
#include "Init.h"

void Timer(int& time, int& past, bool& bPause, int& a)
{
	if (time != 4)
	{
		if (a > past)
		{
			time++;
		}
	}
	else
	{
		bPause = false;
		time = 0;
	}
	past = a;
}

int main(int argc, char* args[])
{
	bool quit = false;
	if (!init()) printf("Failed to initialize!\n");
	else
	{
		if (!loadMedia()) printf("Failed to load media!\n");
		else
		{
			SDL_Event e;
			Change backSize = { screenWidth, screenHeight };
			Ball ball(sBall.getWidth(), sBall.getHeight());
			Player player(sPlayer.getWidth(), sPlayer.getHeight());
			Enemy enemy(sEnemy.getWidth(), sEnemy.getHeight());
			int time = 0, past = 0;
			std::stringstream pScoreText, eScoreText;
			SDL_Color playerColor = { 173, 216, 230, 255 }, enemyColor = { 144, 238, 144, 255 };
			while (!quit)
			{
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
					{
						quit = true;
					}
					player.handleEvent(e);
				}
				int a = SDL_GetTicks() / 1000.f;
				if (ball.isPaused)
					Timer(time, past, ball.isPaused, a);
				ball.move(player.mCollider, enemy.mCollider);
				player.move();
				enemy.move(ball.getCentre());
				if (ball.isPop)
				{
					Mix_PlayChannel(-1, Pop, 0);
					ball.isPop = false;
				}
				switch (ball.isHit)
				{
				case 1: player.score++; ball.isHit = 0; Mix_PlayChannel(-1, Score, 0); break;
				case 2: enemy.score++; ball.isHit = 0; Mix_PlayChannel(-1, Score, 0); break;
				}
				pScoreText.str("");
				pScoreText << "Player: " << player.score;
				if (!sPlayerText.loadFromRenderedText(pScoreText.str().c_str(), playerColor)) printf("Unable to render Player score texture!\n");
				eScoreText.str("");
				eScoreText << "Enemy: " << enemy.score;
				if (!sEnemyText.loadFromRenderedText(eScoreText.str().c_str(), enemyColor)) printf("Unable to render Enemy score texture!\n");
				SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
				SDL_RenderClear(gRenderer);
				sBackground.render(0, 0, &backSize);
				ball.render();
				player.render();
				enemy.render();
				sPlayerText.render((screenWidth / 2) - 300, 10);
				sEnemyText.render((screenWidth / 2) + 100, 10);
				SDL_RenderPresent(gRenderer);
			}
		}
	}
	close();
	if (!quit) system("pause");
	return 0;
}