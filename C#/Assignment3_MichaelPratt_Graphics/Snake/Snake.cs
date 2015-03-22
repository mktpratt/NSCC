using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace Snake
{
    public class SnakeObject
    {
        // Set constant variables, and create required variables
        private const int SNAKEBLOCKHEIGHT = 25;
        private const int SNAKEBLOCKWIDTH = 25;
        private int x, y;
        int screenHeight;
        int screenWidth;

        Image headImage;
        Image bodyImage;

        public Rectangle[] snake;

        public SnakeObject(int numTails)
        {

            // Random used for snake placement
            Random rnd = new Random();

            // Get size of active form
            var screen = System.Windows.Forms.Form.ActiveForm.Bounds;
            screenHeight = screen.Height;
            screenWidth = screen.Width;

            // Create the snake object
            snake = new Rectangle[numTails];
            // Get the image for the snake's head
            headImage = Snake.Properties.Resources.snakeheadright;

            // Set up the snake and it's tails
            for (int i = 0; i < snake.Length; i++)
            {
                if (i == 0)
                {
                    do
                    {
                        // Randomly assign x if it's divisible by 25 and still on screen
                        x = rnd.Next(0, screenWidth);
                    } while (x % 25 != 0 || x >= (screenWidth - 25));

                    do
                    {
                        // Randomly assign y if it's divisible by 25 and still on screen
                        y = rnd.Next(0, screenHeight);
                    } while (y % 25 != 0 || y >= (screenHeight - 50));

                }

                snake[i] = new Rectangle(x, y, SNAKEBLOCKWIDTH, SNAKEBLOCKHEIGHT);
                // Subtract the snake's width so they do not overlap
                x -= SNAKEBLOCKWIDTH;
            }
        }

        public  bool MoveInArray()
        {
            for (int i = snake.Length - 1; i > 0; i--)
            {
                snake[i] = snake[i - 1];
            }

            // Used for unit test
            return true;
        }

        public bool moveLeft()
        {
            MoveInArray();
            headImage = Snake.Properties.Resources.snakeheadleft;
            snake[0].X -= SNAKEBLOCKHEIGHT;

            // Used for unit test
            return true;
        }

        public bool moveRight()
        {
            MoveInArray();
            headImage = Snake.Properties.Resources.snakeheadright;
            snake[0].X += SNAKEBLOCKHEIGHT;

            // Used for unit test
            return true;
        }

        public bool moveUp()
        {
            MoveInArray();
            headImage = Snake.Properties.Resources.snakeheadup;
            snake[0].Y -= SNAKEBLOCKHEIGHT;

            // Used for unit test
            return true;
        }

        public bool moveDown()
        {
            MoveInArray();
            headImage = Snake.Properties.Resources.snakeheaddown;
            snake[0].Y += SNAKEBLOCKHEIGHT;

            // Used for unit test
            return true;
        }

        public bool Draw(Graphics graphics)
        {
            // Draw the head
            foreach (Rectangle block in snake.Take(1))
            {
                graphics.DrawImage(headImage, block);
            }

            // Draw the tail
            foreach (Rectangle block in snake.Skip(1))
            {
                bodyImage = Snake.Properties.Resources.snakebody;
                graphics.DrawImage(bodyImage, block);
            }

            // Used for unit test
            return true;
        }

        public void addTail(int tailPieces)
        {
            List<Rectangle> rec = snake.ToList();
            // Add a tail to the snake
            rec.Add(new Rectangle(snake[snake.Length - 1].X, snake[snake.Length - 1].Y, SNAKEBLOCKWIDTH, SNAKEBLOCKHEIGHT));
            snake = rec.ToArray();
        }
    }
}
