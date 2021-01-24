using GUICalculator.ViewModel;
using GUICalculator.ViewModel.Expressions;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace GUICalculator.View
{
    /// <summary>
    /// MainWindow class contains interaction logic for MainWindow.xaml.
    /// It captures key strokes and performs appropriate actions for some of them,
    /// restrains from inputting disallowed symbols, opens help window.
    /// </summary>
    public partial class MainWindow : Window
    {
        private readonly Regex regex = new Regex("^[0123456789+\\-()!./e]+$");
        private readonly MainWindowVM dataContext;

        public MainWindow()
        {
            InitializeComponent();
            dataContext = DataContext as MainWindowVM;

            CustomTextBoxContainer.Children.Add(Caret.Instance);
            PreviewKeyDown += WhenKeyDown;
            Loaded += WhenInitialized;
        }

        private void WhenKeyDown(object sender, KeyEventArgs e)
        {
            e.Handled = true;

            if (e.Key == Key.Left || e.Key == Key.Right)
            {
                Direction direction = e.Key == Key.Left ? Direction.Left : Direction.Right;
                dataContext.MoveCaret(direction);
            }
            else if (e.Key == Key.Back)
            {
                dataContext.DeleteExpression(Direction.Left);
            }
            else if (e.Key == Key.Delete)
            {
                dataContext.DeleteExpression(Direction.Right);
            }
            else if (e.Key == Key.Multiply)
            {
                dataContext.AddMultiplicationExpression();
            }
            else if (e.Key == Key.P)
            {
                dataContext.AddCharacterExpression('π');
            }
            else if (e.Key == Key.S)
            {
                dataContext.AddTrigonometricExpression(TrigonometricFunctionType.Sine);
            }
            else if (e.Key == Key.C)
            {
                dataContext.AddTrigonometricExpression(TrigonometricFunctionType.Cosine);
            }
            else if (e.Key == Key.T)
            {
                dataContext.AddTrigonometricExpression(TrigonometricFunctionType.Tangent);
            }
            else if (e.Key == Key.Enter)
            {
                dataContext.EvaluateExpression();
            }
            else
            {
                e.Handled = false;
            }
        }
        
        protected override void OnPreviewTextInput(TextCompositionEventArgs e)
        {
            // Check if it an allowed character
            if (regex.IsMatch(e.Text))
            {
                //Console.WriteLine("{0}", e.Text);
                if (e.Text.Length != 1)
                    throw new Exception("Input text should have length of 1 character.");
                dataContext.AddCharacterExpression(e.Text[0]);
            }
            e.Handled = true;
            base.OnPreviewTextInput(e);
        }

        private void WhenInitialized(object sender, EventArgs e)
        {
            // Make sure the Caret is displayed in the middle.
            // The Caret instance doesn't know where it should render itself
            // until the window is loaded and control's sizes are calculated.
            // At this moment, we can update the Caret's position.
            Caret.Instance.UpdateActiveExpression();
        }

        /// <summary>
        ///     When the TextBox is clicked and if it was clicked behind the expression, 
        ///     set the caret position at the the end of the last expression.
        /// </summary>
        private void TextBoxClick(object sender, MouseButtonEventArgs e)
        {
            TextBox control = sender as TextBox;
            MainWindowVM vm = Application.Current.MainWindow.DataContext as MainWindowVM;

            Point relativePoint = e.GetPosition(Application.Current.MainWindow);
            var lastExpression = vm.Expression.LastChild();
            if (lastExpression == null)
                return;
            Point rightPositionOfExp = lastExpression.RightPositionOf();

            if (relativePoint.X >= rightPositionOfExp.X)
            {
                Caret.Instance.ExpressionSide = ExpressionSide.Right;
                Caret.Instance.SetActiveExpression(vm.Expression.LastChild());
            }
        }

        private void ShowHelp(object sender, RoutedEventArgs e)
        {
            HelpWindow helpWindow = new HelpWindow();
            helpWindow.Owner = this;
            helpWindow.WindowStartupLocation = WindowStartupLocation.CenterOwner;
            helpWindow.ShowDialog();
        }
    }
}
