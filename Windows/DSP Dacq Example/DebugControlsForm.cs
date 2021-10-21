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
using System.Diagnostics;

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

        public void debugLog(string message, bool ignoreNewline = false)
        {
            string messageWithNewLine = "";
            if (ignoreNewline)
                messageWithNewLine = message;
            else
                messageWithNewLine = message + "\n";
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

        private void UploadStimParamsButton_Click(object sender, EventArgs e)
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
                    int preplegth = 0;
                    CW2100_StimulatorFunctionNet stim = new CW2100_StimulatorFunctionNet(mea);
                    stim.SelectTimeSlot(receiver + 0);
                    debugLog("Selected TimeSlot: " + stim.GetTimeSlot().ToString());

                    int[] ampl = new[] { 10000, -10000, 0 };
                    ulong[] dur = new ulong[] { 80, 80, 7600 };

                    int maxAmplitude = 1000 * Int32.Parse(MaxAmplitudeTextBox.Text);
                    int amplitudeDelta = (int)(maxAmplitude / 16);

                    debugLog("Max amplitude: " + maxAmplitude.ToString() + "nA");
                    debugLog("Amplitude delta: " + amplitudeDelta.ToString() + "nA");
                    // Define each pulse
                    for (int i = 0; i < 16; i++)
                    {
                        // Define the amplitude (nA) of each of the 3 segments
                        ampl[0] = amplitudeDelta * (i + 1);
                        ampl[1] = -amplitudeDelta * (i + 1);

                        // Define the duration (us) of each of the 3 segments
                        dur[0] = (ulong) Convert.ToUInt64(PulseWidthTextBox.Text);
                        dur[1] = (ulong) Convert.ToUInt64(PulseWidthTextBox.Text);
                        dur[2] = (ulong) Convert.ToUInt64(PauseWidthTextBox.Text);

                        debugLog("Amplitude:" + String.Join(", ", ampl.Select(p => p.ToString()).ToArray()));
                        debugLog("Duration:" + String.Join(", ", dur.Select(p => p.ToString()).ToArray()));
                        
                        // Define the associated pulse
                        CStimulusFunctionNet.StimulusDeviceDataAndUnrolledData prep = stim.PrepareData(0, ampl, dur, STG_DestinationEnumNet.channeldata_current, 1);
                        debugLog(String.Format("Storing pulse {0} into memory...", i), true);
                        // Check the available memory in the headstage  
                        if (i == 0)
                        {
                            preplegth = prep.DeviceDataLength;
                        }

                        // Check that the pulse fits into the designated memory
                        Debug.Assert(preplegth == prep.DeviceDataLength);
                        Debug.Assert(prep.DeviceDataLength <= 15);

                        // Store pulse into designated memory
                        stim.SendPreparedData(0x10 * i + 0, prep, STG_DestinationEnumNet.channeldata_current);
                        debugLog("OK");
                    }
                }
                catch (Exception ex)
                {
                    debugLog("Exception caught: " + ex.ToString());
                }
            }
        }
    }
}
