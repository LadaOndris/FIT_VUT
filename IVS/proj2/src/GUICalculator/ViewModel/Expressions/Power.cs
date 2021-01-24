using GUICalculator.ViewModel.Expressions.Base;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;


namespace GUICalculator.ViewModel.Expressions
{
    /// <summary>
    /// Power expression is a SingleExpression which means it consists of
    /// a single list of expressions.
    /// As of all expressions, the look is represented by the specific template.
    /// </summary>
    internal class Power : SingleExpression
    {
        public Power()
            : base("PowerExpressionTemplate")
        {
        }
        
        public override string ConvertToString()
        {
            StringBuilder sb = new StringBuilder();
            sb.Append("^(");
            foreach (Expression expression in Items)
                sb.Append(expression.ConvertToString());
            sb.Append(")");
            return sb.ToString();
        }
    }
}
