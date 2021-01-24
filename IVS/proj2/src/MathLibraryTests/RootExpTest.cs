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
    /// Class containing methods for RootExp class' Evaulate method testing
    /// </summary>
    [TestClass]
    public class RootExpTest
    {
        RootExp rootExp;
        Difference dif;

        /// <summary>
        /// Testing forbiden value of root (non natural number)
        /// </summary>
        [TestMethod]
        [ExpectedException(typeof(ArgumentException))]
        public void ForbiddenRootValue()
        {
            rootExp = new RootExp(new Number(25.0), new Number(0.0));
            rootExp.Evaluate();

            rootExp = new RootExp(new Number(1.0), new Number(1.4));
            rootExp.Evaluate();

            rootExp = new RootExp(new Number(-2.0), new Number(-152.0));
            rootExp.Evaluate();

            rootExp = new RootExp(new Number(325.0), new Number(-2.245));
            rootExp.Evaluate();

            rootExp = new RootExp(new Number(22455.0), new Number(125.255));
            rootExp.Evaluate();

        }

        /// <summary>
        /// Testing forbiden values (aka even root of negative number)
        /// </summary>
        [TestMethod]
        [ExpectedException(typeof(ArgumentException))]
        public void ComplexResult()
        {
            rootExp = new RootExp(new Number(-2.5), new Number(2.0));
            rootExp.Evaluate();

            rootExp = new RootExp(new Number(-5222), new Number(18.0));
            rootExp.Evaluate();

            rootExp = new RootExp(new Number(-13), new Number(100.0));
            rootExp.Evaluate();

            rootExp = new RootExp(new Number(-0.12), new Number(4.0));
            rootExp.Evaluate();

            rootExp = new RootExp(new Number(-992.2), new Number(36.0));
            rootExp.Evaluate();
        }

        [TestMethod]
        public void NormalInput()
        {
            rootExp = new RootExp(new Number(25.0), new Number(2.0));
            dif = new Difference(5.0, rootExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());
            
            rootExp = new RootExp(new Number(-125.0), new Number(3.0));
            dif = new Difference(-5.0, rootExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());
            
            rootExp = new RootExp(new Number(4235.2155), new Number(7.0));
            dif = new Difference(3.29704650811265609406, rootExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());
            
            rootExp = new RootExp(new Number(0.0), new Number(241.0));
            dif = new Difference(0.0, rootExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());
            
            rootExp = new RootExp(new Number(-6541.765432465), new Number(13));
            dif = new Difference(-1.96568986065280504252, rootExp.Evaluate());
            Assert.IsTrue(dif.IsAlmostSame());

        }


    }
}
