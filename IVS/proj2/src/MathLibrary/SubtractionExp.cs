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
    /// Class implementing function, which compute diference of the 2 numbers
    /// </summary>
    public class SubtractionExp : IExpression
    {
        private IExpression minuend;
        private IExpression subtrahend;

        /// <summary>
        /// Inicializing the minuend and subtrahend
        /// </summary>
        /// <param name="minuend"></param>
        /// <param name="subtrahend"></param>
        public SubtractionExp(IExpression minuend, IExpression subtrahend)
        {
            this.minuend = minuend;
            this.subtrahend = subtrahend;
        }

        /// <summary>
        /// Subtract two number inicialized by Constructor
        /// </summary>
        /// <returns>Difference of Minuend and Subtrahend (in order)</returns>
        public double Evaluate()
        {
            return (minuend.Evaluate() - subtrahend.Evaluate());
        }
    }
}
