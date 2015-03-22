using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Drawing;

namespace SnakeUnitTestProject
{
    [TestClass]
    public class FoodUnitTest
    {
        [TestMethod]
        public void FoodTestMethodRandomizeLocation()
        {
            Random rnd = new Random();
            Snake.Food.initialize(rnd, 250, 250);
            Assert.IsNotNull(Snake.Food.FoodBlock);
            Assert.IsTrue(Snake.Food.FoodBlock.X % 25 == 0);
            Assert.IsTrue(Snake.Food.FoodBlock.Y % 25 == 0);
        }

        [TestMethod]
        public void FoodTestMethodCalculateSize()
        {
            Random rnd = new Random();
            Snake.Food.initialize(rnd, 250, 250);
            Assert.IsTrue(Snake.Food.FoodBlock.Width == 25);
            Assert.IsTrue(Snake.Food.FoodBlock.Height == 25);
        }
    }
}
