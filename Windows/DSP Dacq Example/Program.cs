using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;

namespace Biomed_Closed_Loop_GUI
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Dacq());
        }
    }
}
