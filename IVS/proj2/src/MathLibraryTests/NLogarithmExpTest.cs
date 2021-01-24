/************************************************************
 *      ROZSIVAL MICHAL                                     *
 *      IVS - project 2                                     *
 *      MAR/APR 2019                                        *
 *      Testing class for MathLibrary                       *
 *      Version 1.0                                         *
 ************************************************************/

using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using MathLibrary;



namespace MathLibraryTests
{
    /// <summary>
    /// Class containing methods for NLogharitm class' Evaulate method testing
    /// </summary>
    [TestClass]
    public class NLogarithmExpTest
    {
        private NLogarithmExp  lnExp;
        private Difference dif;

        /// <summary>
        /// Domain range of any logharitm is > 0
        /// </summary>
        [TestMethod]
        [ExpectedException(typeof(ArgumentException))]
        public void ForbiddenInput()
        {
            lnExp = new NLogarithmExp(new Number(-10334.234));
            lnExp.Evaluate();
            lnExp = new NLogarithmExp(new Number(-1266.0));
            lnExp.Evaluate();
            lnExp = new NLogarithmExp(new Number(-52));
            lnExp.Evaluate();
            lnExp = new NLogarithmExp(new Number(-1.34));
            lnExp.Evaluate();
            lnExp = new NLogarithmExp(new Number(-0.0000000012));
            lnExp.Evaluate();
            lnExp = new NLogarithmExp(new Number(0.0));
            lnExp.Evaluate();
        }

        /// <summary>
        /// Testing the log on valid input
        /// </summary>
        [TestMethod]
        public void ValidInput()
        {
            lnExp = new NLogarithmExp(new Number(1.0));
            dif = new Difference(0.0, lnExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());


            lnExp = new NLogarithmExp(new Number(Constants.E));
            dif = new Difference(1.0, lnExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());


            lnExp = new NLogarithmExp(new Number(11.0));
            dif = new Difference(2.39789527279837054406, lnExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());

            lnExp = new NLogarithmExp(new Number(21.24));
            dif = new Difference(3.05588619637373808420, lnExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());

            lnExp = new NLogarithmExp(new Number(0.00000012));
            dif = new Difference(-15.93577409416436516191, lnExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());

            lnExp = new NLogarithmExp(new Number(654324.1622));
            dif = new Difference(13.39135816849633883161, lnExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());

            lnExp = new NLogarithmExp(new Number(99999999992.0));
            dif = new Difference(25.32843602285450252419, lnExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());

            lnExp = new NLogarithmExp(new Number(0.00000000001));
            dif = new Difference(-25.32843602293450252419, lnExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());
            
            lnExp = new NLogarithmExp(new Number(5592.62332632));
            dif = new Difference(8.62920374521233444745, lnExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());

            lnExp = new NLogarithmExp(new Number(599383894048949592.93033));
            dif = new Difference(40.93467867931036735299, lnExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());
        }
    }
}
