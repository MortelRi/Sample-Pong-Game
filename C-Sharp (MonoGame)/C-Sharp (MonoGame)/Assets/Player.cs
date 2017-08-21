using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace C_Sharp__MonoGame_
{
    class Player : Sprite
    {
        public int score = 0;
        public Player(Texture2D newTexture)
        {
            texture = newTexture;
            position = new Vector2(0, (screenHeight - texture.Height) / 2);
        }

        public void Update()
        {
            rectangle = new Rectangle((int)position.X, (int)position.Y, texture.Width, texture.Height);

            if (Keyboard.GetState().IsKeyDown(Keys.Up))
                position.Y -= 5;
            if (Keyboard.GetState().IsKeyDown(Keys.Down))
                position.Y += 5;

            if (position.Y <= 0)
                position.Y = 0;
            if (position.Y + rectangle.Height >= screenHeight)
                position.Y = screenHeight - rectangle.Height;
        }
    }
}
