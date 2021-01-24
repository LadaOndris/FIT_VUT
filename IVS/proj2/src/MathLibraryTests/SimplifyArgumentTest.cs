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
    /// Class testing SimplifyArgument class
    /// </summary>
    [TestClass]
    public class SimplifyArgumentTest
    {
        Difference dif;
        SimplifyArgument sim;

        /// <summary>
        /// Inputing values in accept-able interval of <-pi;pi> ~ <-3.14;3.14>
        /// </summary>
        [TestMethod]
        public void InRange()
        {
            sim = new SimplifyArgument(-Constants.Pi);
            dif = new Difference(-Constants.Pi, sim.SimplifyOfTwoPi());
            Assert.IsTrue(dif.IsAlmostSame());

            sim = new SimplifyArgument(-Constants.PiDivSix);
            dif = new Difference(-Constants.PiDivSix, sim.SimplifyOfTwoPi());
            Assert.IsTrue(dif.IsAlmostSame());

            sim = new SimplifyArgument(Constants.Zero);
            dif = new Difference(Constants.Zero, sim.SimplifyOfTwoPi());
            Assert.IsTrue(dif.IsAlmostSame());

            sim = new SimplifyArgument(Constants.PiDivFour);
            dif = new Difference(Constants.PiDivFour, sim.SimplifyOfTwoPi());
            Assert.IsTrue(dif.IsAlmostSame());

            sim = new SimplifyArgument(Constants.Pi);
            dif = new Difference(Constants.Pi, sim.SimplifyOfTwoPi());
            Assert.IsTrue(dif.IsAlmostSame());

            sim = new SimplifyArgument(2.8665);
            dif = new Difference(2.8665, sim.SimplifyOfTwoPi());
            Assert.IsTrue(dif.IsAlmostSame());
        }

        /// <summary>
        /// Inputing value smaller than -pi ~ -3.14 and expecting output in range of <-pi;pi> ~ <-3.14;3.14>
        /// </summary>
        [TestMethod]
        public void OutOfRangeSmaller()
        {
            sim = new SimplifyArgument(-Constants.ThreePiDivTwo);
            dif = new Difference(Constants.PiDivTwo, sim.SimplifyOfTwoPi());
            Assert.IsTrue(dif.IsAlmostSame());

            sim = new SimplifyArgument(-Constants.TwoPi);
            dif = new Difference(Constants.Zero, sim.SimplifyOfTwoPi());
            Assert.IsTrue(dif.IsAlmostSame());

            sim = new SimplifyArgument(-5443.366);
            dif = new Difference(-2.12752398247811098270, sim.SimplifyOfTwoPi());
            Assert.IsTrue(dif.IsAlmostSame());
        }

        /// <summary>
        /// Inputing value greater than pi ~ 3.14 and expecting output in range of <-pi;pi> ~ <-3.14;3.14>
        /// </summary>
        [TestMethod]
        public void OutOfRangeGreater()
        {
            sim = new SimplifyArgument(Constants.ThreePiDivTwo);
            dif = new Difference(-Constants.PiDivTwo, sim.SimplifyOfTwoPi());
            Assert.IsTrue(dif.IsAlmostSame());

            sim = new SimplifyArgument(Constants.TwoPi);
            dif = new Difference(Constants.Zero, sim.SimplifyOfTwoPi());
            Assert.IsTrue(dif.IsAlmostSame());

            sim = new SimplifyArgument(654354.2572);
            dif = new Difference(-1.79343091085405290706, sim.SimplifyOfTwoPi());
            Assert.IsTrue(dif.IsAlmostSame());
        }

    }
}
