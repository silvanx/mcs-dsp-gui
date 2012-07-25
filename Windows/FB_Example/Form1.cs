using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using UsbNetDll; // saves you from having to add UsbNetDll in front of all class names in the MCS provided dll

namespace my_interface
{
    public partial class Form1 : Form
    {

        CMcsUsbListEntryNet RawPort;
        CMcsUsbListEntryNet DspPort;
        CMcsUsbListEntryNet AnyPort;
        int Fs = 50000; // sampling rate

        public Form1()
        {
            InitializeComponent();


            CMcsUsbListNet devices = new CMcsUsbListNet(); // Create object of CMscUsbListNet Class
            devices.Initialize(DeviceEnumNet.MCS_MEAUSB_DEVICE); // Get list of MEA devices connect by USB

            for (uint i = 0; i < devices.GetDeviceNumber(); i++) // loop through number of devices found
            {
                if (devices.GetSerialNumber(i).EndsWith("A")) // check for each device if serial number ends with "A" (USB 1) This USB interface will be used by MC_Rack
                {
                    RawPort = devices.GetUsbListEntry(i); // assign to RawPort "handle"
                }
                if (devices.GetSerialNumber(i).EndsWith("B"))// check for each device if serial number ends with "B" (USB 2) This USB interface will be used to control DSP
                {
                    DspPort = devices.GetUsbListEntry(i);  // assign to DSPPort "handle"
                }

            }

            // Set Filters
            CMcsUsbFactoryNet factorydev = new CMcsUsbFactoryNet(); // Create object of class CMcsUsbFactoryNet (provides firmware upgrade and register access capabilities)
            if (factorydev.Connect(DspPort) == 0)  // if connect call returns zero, connect has been successful
            {
                factorydev.Mea21WriteRegister(0x8620, 0x0000FE67); // set b[0] fpr 100 Hz HP
                factorydev.Mea21WriteRegister(0x8628, 0x00030199); // set b[1] fpr 100 Hz HP
                factorydev.Mea21WriteRegister(0x862C, 0x00030332); // set a[1] fpr 100 Hz HP
                factorydev.Mea21WriteRegister(0x8630, 0x00000000); // set b[2] fpr 100 Hz HP
                factorydev.Mea21WriteRegister(0x8634, 0x00000000); // set a[2] fpr 100 Hz HP
                factorydev.Disconnect();
            }


        }

        private void ConnectMEA_Click(object sender, EventArgs e)
        {


            CMcsUsbFactoryNet factorydev = new CMcsUsbFactoryNet(); // Create object of class CMcsUsbFactoryNet (provides firmware upgrade and register access capabilities)

            if (factorydev.Connect(DspPort) == 0)  // if connect call returns zero, connect has been successful
            {
                for (int i = 0; i < 10; i++)
                {
                    factorydev.Mea21WriteRegister(0x002c, 0x707);
                    System.Threading.Thread.Sleep(500);
                    factorydev.Mea21WriteRegister(0x002c, 0x700);
                    System.Threading.Thread.Sleep(500);
                }

                factorydev.Disconnect();
            }


        }

        private void UploadDSPBinary_Click(object sender, EventArgs e)
        {

            CMcsUsbFactoryNet factorydev = new CMcsUsbFactoryNet();

            if (factorydev.Connect(DspPort) == 0)  // if connect call returns zero, connect has been successful
            {
                int Thresh = (int)(Convert.ToDouble(SpikeThresh.Text) / (5000000 / Math.Pow(2, 24) / 10)); // 5 V input range ADC, 24bit ADC, 10 volt hardware gain
                int DeadTime = Convert.ToInt32(Deadtime.Text) * Fs / 1000;

                int StimAmplitude = 2*Convert.ToInt32(BoxStimAmplitude.Text); // resolution is 500 uV / bit, thus factor allows user to specify stim amplitude in mV
                int StimPeriod = Fs / Convert.ToInt32(BoxStimPeriod.Text);
                int StimRepeats = Convert.ToInt32(BoxStimRepeats.Text);
                int StimStepsize = 2 * Convert.ToInt32(BoxStimStepsize.Text); // resolution is 500 uV / bit, thus factor allows user to specify stim amplitude in mV

                factorydev.Mea21WriteRegister(0x1000, (uint)Thresh);
                factorydev.Mea21WriteRegister(0x1004, (uint)DeadTime);
                factorydev.Mea21WriteRegister(0x1008, (uint)StimAmplitude);
                factorydev.Mea21WriteRegister(0x100c, (uint)StimPeriod);
                factorydev.Mea21WriteRegister(0x1010, (uint)StimRepeats);
                factorydev.Mea21WriteRegister(0x1014, (uint)StimStepsize);

                factorydev.Disconnect();
            }

            string FirmwareFile;
            FirmwareFile = System.IO.Path.GetDirectoryName(System.Reflection.Assembly.GetExecutingAssembly().Location);
            FirmwareFile += @"\..\..\..\..\TMS320C6454\FB_Example\Release\";
            FirmwareFile += "FB_Example.bin";

            factorydev.UpdateFirmware(FirmwareFile, DspPort, CFirmwareDestinationNet.MCU1, true); // DO NOT change this line of code unless you know what you do
            // Code for uploading compiled binary
        }

        private void button1_Click(object sender, EventArgs e)
        {

            CMcsUsbFactoryNet factorydev = new CMcsUsbFactoryNet(); // Create object of class CMcsUsbFactoryNet (provides firmware upgrade and register access capabilities)

            if (factorydev.Connect(DspPort) == 0)  // if connect call returns zero, connect has been successful
            {

                factorydev.Coldstart(CFirmwareDestinationNet.MCU1);
                factorydev.Disconnect();
            }


        }

    }
}
