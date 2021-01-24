using GUICalculator.View;
using GUICalculator.ViewModel.Expressions;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GUICalculator.ViewModel.Expressions.Base
{
    /// <summary>
    ///     TwoExpression is an expression which contains 
    ///     two collections of expressions.
    ///     Examples of TwoExpression might be root and fraction.
    /// </summary>
    internal abstract class TwoExpression : Expression
    {
        public TwoExpression(string templateName) : base(templateName)
        {
            this.AddAuxiliary(); // add auxiliary to first collection
            this.AddAuxiliary(); // add auxiliary to the second collection
        }

        public ObservableCollection<Expression> FirstExpression { get; set; } = new ObservableCollection<Expression>();
        public ObservableCollection<Expression> SecondExpression { get; set; } = new ObservableCollection<Expression>();

        public override void AddExpression(Expression activeExpression, Expression expressionToBeAdded)
        {
            int activeIndex = SecondExpression.IndexOf(activeExpression);
            if (activeIndex >= 0)
            {
                if (Caret.Instance.ExpressionSide == ExpressionSide.Right)
                    activeIndex++;
                SecondExpression.Insert(activeIndex, expressionToBeAdded);

                // remove auxiliary
                if (activeExpression is Auxiliary)
                    SecondExpression.Remove(activeExpression);

                base.UpdateChildrensBottomMargin(SecondExpression);
                return;
            }

            activeIndex = FirstExpression.IndexOf(activeExpression);
            if (activeIndex >= 0)
            {
                if (Caret.Instance.ExpressionSide == ExpressionSide.Right)
                    activeIndex++;
                FirstExpression.Insert(activeIndex, expressionToBeAdded);

                // remove auxiliary
                if (activeExpression is Auxiliary)
                    FirstExpression.Remove(activeExpression);

                base.UpdateChildrensBottomMargin(FirstExpression);
                return;
            }
            throw new KeyNotFoundException("Active expression wasn't found therefore a new expression couldn't be added.");
        }

        public override Expression NextChild(Expression currentChild)
        {
            for (int i = 0; i < FirstExpression.Count; i++)
            {
                if (currentChild == FirstExpression[i])
                {
                    if (i + 1 == FirstExpression.Count)
                    {
                        if (SecondExpression.Count > 0 && Caret.Instance.ExpressionSide == ExpressionSide.Right)
                        {
                            Caret.Instance.ExpressionSide = ExpressionSide.Left;
                            return SecondExpression[0];
                        }
                        return null;
                    }
                    return FirstExpression[i + 1];
                }
            }
            for (int i = 0; i < SecondExpression.Count; i++)
            {
                if (currentChild == SecondExpression[i])
                {
                    if (i + 1 == SecondExpression.Count)
                        return null;
                    return SecondExpression[i + 1];
                }
            }
            throw new KeyNotFoundException("Expression not found.");
        }

        public override Expression PreviousChild(Expression currentChild)
        {
            for (int i = 0; i < SecondExpression.Count; i++)
            {
                if (currentChild == SecondExpression[i])
                {
                    if (i == 0)
                    {
                        if (FirstExpression.Count > 0 && Caret.Instance.ExpressionSide == ExpressionSide.Left)
                        {
                            Caret.Instance.ExpressionSide = ExpressionSide.Right;
                            return FirstExpression[FirstExpression.Count - 1];
                        }
                        return null;
                    }
                    return SecondExpression[i - 1];
                }
            }
            for (int i = 0; i < FirstExpression.Count; i++)
            {
                if (currentChild == FirstExpression[i])
                {
                    if (i == 0)
                        return null;
                    return FirstExpression[i - 1];
                }
            }
            throw new KeyNotFoundException("Expression not found.");
        }


        public override Expression LastChild()
        {
            if (SecondExpression.Count > 0)
                return SecondExpression[SecondExpression.Count - 1];
            if (FirstExpression.Count > 0)
                return FirstExpression[SecondExpression.Count - 1];
            return null;
        }

        public override Expression FirstChild()
        {
            if (FirstExpression.Count > 0)
                return FirstExpression[0];
            if (SecondExpression.Count > 0)
                return SecondExpression[0];
            return null;
        }


        public override bool DeleteChild(Expression child)
        {
            bool result = SecondExpression.Remove(child) || FirstExpression.Remove(child);
            Expression aux = AddAuxiliary();
            Caret.Instance.SetActiveExpression(aux, ExpressionSide.Left);
            return result;
        }

        public override Expression AddAuxiliary()
        {
            ObservableCollection<Expression> collection = null;

            if (SecondExpression.Count == 0)
                collection = SecondExpression;
            else if (FirstExpression.Count == 0)
                collection = FirstExpression;

            if (collection != null)
            {
                var aux = new Auxiliary();
                aux.ParentExpression = this;
                collection.Add(aux);
                return aux;
            }
            return null;
        }

        public override void UpdateChildrensBottomMargin()
        {
            base.UpdateChildrensBottomMargin(FirstExpression);
            base.UpdateChildrensBottomMargin(SecondExpression);
        }

    }
}
