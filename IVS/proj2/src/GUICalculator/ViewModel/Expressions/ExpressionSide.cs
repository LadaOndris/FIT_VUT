using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GUICalculator.ViewModel.Expressions
{
    /// <summary>
    /// ExpressionSide defines on which side of the expression the Caret is positioned.
    /// The caret can be positioned on either side of the expression. To know on which side it is
    /// the ExpressionSide enumeration is used.
    /// </summary>
    public enum ExpressionSide
    {
        Left, Right
    }
}
