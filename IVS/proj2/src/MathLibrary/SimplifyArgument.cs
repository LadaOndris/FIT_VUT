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
using MathLibrary;

namespace MathLibrary
{
    /// <summary>
    /// Taylor series best aproxymate in interval <-pi;pi> with less iterration
    /// Due to the periodic behavior of trigonometric function, you can convert high argument to lower one by subtracting the n*2PI
    /// where 'n' is natural number or zero
    /// </summary>
    public class SimplifyArgument
    {
        private double argument;
        private uint period;

        public SimplifyArgument(double argument)
        {
            this.argument = argument;
        }

        /// <summary>
        /// Method testing if argument is <-pi;pi> ~ <-3.14;3.14>
        /// </summary>
        /// <returns>true if argument is <-pi;pi> ~ <-3.14;3.14>. Else false</returns>
        private bool InRange()
        {
            Difference dif1 = new Difference(argument, -Constants.Pi);                        //  is almost -pi
            Difference dif2 = new Difference(argument, Constants.Pi);                         //  is almost pi
            bool inRange = ((argument >= -Constants.Pi && argument <= Constants.Pi) ? true : false);    //  in range <-pi;pi>
            return (((dif1.IsAlmostSame() || dif2.IsAlmostSame() || inRange) ? true : false));
        }

        /// <summary>
        /// Method testing if argument is <-2pi;2pi> ~ <-6.28;6.28>
        /// </summary>
        /// <returns>true if argument is <-2pi;2pi> ~ <-6.28;6.28>. Else false</returns>
        private bool InExtendedRange()
        {
            Difference dif1 = new Difference(argument, -Constants.TwoPi);                         //  is almost -2pi
            Difference dif2 = new Difference(argument, Constants.TwoPi);                          //  is almost 2pi
            bool inRange = ((argument >= -Constants.TwoPi && argument <= Constants.TwoPi) ? true : false);  //  in range <-2pi;2pi>
            return (((dif1.IsAlmostSame() || dif2.IsAlmostSame() || inRange) ? true : false));
        }

        /// <summary>
        /// Adding period*2pi and argumnt
        /// </summary>
        private void ExpandArgument()
        {
            argument += period*Constants.TwoPi;
        }

        /// <summary>
        /// Subtracing period*2pi from argumnt
        /// </summary>
        private void SchrinkArgument()
        {
            argument -= period*Constants.TwoPi;
        }

        /// <summary>
        /// Setting argument in range
        /// </summary>
        /// <returns>Argument if no need of setting or argumentSimplified if any change's been made</returns>
        public double SimplifyOfTwoPi()
        {
            period = (uint)(((argument >= 0) ? argument : -argument) / Constants.TwoPi);

            if (InRange())
            {
                return argument;
            }

            if (argument < 0)
            {
                ExpandArgument();
            }
            else if(argument > 0)
            {
                SchrinkArgument();
            }

            if (InExtendedRange() && !InRange() && argument < 0)
            {
                argument += Constants.TwoPi;
            }
            else if (InExtendedRange() && !InRange() && argument > 0)
            {
                argument -= Constants.TwoPi;
            }
            return argument;
        }

    }
}
