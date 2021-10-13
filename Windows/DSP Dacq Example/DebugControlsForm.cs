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

        public void debugLog(string message)
        {
            string messageWithNewLine = message + "\n";
            debugOutputBox.AppendText(messageWithNewLine);
        }

        public DebugControlsForm(Dacq parentForm, CMeaUSBDeviceNet mea, CMcsUsbListNet usbDeviceList)
        {
            this.parentForm = parentForm;
            this.mea = mea;
            this.usbDeviceList = usbDeviceList;
            InitializeComponent();

            debugLog("--- DEBUG WINDOW OPEN ---");
            debugLog("USB Device list contains " + this.usbDeviceList.Count.ToString() + " entries");
            if (this.usbDeviceList.Count > 0)
            {
                debugLog("Selected USB device: " + parentForm.selectedUsbDevice.SerialNumber);
            }
        }

        private void Button1_Click(object sender, EventArgs e)
        {
            uint status;
            debugLog("**Connecting to MEA with Lock Mask = 63");
            status = this.mea.Connect(parentForm.selectedUsbDevice, 63);
            if (status == 0)
            {
                debugLog("Connected!");
            } else
            {
                debugLog("Connection ERROR: " + CMcsUsbNet.GetErrorText(status));
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
            debugLog("** MEA " + meaConnectionStatus);
        }

        private void MeaParamsButton_Click(object sender, EventArgs e)
        {
            string headstagePresentString = "??";
            string headstageActiveString = "??";

            uint status = this.mea.Connect(parentForm.selectedUsbDevice);
            if (status == 0)
            {
                debugLog("** MEA PARAMS:");

                headstagePresentString = this.mea.GetHeadstagePresent(0) ? "YES" : "NO";
                headstageActiveString = this.mea.GetHeadstageActive(0) ? "YES" : "NO";

                int meaSamplerate = this.mea.GetSamplerate(0);

                CW2100_FunctionNet func = new CW2100_FunctionNet(this.mea);

                debugLog("\tSamplerate: " + meaSamplerate.ToString());
                debugLog("\tHeadstage 0 present: " + headstagePresentString);
                debugLog("\tHeadstage 0 active: " + headstageActiveString);
                if (this.mea.GetHeadstagePresent(0))
                    debugLog("\tHeadstage 0 ID: " + this.mea.GetHeadstageID(0));
                this.mea.Disconnect();
            }
            else
            {
                debugLog(CMcsUsbNet.GetErrorText(status));
            }
        }

        private void MeaDisconnectButton_Click(object sender, EventArgs e)
        {
            this.mea.Disconnect();
            debugLog("Disconnected!");
        }
    }
}
