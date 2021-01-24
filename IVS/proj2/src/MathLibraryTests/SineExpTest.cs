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
    /// Class containing methods for SineExp class' Evaulate method testing
    /// Each method name is function input. No exception excepted.
    /// </summary>
    [TestClass]
    public class SineExpTest : ITestTrigono
    {
        private SineExp sineExp;
        private Difference dif;
       
        [TestMethod]
        public void InputEightPiDivSix()
        {
            sineExp = new SineExp(new Number(Constants.EightPiDivSix));
            dif = new Difference(-Constants.SqrtThreeDivTwo, sineExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());
        }

        [TestMethod]
        public void InputElevenPiDivSix()
        {
            sineExp = new SineExp(new Number(Constants.ElevenPiDivSix));
            dif = new Difference(-Constants.OneDivTwo, sineExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());
        }

        [TestMethod]
        public void InputFivePiDivFour()
        {
            sineExp = new SineExp(new Number(Constants.FivePiDivFour));
            dif = new Difference(-Constants.SqrtTwoDivTwo, sineExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());
        }

        [TestMethod]
        public void InputFivePiDivSix()
        {
            sineExp = new SineExp(new Number(Constants.FivePiDivSix));
            dif = new Difference(Constants.OneDivTwo, sineExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());
        }

        [TestMethod]
        public void InputFourPiDivSix()
        {
            sineExp = new SineExp(new Number(Constants.FourPiDivSix));
            dif = new Difference(Constants.SqrtThreeDivTwo, sineExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());
        }

        [TestMethod]
        public void InputPi()
        {
            sineExp = new SineExp(new Number(Constants.Pi));
            dif = new Difference(Constants.Zero, sineExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());
        }

        [TestMethod]
        public void InputPiDivFour()
        {
            sineExp = new SineExp(new Number(Constants.PiDivFour));
            dif = new Difference(Constants.SqrtTwoDivTwo, sineExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());
        }

        [TestMethod]
        public void InputPiDivSix()
        {
            sineExp = new SineExp(new Number(Constants.PiDivSix));
            dif = new Difference(Constants.OneDivTwo, sineExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());
        }

        [TestMethod]
        public void InputPiDivTwo()
        {
            sineExp = new SineExp(new Number(Constants.PiDivTwo));
            dif = new Difference(Constants.One, sineExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());
        }

        [TestMethod]
        public void InputSevenPiDivFour()
        {
            sineExp = new SineExp(new Number(Constants.SevenPiDivFour));
            dif = new Difference(-Constants.SqrtTwoDivTwo, sineExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());
        }

        [TestMethod]
        public void InputSevenPiDivSix()
        {
            sineExp = new SineExp(new Number(Constants.SevenPiDivSix));
            dif = new Difference(-Constants.OneDivTwo, sineExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());
        }

        [TestMethod]
        public void InputTenPiDivSix()
        {
            sineExp = new SineExp(new Number(Constants.TenPiDivSix));
            dif = new Difference(-Constants.SqrtThreeDivTwo, sineExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());
        }

        [TestMethod]
        public void InputThreePiDivFour()
        {
            sineExp = new SineExp(new Number(Constants.ThreePiDivFour));
            dif = new Difference(Constants.SqrtTwoDivTwo, sineExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());
        }

        [TestMethod]
        public void InputThreePiDivTwo()
        {
            sineExp = new SineExp(new Number(Constants.ThreePiDivTwo));
            dif = new Difference(-Constants.One, sineExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());
        }

        [TestMethod]
        public void InputTwoPiDivSix()
        {
            sineExp = new SineExp(new Number(Constants.TwoPiDivSix));
            dif = new Difference(Constants.SqrtThreeDivTwo, sineExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());
        }

        [TestMethod]
        public void InputZero()
        {
            sineExp = new SineExp(new Number(Constants.Zero));
            dif = new Difference(Constants.Zero, sineExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());
        }

        [TestMethod]
        public void RandomValues()
        {
            sineExp = new SineExp(new Number(-363.25334));
            dif = new Difference((0.92129894706128631927), sineExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());

            sineExp = new SineExp(new Number(1.235));
            dif = new Difference((0.94414820251856255790), sineExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());

            sineExp = new SineExp(new Number(1.7));
            dif = new Difference((0.99166481045246861534), sineExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());

            sineExp = new SineExp(new Number(3.0));
            dif = new Difference((0.14112000805986722210), sineExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());

            sineExp = new SineExp(new Number(25455.35221));
            dif = new Difference((0.82661281223969933138), sineExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());
        }
    }
}
