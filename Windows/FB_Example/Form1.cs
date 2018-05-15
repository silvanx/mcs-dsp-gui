using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using Mcs.Usb; // saves you from having to add UsbNetDll in front of all class names in the MCS provided dll

namespace my_interface
{
    public partial class Form1 : Form
    {
        CMcsUsbListEntryNet RawPort;
        CMcsUsbListEntryNet DspPort;

        CMcsUsbListNet devices = new CMcsUsbListNet(); // Create object of CMscUsbListNet Class

        int Fs = 50000; // sampling rate

        const uint LockMask = 64;

        public Form1()
        {
            InitializeComponent();

            devices.DeviceArrival += new OnDeviceArrivalRemoval(devices_DeviceArrival);
            devices.DeviceRemoval += new OnDeviceArrivalRemoval(devices_DeviceRemoval);

            SearchDevice();
        }

        void devices_DeviceRemoval(CMcsUsbListEntryNet entry)
        {
            SearchDevice();
        }

        void devices_DeviceArrival(CMcsUsbListEntryNet entry)
        {
            SearchDevice();
        }

        private void SearchDevice()
        {
            devices.Initialize(DeviceEnumNet.MCS_MEAUSB_DEVICE); // Get list of MEA devices connect by USB

            RawPort = null;
            DspPort = null;

            rawSerial.Text = "not found";
            dspSerial.Text = "not found";

            
            for (uint i = 0; i < devices.Count; i++) // loop through number of devices found
            {
                if (devices.GetUsbListEntry(i).SerialNumber.EndsWith("A")) // check for each device if serial number ends with "A" (USB 1) This USB interface will be used by MC_Rack
                {
                    RawPort = devices.GetUsbListEntry(i); // assign to RawPort "handle"
                    rawSerial.Text = RawPort.SerialNumber;
                }
                if (devices.GetUsbListEntry(i).SerialNumber.EndsWith("B"))// check for each device if serial number ends with "B" (USB 2) This USB interface will be used to control DSP
                {
                    DspPort = devices.GetUsbListEntry(i);  // assign to DSPPort "handle"
                    dspSerial.Text = DspPort.SerialNumber;
                }
            }

            if (RawPort != null && DspPort != null)
            {
                btnDeviceOK.BackColor = Color.LawnGreen;
            }
            else if (RawPort != null || DspPort != null)
            {
                btnDeviceOK.BackColor = Color.Yellow;
            }
            else
            {
                btnDeviceOK.BackColor = Color.Red;
            }

            // Set Filters
            CMcsUsbFactoryNet factorydev = new CMcsUsbFactoryNet(); // Create object of class CMcsUsbFactoryNet (provides firmware upgrade and register access capabilities)
            if (DspPort != null && factorydev.Connect(DspPort, LockMask) == 0)  // if connect call returns zero, connect has been successful
            {
#if false
                double[] xcoeffs;
                double[] ycoeffs;
                mkfilterNet.mkfilter("Bu", 0, "Lp", 2, 1000.0 / 50000.0, 0, out xcoeffs, out ycoeffs);
                factorydev.WriteRegister(0x600, DoubleToFixedInt(1, 16, 30, xcoeffs[0])); // set b[0] fpr 100 Hz HP
                factorydev.WriteRegister(0x608, DoubleToFixedInt(1, 15, 30, xcoeffs[1])); // set b[1] fpr 100 Hz HP
                factorydev.WriteRegister(0x60C, DoubleToFixedInt(1, 30, 30, ycoeffs[1])); // set a[1] fpr 100 Hz HP
                factorydev.WriteRegister(0x610, DoubleToFixedInt(1, 16, 30, xcoeffs[2])); // set b[2] fpr 100 Hz HP
                factorydev.WriteRegister(0x614, DoubleToFixedInt(1, 30, 30, ycoeffs[2])); // set a[2] fpr 100 Hz HP
                factorydev.WriteRegister(0x61C, 0x00000001); // enable
                mkfilterNet.mkfilter("Bu", 0, "Hp", 2, 100.0 / 50000.0, 0, out xcoeffs, out ycoeffs);
                factorydev.WriteRegister(0x620, DoubleToFixedInt(1, 16, 30, xcoeffs[0])); // set b[0] fpr 100 Hz HP
                factorydev.WriteRegister(0x628, DoubleToFixedInt(1, 15, 30, xcoeffs[1])); // set b[1] fpr 100 Hz HP
                factorydev.WriteRegister(0x62C, DoubleToFixedInt(1, 30, 30, ycoeffs[1])); // set a[1] fpr 100 Hz HP
                factorydev.WriteRegister(0x630, DoubleToFixedInt(1, 16, 30, xcoeffs[2])); // set b[2] fpr 100 Hz HP
                factorydev.WriteRegister(0x634, DoubleToFixedInt(1, 30, 30, ycoeffs[2])); // set a[2] fpr 100 Hz HP
                factorydev.WriteRegister(0x63C, 0x00000001); // enable
#endif
                factorydev.Disconnect();
            }
        }

        static uint DoubleToFixedInt(int vk, int nk, int commaPos, double valF)
        {
            valF *= 1 << nk;
            if (valF > 0)
            {
                valF += 0.5;
            }
            else
            {
                valF -= 0.5;
            }
            ulong mask = ((ulong)1 << (vk + nk + 1)) -1;
            ulong val = (ulong)valF;
            uint value = (uint)(val & mask);
            if (commaPos > nk)
            {
                value = value << (commaPos - nk);
            }

            return value;
        }


        private void ConnectMEA_Click(object sender, EventArgs e)
        {
            CMcsUsbFactoryNet factorydev = new CMcsUsbFactoryNet(); // Create object of class CMcsUsbFactoryNet (provides firmware upgrade and register access capabilities)

            if (factorydev.Connect(DspPort, LockMask) == 0)  // if connect call returns zero, connect has been successful
            {
                //int Thresh = (int)(Convert.ToDouble(SpikeThresh.Text) / (5000000 / Math.Pow(2, 24) / 10)); // 5 V input range ADC, 24bit ADC, 10 volt hardware gain
                int Thresh = (int)(Convert.ToInt64(SpikeThresh.Text) * 8388608 / 2500);
                int DeadTime = Convert.ToInt32(Deadtime.Text) * Fs / 1000;

                int StimAmplitude = 2 * Convert.ToInt32(BoxStimAmplitude.Text); // resolution is 500 uV / bit, thus factor allows user to specify stim amplitude in mV
                int StimPeriod = Fs / Convert.ToInt32(BoxStimPeriod.Text);
                int StimRepeats = Convert.ToInt32(BoxStimRepeats.Text);
                int StimStepsize = 2 * Convert.ToInt32(BoxStimStepsize.Text); // resolution is 500 uV / bit, thus factor allows user to specify stim amplitude in mV

                factorydev.WriteRegister(0x1000, (uint)Thresh);
                factorydev.WriteRegister(0x1004, (uint)DeadTime);
                factorydev.WriteRegister(0x1008, (uint)StimAmplitude);
                factorydev.WriteRegister(0x100c, (uint)StimPeriod);
                factorydev.WriteRegister(0x1010, (uint)StimRepeats);
                factorydev.WriteRegister(0x1014, (uint)StimStepsize);

                factorydev.Disconnect();
            }
        }

        private void UploadDSPBinary_Click(object sender, EventArgs e)
        {
            CMcsUsbFactoryNet factorydev = new CMcsUsbFactoryNet();

            string FirmwareFile;
            FirmwareFile = System.IO.Path.GetDirectoryName(System.Reflection.Assembly.GetExecutingAssembly().Location);
            FirmwareFile += @"\..\..\..\..\DSP\FB_Example\Release\";
            FirmwareFile += "FB_Example.bin";

            factorydev.LoadUserFirmware(FirmwareFile, DspPort);           // Code for uploading compiled binary
        }

        private void StopDSP_Click(object sender, EventArgs e)
        {
            CMcsUsbFactoryNet factorydev = new CMcsUsbFactoryNet(); // Create object of class CMcsUsbFactoryNet (provides firmware upgrade and register access capabilities)

            if (factorydev.Connect(DspPort, LockMask) == 0)  // if connect call returns zero, connect has been successful
            {
                factorydev.Coldstart(CFirmwareDestinationNet.MCU1);
                factorydev.Disconnect();
            }
        }
    }
}
