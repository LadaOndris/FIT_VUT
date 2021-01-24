using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using GUICalculator.Properties;

namespace GUICalculator.View
{
    /// <summary>
    /// HelpWindow class contains interaction logic for HelpWindow.xaml.
    /// Loads a manual and displays it as an RTF document.
    /// </summary>
    public partial class HelpWindow : Window
    {
        public HelpWindow()
        {
            InitializeComponent();

            LoadRTFContent();
        }

        private void LoadRTFContent()
        {
            try
            {
                var stream = new MemoryStream(Encoding.UTF8.GetBytes(Resources1.manual));
                richTextBox.Selection.Load(stream, DataFormats.Rtf);
            }
            catch (Exception e)
            {
                richTextBox.AppendText("Nepodařilo se načíst soubor.");
                richTextBox.AppendText(e.Message);
            }
        }
    }
}
