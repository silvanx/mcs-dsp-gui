﻿using System;
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
            debugOutputBox.AppendText("** Testing mea.connect() without Lock Mask\n");
            uint status = this.mea.Connect(parentForm.selectedUsbDevice);
            debugOutputBox.AppendText("STATUS: " + status.ToString() + "\n");
            this.mea.Disconnect();
            debugOutputBox.AppendText("** Testing mea.connect() with Lock Mask = 63\n");
            status = this.mea.Connect(parentForm.selectedUsbDevice, 63);
            debugOutputBox.AppendText("STATUS: " + status.ToString() + "\n");
            this.mea.Disconnect();
        }

        private void Button2_Click(object sender, EventArgs e)
        {

        }
    }
}
