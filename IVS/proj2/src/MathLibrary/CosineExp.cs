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
    /// Class implementing function, which compute cosine of the given argument
    /// </summary>
    public class CosineExp : IExpression
    {
        private IExpression argument;


        /// <summary>
        ///  Inicializing the argument
        /// </summary>
        /// <param name="argument"></param>
        public CosineExp(IExpression argument)
        {
            this.argument = argument;
        }

        /// <summary>
        /// Calculate cosine of inputed value in radians using sin function
        /// cos(x) = sin(x+pi/2)
        /// </summary>
        /// <returns>Cosine of value</returns>
        public double Evaluate()
        {
            SineExp sin = new SineExp(new Number(argument.Evaluate() + Constants.PiDivTwo));
            return sin.Evaluate();
        }
    }
}
