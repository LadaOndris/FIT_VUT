using System;
using System.Collections.Generic;
using MathLibrary;
using System.Linq;
namespace GUICalculator.Model
{
    /// <summary>
    /// PostfixEvaluator is used to evaluate (compute) mathematical expressions 
    /// in the form of a postfix expression. 
    /// </summary>
    /// <remarks>
    /// The mathematical expression (infix expression) can be converted to postfix expression
    /// with InfixToPostfixConverter class.
    /// </remarks>
    class PostfixEvaluator
    {
        private static readonly string[] oneParamOperators = { "sin", "cos", "tg", "!", "sqrt", "neg" };

        /// <summary>
        /// Evaluates postfix expression.
        /// </summary>
        /// <param name="postfixExpression">
        ///     Postfix expression to be evaluated. 
        ///     Postfix expressions look like this "2 5 6 ^ 25 2 20 sin * / * +".
        /// </param>
        /// <returns>Returns evaluated given postfix expression.</returns>
        public double EvaluatePostfixExp(string postfixExpression)
        {
            Stack<double> operandStack = new Stack<double>();
            double number = 0;
            bool isNumber = false;

            foreach (string element in postfixExpression.Split(' '))
            {
                if (element == string.Empty)
                    continue;
                isNumber = Double.TryParse(element, out number);
                if (element == "π")
                {
                    isNumber = true;
                    number = Constants.Pi;
                }
                else if (element == "e")
                {
                    isNumber = true;
                    number = Constants.E; // TODO from math lib
                }
                if (isNumber == true)
                {
                    operandStack.Push(number);
                }
                else
                {
                    if (oneParamOperators.Contains(element))
                        operandStack.Push(GetOperation(element, new Number(operandStack.Pop()), new Number(0)).Evaluate());

                    else operandStack.Push(GetOperation(element, new Number(operandStack.Pop()), new Number(operandStack.Pop())).Evaluate());
                }
            }
            
            return operandStack.Count > 0 ? operandStack.Pop() : 0;
        }

        private IExpression GetOperation(string op, IExpression rightOperand, IExpression leftOperand)
        {
            switch (op)
            {
                case "-":
                    return new SubtractionExp(leftOperand, rightOperand);
                case "+":
                    return new AdditionExp(leftOperand, rightOperand);
                case "*":
                    return new MultiplicationExp(leftOperand, rightOperand);
                case "/":
                    return new DivisionExp(leftOperand, rightOperand);
                case "^":
                    return new PowerExp(leftOperand, rightOperand);
                case "cos":
                    return new CosineExp(rightOperand);
                case "sin":
                    return new SineExp(rightOperand);
                case "tg":
                    return new TangentExp(rightOperand);
                case "!":
                    return new FactorialExp(rightOperand);
                case "sqrt":
                    return new RootExp(rightOperand, new Number(2));
                case "rt":
                    return new RootExp(rightOperand, leftOperand);
                case "neg":
                    return new MultiplicationExp(rightOperand, new Number(-1));

                default: throw new Exception("Illegal operation");
            }
        }
    }
}
