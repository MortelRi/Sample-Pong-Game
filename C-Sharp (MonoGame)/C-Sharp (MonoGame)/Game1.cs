using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using System;

namespace C_Sharp__MonoGame_
{
    /// <summary>
    /// This is the main type for your game.
    /// </summary>
    public class Pong : Game
    {
        GraphicsDeviceManager graphics;
        SpriteBatch spriteBatch;

        Ball ball;

        Player player;

        Enemy enemy;

        Background back;

        SpriteFont font;
        SoundEffect pop;
        SoundEffect score;

        int screenWidth;
        int screenHeight;

        int time = 0, past = 0;

        public Pong()
        {
            graphics = new GraphicsDeviceManager(this);
            Content.RootDirectory = "Content";
            graphics.PreferredBackBufferWidth = 1280;
            graphics.PreferredBackBufferHeight = 720;
        }
        
        protected override void Initialize()
        {
            screenWidth = GraphicsDevice.Viewport.Width;
            screenHeight = GraphicsDevice.Viewport.Height;
            base.Initialize();
        }
        
        protected override void LoadContent()
        {
            spriteBatch = new SpriteBatch(GraphicsDevice);
            back = new Background(Content.Load<Texture2D>("fancy-court"), new Rectangle(0, 0, screenWidth, screenHeight));
            ball = new Ball(Content.Load<Texture2D>("fancy-ball"));
            player = new Player(Content.Load<Texture2D>("fancy-paddle-blue"));
            enemy = new Enemy(Content.Load<Texture2D>("fancy-paddle-green"));
            font = Content.Load<SpriteFont>("Font");
            pop = Content.Load<SoundEffect>("Pop");
            score = Content.Load<SoundEffect>("Score");
        }
        
        protected override void UnloadContent()
        {
            // TODO: Unload any non ContentManager content here
        }
        
        protected override void Update(GameTime gameTime)
        {
            if (Keyboard.GetState().IsKeyDown(Keys.Escape))
                Exit();
            if (ball.isPaused)
                Timer(gameTime);

            ball.Update(player.rectangle, enemy.rectangle);

            player.Update();

            enemy.Update(ball.Centre);

            switch(ball.isHit)
            {
                case 1: player.score++; ball.isHit = 0; score.Play(); break;
                case 2: enemy.score++; ball.isHit = 0; score.Play(); break;
            }

            if (ball.isPop)
            {
                pop.Play();
                ball.isPop = false;
            }
            base.Update(gameTime);
        }

        void Timer(GameTime gameTime)
        {
            if (time != 4)
            {
                if (gameTime.TotalGameTime.Seconds > past)
                {
                    time++;
                }
            }
            else
            {
                ball.isPaused = false;
                time = 0;
            }
            past = gameTime.TotalGameTime.Seconds;
        }
        
        protected override void Draw(GameTime gameTime)
        {
            GraphicsDevice.Clear(Color.CornflowerBlue);

            spriteBatch.Begin();
            back.Draw(spriteBatch);
            ball.Draw(spriteBatch);
            player.Draw(spriteBatch);
            enemy.Draw(spriteBatch);
            spriteBatch.DrawString(font, "Player : " + player.score, new Vector2((screenWidth / 2) - 300, 10), Color.LightBlue);
            spriteBatch.DrawString(font, "Enemy : " + enemy.score, new Vector2((screenWidth / 2) + 100, 10), Color.LightGreen);
            spriteBatch.End();

            base.Draw(gameTime);
        }
    }
}