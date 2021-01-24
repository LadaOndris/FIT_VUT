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
    /// Class implementing function, which compute division of 2 numbers
    /// </summary>
    public class DivisionExp : IExpression
    {
        private IExpression divident;
        private IExpression divisor;

        /// <summary>
        /// Initializing the divident and divisor
        /// </summary>
        /// <param name="divident"></param>
        /// <param name="divisor"></param>
        public DivisionExp(IExpression divident, IExpression divisor)
        {
            
            this.divident = divident;
            this.divisor = divisor;
        }

        /// <summary>
        /// Divide two numbers initialized by constructor
        /// </summary>
        /// <returns>Quotient of two numbers (in order) or throw exception if zero division is tried</returns>
        public double Evaluate()
        {
            if (divisor.Evaluate() == 0)
            {
                throw new ArgumentException("Can't devide by zero!");
            }
            return (divident.Evaluate() / divisor.Evaluate());
        }
    }
}
