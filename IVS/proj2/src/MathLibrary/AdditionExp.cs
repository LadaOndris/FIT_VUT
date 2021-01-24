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

/// <summary>
/// Containing basic+ math algorithms
/// </summary>
namespace MathLibrary
{
    /// <summary>
    /// Class implementing function, which compute sum of the 2 numbers
    /// </summary>
    public class AdditionExp : IExpression
    {
        private IExpression addend1;
        private IExpression addend2;

        /// <summary>
        /// Initializing the addend1 and addend2
        /// </summary>
        /// <param name="addend1"></param>
        /// <param name="addend2"></param>
        public AdditionExp(IExpression addend1, IExpression addend2)
        {
            this.addend1 = addend1;
            this.addend2 = addend2;
        }

        /// <summary>
        /// Sum two number inicialized by constructor
        /// </summary>
        /// <returns>Sum of addend1 and addend2</returns>
        public double Evaluate()
        {
            return (addend1.Evaluate() + addend2.Evaluate());
        }
    }
}
