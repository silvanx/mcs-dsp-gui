using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Mcs.Usb;

namespace MCS_USB_Windows_Forms_Application1
{
    public partial class DebugControlsForm : Form
    {
        private Dacq parentForm = null;
        private CMeaUSBDeviceNet mea = null;
        private CMcsUsbListNet usbDeviceList = null;

        public DebugControlsForm()
        {
            InitializeComponent();
        }

        public DebugControlsForm(Dacq parentForm, CMeaUSBDeviceNet mea, CMcsUsbListNet usbDeviceList)
        {
            this.parentForm = parentForm;
            this.mea = mea;
            this.usbDeviceList = usbDeviceList;
            InitializeComponent();

            debugOutputBox.AppendText("--- DEBUG WINDOW OPEN ---\n");
            debugOutputBox.AppendText("USB Device list contains " + this.usbDeviceList.Count.ToString() + " entries\n");
            if (this.usbDeviceList.Count > 0)
            {
                debugOutputBox.AppendText("Selected USB device: " + parentForm.selectedUsbDevice.SerialNumber + "\n");
            }
        }

        private void Button1_Click(object sender, EventArgs e)
        {
            uint status;
            debugOutputBox.AppendText("**Trying mea.connect() with Lock Mask = 63\n");
            status = this.mea.Connect(parentForm.selectedUsbDevice, 63);
            if (status == 0)
            {
                debugOutputBox.AppendText("Connected!\n");
            } else
            {
                debugOutputBox.AppendText("Connection ERROR: " + CMcsUsbNet.GetErrorText(status) + "\n");
            }
        }

        private void Button2_Click(object sender, EventArgs e)
        {
            string meaConnectionStatus = "";
            if (this.mea.IsConnected())
            {
                meaConnectionStatus = "CONNECTED";
            } else
            {
                meaConnectionStatus = "DISCONNECTED";
            }
            debugOutputBox.AppendText("** MEA " + meaConnectionStatus + "\n");
        }

        private void MeaParamsButton_Click(object sender, EventArgs e)
        {
            string headstagePresentString = "??";
            string headstageActiveString = "??";

            uint status = this.mea.Connect(parentForm.selectedUsbDevice);
            if (status == 0)
            {
                debugOutputBox.AppendText("** MEA PARAMS:\n");

                headstagePresentString = this.mea.GetHeadstagePresent(0) ? "YES" : "NO";
                headstageActiveString = this.mea.GetHeadstageActive(0) ? "YES" : "NO";

                int meaSamplerate = this.mea.GetSamplerate(0);

                CW2100_FunctionNet func = new CW2100_FunctionNet(this.mea);

                debugOutputBox.AppendText("\tSamplerate: " + meaSamplerate.ToString() + "\n");
                debugOutputBox.AppendText("\tHeadstage 0 present: " + headstagePresentString + "\n");
                debugOutputBox.AppendText("\tHeadstage 0 active: " + headstageActiveString + "\n");
                this.mea.Disconnect();
            }
            else
            {
                debugOutputBox.AppendText(CMcsUsbNet.GetErrorText(status) + "\n");
            }
        }

        private void MeaDisconnectButton_Click(object sender, EventArgs e)
        {
            this.mea.Disconnect();
            debugOutputBox.AppendText("Disconnected!\n");
        }
    }
}
