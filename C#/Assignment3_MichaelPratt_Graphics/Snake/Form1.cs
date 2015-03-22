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
    public partial class Form1 : Form
    {

        SnakeHead head;

        public Form1()
        {
            InitializeComponent();
            FitEntireScreen();

            head = new SnakeHead();
        }

        private void FitEntireScreen()
        {
            Size resolutionSize = SystemInformation.PrimaryMonitorSize;
            this.Height = resolutionSize.Height;
            this.Width = resolutionSize.Width;
        }

        private void Form1_Paint(object sender, PaintEventArgs e)
        {
            head.Draw(e.Graphics);
        }

        private void Form1_KeyDown(object sender, KeyEventArgs e)
        {
            switch (e.KeyValue.ToString())
            {
                case "Left":
                    {
                        head.Move(SnakeHead.Direction.Left);
                        Invalidate();
                        break;
                    }
                case "Right":
                    {
                        head.Move(SnakeHead.Direction.Right);
                        Invalidate();
                            break;
                    }
                case "Up":
                    {
                        head.Move(SnakeHead.Direction.Up);
                        Invalidate();
                        break;
                    }
                case "Down":
                    {
                        head.Move(SnakeHead.Direction.Down);
                        Invalidate();
                        break;
                    }

            }
        }

    }
}
