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
using System.Collections.Generic;

namespace MathLibraryTests
{
    /// <summary>
    /// Class containing methods for MultiplicationExp class' Evaulate method testing
    /// </summary>
    [TestClass]
    public class MultiplicationExpTest : ITest
    {

        private MultiplicationExp mulExp;
        private Difference dif;

        /// <summary>
        /// Testing the product of two random real numbers
        /// </summary>
        [TestMethod]
        public void TwoDifferentNumbers()
        {
            mulExp = new MultiplicationExp(new Number(13553.2992), new Number(-2884.2155431));
            dif = new Difference(-39090636.21292479552, mulExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());

        }

        /// <summary>
        /// Testing the pruduct of two opposite real numbers
        /// </summary>
        [TestMethod]
        public void TwoOppositeNumbers()
        {
            mulExp = new MultiplicationExp(new Number(125235.1265436), new Number(0.00000798498015372));
            dif = new Difference(1.0, mulExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());


        }

        /// <summary>
        /// Testing the product of two same real numbers
        /// </summary>
        [TestMethod]
        public void TwoSameNumbers()
        {
            mulExp = new MultiplicationExp(new Number(124.126665435654356543), new Number(124.126665435654356543));
            dif = new Difference(15407.4290721748699306017565, mulExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());
        }

        /// <summary>
        /// Testing the sum of two numbers in speacial exponent format
        /// </summary>
        [TestMethod]
        public void TwoSpecialFormatNumbers()
        {
            mulExp = new MultiplicationExp(new Number(14e21), new Number(3e-15));
            dif = new Difference(4.2e7, mulExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());
        }

        /// <summary>
        /// Method testing the sum of number and zero in multiple combination
        /// </summary>
        [TestMethod]
        public void WithZero()
        {
            //---Testing two zeroes
            mulExp = new MultiplicationExp(new Number(0.0), new Number(0.0));
            dif = new Difference(0.0, mulExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());

            //---Testing zero as first argument
            mulExp = new MultiplicationExp(new Number(0.0), new Number(1356.236242141241));
            dif = new Difference(0.0, mulExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());


            //---Testing zero as second argument
            mulExp = new MultiplicationExp(new Number(-1.25125112), new Number(0.0));
            dif = new Difference(0.0, mulExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());



        }
    }
}
