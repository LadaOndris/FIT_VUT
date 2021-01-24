using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Data;

/// <summary>
/// Contains converters that are used by the view to convert data 
/// from view model to a representable form.
/// </summary>
namespace GUICalculator.View.Converter
{
    class RoundValueConverter : IValueConverter
    {
        /// <summary>
        /// Rounds a double value to a certain number of fractional digits.
        /// </summary>
        /// <param name="value">Double value to be converted.</param>
        /// <param name="targetType">This parameter is not used.</param>
        /// <param name="parameter">This parameter is not used.</param>
        /// <param name="culture">This parameter is not used.</param>
        /// <returns>
        /// Returns the converted value.
        /// If type of the <paramref name="value"/> is not double, the value given is returned.
        /// </returns>
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            string val = value as string;
            double number;
            if (double.TryParse(val, out number))
            {
                long precision = 10000000000;
                int counter = 0;
                while (number < precision && counter < 10)
                {
                    number *= 10;
                    counter++;
                }
                number = Math.Round(number);
                for (counter--; counter >= 0; counter--)
                {
                    number /= 10;
                }
                return number;
            }
            else
            {
                return value;
            }
        }
        /// <summary>
        /// Not supported operation.
        /// Shouldn't be executed, otherwise NotSupportedException is thrown.
        /// </summary>
        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotSupportedException();
        }
    }
}
