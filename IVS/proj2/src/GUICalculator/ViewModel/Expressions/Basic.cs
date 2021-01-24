using GUICalculator.View;
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
    /// Basic (Base expression) is an expression which contains all other expressions.
    /// Its specific behavior is when moving the caret inside the Basic expression.
    /// When it encounters a border (last element) on the right side (or the left),
    /// the Caret doesn't jump out of the Basic expression and stays within 
    /// (which makes the Basic expression a parent for all other).
    /// </summary>
    class Basic : SingleExpression
    {

        public Basic()
            : base("BasicExpressionTemplate")
        {
            AddAuxiliary();
        }
        
        public override Expression MoveLeft(Expression child, bool jumpIn)
        {
            // Makes sure the caret remains inside the Base expression 
            // on the left side of the first child.
            if (Caret.Instance.ExpressionSide == ExpressionSide.Left)
            {
                if (child != null && PreviousChild(child) == null)
                    return FirstChild();
            }
            return base.MoveLeft(child, jumpIn);
        }

        public override Expression MoveRight(Expression child, bool jumpIn)
        {
            // Makes sure the caret remains inside the Base expression 
            // on the right side of the right child.
            if (Caret.Instance.ExpressionSide == ExpressionSide.Right)
            {
                if (child != null && NextChild(child) == null)
                    return LastChild();
            }
            return base.MoveRight(child, jumpIn);
        }

        public override string ConvertToString()
        {
            StringBuilder sb = new StringBuilder("(");
            foreach (Expression expression in Items)
                sb.Append(expression.ConvertToString());
            sb.Append(")");
            return sb.ToString();
        }
    }
}
