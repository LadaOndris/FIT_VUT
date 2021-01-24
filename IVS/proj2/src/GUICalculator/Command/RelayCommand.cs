using System;
using System.Windows.Input;

/// <summary>
/// Contains Command related classes.
/// </summary>
namespace GUICalculator.Command
{
    /// <summary>
    ///     RelayCommand is an implementation of ICommand interface used 
    ///     for executing button actions.
    /// </summary>
    public class RelayCommand : ICommand
    {
        /// <summary>
        /// Represents the action that will be executed if canExecute returns true.
        /// </summary>
        private readonly Action execute;
        /// <summary>
        /// Represents a method that returns boolean value determining whether 
        /// the action can be executed.
        /// If the canExecute method returns false, no action is executed.
        /// </summary>
        private readonly Func<bool> canExecute;

        /// <summary>
        /// Initializes the RelayCommand class.
        /// The given action <paramref name="execute"/> will be always executed.
        /// </summary>
        /// <param name="execute">The action that will be executed.</param>
        public RelayCommand(Action execute)
            : this(execute, null)
        {

        }

        /// <summary>
        /// Initializes the RelayCommand class.
        /// The given action <paramref name="execute"/> will be executed only if 
        /// <paramref name="canExecute"/> returns true.
        /// </summary>
        /// <param name="execute">The action that will be executed.</param>
        /// <param name="canExecute">The method determining whether the action will be executed.</param>
        public RelayCommand(Action execute, Func<bool> canExecute)
        {
            if (execute == null)
                throw new ArgumentNullException("execute");

            this.execute = execute;
            this.canExecute = canExecute;
        }

        #region ICommand Members

        public event EventHandler CanExecuteChanged
        {
            add { CommandManager.RequerySuggested += value; }
            remove { CommandManager.RequerySuggested -= value; }
        }

        public bool CanExecute(object parameter)
        {
            if (canExecute == null)
                return true;
            return canExecute();
        }

        public void Execute(object parameter)
        {
            execute();
        }

        #endregion
    }

    /// <summary>
    ///     RelayCommand is a generic implementation of ICommand interface used 
    ///     for executing button actions.
    /// </summary>
    public class RelayCommand<T> : ICommand
    {
        /// <summary>
        /// Represents the action that will be executed if canExecute returns true.
        /// </summary>
        private readonly Action<T> execute;
        /// <summary>
        /// Represents a method that returns boolean value determining whether 
        /// the action can be executed.
        /// If the canExecute method returns false, no action is executed.
        /// </summary>
        private readonly Func<bool> canExecute;

        /// <summary>
        /// Initializes the RelayCommand class.
        /// The given action <paramref name="execute"/> will be always executed.
        /// </summary>
        /// <param name="execute">The action that will be executed.</param>
        public RelayCommand(Action<T> execute)
            : this(execute, null)
        {

        }

        /// <summary>
        /// Initializes the RelayCommand class.
        /// The given action <paramref name="execute"/> will be executed only if 
        /// <paramref name="canExecute"/> returns true.
        /// </summary>
        /// <param name="execute">The action that will be executed.</param>
        /// <param name="canExecute">The method determining whether the action will be executed.</param>
        public RelayCommand(Action<T> execute, Func<bool> canExecute)
        {
            if (execute == null)
                throw new ArgumentNullException("execute");

            this.execute = execute;
            this.canExecute = canExecute;
        }

        #region ICommand Members

        public event EventHandler CanExecuteChanged
        {
            add { CommandManager.RequerySuggested += value; }
            remove { CommandManager.RequerySuggested -= value; }
        }

        public bool CanExecute(object parameter)
        {
            if (canExecute == null)
                return true;
            return canExecute();
        }

        public void Execute(object parameter)
        {
            if (parameter is T)
            {
                T param = (T)parameter;

                execute(param);
            }

        }

        #endregion
    }
}
