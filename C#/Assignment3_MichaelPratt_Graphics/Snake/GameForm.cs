using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Snake
{
    public partial class GameForm : Form
    {
        SnakeObject head;
        Random randomFood = new Random();
        Food food;
        Rectangle gameArea;
        RectangleF gameOverPopup;
        Image gameOver = Snake.Properties.Resources.snakewall;
        Image snakeEatSelf = Snake.Properties.Resources.snakeeatself;
        Image gameWon = Snake.Properties.Resources.snakewin;
        private const int EASYWIDTH = 815, EASYHEIGHT = 810, MEDIUMWIDTH = 615, MEDIUMHEIGHT = 610,
                          HARDWIDTH = 415, HARDHEIGHT = 410;

        // Actually only requires 20 (excluding head + 1 tail) to win
        private const int WINTOTAL = 22;
        private const int STARTINGTOTAL = 2;
        private bool leftDirection = false;
        private bool rightDirection = true;
        private bool upDirection = false;
        private bool downDirection = false;
        private bool boolGameOver = false;
        private bool boolLevelComplete = false;
        private int screenHeight;
        private int screenWidth;
        private int tailCount = 0;
        private string titleText;

        public GameForm()
        {
            InitializeComponent();
            AdjustGame();

            // Create new head object
            do
            {
                // Make sure the head is on the screen
                head = new SnakeObject(STARTINGTOTAL);
            } while (head.snake[0].X < 0);

            food = new Food(randomFood);
            do
            {
                // Create the new food an make sure it doesn't overlap
                food.randomizeLocation(randomFood);
            } while (head.snake[0].X == Food.FoodBlock.X || head.snake[0].X == Food.FoodBlock.X);
            gameArea = new Rectangle(0, 0, screenWidth, screenHeight);

        }

        public bool AdjustGame()
        {
            // Disable minimize and maximize boxes on toolbar
            this.MinimizeBox = false;
            this.MaximizeBox = false;
            System.Windows.Forms.Form.ActiveForm.Text = this.titleText;

            // Used for unit test
            return true;
        }

        public bool HandleCollisions()
        {

            // Get the size of active form
            var screen = System.Windows.Forms.Form.ActiveForm.Bounds;
            screenHeight = screen.Height;
            screenWidth = screen.Width;

            // Create game over image based on screen dimension
            // Assign score change on collisions
            if (screenHeight == EASYHEIGHT)
            {
                // Easy game height and width, speed and score assignment
                gameOverPopup = new RectangleF(screenHeight / 3.5F, screenWidth / 3.5F, gameOver.Width, gameOver.Height);
                titleText = "Michael Pratt Snake Game - Easy Mode - Score: ";
                animationTimer.Interval = 80;
            }
            else if (screenHeight == MEDIUMHEIGHT)
            {
                // Medium game height and width, speed and score assignment
                gameOverPopup = new RectangleF(screenHeight / 4, screenWidth / 4, gameOver.Width, gameOver.Height);
                titleText = "Michael Pratt Snake Game - Medium Mode - Score: ";
                animationTimer.Interval = 60;
            }
            else if (screenHeight == HARDHEIGHT)
            {
                // Hard game height and width, speed and score assignment
                gameOverPopup = new RectangleF(screenHeight / 10, screenWidth / 10, gameOver.Width, gameOver.Height);
                titleText = "Michael Pratt Snake Game - Hard Mode - Score: ";
                animationTimer.Interval = 50;
            }


            // Check for head hitting the walls
            if (SnakeHitsLeftWall(head, screenWidth) || SnakeHitsRightWall(head, screenWidth)
               || SnakeHitsTopWall(head, screenHeight) || SnakeHitsBottomWall(head, screenHeight))
            {
                stopSnakeMoving();
                boolGameOver = true;
                tailCount = 0;
                return true;
            }

            // Check for head running into tail
            if (SnakeHitsItself(head))
            {
                stopSnakeMoving();
                boolGameOver = true;
                tailCount = 0;
                return true;
            }
            return false;
        }

        // Stop the snake
        public bool stopSnakeMoving()
        {
            leftDirection = false;
            rightDirection = false;
            upDirection = false;
            downDirection = false;
            animationTimer.Stop();

            // Used for unit test
            return true;
        }

        // Check if the snake hit itself
        public bool SnakeHitsItself(SnakeObject head)
        {
            for (int i = 1; i < head.snake.Length; i++)
            {
                if (head.snake[0].X == head.snake[i].X && head.snake[0].Y == head.snake[i].Y)
                {
                    return true;
                }
            }
            return false;
        }

        // Snake hits bottom ball
        public bool SnakeHitsBottomWall(SnakeObject head, int h)
        {
            return head.snake[0].Y + 50 > h;
        }

        // Snake hits top ball
        public bool SnakeHitsTopWall(SnakeObject head, int h)
        {
            return head.snake[0].Y < 0;
        }

        // Snake hits right ball
        public bool SnakeHitsRightWall(SnakeObject head, int w)
        {
            return head.snake[0].X + 25 >= w;
        }

        // Snake hits left ball
        public bool SnakeHitsLeftWall(SnakeObject head, int w)
        {
            return head.snake[0].X < 0;
        }

        // Paint method
        public void Form1_Paint(object sender, PaintEventArgs e)
        {
            // Draw the snake's head
            head.Draw(e.Graphics);
            food.Draw(e.Graphics);

            for (int i = 0; i < head.snake.Length; i++)
            {

                if (head.snake.Length >= WINTOTAL)
                {
                    e.Graphics.DrawImage(gameWon, gameOverPopup);
                    boolGameOver = true;
                    stopSnakeMoving();
                }


                if (head.snake[i].IntersectsWith(Food.FoodBlock))
                {
                    food.randomizeLocation(randomFood);
                    head.addTail(1);
                    animationTimer.Interval -= 2;
                    tailCount++;
                    this.Text = this.titleText + tailCount;
                }
                else if (SnakeHitsItself(head))
                {
                    e.Graphics.DrawImage(snakeEatSelf, gameOverPopup);
                }
                else if (HandleCollisions())
                {
                    e.Graphics.DrawImage(gameOver, gameOverPopup);
                }
            }
        }

        // Keydown method
        public void Form1_KeyDown(object sender, KeyEventArgs e)
        {
            // Check for change of direction
            switch (e.KeyData.ToString())
            {
                case "Space":
                    {
                        // BELOW ARE CURRENTLY USED AS FEATURE TESTING
                        //food.randomizeLocation(randomFood);
                        //head.addTail(1);

                        if (boolGameOver)
                        {
                            head = new SnakeObject(STARTINGTOTAL);
                            food = new Food(randomFood);
                            if (head.snake[0].X == Food.FoodBlock.X)
                            {
                                food.randomizeLocation(randomFood);
                            }
                            boolGameOver = false;
                            this.Text = this.titleText + 0;
                            this.tailCount = 0;

                        }
                        else
                        {
                            animationTimer.Start();
                        }
                        // TODO: Add level scaling with increased speed.
                        if (boolLevelComplete)
                        {

                        }
                        break;
                    }
                case "Left":
                    {
                        if (rightDirection == false)
                        {
                            leftDirection = true;
                            rightDirection = false;
                            upDirection = false;
                            downDirection = false;
                        }
                        break;
                    }
                case "Right":
                    {
                        if (animationTimer.Enabled == false)
                        {
                            animationTimer.Start();
                        }
                        if (leftDirection == false)
                        {
                            rightDirection = true;
                            leftDirection = false;
                            upDirection = false;
                            downDirection = false;
                        }
                        break;
                    }
                case "Up":
                    {
                        if (animationTimer.Enabled == false)
                        {
                            animationTimer.Start();
                        }
                        if (downDirection == false)
                        {
                            upDirection = true;
                            downDirection = false;
                            leftDirection = false;
                            rightDirection = false;
                        }
                        break;
                    }
                case "Down":
                    {
                        if (animationTimer.Enabled == false)
                        {
                            animationTimer.Start();
                        }
                        if (upDirection == false)
                        {
                            downDirection = true;
                            upDirection = false;
                            rightDirection = false;
                            leftDirection = false;
                        }
                        break;
                    }
            }

            // Repaint
            Invalidate();
        }

        // Tick method
        public void animationTimer_Tick(object sender, EventArgs e)
        {
            // Move depending on what direction
            if (rightDirection)
            {
                head.moveRight();
            }
            else if (leftDirection)
            {
                head.moveLeft();
            }
            else if (upDirection)
            {
                head.moveUp();
            }
            else if (downDirection)
            {
                head.moveDown();
            }

            HandleCollisions();
            Invalidate();

        }

    }
}
