using GUICalculator.ViewModel.Expressions.Base;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

/// <summary>
/// Contains custom ContentControl based controls with a special template each.
/// For example defined the Root, its appearance and behaviour.
/// </summary>
namespace GUICalculator.ViewModel.Expressions
{
    /// <summary>
    /// Ans expression is a terminal expression which contains
    /// a Result and is displayed as ANS.
    /// </summary>
    internal class Ans : TerminalExpression
    {
        private Result result;

        public Ans(Result result)
            : base("AnsExpressionTemplate")
        {
            this.result = result;
        }

        public override string ConvertToString()
        {
            return result.Value.ToString();
        }
    }
}
