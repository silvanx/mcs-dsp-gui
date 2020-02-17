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

        const int TotalChannels = Channels + Checksum;

        int Samplerate = 50000;

        CMcsUsbListNet UsbDeviceList = new CMcsUsbListNet();
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
            for (int i = 0; i < Channels; i++)
            {
                Text = "Channel "+(i+1).ToString();
                series0Channel.Items.Add(Text);
                series1Channel.Items.Add(Text);
                series2Channel.Items.Add(Text);
                series3Channel.Items.Add(Text);
            }
            for (int i = 0; i < Checksum; i++)
            {
                Text = "Checksum " + (i+1).ToString();
                series0Channel.Items.Add(Text);
                series1Channel.Items.Add(Text);
                series2Channel.Items.Add(Text);
                series3Channel.Items.Add(Text);
            }
            series0Channel.SelectedIndex = 0;
            series1Channel.SelectedIndex = 1;
            series2Channel.SelectedIndex = 2;
            series3Channel.SelectedIndex = 3;

            dataSource.Items.Add("Raw Data");
            dataSource.Items.Add("DSP Data");
            dataSource.SelectedIndex = 0;

        }

        private void RefreshDeviceList()
        {
            UsbDeviceList.Initialize(DeviceEnumNet.MCS_DEVICE_USB);
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

            if (mea.Connect((CMcsUsbListEntryNet)cbDeviceList.SelectedItem) == 0)
            {
                int ChannelsInBlock;

                mea.SetDataMode(DataModeEnumNet.dmSigned32bit, 0);
                if (mea.GetDeviceId().IdProduct == ProductIdEnumNet.W2100)
                {
                    Samplerate = 10000;
                }
                if (dataSource.SelectedIndex == 0)
                {
                    mea.SetNumberOfAnalogChannels(Channels, 0, 0, 0, 0); // Read raw data
                }
                else
                {
                    mea.SetNumberOfAnalogChannels(0, 0, Channels, 0, 0); // Read Data from DSP
                }
                mea.SetSampleRate(Samplerate, 1, 0);

                mea.EnableDigitalIn(false, 0);
                mea.EnableChecksum(true, 0);
                ChannelsInBlock = mea.GetChannelsInBlock();

                mea.GetChannelLayout(out int ana, out int digi, out int checksum, out int tim, out int cheb, 0);
                mea.SetSelectedData(TotalChannels, Samplerate * 10, Samplerate, SampleSizeNet.SampleSize32Signed, ChannelsInBlock);
                mea.StartDacq();
                if (mea.GetDeviceId().IdProduct == ProductIdEnumNet.W2100)
                {
                    CW2100_StimulatorFunctionNet stim = new CW2100_StimulatorFunctionNet(mea);
                    int[] ampl = new[] {0, -100000, 100000, 0, 3};
                    ulong[] dur = new ulong[] {0, 1000, 1000, 2000, 0};
                    CStimulusFunctionNet.StimulusDeviceDataAndUnrolledData prep = stim.PrepareData(0, ampl, dur, STG_DestinationEnumNet.channeldata_current, 0);
                    stim.SendPreparedData(0, prep, STG_DestinationEnumNet.channeldata_current);
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
            for (int i = 0; i < Samplerate; i += 10)
            {
                dspData.Series[0].Points.AddXY((double)i / Samplerate, data[i * TotalChannels + series0Channel.SelectedIndex]);
                dspData.Series[1].Points.AddXY((double)i / Samplerate, data[i * TotalChannels + series1Channel.SelectedIndex]);
                dspData.Series[2].Points.AddXY((double)i / Samplerate, data[i * TotalChannels + series2Channel.SelectedIndex]);
                dspData.Series[3].Points.AddXY((double)i / Samplerate, data[i * TotalChannels + series3Channel.SelectedIndex]);
            }
        }

        private void btTrigger_Click(object sender, EventArgs e)
        {
            if (mea.GetDeviceId().IdProduct == ProductIdEnumNet.W2100)
            {
                CW2100_StimulatorFunctionNet stim = new CW2100_StimulatorFunctionNet(mea);
                stim.SendStart(1);
            }
        }
    }
}
