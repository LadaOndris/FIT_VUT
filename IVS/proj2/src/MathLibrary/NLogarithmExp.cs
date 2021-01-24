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
    /// Class implementing logharitm computing algorithm
    /// </summary>
public class NLogarithmExp :IExpression
    {
        private IExpression argument;
        private Difference dif;
        private const int iteration = 1000000;
        private int parametr = 0;
        private const double ln10 = 2.30258509299404568401;


        /// <summary>
        /// Initializing the argument of logarithm
        /// </summary>
        /// <param name="argument"></param>
        public NLogarithmExp(IExpression argument)
        {
            this.argument = argument;
        }

        /// <summary>
        /// Class implementing function, which compute natural logarithm of the given number
        /// Set the argument value in interval <1;10>
        /// </summary>
        private void ParseArgument()
        {
            double mantis = argument.Evaluate();
            while(mantis > 10)
            {
                mantis /= 10;
                parametr++;
            }

            while(mantis < 1)
            {
                mantis *= 10;
                parametr--;
            }
            argument = new Number(mantis);
        }



        /// <summary>
        /// Main alorithm for logarithm computing using continued fraction
        /// </summary>
        /// <returns>Natural logarithm of argument</returns>
        private double Logarithm()
        {
            double result = 0;
            //ln(x) -> ln((1+z)/(1-z)) ->  (1+z)/(1-z) = x = x -> z = (x-1)/(x+1)
            double z = (argument.Evaluate() - 1) / (argument.Evaluate() + 1);
            double z2 = z * z;
            for(int i = iteration; i > 0; i--)
            {
                result = (i * i * z2) / ((2 * i + 1) - result);
            }
            result = (2 * z) / (1 - result);
            result += parametr * ln10;
            return result;
        }

        /// <summary>
        /// Evaulate natural logarithm of argument 
        /// </summary>
        /// <returns>Natural logarithm of argument or throw error in case of wrong argument</returns>
        public double Evaluate()
        {
            if (argument.Evaluate() <= 0)
            {
                throw new ArgumentException("Argument of logharitm has to be greater than zero!");
            }

            //ln(1.0) = 0.0
            dif = new Difference(1.0, argument.Evaluate());
            if (dif.IsAlmostSame())
            {
                return 0.0;
            }

            //ln(e) = 1.0
            dif = new Difference(Constants.E, argument.Evaluate());
            if (dif.IsAlmostSame())
            {
                return 1.0;
            }

            ParseArgument();
            return Logarithm();
        }
    }
}
