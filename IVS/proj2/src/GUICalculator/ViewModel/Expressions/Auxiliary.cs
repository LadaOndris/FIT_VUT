using GUICalculator.View;
using GUICalculator.ViewModel.Expressions.Base;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;

namespace GUICalculator.ViewModel.Expressions
{

    /// <summary>
    /// Auxiliary expression is an expression that doesn't hold any value and 
    /// its only purpose is to temporarily fill components that doesn't contain
    /// any value yet. For example root doesn't contain any value when inserted, so 
    /// auxiliary expression is inserted instead until a real value is inserted.
    /// </summary>
    internal class Auxiliary : TerminalExpression
    {
        public Auxiliary()
            : base("AuxiliaryExpressionTemplate")
        {
            Background = Brushes.LightGray;
        }

        protected override void OnParentExpressionSet(Expression parent)
        {
            base.OnParentExpressionSet(parent);
        }

        private System.Windows.Size GetSize(Expression parent)
        {
            var typeface = new Typeface(parent.FontFamily, parent.FontStyle, parent.FontWeight, parent.FontStretch);
            var formattedText = new FormattedText("0", Thread.CurrentThread.CurrentCulture, parent.FlowDirection, typeface, parent.FontSize, parent.Foreground);

            return new System.Windows.Size(formattedText.Width, formattedText.Height);
        }

        protected override void OnMouseClick(object sender, MouseButtonEventArgs e)
        {
            Caret.Instance.SetActiveExpression(this, ExpressionSide.Left);
            e.Handled = true;
        }

        public override Expression MoveLeft(Expression child, bool jumpIn)
        {
            // Without this modification of caret's expression side it would be needed
            // to press the left arrow key twice to move left because the auxiliary is invisible.
            if (Caret.Instance.ExpressionSide == ExpressionSide.Right)
            {
                Caret.Instance.ExpressionSide = ExpressionSide.Left;
            }
            return ParentExpression.MoveLeft(this, false);
        }

        public override Expression MoveRight(Expression child, bool jumpIn)
        {
            // Without this modification of caret's expression side it would be needed
            // to press the left arrow key twice to move right because the auxiliary is invisible.
            if (Caret.Instance.ExpressionSide == ExpressionSide.Left)
            {
                Caret.Instance.ExpressionSide = ExpressionSide.Right;
            }
            return ParentExpression.MoveRight(this, false);
        }
        
        public override string ConvertToString()
        {
            return String.Empty;
        }
    }
}
