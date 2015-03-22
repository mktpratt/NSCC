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
    public partial class MainMenu : Form
    {
        public MainMenu()
        {
            InitializeComponent();
        }

        // Magic numbers below to account for exact size of screen so that
        // food doesn't get cut in half
        private void buttonEasy_Click(object sender, EventArgs e)
        {
            GameForm form = new GameForm();
            form.Width = 815;
            form.Height = 810;
            form.Text = "Michael Pratt Snake Game - Easy Mode - Score: 0";
            form.StartPosition = FormStartPosition.CenterScreen;
            form.Show();
        }

        private void buttonMedium_Click(object sender, EventArgs e)
        {
            GameForm form = new GameForm();
            form.Width = 615;
            form.Height = 610;
            form.Text = "Michael Pratt Snake Game - Medium Mode - Score: 0";
            form.StartPosition = FormStartPosition.CenterScreen;
            form.Show();
        }

        private void buttonHard_Click(object sender, EventArgs e)
        {
            GameForm form = new GameForm();
            form.Width = 415;
            form.Height = 410;
            form.Text = "Michael Pratt Snake Game - Hard Mode - Score: 0";
            form.StartPosition = FormStartPosition.CenterScreen;
            form.Show();
        }

        private void MainMenu_Paint(object sender, PaintEventArgs e)
        {
            String drawString = "Eat 20 snakes to win!";
            Font drawFont = new Font("Arial", 16);
            SolidBrush drawBrush = new SolidBrush(Color.Black);

            // Print location
            PointF drawPoint = new PointF(65.0F, 50.0F);

            // Draw the string
            e.Graphics.DrawString(drawString, drawFont, drawBrush, drawPoint);
        }
    }
}
