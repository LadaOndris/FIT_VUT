using GUICalculator.ViewModel;
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
    /// SquareRoot expression is similar to the Root expression, except
    /// the degree is always 2. So only one list of expressions is used
    /// as the number to calculate the square root from.
    /// </summary>
    internal class SquareRoot : SingleExpression
    {
        public SquareRoot()
            : base("SquareRootExpressionTemplate")
        {
        }
        
        public override string ConvertToString()
        {
            StringBuilder sb = new StringBuilder("(sqrt(");
            foreach (Expression expression in Items)
                sb.Append(expression.ConvertToString());
            sb.Append("))");
            return sb.ToString();
        }
    }
}
