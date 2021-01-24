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
    /// Class containing methods for PowerExp class' Evaulate method testing
    /// </summary>
    [TestClass]
    public class PowerExpTest
    {
        private PowerExp powExp;
        private Difference dif;

        /// <summary>
        /// Testing the forbidden zero power
        /// </summary>
        [TestMethod]
        [ExpectedException(typeof(ArgumentException))]
        public void ZeroPowerZero()
        {
            powExp = new PowerExp(new Number(0.0), new Number(0.0));
            powExp.Evaluate();
        }

        /// <summary>
        /// Testign the accept-able zero power
        /// </summary>
        [TestMethod]
        public void NumberToZero()
        {
            //---Negative values
            powExp = new PowerExp(new Number(-125.261), new Number(0.0));
            dif = new Difference(1.0, powExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());

            powExp = new PowerExp(new Number(-6333.0), new Number(0.0));
            dif = new Difference(1.0, powExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());

            powExp = new PowerExp(new Number(-91.2522222222252), new Number(0.0));
            dif = new Difference(1.0, powExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());

            //---Possitive values
            powExp = new PowerExp(new Number(2.0), new Number(0.0));
            dif = new Difference(1.0, powExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());

            powExp = new PowerExp(new Number(13.0), new Number(0.0));
            dif = new Difference(1.0, powExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());

            powExp = new PowerExp(new Number(250.0), new Number(0.0));
            dif = new Difference(1.0, powExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());
        }

        /// <summary>
        /// Testing the oneth power
        /// </summary>
        [TestMethod]
        public void NumberToOne()
        {
            //---Negative values
            powExp = new PowerExp(new Number(-2524.256), new Number(1.0));
            dif = new Difference(-2524.256, powExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());

            powExp = new PowerExp(new Number(-635442.0), new Number(1.0));
            dif = new Difference(-635442.0, powExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());

            //---Zero
            powExp = new PowerExp(new Number(0.0), new Number(1.0));
            dif = new Difference(0.0, powExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());

            //---Possitive values
            powExp = new PowerExp(new Number(9449593.0), new Number(1.0));
            dif = new Difference(9449593.0, powExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());

            powExp = new PowerExp(new Number(935.7654334565), new Number(1.0));
            dif = new Difference(935.7654334565, powExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());
        }

        /// <summary>
        /// Testing the non-natural exponent
        /// </summary>
        [TestMethod]
        [ExpectedException(typeof(ArgumentException))]
        public void ForbiddenExponent()
        {
            powExp = new PowerExp(new Number(-35.0), new Number(-5.0));
            powExp.Evaluate();

            powExp = new PowerExp(new Number(9.0), new Number(-3.1));
            powExp.Evaluate();

            powExp = new PowerExp(new Number(0.0), new Number(0.6));
            powExp.Evaluate();

            powExp = new PowerExp(new Number(53.0), new Number(1.2));
            powExp.Evaluate();
        }

        /// <summary>
        /// Testing the even power
        /// </summary>
        [TestMethod]
        public void EvenPower()
        {
            powExp = new PowerExp(new Number(-524.2566), new Number(2.0));
            dif = new Difference(274844.98264356, powExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());

            powExp = new PowerExp(new Number(52.5), new Number(4.0));
            dif = new Difference(7.5969140625e6, powExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());

            powExp = new PowerExp(new Number(-6.2), new Number(8.0));
            dif = new Difference(2.18340105584896e6, powExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());

            powExp = new PowerExp(new Number(3.0), new Number(32.0));
            dif = new Difference(1853020188851841.0, powExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());

            powExp = new PowerExp(new Number(-1.0), new Number(100.0));
            dif = new Difference(1.0, powExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());
        }

        /// <summary>
        /// Testing the odd power
        /// </summary>
        [TestMethod]
        public void OddPower()
        {
            powExp = new PowerExp(new Number(-1.0), new Number(3.0));
            dif = new Difference(-1.0, powExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());

            powExp = new PowerExp(new Number(-6442.99809), new Number(7.0));
            dif = new Difference(-4.6090988054196385739060494644026e26, powExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());

            powExp = new PowerExp(new Number(16.2), new Number(21.0));
            dif = new Difference(2.51081841601403049237078134525e25, powExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());

            powExp = new PowerExp(new Number(7.0), new Number(43.0));
            dif = new Difference(2.18381437599179659910931225275e36, powExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());

            powExp = new PowerExp(new Number(-1.12), new Number(101.0));
            dif = new Difference(-93544.93761371921053534641094, powExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());
        }
    }
}
