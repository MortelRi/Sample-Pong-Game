using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace C_Sharp__MonoGame_
{
    class Ball : Sprite
    {
        public int Centre;
        Vector2 velocity;
        private float boost = 1f;
        Random rand = new Random();
        public bool isPaused = true;
        bool isStarted = true;
        public int isHit = 0;
        public bool isPop = false;

        public Ball(Texture2D newTexture)
        {
            texture = newTexture;
            position = new Vector2((screenWidth - texture.Width) / 2, (screenHeight - texture.Height) / 2);
        }
        
        public void Update(Rectangle playerRect, Rectangle enemyRect)
        {
            if(isStarted && !isPaused)
            {
                RandomLand();
                isStarted = false;
            }

            rectangle = new Rectangle((int)position.X, (int)position.Y, texture.Width, texture.Height);

            if (rectangle.IsOnTopOf(playerRect))
            {
                boost += 0.1f;
                velocity.X = -velocity.X * boost;
                velocity.Y *= boost;
                isPop = true;
            }
            if (rectangle.IsOnTopOf(enemyRect))
            {
                boost += 0.1f;
                velocity.X = -velocity.X * boost;
                velocity.Y *= boost;
                isPop = true;
            }

            position.X += (int)velocity.X;
            position.Y += (int)velocity.Y;

            if (position.X <= -100)
            {
                position.X = (screenWidth - rectangle.Width) / 2;
                position.Y = (screenHeight - rectangle.Height) / 2;
                boost = 1f;
                isPaused = true;
                isStarted = true;
                velocity = Vector2.Zero;
                isHit = 2;
            }
            if (position.Y <= 0)
            {
                velocity.Y = -velocity.Y;
            }
            if (position.X + rectangle.Width >= screenWidth + 100)
            {
                position.X = (screenWidth - rectangle.Width) / 2;
                position.Y = (screenHeight - rectangle.Height) / 2;
                boost = 1f;
                isPaused = true;
                isStarted = true;
                velocity = Vector2.Zero;
                isHit = 1;
            }
            if (position.Y + rectangle.Height >= screenHeight)
            {
                velocity.Y = -velocity.Y;
            }

            Centre = (int)position.Y + (rectangle.Height / 2);
        }

        private void RandomLand()
        {
            int random = rand.Next(0, 4);
            if (random == 0)
            {
                velocity.X = 3f;
                velocity.Y = 3f;
            }
            if (random == 1)
            {
                velocity.X = -3f;
                velocity.Y = 3f;
            }
            if (random == 2)
            {
                velocity.X = -3f;
                velocity.Y = -3f;
            }
            if (random == 3)
            {
                velocity.X = 3f;
                velocity.Y = -3f;
            }
        }
    }
}

static class RectangleHelper
{
    public static bool IsOnTopOf(this Rectangle r1, Rectangle r2)
    {
        return (r1.Bottom >= r2.Top &&
            r1.Top <= r2.Bottom && 
            r1.Right >= r2.Left &&
            r1.Left <= r2.Right);
    }
}