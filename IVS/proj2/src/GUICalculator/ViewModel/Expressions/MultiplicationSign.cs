using GUICalculator.ViewModel.Expressions.Base;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GUICalculator.ViewModel.Expressions
{
    /// <summary>
    /// MultiplicationSign expression is a TerminalExpression
    /// pretty much similar to Character, except it has its own template.
    /// </summary>
    /// <remarks>
    /// It might be deleted in the future as no special template for the
    /// multiplication sign is needed.
    /// </remarks>
    class MultiplicationSign : TerminalExpression
    {
        public MultiplicationSign()
            : base("MultiplicationSignExpressionTemplate")
        {
        }

        public override string ConvertToString()
        {
            return "*";
        }
    }
}
