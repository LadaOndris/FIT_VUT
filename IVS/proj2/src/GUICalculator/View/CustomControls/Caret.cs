using GUICalculator.ViewModel.Expressions;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Media;

namespace GUICalculator.View
{
    /// <summary>
    /// A caret is a blinking cursor usually used in textboxes.
    /// The Caret class is implemented as a singleton, so only once instance can exist.
    /// 
    /// The caret is always displayed for a particular expression. Either on the left side of 
    /// the particular expression or on the right side.
    /// The expression by which the caret is displayed is usually being changed, since the caret should 
    /// be able to move around in the textbox. 
    /// 
    /// In order to move the caret, call the SetActiveExpression method. 
    /// Sometimes also calling the UpdateActiveExpression method might be needed.
    /// </summary>
    /// <remarks>
    /// Sometimes it is desired to have more than one instance of the caret class.
    /// If such case occurs, a modification of the Caret class will probably be needed.
    /// </remarks>
    public class Caret : FrameworkElement
    {
        /// <summary>
        /// The timer is responsible for making the caret blink after every blinkPeriod.
        /// </summary>
        private readonly Timer timer;
        /// <summary>
        /// The caret blinks every blinkPeriod.
        /// </summary>
        private readonly int blinkPeriod = 500;
        /// <summary>
        /// The current location of the caret.
        /// </summary>
        private Point location;
        /// <summary>
        /// The pen is used for drawing the caret.
        /// </summary>
        private Pen pen = new Pen(Brushes.Black, 1);
        
        public static readonly DependencyProperty VisibleProperty =
            DependencyProperty.Register("Visible", typeof(bool),
            typeof(Caret), new FrameworkPropertyMetadata(true, FrameworkPropertyMetadataOptions.AffectsRender));

        private Caret()
        {
            pen.Freeze();
            CaretHeight = DefaultHeight;
            Left = DefaultPosition.X;
            Top = DefaultPosition.Y;
            Visible = true;
            timer = new Timer(BlinkCaret, null, 0, blinkPeriod);
        }

        public static Caret Instance { get; } = new Caret();
        public double CaretHeight { get; set; }
        /// <summary>
        /// The caret keeps track of which expression it is displayed for.
        /// For theses purposes the ActiveExpression property is used.
        /// </summary>
        public ViewModel.Expressions.Base.Expression ActiveExpression { get; private set; }
        public ExpressionSide ExpressionSide { get; set; } // defines on which side of the ActiveExpression the Caret lies
        public Point DefaultPosition { get; } = new Point(0, 10);
        public double DefaultHeight { get; } = 18;

        protected override void OnRender(DrawingContext dc)
        {
            if (Visible)
            {
                dc.DrawLine(pen, location, new Point(Left, location.Y + CaretHeight));
            }
        }
        
        public bool Visible
        {
            get
            {
                return (bool)GetValue(VisibleProperty);
            }
            set
            {
                SetValue(VisibleProperty, value);
            }
        }

        public double Left
        {
            get { return location.X; }
            set
            {
                if (location.X != value)
                {
                    location.X = Math.Floor(value) + .5; //to avoid WPF antialiasing
                    if (Visible)
                    {
                        Visible = false;
                    }
                }
            }
        }

        public double Top
        {
            get { return location.Y; }
            set
            {
                if (location.Y != value)
                {
                    location.Y = Math.Floor(value) + .5; //to avoid WPF antialiasing
                    if (Visible)
                    {
                        Visible = false;
                    }
                }
            }
        }
        public bool RestartBlinking()
        {
            return timer.Change(0, blinkPeriod);
        }

        public void FlipSide()
        {
            ExpressionSide = ExpressionSide == ExpressionSide.Left ? 
                ExpressionSide.Right : ExpressionSide.Left;

            if (ActiveExpression == null)
                return;

            Point position;
            if (ExpressionSide == ExpressionSide.Left)
                position = ActiveExpression.RightPositionOf();
            else
                position = ActiveExpression.LeftPositionOf();
            Left = position.X;
        }

        public void SetActiveExpression(ViewModel.Expressions.Base.Expression exp)
        {
            if (exp == null)
                return;
            ActiveExpression = exp;
            if (exp is Auxiliary)
                ExpressionSide = ExpressionSide.Left;
            UpdateActiveExpression();
            RestartBlinking();
        }

        public void SetActiveExpression(ViewModel.Expressions.Base.Expression exp, ExpressionSide desiredExpressionSide)
        {
            if (exp == null)
                return;
            ExpressionSide = desiredExpressionSide;
            SetActiveExpression(exp);
        }

        public void UpdateActiveExpression()
        {
            Point position = default(Point);

            if (ExpressionSide == ExpressionSide.Left)
                position = ActiveExpression.LeftPositionOf();
            else
                position = ActiveExpression.RightPositionOf();

            Left = position.X;
            Top = position.Y;
            CaretHeight = ActiveExpression.ActualHeight;

            // If the active expression's height is zero (most probably not available at this moment
            // or not calculated) set the caret height to nonzero number just so that the Caret is visible.
            if (CaretHeight == 0)
                CaretHeight = 18;
        }

        private void BlinkCaret(Object state)
        {
            //Console.WriteLine("Left {0}, Top {1}, Height {2}", Left, Top, CaretHeight);
            Dispatcher.Invoke(new Action(delegate { Visible = !Visible; }));
        }
        
    }
}
