using GUICalculator.ViewModel.Expressions.Base;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;

namespace GUICalculator.ViewModel.Expressions
{
    /// <summary>
    /// Character expression is a terminal expression which
    /// holds a single character.
    /// </summary>
    class Character : TerminalExpression
    {

        public Character(char value)
            : base("CharacterExpressionTemplate")
        {
            Value = value;
        }
        
        public char Value { get; set; }


        public override string ConvertToString()
        {
            return Value.ToString();
        }
    }
}
