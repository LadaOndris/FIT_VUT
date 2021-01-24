using GUICalculator.View;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;

/// <summary>
/// Provides base classes for expressions and their default behaviour.
/// </summary>
namespace GUICalculator.ViewModel.Expressions.Base
{
    public abstract class Expression : ContentControl
    {
        private static Caret caret = Caret.Instance;
        private Expression _parentExpression;

        public Expression(string templateName)
        {
            this.Template = Application.Current.FindResource(templateName) as ControlTemplate;
            this.DataContext = this;

            VerticalAlignment = VerticalAlignment.Bottom;
            MouseLeftButtonUp += OnMouseClick;
        }

        public Expression ParentExpression
        {
            get => _parentExpression;
            set
            {
                _parentExpression = value;
                OnParentExpressionSet(_parentExpression);
            }
        }

        /// <summary>
        ///     Adds Auxiliary expression if the items count is 0.
        /// </summary>
        /// <returns>Returns the instance of Auxiliary expression class. 
        /// Returns null if no expression was added.</returns>
        public abstract Expression AddAuxiliary();
        public abstract void AddExpression(Expression activeExpression, Expression expressionToBeAdded);
        public abstract Expression PreviousChild(Expression currentChild);
        public abstract Expression NextChild(Expression currentChild);
        public abstract Expression LastChild();
        public abstract Expression FirstChild();
        public abstract bool DeleteChild(Expression child);
        public abstract void UpdateChildrensBottomMargin();
        public abstract string ConvertToString();


        protected virtual void OnParentExpressionSet(Expression parent)
        {

        }
        
        protected virtual void OnMouseClick(object sender, MouseButtonEventArgs e)
        {
            //Console.WriteLine("Type of sender: {0}", sender.GetType());
            ContentControl control = sender as ContentControl;

            Point relativePoint = e.GetPosition(Application.Current.MainWindow);
            //Console.WriteLine("{0}", relativePoint);

            Point locationFromWindow = control.LeftPositionOf();
            double distFromLeft = relativePoint.X - locationFromWindow.X;
            double distFromRight = locationFromWindow.X + control.ActualWidth - relativePoint.X;
            //Console.WriteLine("From left: {0}, from right: {1}", distFromLeft, distFromRight);

            if (distFromLeft <= distFromRight)
            {
                //Console.WriteLine("Caret X location: {0}, height: {1}", locationFromWindow.X, control.ActualHeight);
                locationFromWindow = control.LeftPositionOf();
                caret.ExpressionSide = ExpressionSide.Left;
            }
            else
            {
                //Console.WriteLine("Caret X location: {0}, height: {1}", locationFromWindow.X + control.ActualWidth, control.ActualHeight);
                locationFromWindow = control.RightPositionOf();
                caret.ExpressionSide = ExpressionSide.Right;
            }

            caret.SetActiveExpression(this);
            caret.RestartBlinking();
            e.Handled = true;
        }
        
        public virtual Expression MoveLeft(Expression child, bool jumpIn)
        {
            if (Caret.Instance.ExpressionSide == ExpressionSide.Left)
            {
                Expression previousChild = null;
                if (child != null && (previousChild = PreviousChild(child)) != null)
                {
                    Expression lastChild = previousChild.LastChild();
                    if (lastChild != null)
                    {
                        Caret.Instance.ExpressionSide = ExpressionSide.Right;
                        return lastChild;
                    }
                    return previousChild; // leave Left
                }
                else if (child != null && previousChild == null)
                {
                    return this;
                }
                else
                {
                    Expression tmp;
                    if (ParentExpression != null && (tmp = ParentExpression.MoveLeft(this, false)) != null)
                        return tmp;
                }
            }
            else // ExpressionSide.Right
            {
                Expression previousChild = null;
                // jump in from right
                if (jumpIn && LastChild() != null)
                {
                    return LastChild();
                }
                else if (child != null && (previousChild = PreviousChild(child)) != null)
                {
                    return previousChild;
                }
                else if (child != null && previousChild == null)
                {
                    Caret.Instance.ExpressionSide = ExpressionSide.Left;
                    return child;
                }
                else
                {
                    Expression tmp;
                    if (ParentExpression != null && (tmp = ParentExpression.MoveLeft(this, false)) != null)
                        return tmp;
                }
            }
            return FirstChild();
        }

        public virtual Expression MoveRight(Expression child, bool jumpIn)
        {
            if (Caret.Instance.ExpressionSide == ExpressionSide.Right)
            {
                Expression nextChild = null;
                if (child != null && (nextChild = NextChild(child)) != null)
                {
                    Expression firstChild = nextChild.FirstChild();
                    if (firstChild != null)
                    {
                        Caret.Instance.ExpressionSide = ExpressionSide.Left;
                        return firstChild;
                    }
                    return nextChild;
                }
                else if (child != null && nextChild == null)
                {
                    return this;
                }
                else
                {
                    Expression tmp;
                    if (ParentExpression != null && (tmp = ParentExpression.MoveRight(this, false)) != null)
                        return tmp;
                }
            }
            else // ExpressionSide.Left
            {
                Expression nextChild = null;
                // jump in from left
                if (jumpIn && FirstChild() != null)
                {
                    return FirstChild(); 
                }
                else if (child != null && (nextChild = NextChild(child)) != null)
                {
                    return nextChild ; 
                }
                else if (child != null && nextChild == null)
                {
                    Caret.Instance.ExpressionSide = ExpressionSide.Right;
                    return child;
                }
                else {
                    Expression tmp;
                    if (ParentExpression != null && (tmp = ParentExpression.MoveRight(this, false)) != null)
                        return tmp;
                }
            }
            return LastChild();
        }


        protected void UpdateChildrensBottomMargin(Collection<Expression> collection)
        {
            // Make sure that the layout is updated. 
            // Otherwise the size of newly added components would be 0.
            this.UpdateLayout();

            int highestBottomMargin = GetHighestBottomMargin(collection);
            if (highestBottomMargin != 0)
            {
                foreach (Expression exp in collection)
                {
                    //double expHeight = exp.ActualHeight;
                    Thickness margin = exp.Margin;
                    if (exp is Fraction)
                    {
                        double fractionHeight = ((Fraction)exp).SecondExpression.Max(e => e.ActualHeight);
                        margin.Bottom = highestBottomMargin - fractionHeight;
                    }
                    else
                    {
                        // Caution! if the font size changes, the number 13 won't be right.
                        int halfFontSize = 13;
                        margin.Bottom = highestBottomMargin - halfFontSize; // - expHeight / 2
                    }
                    exp.Margin = margin;
                }
            }

            if (ParentExpression != null)
            {
                ParentExpression.UpdateChildrensBottomMargin();
            }
        }

        private int GetHighestBottomMargin(Collection<Expression> collection)
        {
            int highestBottomMargin = 0;
            // only denominator of fraction counts
            foreach (Expression expression in collection)
            {
                Fraction fraction = expression as Fraction;
                if (fraction != null)
                {
                    int height = (int) fraction.SecondExpression.Max(exp => exp.ActualHeight);
                    if (height > highestBottomMargin)
                    {
                        highestBottomMargin = height;
                    }
                }
            }
            return highestBottomMargin;
        }

    }
}
