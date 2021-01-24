using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

/// <summary>
/// Contains logic that is not GUI related. It usually contains indpendent algorithms,
/// calculations and classes representing data.
/// </summary>
namespace GUICalculator.Model
{
    /// <summary>
    /// InfixToPostfixConverter is converter that converts an infix expression 
    /// to postfix expression. 
    /// </summary>
    /// <remarks>
    /// Postfix expression is easier computed than the infix one.
    /// </remarks>
    class InfixToPostfixConverter
    {
        private string unaryOperators = "+-";
        private string binaryOperators = "+-*/";
        private string operators = "+-*/!^";
        private int[] precedences = { 1, 1, 2, 2, 3, 4 };
        private string[] functions = { "sqrt", "rt", "sin", "cos", "tg", "neg" };

        private bool IsDigit(char ch)
        {
            return Char.IsDigit(ch) || ch == 'e' || ch == 'π' || ch == '.';
        }

        private bool IsOperator(char ch)
        {
            return operators.Contains(ch);
        }

        private bool IsFunction(string str)
        {
            return functions.Contains(str);
        }

        private int GetPrecedence(char ch)
        {
            int index = operators.IndexOf(ch);
            if (index < 0)
                throw new FormatException("Unrecognized operator.");
            return precedences[index];
        }

        /// <param name="index">
        ///     Index of the current character which is to be determined 
        ///     whether it is a binary negation operator or not.
        /// </param>
        /// <returns></returns>
        private bool IsBinaryNegation(string infix, int index)
        {
            if (!unaryOperators.Contains(infix[index]))
                return false;

            if (IsBinaryNegationFunction(infix, index))
                return false;

            if (index == 0)
                return true;

            if (index > 0)
            {
                if (binaryOperators.Contains(infix[index - 1]) || infix[index - 1] == '(')
                    return true;
            }
            return false;
        }

        private bool IsBinaryNegationFunction(string infix, int index)
        {
            if (!unaryOperators.Contains(infix[index]))
                return false;

            if (index != 0 && 
                !binaryOperators.Contains(infix[index - 1]) &&
                infix[index - 1] != '(')
                return false;

            return index < infix.Length - 1 && infix[index + 1] == '(';
        }

        /// <summary>
        /// Given an infix expression it converts to a postfix expression.
        /// </summary>
        /// <param name="infix">Expression that looks like "(2+5^(6)*(25)/(2)*sin(20))".</param>
        /// <returns>Returns a postfix expression that looks like the following expresion "2 5 6 ^ 25 2 20 sin * / * +".</returns>
        public string Convert(string infix)
        {
            Console.WriteLine(infix);
            StringBuilder postfix = new StringBuilder();
            Stack<string> stack = new Stack<string>();

            for (int i = 0; i < infix.Length; i++)
            {
                if (IsDigit(infix[i]))
                {
                    postfix.Append(infix[i]);
                    if (i + 1 < infix.Length && !IsDigit(infix[i + 1]))
                        postfix.Append(" ");
                }
                else if (infix[i] == '(')
                {
                    stack.Push(infix[i].ToString());
                }
                else if (infix[i] == ')')
                {
                    while (stack.Peek()[0] != '(')
                    {
                        postfix.Append(stack.Pop());
                        postfix.Append(" ");
                    }
                    stack.Pop(); // pop '(' from the stack

                    if (stack.Count > 0 && IsFunction(stack.Peek()))
                    {
                        postfix.Append(stack.Pop());
                        postfix.Append(" ");
                    }
                }
                else if (IsBinaryNegationFunction(infix, i))
                {
                    stack.Push("neg");
                }
                else if (IsBinaryNegation(infix, i))
                {
                    postfix.Append(infix[i]);
                }
                else if (IsOperator(infix[i]))
                {
                    while (stack.Count > 0 &&
                        IsOperator(stack.Peek()[0]) &&
                        GetPrecedence(stack.Peek()[0]) > GetPrecedence(infix[i]))
                    {
                        string op = stack.Pop();
                        postfix.Append(op[0]);
                        postfix.Append(" ");
                    }
                    stack.Push(infix[i].ToString());
                }
                else
                {
                    int n = i;
                    while (Char.IsLetter(infix[n]))
                        n++;
                    string function = infix.Substring(i, n - i);
                    if (IsFunction(function))
                    {
                        stack.Push(function);
                        i = n - 1;
                    }
                }
            }

            while (stack.Count > 0)
            {
                postfix.Append(stack.Pop());
                if (stack.Count != 0)
                    postfix.Append(" ");
            }

            Console.WriteLine(postfix.ToString().TrimEnd());
            return postfix.ToString().TrimEnd();
        }
    }
}
