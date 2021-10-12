using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MCS_USB_Windows_Forms_Application1
{
    public partial class DebugControlsForm : Form
    {
        public DebugControlsForm()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            debugOutputBox.AppendText("Button 1 clicked \n");
        }
    }
}
