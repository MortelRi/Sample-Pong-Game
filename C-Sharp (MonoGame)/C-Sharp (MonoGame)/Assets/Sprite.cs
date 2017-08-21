using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Graphics;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace C_Sharp__MonoGame_
{
    class Sprite
    {
        protected Texture2D texture;
        public Rectangle rectangle;
        protected Vector2 position;
        protected static int screenWidth, screenHeight;

        public void Draw(SpriteBatch spriteBatch)
        {
            spriteBatch.Draw(texture, rectangle, null, Color.White, 0, Vector2.Zero, SpriteEffects.None, 0);
        }
    }
}
