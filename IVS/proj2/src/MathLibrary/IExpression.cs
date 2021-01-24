
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MathLibrary
{
    /// <summary>
    /// Abstraction for Math's classes providing identical Evaluate() method
    /// </summary>
    public interface IExpression
    {
        double Evaluate();
    }
}
