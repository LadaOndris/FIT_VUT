using System.ComponentModel;

namespace GUICalculator.ViewModel
{
    /// <summary>
    /// The ViewModelBase class is a base class for all view-model objects
    /// which contain properties whose changes are propagated to view.
    /// (When those properties are changed, the view is notified through binding.)
    /// </summary>
    public abstract class ViewModelBase : INotifyPropertyChanged
    {
        /// <summary>
        /// An Event that is raised from OnPropertyChanged method is called.
        /// </summary>
        public event PropertyChangedEventHandler PropertyChanged;

        /// <summary>
        /// Raises the PropertyChanged event, whose function is to notify 
        /// the view that a property was changes, so the view can be updated.
        /// </summary>
        /// <param name="propertyName">The name of the property that was changed.</param>
        protected virtual void OnPropertyChanged(string propertyName)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}
