using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace C_Sharp__MonoGame_
{
    class Enemy : Sprite
    {
        int enemyCentre;
        public int score = 0;

        public Enemy(Texture2D newTexture)
        {
            texture = newTexture;
            position = new Vector2(screenWidth - texture.Width, (screenHeight - texture.Height) / 2);
        }

        public void Update(int ballCentre)
        {
            rectangle = new Rectangle((int)position.X, (int)position.Y, texture.Width, texture.Height);

            if (ballCentre > enemyCentre)
            {
                position.Y += 5;
            }
            if (ballCentre < enemyCentre)
            {
                position.Y -= 5;
            }
            if (position.Y <= 0)
                position.Y = 0;
            if (position.Y + rectangle.Height >= screenHeight)
                position.Y = screenHeight - rectangle.Height;

            enemyCentre = (int)position.Y + (rectangle.Height / 2);
        }
    }
}
