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
    /// Class containing methods for DivisionExp class' Evaulate method testing
    /// </summary>
    [TestClass]
    public class DivisionExpTest :ITest
    {
        private DivisionExp divExp;
        private Difference dif;

        /// <summary>
        /// Testing the quotient of two random real numbers
        /// </summary>
        [TestMethod]
        public void TwoDifferentNumbers()
        {
            divExp = new DivisionExp(new Number(-1.2654345654), new Number(0.76543));
            dif = new Difference(-1.65323356205008949218, divExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());
        }

        /// <summary>
        /// Testing the quotient of two opposite real numbers
        /// </summary>
        [TestMethod]
        public void TwoOppositeNumbers()
        {
            divExp = new DivisionExp(new Number(352.543), new Number(0.0028365334157819046187));
            dif = new Difference(124286.566849000000001, divExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());
        }

        /// <summary>
        /// Testing the quotient of two same real numbers
        /// </summary>
        [TestMethod]
        public void TwoSameNumbers()
        {
            divExp = new DivisionExp(new Number(3255.265435654), new Number(3255.265435654));
            dif = new Difference(1.0, divExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());
        }

        /// <summary>
        /// Testing the quotient of two numbers in speacial exponent format
        /// </summary>
        [TestMethod]
        public void TwoSpecialFormatNumbers()
        {
            divExp = new DivisionExp(new Number(3.0e-12), new Number(3.621e51));
            dif = new Difference(8.2850041425020712510356e-64, divExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());
        }

        /// <summary>
        /// Method testing the quotient of number and zero in multiple combination
        /// </summary>
        [TestMethod]
        [ExpectedException(typeof(ArgumentException))]
        public void WithZero()
        {
            //---Testing two zeroes
            divExp = new DivisionExp(new Number(0.0), new Number(0.0));
            divExp.Evaluate();

            //---Testing zero as first argument
            divExp = new DivisionExp(new Number(0.0), new Number(125125.256121411));
            dif = new Difference(0.0, divExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());

            //---Testing zero as second argument
            divExp = new DivisionExp(new Number(525342.25), new Number(0.0));
            divExp.Evaluate();
        }
    }
}
