


using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using MathLibrary;
using System.Collections.Generic;

/// <summary>
/// Containing tests for  basic+ math algorithms
/// </summary>
namespace MathLibraryTests
{

    /// <summary>
    /// Class containing methods for AdditionExp class' Evaulate method testing
    /// </summary>
    [TestClass]
    public class AdditionExpTest : ITest
    {
        private AdditionExp addExp;
        private Difference dif;

        /// <summary>
        /// Testing the sum of two random real numbers
        /// </summary>
        [TestMethod]
        public void TwoDifferentNumbers()
        {
            addExp = new AdditionExp(new Number(-35216.012552), new Number(162.26671));
            dif = new Difference(-35053.745842, addExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());
        }

        /// <summary>
        /// Testing the sum of two opposite real numbers
        /// </summary>
        [TestMethod]
        public void TwoOppositeNumbers()
        {
            addExp = new AdditionExp(new Number(734.13623), new Number(-734.13623));
            dif = new Difference(0.0, addExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());
        }

        /// <summary>
        /// Testing the sum of two same real numbers
        /// </summary>
        [TestMethod]
        public void TwoSameNumbers()
        {
            addExp = new AdditionExp(new Number(120.0000001452), new Number(120.0000001452));
            dif = new Difference(240.0000002904, addExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());
        }

        /// <summary>
        /// Testing the sum of two numbers in speacial exponent format
        /// </summary>
        [TestMethod]
        public void TwoSpecialFormatNumbers()
        {
            addExp = new AdditionExp(new Number(1.5e23), new Number(3.0e21));
            dif = new Difference(1.53e23, addExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());
        }

        /// <summary>
        /// Method testing the sum of number and zero in multiple combination
        /// </summary>
        [TestMethod]
        public void WithZero()
        {
            //---Testing two zeroes
            addExp = new AdditionExp(new Number(0.0), new Number(0.0));
            dif = new Difference(0.0, addExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());

            //---Testing zero as first argument
            addExp = new AdditionExp(new Number(0.0), new Number(-152.252));
            dif = new Difference(-152.252, addExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());

            //---Testing zero as second argument
            addExp = new AdditionExp(new Number(3333.025123), new Number(0.0));
            dif = new Difference(3333.025123, addExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());
        }
    }
}