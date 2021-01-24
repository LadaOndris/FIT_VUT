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
    /// Class implementing function, which compute factorial of the given number
    /// </summary>
    public class FactorialExp : IExpression
    {
        private IExpression argument;
        private double result = 1;
        private int naturalArgument;

        
        /// <summary>
        /// Constructor inicializing arguments
        /// </summary>
        /// <param name="argument"></param>
        public FactorialExp(IExpression argument)
        {
            this.argument = argument;
        }

        /// <summary>
        /// Mathod checking if argument is natural number or zero
        /// </summary>
        /// <returns></returns>
        private bool NaturalOrZero()
        {
            if(argument.Evaluate() < 0.0)
            {
                return false;
            }
            if(argument.Evaluate() - (int)argument.Evaluate() != 0)
            {
                return false;
            }
            return true;
        }

        /// <summary>
        /// Computing factorial of argument
        /// </summary>
        private void Factorial()
        {
            for (int i = 1; i <= naturalArgument; i++)
                result *= i;
        }

        /// <summary>
        /// Calculate factorial of argument
        /// </summary>
        /// <returns>Factorial of the inputed argument or throw exception if non-natural number* (*including zero)</returns>
        public double Evaluate()
        {
            if(!NaturalOrZero())
            {
                throw new ArgumentException("Argument of factorial has to be natural number or zero!");
            }
            naturalArgument = (int)argument.Evaluate();
            if(naturalArgument == 0)
            {
                result = 1;
            }
            else
            {
                Factorial();
            }
            return result;
        }



    }
}
