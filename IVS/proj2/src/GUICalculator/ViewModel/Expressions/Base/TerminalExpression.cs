using GUICalculator.View;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GUICalculator.ViewModel.Expressions.Base
{
    abstract class TerminalExpression : Expression
    {
        public TerminalExpression(string templateName)
            : base(templateName)
        {

        }
        
        public override Expression FirstChild()
        {
            return null;
        }

        public override Expression LastChild()
        {
            return null;
        }

        public override Expression NextChild(Expression currentChild)
        {
            return null;
        }

        public override Expression PreviousChild(Expression currentChild)
        {
            return null;
        }

        public override void AddExpression(Expression activeExpression, Expression expression)
        {
            return;
        }

        public override bool DeleteChild(Expression child)
        {
            throw new NotSupportedException("Not supported operation.");
        }

        public override Expression AddAuxiliary()
        {
            throw new NotSupportedException("Not supported operation.");
        }

        public override void UpdateChildrensBottomMargin()
        {
            
        }
    }
}
