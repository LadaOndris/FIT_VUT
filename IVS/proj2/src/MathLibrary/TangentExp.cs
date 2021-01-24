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
    /// Class implementing function, which compute tg of the fiven argument
    /// </summary>
    public class TangentExp : IExpression
    {

        private double result = 0;
        private IExpression argument;
        private double simplifiedArgument;
        private Difference dif1;
        private Difference dif2;
        private SimplifyArgument sim;
        private readonly int iteration = 1000000;

        /// <summary>
        /// Constructor inicializin argument
        /// </summary>
        /// <param name="argument"></param>
        public TangentExp(IExpression argument)
        {
            this.argument = argument;
        }


        /// <summary>
        /// Computing the tan of the simplified argument using continued fraction
        /// </summary>
        private void Tan()
        {
            double argumentToTwo = simplifiedArgument * simplifiedArgument;
            for (int i = iteration; i > 0; i--)
            {
                result = (argumentToTwo / ((i * 2 + 1) - result));
            }
            result = simplifiedArgument / (1 - result);
            return;
        }

        /// <summary>
        /// Calculate tan of simplified argument using the continued fraction
        /// </summary>
        /// <returns>tan value of argument or throw exception if case of wrong argument</returns>
        public double Evaluate()
        {
            sim = new SimplifyArgument(argument.Evaluate());
            simplifiedArgument = sim.SimplifyOfTwoPi();
            if (!BaseValue())
            {
                Tan();
            }
            return result;
        }

        /// <summary>
        /// Method testing if argument is one of the base values
        /// </summary>
        /// <returns></returns>
        private bool BaseValue()
        {
            dif1 = new Difference(simplifiedArgument, -Constants.Pi);
            dif2 = new Difference(simplifiedArgument, Constants.Pi);
            if (dif1.IsAlmostSame() || dif2.IsAlmostSame())
            {
                result = 0;
                return true;
            }

            dif1 = new Difference(simplifiedArgument, -Constants.FivePiDivSix);
            dif2 = new Difference(simplifiedArgument, Constants.PiDivSix);
            if (dif1.IsAlmostSame() || dif2.IsAlmostSame())
            {
                result = Constants.SqrtThreeDivThree;
                return true;
            }

            dif1 = new Difference(simplifiedArgument, -Constants.ThreePiDivFour);
            dif2 = new Difference(simplifiedArgument, Constants.PiDivFour);
            if (dif1.IsAlmostSame() || dif2.IsAlmostSame())
            {
                result = 1;
                return true;
            }

            dif1 = new Difference(simplifiedArgument, -Constants.FourPiDivSix);
            dif2 = new Difference(simplifiedArgument, Constants.TwoPiDivSix);
            if (dif1.IsAlmostSame() || dif2.IsAlmostSame())
            {
                result = Constants.SqrtThree; return true;
            }

            dif1 = new Difference(simplifiedArgument, -Constants.TwoPiDivSix);
            dif2 = new Difference(simplifiedArgument, Constants.FourPiDivSix);
            if (dif1.IsAlmostSame() || dif2.IsAlmostSame())
            {
                result = -Constants.SqrtThree; return true;
            }

            dif2 = new Difference(simplifiedArgument, -Constants.PiDivFour);
            dif1 = new Difference(simplifiedArgument, Constants.ThreePiDivFour);
            if (dif1.IsAlmostSame() || dif2.IsAlmostSame())
            {
                result = -1; return true;
            }

            dif1 = new Difference(simplifiedArgument, -Constants.PiDivSix);
            dif2 = new Difference(simplifiedArgument, Constants.FivePiDivSix);
            if (dif1.IsAlmostSame() || dif2.IsAlmostSame())
            {
                result = -Constants.SqrtThreeDivThree; return true;
            }

            dif1 = new Difference(simplifiedArgument, 0);
            if (dif1.IsAlmostSame()) { result = 0; return true; }

            dif1 = new Difference(simplifiedArgument, -Constants.PiDivTwo);
            dif2 = new Difference(simplifiedArgument, Constants.PiDivTwo);
            if (dif1.IsAlmostSame() || dif2.IsAlmostSame())
            {
                result = -Constants.One;
                throw new ArgumentException("Wrong argument of tan(x) function!");
            }

            return false;

        }


    }
}
