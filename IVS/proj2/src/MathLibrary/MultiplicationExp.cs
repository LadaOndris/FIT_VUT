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
    /// Class implementing function, which compute product of the 2 numbers
    /// </summary>
    public class MultiplicationExp : IExpression
    {
        private IExpression multiplicant;
        private IExpression multiplier;


        /// <summary>
        /// Initializing the multiplicant and multiplier
        /// </summary>
        /// <param name="multiplicant"></param>
        /// <param name="multiplier"></param>
        public MultiplicationExp(IExpression multiplicant, IExpression multiplier)
        {
            this.multiplicant = multiplicant;
            this.multiplier = multiplier;
        }

        /// <summary>
        /// Multiplies two numbers initialized by constructor
        /// </summary>
        /// <returns>Product of multiplicant and multiplier</returns>
        public double Evaluate()
        {
            return (multiplicant.Evaluate() * multiplier.Evaluate());
        }
    }
}
