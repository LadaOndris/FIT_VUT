using GUICalculator.Command;
using GUICalculator.Model;
using GUICalculator.View;
using GUICalculator.ViewModel;
using GUICalculator.ViewModel.Expressions;
using GUICalculator.ViewModel.Expressions.Base;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;

namespace GUICalculator.ViewModel
{
    /// <summary>
    /// This class contains logic for handling user actions (such as button clicks) 
    /// and delegates it further for processing.
    /// </summary>
    public sealed class MainWindowVM : ViewModelBase
    {
        public Expression _expression;
        public string _resultString;
        public ICommand _characterInputCommand;
        public ICommand _multiplicationCommand;
        public ICommand _powerCommand;
        public ICommand _rootCommand;
        public ICommand _squareRootCommand;
        public ICommand _fractionCommand;
        public ICommand _ansCommand;
        public ICommand _clearCommand;
        public ICommand _deleteCommand;
        public ICommand _evaluateCommand;
        public ICommand _sineCommand;
        public ICommand _cosineCommand;
        public ICommand _tangentCommand;

        private Result result = new Result(0);
        private InfixToPostfixConverter converter = new InfixToPostfixConverter();

        public MainWindowVM()
        {
            Clear();
        }

        public ICommand CharacterInputCommand => _characterInputCommand ?? (_characterInputCommand = new RelayCommand<string>(AddCharacterExpression));
        public ICommand MultiplicationCommand => _multiplicationCommand ?? (_multiplicationCommand = new RelayCommand(AddMultiplicationExpression));
        public ICommand PowerCommand => _powerCommand ?? (_powerCommand = new RelayCommand(AddPowerExpression));
        public ICommand RootCommand => _rootCommand ?? (_rootCommand = new RelayCommand(AddRootExpression));
        public ICommand SquareRootCommand => _squareRootCommand ?? (_squareRootCommand = new RelayCommand(AddSquareRootExpression));
        public ICommand FractionCommand => _fractionCommand ?? (_fractionCommand = new RelayCommand(AddFractionExpression));
        public ICommand AnsCommand => _ansCommand ?? (_ansCommand = new RelayCommand(AddAns));
        public ICommand ClearCommand => _clearCommand ?? (_clearCommand = new RelayCommand(Clear));
        public ICommand DeleteCommand => _deleteCommand ?? (_deleteCommand = new RelayCommand(() => DeleteExpression(Direction.Left)));
        public ICommand EvaluateCommand => _evaluateCommand ?? (_evaluateCommand = new RelayCommand(EvaluateExpression));
        public ICommand SineCommand => _sineCommand ?? (_sineCommand = new RelayCommand(() => AddTrigonometricExpression(TrigonometricFunctionType.Sine)));
        public ICommand CosineCommand => _cosineCommand ?? (_cosineCommand = new RelayCommand(() => AddTrigonometricExpression(TrigonometricFunctionType.Cosine)));
        public ICommand TangentCommand => _tangentCommand ?? (_tangentCommand = new RelayCommand(() => AddTrigonometricExpression(TrigonometricFunctionType.Tangent)));

        public Expression Expression
        {
            get => _expression;
            set
            {
                _expression = value;
                OnPropertyChanged(nameof(Expression));
            }
        }

        public string ResultString
        {
            get => _resultString;
            set
            {
                _resultString = value;
                OnPropertyChanged(nameof(ResultString));
            }
        }

        private void SetResult(double value)
        {
            result.Value = value;
            ResultString = value.ToString();
        }

        private void SetResult(string message)
        {
            result.Value = 0;
            ResultString = message;
        }
        
        internal void EvaluateExpression()
        {
            //string test = "56+sin(89*sqrt(26^(4)+26*5))*((25)/(p)+12!-cos(p*e))+2e^(5+4)";
            PostfixEvaluator parser = new PostfixEvaluator();
            string infix = Expression.ConvertToString();
            Console.WriteLine(infix);
            try
            {
                string postfix = converter.Convert(infix);
                // no input to process
                if (postfix == "()" || postfix == string.Empty)
                    return;
                SetResult(parser.EvaluatePostfixExp(postfix));
            }
            catch (Exception e)
            {
                if (string.Equals(e.Message, "Stack empty.", StringComparison.Ordinal))
                    SetResult("Syntax error");
                else
                    SetResult(e.Message);
            }
        }

        private void Clear()
        {
            ClearExpressions();
            ResultString = "0";
        }

        private void ClearExpressions()
        {
            Expression = new Basic();
            Expression.VerticalAlignment = System.Windows.VerticalAlignment.Center;
            Expression.FirstChild().Background = Brushes.White;
            Caret.Instance.SetActiveExpression(Expression.FirstChild());
            Expression.UpdateLayout();
            Caret.Instance.UpdateActiveExpression();
        }
        
        private void AddAns()
        {
            Ans ans = new Ans(result);
            AddNewExpression(Caret.Instance.ActiveExpression, ans);
            Caret.Instance.SetActiveExpression(ans);
        }

        private void AddFractionExpression()
        {
            Fraction fraction = new Fraction();
            AddNewExpression(Caret.Instance.ActiveExpression, fraction);
            Caret.Instance.SetActiveExpression(fraction.FirstChild(), ExpressionSide.Left);
        }

        public void AddRootExpression()
        {
            Expression root = new Root();
            AddNewExpression(Caret.Instance.ActiveExpression, root);
            Caret.Instance.SetActiveExpression(root.FirstChild(), ExpressionSide.Left);
        }

        public void AddSquareRootExpression()
        {
            Expression squareRoot = new SquareRoot();
            AddNewExpression(Caret.Instance.ActiveExpression, squareRoot);
            Caret.Instance.SetActiveExpression(squareRoot.FirstChild(), ExpressionSide.Left);
        }

        public void AddPowerExpression()
        {
            Expression power = new Power();
            AddNewExpression(Caret.Instance.ActiveExpression, power);
            Caret.Instance.SetActiveExpression(power.FirstChild(), ExpressionSide.Left);
        }

        public void AddTrigonometricExpression(TrigonometricFunctionType type)
        {
            Expression trigFunc = new TrigonometricFunction(type);
            AddNewExpression(Caret.Instance.ActiveExpression, trigFunc);
            Caret.Instance.SetActiveExpression(trigFunc.FirstChild(), ExpressionSide.Left);
        }

        public void AddMultiplicationExpression()
        {
            Expression multiplicationSign = new MultiplicationSign();
            AddNewExpression(Caret.Instance.ActiveExpression, multiplicationSign);
            Caret.Instance.SetActiveExpression(multiplicationSign);
        }

        public void AddCharacterExpression(string str)
        {
            if (str.Length != 1)
                throw new Exception("String's length should be 1.");
            AddCharacterExpression(str[0]);
        }

        public void AddCharacterExpression(char character)
        {
            Expression characterExp = null;
            switch (character)
            {
                case '(':
                    {
                        characterExp = new LeftParenthesis();
                    } break;
                case ')':
                    {
                        characterExp = new RightParenthesis();
                    } break;
                default:
                    {
                        characterExp = new Character(character);
                    } break;
            }

            Expression activeExp = Caret.Instance.ActiveExpression;
            AddNewExpression(activeExp, characterExp);
            Caret.Instance.SetActiveExpression(characterExp);
        }

        public void AddNewExpression(Expression activeExp, Expression newExpression)
        {
            //Expression activeExp = Caret.Instance.ActiveExpression;
            if (activeExp != null)
            {
                // create new expression and add it to the appropriate parent expression
                Expression parent = activeExp.ParentExpression;
                if (parent == null)
                    return;
                parent.AddExpression(activeExp, newExpression);
                newExpression.ParentExpression = parent;

                // make sure the new expression is displayed and new position is calculated for this element
                activeExp.UpdateLayout();
                parent.UpdateLayout();
                newExpression.UpdateLayout();

                Caret.Instance.ExpressionSide = ExpressionSide.Right;
                // make sure the the caret is displayed correctly after parent's layout is updated
                Caret.Instance.UpdateActiveExpression();
            }
        }

        public void MoveCaret(Direction direction)
        {
            Caret caret = Caret.Instance;
            Expression exp = null;

            if (direction == Direction.Left)
                exp = caret.ActiveExpression.MoveLeft(null, true);
            else if (direction == Direction.Right)
                exp = caret.ActiveExpression.MoveRight(null, true);

            if (exp == null)
                return;

            caret.SetActiveExpression(exp);
            caret.RestartBlinking();
        }

        public void DeleteExpression(Direction direction)
        {
            Expression activeExp = Caret.Instance.ActiveExpression;
            if (activeExp == null)
                return;
            Expression parentExp = activeExp.ParentExpression;
            if (parentExp == null)
                return;

            Expression nextActive;
            Expression toBeRemoved;

            if (Caret.Instance.ExpressionSide == ExpressionSide.Right)
            {
                if (direction == Direction.Left)
                {
                    nextActive = parentExp.PreviousChild(activeExp);
                    toBeRemoved = activeExp;

                    // handle the situation when the toBeRemoved is leftmost
                    if (nextActive == null)
                    {
                        Caret.Instance.ExpressionSide = ExpressionSide.Left;
                        nextActive = parentExp.NextChild(activeExp);
                    }
                }
                else
                {
                    nextActive = activeExp;
                    toBeRemoved = parentExp.NextChild(activeExp);
                }
            }
            else
            {
                if (direction == Direction.Left)
                {
                    nextActive = activeExp;
                    toBeRemoved = parentExp.PreviousChild(activeExp); 
                }
                else
                {
                    nextActive = parentExp.NextChild(activeExp);
                    toBeRemoved = activeExp;

                    // handle the situation when the toBeRemoved is rightmost
                    if (nextActive == null)
                    {
                        Caret.Instance.ExpressionSide = ExpressionSide.Right;
                        nextActive = parentExp.PreviousChild(activeExp);
                    }
                }
            }

            if (toBeRemoved != null)
            {
                parentExp.DeleteChild(toBeRemoved);
                parentExp.UpdateLayout();
                Caret.Instance.SetActiveExpression(nextActive);
                Caret.Instance.UpdateActiveExpression();
            }
        }

    }
}
