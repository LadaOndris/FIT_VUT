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
    /// Class implementing function, which compute result of the 'a' ^ 'b' 
    /// </summary>
    public class PowerExp : IExpression
    {
        private IExpression mantis;
        private IExpression exponent;
        private int naturalExponent;
        private double result;

        /// <summary>
        /// Constructor inicializing mantis and exponent
        /// </summary>
        /// <param name="mantis"></param>
        /// <param name="exponent"></param>
        public PowerExp(IExpression mantis, IExpression exponent)
        {
            this.mantis = mantis;
            this.exponent = exponent;
        }

        /// <summary>
        /// Method checking if the exponent is natural number
        /// </summary>
        /// <returns>true if power is natural number or zero. Else false</returns>
        private bool NaturalOrZero()
        {
            if(exponent.Evaluate() < 0)
            {
                return false;
            }
            if(exponent.Evaluate() - (int)exponent.Evaluate() != 0)
            {
                return false;
            }
            return true;
        }

        /// <summary>
        /// Computing the mantis to exponent power
        /// </summary>
        private void Power()
        {
            result = mantis.Evaluate();
            for(int i = 1; i < naturalExponent; i++)
            {
                result *= mantis.Evaluate();
            }
        }

        /// <summary>
        /// Calculate the mantis to exponent power
        /// </summary>
        /// <returns>mantis to exponent power or throw exception if exponent is non natural or in case of undefined expression</returns>
        public double Evaluate()
        {

            if (mantis.Evaluate() == 0.0 && exponent.Evaluate() == 0.0) //cant take zero to zero power
            {
                throw new ArgumentException("Zero to Zero power is undeffined expression!!");
            }
            if (!NaturalOrZero()) //if exponent is decimal or negative number
            {
                throw new ArgumentException("Power has to be Natural number or zero by zero!");
            }
            naturalExponent = (int)exponent.Evaluate();
            if(naturalExponent == 0) //number (excluding 0) to zero is one
            {
                result = 1;
            }
            else if(naturalExponent == 1) //number to first power is the same number
            {
                result = mantis.Evaluate();
            }
            else
            {
                Power();
            }
            return result;

        }
    }
}
