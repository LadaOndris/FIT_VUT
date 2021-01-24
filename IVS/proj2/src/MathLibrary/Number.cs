using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MathLibrary
{
    /// <summary>
    /// Class converting abstracted interface to comptutable numbers
    /// </summary>
    public class Number : IExpression
    {
        private readonly double value;

        public Number(double value)
        {
            this.value = value;
        }

        public double Evaluate()
        {
            return value;
        }
    }
}
