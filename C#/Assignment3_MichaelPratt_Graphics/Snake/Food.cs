using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using System.Resources;

namespace Snake
{
    public class Food
    {
        private static int x;
        private static int y;
        private const int FOODBLOCKHEIGHT = 25;
        private const int FOODBLOCKWIDTH = 25;
        public int screenWidth;
        public int screenHeight;
        Image foodImage;

        public static Rectangle FoodBlock;

        public Food(Random random)
        {
            // Create mouse image for the food block
            foodImage = Snake.Properties.Resources.mouse;

            // Get size of active form
            var screen = System.Windows.Forms.Form.ActiveForm.Bounds;
            screenHeight = screen.Height;
            screenWidth = screen.Width;

            initialize(random, screenHeight, screenWidth);
           
        }

        public static void initialize(Random random, int screenHeight, int screenWidth)
        {
            do
            {
                // Randomly assign x if it's divisible by 25 and still on screen
                x = random.Next(0, screenWidth);
            } while (x % 25 != 0 || x >= (screenWidth - 25));

            do
            {
                // Randomly assign y if it's divisible by 25 and still on screen
                y = random.Next(0, screenHeight);
            } while (y % 25 != 0 || y >= (screenHeight - 50));

            // Create the new food block
            FoodBlock = new Rectangle(x, y, FOODBLOCKWIDTH, FOODBLOCKHEIGHT);
        }

        public void randomizeLocation(Random random)
        {
            // Get size of active form
            var screen = System.Windows.Forms.Form.ActiveForm.Bounds;
            screenHeight = screen.Height;
            screenWidth = screen.Width;

            do
            {
                // Randomly assign x if it's divisible by 25 and still on screen
                x = random.Next(0, screenWidth);
            } while (x % 25 != 0 || x >= (screenWidth - 25));

            do
            {
                // Randomly assign y if it's divisible by 25 and still on screen
                y = random.Next(0, screenHeight);
            } while (y % 25 != 0 || y >= (screenHeight - 50));

            FoodBlock = new Rectangle(x, y, FOODBLOCKWIDTH, FOODBLOCKHEIGHT);

        }

        public void Draw(Graphics graphics)
        {
            // Draw the mouse food block
            graphics.DrawImage(foodImage, FoodBlock);

        }

    }
}
