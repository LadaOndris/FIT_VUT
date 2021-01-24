using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using GUICalculator.ViewModel.Expressions.Base;

namespace GUICalculator.ViewModel.Expressions
{
    /// <summary>
    /// LeftParenthesis expression is a TerminalExpression which displays
    /// only the '(' character. One can think of the LeftParenthesis as Character
    /// with specific template.
    /// </summary>
    class LeftParenthesis : TerminalExpression
    {
        public LeftParenthesis() 
            : base("LeftParenthesisExpressionTemplate")
        {
            MinHeight = 18;
            VerticalAlignment = System.Windows.VerticalAlignment.Stretch;
        }
        
        protected override void OnParentExpressionSet(Expression parent)
        {
            //Expression nextChild = parent.NextChild(this);
            //if (nextChild == null)
            //    return;

            //Height = nextChild.ActualHeight;
        }

        public override string ConvertToString()
        {
            return "(";
        }
    }
}
