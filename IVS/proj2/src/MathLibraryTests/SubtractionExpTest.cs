/************************************************************
 *      ROZSIVAL MICHAL                                     *
 *      IVS - project 2                                     *
 *      FEB/MAR 2019                                        *
 *      Testing class for MathLibrary                       *
 *      Version 1.0                                         *
 ************************************************************/

using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Collections.Generic;
using MathLibrary;

namespace MathLibraryTests
{
    /// <summary>
    /// Class containing methods for SubtractionExp class' Evaulate method testing
    /// </summary>
    [TestClass]
    public class SubtractionExpTest : ITest
    {
        private SubtractionExp subExp;
        private Difference dif;

        /// <summary>
        /// Testing the difference of two random real numbers
        /// </summary>
        [TestMethod]
        public void TwoDifferentNumbers()
        {
            subExp = new SubtractionExp(new Number(456.336136), new Number(40.2500011));
            dif = new Difference(416.0861349, subExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());
        }

        [TestMethod]
        public void TwoOppositeNumbers()
        {
            subExp = new SubtractionExp(new Number(156776323.0012), new Number(-156776323.0012));
            dif = new Difference(313552646.0024, subExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());
        }


        [TestMethod]
        public void TwoSameNumbers()
        {
            subExp = new SubtractionExp(new Number(0.1111125224), new Number(0.1111125224));
            dif = new Difference(0.0, subExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());
        }

        [TestMethod]
        public void TwoSpecialFormatNumbers()
        {
            subExp = new SubtractionExp(new Number(3e-13), new Number(2.1e-15));
            dif = new Difference(2.979e-13, subExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());
        }

        [TestMethod]
        public void WithZero()
        {
            //---Testing two zeroes
            subExp = new SubtractionExp(new Number(0.0), new Number(0.0));
            dif = new Difference(0.0, subExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());


            //---Testing zero as first argument
            subExp = new SubtractionExp(new Number(0.0), new Number(-0.00000000001));
            dif = new Difference(0.00000000001, subExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());

            //---Testing zero as second argument
            subExp = new SubtractionExp(new Number(12e300), new Number(0.0));
            dif = new Difference(12e300, subExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());
        }
    }
}