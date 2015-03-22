using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace Snake
{
    class SnakeHead
    {
        private Rectangle snakesHead;

        public enum Direction
        {
            Left,
            Right,
            Up,
            Down,
            Stopped
        }

        public SnakeHead()
        {
            snakesHead.Width = 20;
            snakesHead.Height = 20;
            snakesHead.X = 500;
            snakesHead.Y = 500;
        }

        public void Move(Direction direction)
        {
            switch (direction)
            {
                case Direction.Left:
                    {
                        snakesHead.X -= 25;
                        break;
                    }
                case Direction.Right:
                    {
                        snakesHead.X += 25;
                        break;
                    }
                case Direction.Up:
                    {
                        snakesHead.Y += -25;
                        break;
                    }
                case Direction.Down:
                    {
                        snakesHead.Y += 25;
                        break;
                    }
                case Direction.Stopped:
                    {
                        break;
                    }
            }
        }

        public void Draw(Graphics graphics)
        {
            SolidBrush brush = new SolidBrush(Color.White);
            graphics.FillRectangle(brush, snakesHead);
        }

    }
}
