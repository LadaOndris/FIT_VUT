using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GUICalculator.ViewModel
{
    /// <summary>
    /// The Result class holds a double value, that is the
    /// last result evaluated by calculator.
    /// </summary>
    internal sealed class Result : ViewModelBase
    {
        public Result(double value)
        {
            Value = value;
        }

        public double Value { get; set; }
    }
}
