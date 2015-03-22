using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace SnakeUnitTestProject
{
    [TestClass]
    public class SnakeUnitTest
    {
        [TestMethod]
        public void SnakeTestMethodAddTail()
        {
            int numTails = 1;
            Snake.SnakeObject snake = new Snake.SnakeObject(numTails);
            Assert.IsNotNull(snake);
        }
    }
}
