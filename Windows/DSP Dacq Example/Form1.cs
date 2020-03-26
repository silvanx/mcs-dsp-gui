using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Threading;
using System.Diagnostics;
using System.Runtime.CompilerServices;
using Mcs.Usb;

namespace MCS_USB_Windows_Forms_Application1
{
    public partial class Form1 : Form
    {
        const int Channels = 64;
        const int Checksum = 2;

        private bool use_digital_in = true;

        private int TotalChannels = 0;

        int Samplerate = 50000;

        CMcsUsbListNet UsbDeviceList = new CMcsUsbListNet(DeviceEnumNet.MCS_DEVICE_USB);
        CMeaUSBDeviceNet mea = new CMeaUSBDeviceNet();

        public Form1()
        {
            InitializeComponent();
            RefreshDeviceList();
            InitDialog();

            startDacq.Enabled = true;
            stopDacq.Enabled = false;

            mea.ChannelDataEvent += new OnChannelData(mea_ChannelDataEvent);
        }

        void InitDialog()
        {
            string text;
            for (int i = 0; i < Channels; i++)
            {
                text = "Channel " + (i + 1).ToString();
                series0Channel.Items.Add(text);
                series1Channel.Items.Add(text);
                series2Channel.Items.Add(text);
                series3Channel.Items.Add(text);
            }

            for (int i = 0; i < Channels; i++)
            {
                text = "DSP " + (i + 1).ToString();
                series0Channel.Items.Add(text);
                series1Channel.Items.Add(text);
                series2Channel.Items.Add(text);
                series3Channel.Items.Add(text);
            }

            if (use_digital_in)
            {
                text = "Digital In";
                series0Channel.Items.Add(text);
                series1Channel.Items.Add(text);
                series2Channel.Items.Add(text);
                series3Channel.Items.Add(text);
            }

            for (int i = 0; i < Checksum; i++)
            {
                text = "Checksum " + (i+1).ToString();
                series0Channel.Items.Add(text);
                series1Channel.Items.Add(text);
                series2Channel.Items.Add(text);
                series3Channel.Items.Add(text);
            }
            series0Channel.SelectedIndex = 0;
            series1Channel.SelectedIndex = 1;
            series2Channel.SelectedIndex = 2;
            series3Channel.SelectedIndex = 3;

            dataSource.Items.Add("Raw Data");
            dataSource.Items.Add("DSP Data");
            dataSource.SelectedIndex = 0;

            for (int i = 0; i < 16; i++)
            {
                cbTriggerSegment.Items.Add(i);
            }

            cbTriggerSegment.SelectedIndex = 0;

        }

        private void RefreshDeviceList()
        {
            cbDeviceList.Items.Clear();
            for (uint i = 0; i < UsbDeviceList.Count; i++)
            {
                cbDeviceList.Items.Add(UsbDeviceList.GetUsbListEntry(i));
            }
            if (cbDeviceList.Items.Count > 0)
            {
                cbDeviceList.SelectedIndex = 0;
            }
        }

        private void btnRefresh_Click(object sender, EventArgs e)
        {
            RefreshDeviceList();
        }

        private void btnConnect_Click(object sender, EventArgs e)
        {
            CMcsUsbNet device = new CMcsUsbNet();
            if (device.Connect((CMcsUsbListEntryNet)cbDeviceList.SelectedItem, 2) == 0)
            {
                serialNumber.Text = device.GetSerialNumber();
                device.WriteRegister(0x8200, 0x8000+100);
                device.Disconnect();
            }
            else
            {
                serialNumber.Text = "device is locked 2";
            }
        }

        private void startDacq_Click(object sender, EventArgs e)
        {
            startDacq.Enabled = false;
            stopDacq.Enabled = true;

            if (mea.Connect((CMcsUsbListEntryNet) cbDeviceList.SelectedItem) == 0)
            {
                int ChannelsInBlock;

                mea.SetDataMode(DataModeEnumNet.Signed_32bit, 0);
                if (mea.GetDeviceId().IdProduct == ProductIdEnumNet.W2100)
                {
                    mea.SetDataMode(DataModeEnumNet.Signed_16bit, 0);
                    Samplerate = 20000;
                }
                else
                {
                    mea.SetDataMode(DataModeEnumNet.Signed_32bit, 0);
                }
#if false
                if (dataSource.SelectedIndex == 0)
                {
                    mea.SetNumberOfAnalogChannels(Channels, 0, 0, 0, 0); // Read raw data
                }
                else
                {
                    mea.SetNumberOfAnalogChannels(0, 0, Channels, 0, 0); // Read Data from DSP
                }
#endif
                mea.SetNumberOfAnalogChannels(Channels, 0, Channels, 0, 0); // Read raw data

                mea.SetSamplerate(Samplerate, 1, 0);

                mea.EnableDigitalIn(use_digital_in, 0);

                // map feedback bit 0 to digital(in) stream bit 4
                mea.SetDigitalSource(DigitalTargetEnumNet.Digstream, 4, W2100DigitalSourceEnumNet.Feedback, 0);

                mea.EnableChecksum(true, 0);
                ChannelsInBlock = mea.GetChannelsInBlock(0);

                mea.GetChannelLayout(out int analogChannels, out int digitalChannels, out int checksumChannels, out int timestampChannels, out int channelsInBlock, 0);
                if (mea.GetDeviceId().IdProduct == ProductIdEnumNet.W2100)
                {
                    TotalChannels = channelsInBlock;
                    mea.SetSelectedData(TotalChannels, Samplerate * 10, Samplerate, SampleSizeNet.SampleSize16Signed, SampleDstSizeNet.SampleDstSize32, ChannelsInBlock);
                }
                else
                {
                    TotalChannels = channelsInBlock / 2;
                    mea.SetSelectedData(TotalChannels, Samplerate * 10, Samplerate, SampleSizeNet.SampleSize32Signed, ChannelsInBlock);
                }

                mea.ChannelBlock_SetCheckChecksum((uint)checksumChannels, (uint)timestampChannels);
                mea.StartDacq();
                if (mea.GetDeviceId().IdProduct == ProductIdEnumNet.W2100)
                {
#if true
                    // Send Stimulation pattern
                    bool first = true;
                    int preplegth = 0;
                    CW2100_StimulatorFunctionNet stim = new CW2100_StimulatorFunctionNet(mea);
#if false
                    int[] ampl = new[] {0, 1000000, -1000000, 0, 6};
                    ulong[] dur = new ulong[] {0, 10000, 10000, 10000, 0};
                    for (int i = 0; i < 16; i++)
                    {
                        ampl[4] = i + 2;
#else
                    int[] ampl = new[] { 1000000, -1000000, 0 };
                    ulong[] dur = new ulong[] { 10000, 10000, 10000 };
                    for (int i = 0; i < 16; i++)
                    {
                        ampl[0] = 100000 * i + 100000;
                        ampl[1] = -100000 * i - 100000;

#endif
                        CStimulusFunctionNet.StimulusDeviceDataAndUnrolledData prep = stim.PrepareData(0, ampl, dur, STG_DestinationEnumNet.channeldata_current, 0);
                        if (first)
                        {
                            first = false;
                            preplegth = prep.DeviceDataLength;
                        }

                        Debug.Assert(preplegth == prep.DeviceDataLength);
                        Debug.Assert(prep.DeviceDataLength < 15);
                        stim.SendPreparedData(0x10 * i + 0, prep, STG_DestinationEnumNet.channeldata_current);
                    }

                    // switch the headstage to segmented mode
                    mea.WriteRegisterTimeSlot(0x93B5, 0x4F, 0);
                    mea.WriteRegisterTimeSlot(0x93B6, 1, 0);
#endif
                    CW2100_FunctionNet func = new CW2100_FunctionNet(mea);
                    func.SetHeadstageSamplingActive(true, 0);
                }
            }
        }

        private void stopDacq_Click(object sender, EventArgs e)
        {
            if (mea.GetDeviceId().IdProduct == ProductIdEnumNet.W2100)
            {
                CW2100_FunctionNet func = new CW2100_FunctionNet(mea);
                func.SetHeadstageSamplingActive(false, 0);
            }

            startDacq.Enabled = true;
            stopDacq.Enabled = false;

            mea.StopDacq();
            mea.Disconnect();
        }

        void mea_ChannelDataEvent(CMcsUsbDacqNet dacq, int CbHandle, int numFrames)
        {
            Debug.WriteLine("data available " + numFrames);

            if (numFrames >= Samplerate)
            {
                int[] data = mea.ChannelBlock_ReadFramesI32(0, Samplerate, out int frames_read);
                BeginInvoke(new DisplayDataAction(DisplayData), data);
            }
            else
            {
                int[] data = mea.ChannelBlock_ReadFramesI32(0, numFrames, out int frames_read);
            }
        }

        delegate void DisplayDataAction(int[] data);

        void DisplayData(int[] data)
        {
            dspData.Series[0].Points.Clear();
            dspData.Series[1].Points.Clear();
            dspData.Series[2].Points.Clear();
            dspData.Series[3].Points.Clear();


            // the chart can not handle every datapoint
            for (int i = 0; i < Samplerate; i += 1) // show each data point
            //for (int i = 0; i < Samplerate / 100; i += 1) // show only 1/10 data points
            //for (int i = 0; i < Samplerate; i += 10) // show only each 10th data points
            {
                dspData.Series[0].Points.AddXY((double)i / Samplerate, data[i * TotalChannels + series0Channel.SelectedIndex]);
                dspData.Series[1].Points.AddXY((double)i / Samplerate, data[i * TotalChannels + series1Channel.SelectedIndex]);
                dspData.Series[2].Points.AddXY((double)i / Samplerate, data[i * TotalChannels + series2Channel.SelectedIndex]);
                dspData.Series[3].Points.AddXY((double)i / Samplerate, data[i * TotalChannels + series3Channel.SelectedIndex]);
            }
        }

        private void btTrigger_Click(object sender, EventArgs e)
        {
            int segment = cbTriggerSegment.SelectedIndex;

            if (mea.GetDeviceId().IdProduct == ProductIdEnumNet.W2100)
            {
                CW2100_StimulatorFunctionNet stim = new CW2100_StimulatorFunctionNet(mea);
                stim.SendStart((uint)((segment << 4) + 1));
            }
        }
    }
}
