/************************************************************
 *      ROZSIVAL MICHAL                                     *
 *      IVS - project 2                                     *
 *      FEB/MAR 2019                                        *
 *      Testing class for MathLibrary                       *
 *      Version 1.0                                         *
 ************************************************************/

using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using MathLibrary;

namespace MathLibraryTests
{
    /// <summary>
    /// Class containing methods for FactorialExp class' Evaulate method testing
    /// </summary>
    [TestClass]
    public class FactorialExpTest
    {
        private  FactorialExp factExp;
        private Difference dif;

        /// <summary>
        /// Testing the output for zero input
        /// </summary>
        [TestMethod]
        public void ZeroTested()
        {
            factExp = new FactorialExp(new Number(0.0));
            dif = new Difference(factExp.Evaluate(), 1.0);
            Assert.IsTrue(dif.IsAlmostSame());
            factExp = new FactorialExp(new Number(-0.0));
            dif = new Difference(factExp.Evaluate(), 1.0);
            Assert.IsTrue(dif.IsAlmostSame());
        }


        /// <summary>
        /// Testing the exception for negative value
        /// </summary>
        [TestMethod]
        [ExpectedException(typeof(ArgumentException))]
        public void NegativeValue()
        {
            factExp = new FactorialExp(new Number(-5.0));
            factExp.Evaluate();
            factExp = new FactorialExp(new Number(-11456.0));
            factExp.Evaluate();
            factExp = new FactorialExp(new Number(-12.5262));
            factExp.Evaluate();
        }

        /// <summary>
        /// Testing the exception for non-integer values
        /// </summary>
        [TestMethod]
        [ExpectedException(typeof(ArgumentException))]
        public void ForbiddenValue()
        {
            factExp = new FactorialExp(new Number(1.4));
            factExp.Evaluate();
            factExp = new FactorialExp(new Number(215.6));
            factExp.Evaluate();
            factExp = new FactorialExp(new Number(222262.56));
            factExp.Evaluate();
        }


        /// <summary>
        /// Testing the result for accept-able values
        /// </summary>
        [TestMethod]
        public void NormalValue()
        {
            factExp = new FactorialExp(new Number(1.0));
            dif = new Difference(1.0, factExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());

            factExp = new FactorialExp(new Number(3.0));
            dif = new Difference(6.0, factExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());

            factExp = new FactorialExp(new Number(7.0));
            dif = new Difference(5040.0, factExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());

            factExp = new FactorialExp(new Number(8.0));
            dif = new Difference(40320.0, factExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());

            factExp = new FactorialExp(new Number(21.0));
            dif = new Difference(51090942171709440000.0, factExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());
        }







    }
}
