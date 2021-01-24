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
    /// Class containing methods for Difference class' IsAlmostSame method testing
    /// </summary>
    [TestClass]
    public class DifferenceTest
    {
        private Difference dif;

        /// <summary>
        /// Testing identical values
        /// </summary>
        [TestMethod]
        public void SameValues()
        {
            dif = new Difference(65432.765, 65432.765);
            Assert.IsTrue(dif.IsAlmostSame());

            dif = new Difference(-2654.2345, -2654.2345);
            Assert.IsTrue(dif.IsAlmostSame());

            dif = new Difference(9683.63562577, 9683.63562577);
            Assert.IsTrue(dif.IsAlmostSame());

            dif = new Difference(0.6434567654, 0.6434567654);
            Assert.IsTrue(dif.IsAlmostSame());

            dif = new Difference(8765434567654.0, 8765434567654.0);
            Assert.IsTrue(dif.IsAlmostSame());
        }

        /// <summary>
        /// Testing the aproximatly same values (+-10^-8% of first Difference argument)
        /// </summary>
        [TestMethod]
        public void AlmostSame()
        {
            dif = new Difference(65432.768765435676545, 65432.768761234568642);
            Assert.IsTrue(dif.IsAlmostSame());

            dif = new Difference(-2654.2345, -2654.23450009876543456);
            Assert.IsTrue(dif.IsAlmostSame());

            dif = new Difference(0.0123435625772, 0.0123435625771);
            Assert.IsTrue(dif.IsAlmostSame());

            dif = new Difference(2.1e25, 2.1000000000256e25);
            Assert.IsTrue(dif.IsAlmostSame());

            dif = new Difference(165.0, 165.000000009999999999);
            Assert.IsTrue(dif.IsAlmostSame());
        }


        /// <summary>
        /// Testing different values
        /// </summary>
        [TestMethod]
        public void DifferentValues()
        {
            dif = new Difference(123.999999999, 123.999999889);
            Assert.IsFalse(dif.IsAlmostSame());

            dif = new Difference(65432.765, 75432.765);
            Assert.IsFalse(dif.IsAlmostSame());

            dif = new Difference(-2654.2345, 2654.2345);
            Assert.IsFalse(dif.IsAlmostSame());

            dif = new Difference(9683.43562577, 9683.63562577);
            Assert.IsFalse(dif.IsAlmostSame());

            dif = new Difference(2, 25);
            Assert.IsFalse(dif.IsAlmostSame());

            dif = new Difference(1.2, 1.19999);
            Assert.IsFalse(dif.IsAlmostSame());
        }

    }
}
