using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

/// <summary>
/// Contains all view related files (classes, styles, templates, converters, etc).
/// </summary>
namespace GUICalculator.View
{
    static class FrameworkElementExtension
    {
        /// <summary>
        /// Calculates the position of a framework element from the left side
        /// of the window to the left side of the element.
        /// </summary>
        /// <param name="element">The element to find the position of.</param>
        /// <returns>Returns a point on the left side of the element
        /// located relatively to the left side of a MainWindow.</returns>
        public static Point LeftPositionOf(this FrameworkElement element)
        {
            return element.TranslatePoint(new Point(0, 0), Application.Current.MainWindow);
        }

        /// <summary>
        /// Calculates the position of a framework element from the left side
        /// of the window to the ŕight side of the element.
        /// </summary>
        /// <param name="element">The element to find the position of.</param>
        /// <returns>Returns a point on the right side of the element
        /// located relatively to the left side of a MainWindow.</returns>
        public static Point RightPositionOf(this FrameworkElement element)
        {
            Point point = LeftPositionOf(element);
            point.X += element.ActualWidth;
            return point;
        }
    }
}
