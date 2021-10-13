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
        private uint stimulationToSend = 0;

        public DebugControlsForm()
        {
            InitializeComponent();
        }

        public void debugLog(string message)
        {
            string messageWithNewLine = message + "\n";
            debugOutputBox.AppendText(messageWithNewLine);
            debugOutputBox.ScrollToCaret();
        }

        private void radioButton_CheckedChanged(object sender, EventArgs e)
        {
            if (((RadioButton)sender).Checked)
            {
                stimulationToSend = UInt32.Parse(((RadioButton)sender).Text);
            }
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
            if (parentForm.selectedUsbDevice != null)
            {
                status = this.mea.Connect(parentForm.selectedUsbDevice, 63);
                if (status == 0)
                {
                    debugLog("Connected!");
                }
                else
                {
                    debugLog("Connection ERROR: " + CMcsUsbNet.GetErrorText(status));
                }
            }
            else
            {
                debugLog("ERROR: No USB device selected");
            }
        }

        private void Button2_Click(object sender, EventArgs e)
        {
            string meaConnectionStatus = this.mea.IsConnected() ? "CONNECTED" : "DISCONNECTED";
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
                DataModeEnumNet meaDataMode = this.mea.GetDataMode(0);

                int analogChannels, digitalChannels, checksumChannels, timestampChannels, channelsInBlock;
                this.mea.GetChannelLayout(out analogChannels, out digitalChannels, out checksumChannels, out timestampChannels, out channelsInBlock, 0);

                debugLog("\tSamplerate: " + meaSamplerate.ToString());
                debugLog("\tData Mode: " + meaDataMode.ToString());
                debugLog(String.Format("\tChannels: A{0} D{1} C{2} T{3} B{4}", analogChannels, digitalChannels, checksumChannels, timestampChannels, channelsInBlock));
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

        private void Read9A80RegisterButton_Click(object sender, EventArgs e)
        {
            try
            {
                uint value = this.mea.ReadRegister(0x9A80);
                debugLog("Value in 0x9A80 register: " + value.ToString("X"));
            } catch (Exception ex)
            {
                debugLog("Exception caught: " + ex.ToString());
            }
        }

        private void Write9A80RegisterButton_Click(object sender, EventArgs e)
        {
            try
            {
                uint value = stimulationToSend == 0 ? 0 : 0x1000 * (stimulationToSend - 1) + 0x100;
                debugLog(String.Format("Sending {0:X} to 0x9A80", value));
                this.mea.WriteRegister(0x9A80, value);
            } catch (Exception ex)
            {
                debugLog("Exception caught: " + ex.ToString());
            }
        }

        private void GetHeadstageSamplingButton_Click(object sender, EventArgs e)
        {
            if (parentForm.selectedUsbDevice == null)
            {
                debugLog("No USB device selected!");
            }
            else
            {
                try
                {
                    int receiver = 0;
                    if (((CMcsUsbListEntryNet)parentForm.selectedUsbDevice).SerialNumber.EndsWith("-B"))
                    {
                        receiver = 4; // bit 0/1 select the timeslot of: bit 2/3 = 0 receiver according to USB port, 1 receiver A, 2 receiver B
                    }
                    CW2100_FunctionNet func = new CW2100_FunctionNet(this.mea);
                    bool receiverSamplingActive = func.GetHeadstageSamplingActive(receiver + 0);
                    debugLog(String.Format("Receiver {0}: Sampling {1}", parentForm.selectedUsbDevice.SerialNumber, receiverSamplingActive ? "ACTIVE" : "INACTIVE"));
                }
                catch (Exception ex)
                {
                    debugLog("Exception caught: " + ex.ToString());
                }
            }
        }

        private void HeadstageSamplingOnButton_Click(object sender, EventArgs e)
        {
            if (parentForm.selectedUsbDevice == null)
            {
                debugLog("No USB device selected!");
            }
            else
            {
                try
                {
                    int receiver = 0;
                    if (((CMcsUsbListEntryNet)parentForm.selectedUsbDevice).SerialNumber.EndsWith("-B"))
                    {
                        receiver = 4; // bit 0/1 select the timeslot of: bit 2/3 = 0 receiver according to USB port, 1 receiver A, 2 receiver B
                    }
                    CW2100_FunctionNet func = new CW2100_FunctionNet(this.mea);
                    func.SetHeadstageSamplingActive(true, receiver + 0);
                    debugLog("**Set HS Sampling Active");
                }
                catch (Exception ex)
                {
                    debugLog("Exception caught: " + ex.ToString());
                }
            }
        }

        private void HeadstageSamplingOffButton_Click(object sender, EventArgs e)
        {
            if (parentForm.selectedUsbDevice == null)
            {
                debugLog("No USB device selected!");
            }
            else
            {
                try
                {
                    int receiver = 0;
                    if (((CMcsUsbListEntryNet)parentForm.selectedUsbDevice).SerialNumber.EndsWith("-B"))
                    {
                        receiver = 4; // bit 0/1 select the timeslot of: bit 2/3 = 0 receiver according to USB port, 1 receiver A, 2 receiver B
                    }
                    CW2100_FunctionNet func = new CW2100_FunctionNet(this.mea);
                    func.SetHeadstageSamplingActive(false, receiver + 0);
                    debugLog("**Set HS Sampling Inactive");
                }
                catch (Exception ex)
                {
                    debugLog("Exception caught: " + ex.ToString());
                }
            }
        }
    }
}
