using GUICalculator.ViewModel;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Markup;

namespace GUICalculator.View
{
    /// <summary>
    /// A textbox extended by Content dependency property to hold any content.
    /// The TextBox provided by the framework can contain only text.
    /// Here we need the TextBox to hold different objects.
    /// </summary>
    [ContentProperty("Content")]
    internal sealed class CustomTextBox : TextBox
    {
        
        public FrameworkElement Content
        {
            get { return (FrameworkElement)GetValue(ContentProperty); }
            set { SetValue(ContentProperty, value); }
        }

        public static readonly DependencyProperty ContentProperty =
            DependencyProperty.Register("Content", typeof(FrameworkElement), typeof(CustomTextBox), new UIPropertyMetadata(null));
        
    }
}
