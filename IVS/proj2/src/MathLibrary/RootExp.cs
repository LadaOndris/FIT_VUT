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
    /// Class implementing function, which compute Nth root of the given number
    /// </summary>
    public class RootExp : IExpression
    {
        private NLogarithmExp logExp;
        private Difference dif;
        private PowerExp powExp;
        private IExpression mantis;
        private IExpression root;
        private int naturalRoot;
        private const int iteration = 1000000;
        private double parametr = 0;

        /// <summary>
        /// Contructor inicializing arguments
        /// </summary>
        /// <param name="mantis"></param>
        /// <param name="root"></param>
        public RootExp(IExpression mantis, IExpression root)
        {
            this.mantis = mantis;
            this.root = root;
        }

        /// <summary>
        /// Method chceking if root is natural number
        /// </summary>
        /// <returns></returns>
        private bool Natural()
        {
            if (root.Evaluate() < 0.0)
            {
                return false;
            }
            if (root.Evaluate() - (int)root.Evaluate() != 0)
            {
                return false;
            }
            return true;
        }


        /// <summary>
        /// Method checking if root is even number
        /// </summary>
        /// <returns>true if natural root is even number</returns>
        private bool EvenRoot()
        {
            if (root.Evaluate() / 2.0 - naturalRoot/2  == 0)
            {
                return true;
            }
            return false;
        }

        /// <summary>
        /// Changing the value of argument for better aproximation using basic exponential formulas
        /// Set the exponent value in interval <-1;1>
        /// </summary>
        private double ParseArgument(double y)
        {
            while(y > 1)
            {
                y -= 2;
                parametr++;

            }
            while(y < -1)
            {
                y += 2;
                parametr--;
            }
            return y;
        }
        /// <summary>
        /// Comptuting nth root of number using formula: n root of x ~ x ^ (1/n) ~ e^((1/n)*ln(x))
        /// </summary>
        private double Root()
        {
            double result = 0;
            bool negativeMantis = (mantis.Evaluate() < 0 ? true : false); //keeping the sign for the negative input and odd root
            double absMantis = (mantis.Evaluate() >= 0 ? mantis.Evaluate() : -mantis.Evaluate());
            //---Computing ln(x)
            logExp = new NLogarithmExp(new Number(absMantis));
            //---Computing e^(alfa), where alfa = (1/n)*ln(x)
            double alfa = (1.0 / naturalRoot) * logExp.Evaluate();
            alfa = ParseArgument(alfa);
            for(int i = iteration; i > 0; i--)
            {
                result = (i * alfa) / ((i + 1.0 + alfa - result));
            }
            result = 1.0 / (1.0 - alfa / (1.0 + alfa - result));

            powExp = new PowerExp(new Number(Constants.E), new Number(parametr >= 0 ? 2*parametr : -2*parametr));
            result = result * (parametr >= 0 ? powExp.Evaluate() : (1 / powExp.Evaluate()));

            result = (negativeMantis && !EvenRoot()) ? -result: result; //changing the sign to original 
            return result;
        }

        /// <summary>
        /// Calculating root of mantis
        /// </summary>
        /// <returns>root of mantis or throw error if root is not natural number or even root of negative value</returns>
        public double Evaluate()
        {
            if(!Natural()) //if root is not natural number
            {
                throw new ArgumentException("Can only calculate natural root of number!");
            }
            naturalRoot = (int)root.Evaluate();

            dif = new Difference(naturalRoot, 0.0);
            if (dif.IsAlmostSame()) //if root is zero
            {
                throw new ArgumentException("Root cannot be zero!");
            }
            if (EvenRoot() && mantis.Evaluate() < 0)
            {
                throw new ArgumentException("Cant compute even root of negative value!");
            }
            dif = new Difference(mantis.Evaluate(), 0.0);
            if (dif.IsAlmostSame()) //nth root of zero is zero
            {
                return 0.0;
            }
            dif = new Difference(naturalRoot, 1.0);
            if(dif.IsAlmostSame()) //first root of any number is same number
            {
                return mantis.Evaluate();
            }
            return Root();
        }
    }
}
