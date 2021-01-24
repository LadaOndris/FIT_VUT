using GUICalculator.ViewModel.Expressions.Base;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GUICalculator.ViewModel.Expressions
{
    /// <summary>
    /// RightParenthesis expression is a TerminalExpression which displays
    /// only the ')' character. One can think of the RightParenthesis as Character
    /// with specific template.
    /// </summary>
    class RightParenthesis : TerminalExpression
    {
        public RightParenthesis()
            : base("RightParenthesisExpressionTemplate")
        {
            MinHeight = 18;
            VerticalAlignment = System.Windows.VerticalAlignment.Stretch;
        }

        protected override void OnParentExpressionSet(Expression parent)
        {
            //Expression previousChild = parent.PreviousChild(this);
            //if (previousChild == null)
            //    return;

            //Height = previousChild.ActualHeight;
        }

        public override string ConvertToString()
        {
            return ")";
        }
    }
}
