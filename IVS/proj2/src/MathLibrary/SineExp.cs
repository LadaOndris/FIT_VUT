/************************************************************
 *      ROZSIVAL MICHAL                                     *
 *      IVS - project 2                                     *
 *      FEB/MAR 2019                                        *
 *      Class of the MathLibary                             *
 *      Version 1.0                                         *
 ************************************************************/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MathLibrary
{
    /// <summary>
    /// Class implementing function, which compute sine of the given argument
    /// </summary>
    public class SineExp : IExpression
    {
        private SimplifyArgument sim;
        private IExpression argument;
        private double simplifiedArgument;
        private const int iteration = 1000000; //number of iteration to compute sin value.
        private double result = 0;
        private Difference dif1;
        private Difference dif2;


        /// <summary>
        /// Constructor inicializing argument
        /// </summary>
        /// <param name="argument"></param>
        public SineExp(IExpression argument)
        {
            this.argument = argument;
        }

        /// <summary>
        /// Computing the value of sin(argument) using continued fraction
        /// </summary>
        private void Sin()
        {
            if (BaseValue())
            {
                return;
            }
            double argumentToTwo = simplifiedArgument * simplifiedArgument;

            for (int i = iteration - 1; i > 1; i--)
            {
                result = ((2 * i - 2) * (2 * i - 1) * argumentToTwo) / ((2 * i) * (2 * i + 1) - argumentToTwo + result);
            }
            result = 1 + (argumentToTwo) / (2 * 3 - argumentToTwo + result);
            result = simplifiedArgument / result;
            return;
        }

        /// <summary>
        /// Method calculating sin value of simplified argument
        /// </summary>
        /// <returns>Sin value of argument</returns>
        public double Evaluate()
        {
            sim = new SimplifyArgument(argument.Evaluate());
            simplifiedArgument = sim.SimplifyOfTwoPi();
            Sin();
            return result;
        }

        /// <summary>
        /// Method testing if argument is one of the base values
        /// </summary>
        public bool BaseValue()
        {
            dif1 = new Difference(simplifiedArgument, -Constants.Pi);
            dif2 = new Difference(simplifiedArgument, Constants.Pi);
            if (dif1.IsAlmostSame() || dif2.IsAlmostSame()) { result = 0; return true; }

            dif1 = new Difference(simplifiedArgument, -Constants.FivePiDivSix);
            dif2 = new Difference(simplifiedArgument, -Constants.PiDivSix);
            if (dif1.IsAlmostSame() || dif2.IsAlmostSame()) { result = -Constants.OneDivTwo; return true; }

            dif1 = new Difference(simplifiedArgument, -Constants.ThreePiDivFour);
            dif2 = new Difference(simplifiedArgument, -Constants.PiDivFour);
            if (dif1.IsAlmostSame() || dif2.IsAlmostSame()) { result = -Constants.SqrtTwoDivTwo; return true; }

            dif1 = new Difference(simplifiedArgument, -Constants.FourPiDivSix);
            dif2 = new Difference(simplifiedArgument, -Constants.TwoPiDivSix);
            if (dif1.IsAlmostSame() || dif2.IsAlmostSame()) { result = -Constants.SqrtThreeDivTwo; return true; }

            dif1 = new Difference(simplifiedArgument, Constants.PiDivSix);
            dif2 = new Difference(simplifiedArgument, Constants.FivePiDivSix);
            if (dif1.IsAlmostSame() || dif2.IsAlmostSame()) { result = Constants.OneDivTwo; return true; }

            dif2 = new Difference(simplifiedArgument, Constants.PiDivFour);
            dif1 = new Difference(simplifiedArgument, Constants.ThreePiDivFour);
            if (dif1.IsAlmostSame() || dif2.IsAlmostSame()) { result = Constants.SqrtTwoDivTwo; return true; }

            dif1 = new Difference(simplifiedArgument, Constants.TwoPiDivSix);
            dif2 = new Difference(simplifiedArgument, Constants.FourPiDivSix);
            if (dif1.IsAlmostSame() || dif2.IsAlmostSame()) { result = Constants.SqrtThreeDivTwo; return true; }

            dif1 = new Difference(simplifiedArgument, -Constants.PiDivTwo);
            if (dif1.IsAlmostSame()) { result = -Constants.One; return true; }

            dif1 = new Difference(simplifiedArgument, 0);
            if (dif1.IsAlmostSame()) { result = 0; return true; }

            dif1 = new Difference(simplifiedArgument, Constants.PiDivTwo);
            if (dif1.IsAlmostSame()) { result = Constants.One; return true; }

            return false;
        }
    }
}
