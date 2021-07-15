using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Threading;
using System.Threading.Tasks;
using System.Diagnostics;
using System.IO;
using System.Runtime.CompilerServices;
using Mcs.Usb;

namespace MCS_USB_Windows_Forms_Application1
{
    public partial class Dacq : Form
    {
        CMcsUsbListEntryNet RawPort;
        CMcsUsbListEntryNet DspPort;

        const int Channels = 64;
        const int AnalogChannels = 8;
        const int Checksum = 2;

        private bool use_digital_in = true;

        private int TotalChannels = 0;

        const uint LockMask = 64;

        int Samplerate = 20000;

        int maxAmplitudeValue = 10;
        uint stimThresholdValue = 100000;
        float proportionalGain = 0;


        bool RandomStimOn = false;

        // for W2100
        private int other_receiver = 0;
        private bool w2100_hs_samling = false;


        CMcsUsbListNet UsbDeviceList = new CMcsUsbListNet(DeviceEnumNet.MCS_DEVICE_USB);
        CMeaUSBDeviceNet mea = new CMeaUSBDeviceNet();

        public Dacq()
        {
            InitializeComponent();
            UsbDeviceList.DeviceArrival += new OnDeviceArrivalRemoval(devices_DeviceArrival);
            UsbDeviceList.DeviceRemoval += new OnDeviceArrivalRemoval(devices_DeviceRemoval);
            SearchDevice();
            InitDialog();

            startDacq.Enabled = true;
            stopDacq.Enabled = false;

            mea.ChannelDataEvent += new OnChannelData(mea_ChannelDataEvent);
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
            RawPort = null;
            DspPort = null;

            rawSerial.Text = "not found";
            dspSerial.Text = "not found";

            cbDeviceList.Items.Clear();
            for (uint i = 0; i < UsbDeviceList.Count; i++) // loop through number of devices found
            {
                if (UsbDeviceList.GetUsbListEntry(i).SerialNumber.EndsWith("A")) // check for each device if serial number ends with "A" (USB 1) This USB interface will be used by MC_Rack / Multi Channel Experimenter
                {
                    RawPort = UsbDeviceList.GetUsbListEntry(i); // assign to RawPort "handle"
                    rawSerial.Text = RawPort.SerialNumber;
                }
                if (UsbDeviceList.GetUsbListEntry(i).SerialNumber.EndsWith("B"))// check for each device if serial number ends with "B" (USB 2) This USB interface will be used to control DSP
                {
                    DspPort = UsbDeviceList.GetUsbListEntry(i);  // assign to DSPPort "handle"
                    dspSerial.Text = DspPort.SerialNumber;
                }
                cbDeviceList.Items.Add(UsbDeviceList.GetUsbListEntry(i));
            }
            if (cbDeviceList.Items.Count > 0)
            {
                cbDeviceList.SelectedIndex = 1;
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
                //double[] xcoeffs;
                //double[] ycoeffs;
                //mkfilterNet.mkfilter("Bu", 0, "Lp", 2, 1000.0 / (float)Samplerate, 0, out xcoeffs, out ycoeffs);
                //factorydev.WriteRegister(0x600, DoubleToFixedInt(1, 16, 30, xcoeffs[0])); // set b[0] fpr 30 Hz LP
                //factorydev.WriteRegister(0x608, DoubleToFixedInt(1, 15, 30, xcoeffs[1])); // set b[1] fpr 30 Hz LP
                //factorydev.WriteRegister(0x60C, DoubleToFixedInt(1, 30, 30, ycoeffs[1])); // set a[1] fpr 30 Hz LP
                //factorydev.WriteRegister(0x610, DoubleToFixedInt(1, 16, 30, xcoeffs[2])); // set b[2] fpr 30 Hz LP
                //factorydev.WriteRegister(0x614, DoubleToFixedInt(1, 30, 30, ycoeffs[2])); // set a[2] fpr 30 Hz LP
                //factorydev.WriteRegister(0x61C, 0x00000001); // enable

                //mkfilterNet.mkfilter("Bu", 0, "Hp", 2, 1.0 / 50000.0, 0, out xcoeffs, out ycoeffs);
                //factorydev.WriteRegister(0x620, DoubleToFixedInt(1, 16, 30, xcoeffs[0])); // set b[0] fpr 100 Hz HP
                //factorydev.WriteRegister(0x628, DoubleToFixedInt(1, 15, 30, xcoeffs[1])); // set b[1] fpr 100 Hz HP
                //factorydev.WriteRegister(0x62C, DoubleToFixedInt(1, 30, 30, ycoeffs[1])); // set a[1] fpr 100 Hz HP
                //factorydev.WriteRegister(0x630, DoubleToFixedInt(1, 16, 30, xcoeffs[2])); // set b[2] fpr 100 Hz HP
                //factorydev.WriteRegister(0x634, DoubleToFixedInt(1, 30, 30, ycoeffs[2])); // set a[2] fpr 100 Hz HP
                //factorydev.WriteRegister(0x63C, 0x00000001); // enable

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
            ulong mask = ((ulong)1 << (vk + nk + 1)) - 1;
            ulong val = (ulong)valF;
            uint value = (uint)(val & mask);
            if (commaPos > nk)
            {
                value = value << (commaPos - nk);
            }

            return value;
        }

        void InitDialog()
        {
            string text;
            for (int i = 0; i < Channels; i++)
            {
                text = "Channel " + (i + 1).ToString();
                series0Channel.Items.Add(text);
                series1Channel.Items.Add(text);
            }

            for (int i = 0; i < AnalogChannels; i++)
            {
                text = "ANA " + (i + 1).ToString();
                series0Channel.Items.Add(text);
                series1Channel.Items.Add(text);
            }

            for (int i = 0; i < Channels; i++)
            {
                text = "DSP " + (i + 1).ToString();
                series0Channel.Items.Add(text);
                series1Channel.Items.Add(text);
            }

            if (use_digital_in)
            {
                text = "Digital In";
                series0Channel.Items.Add(text);
                series1Channel.Items.Add(text);
            }

            for (int i = 0; i < Checksum; i++)
            {
                text = "Checksum " + (i + 1).ToString();
                series0Channel.Items.Add(text);
                series1Channel.Items.Add(text);
            }

            series0Channel.SelectedIndex = 0;
            series1Channel.SelectedIndex = 1;

        }

        private void startDacq_Click(object sender, EventArgs e)
        {

            startDacq.Enabled = false;
            stopDacq.Enabled = true;
            SaveToFileCheckBox.Enabled = false;

            other_receiver = 0;
            if (((CMcsUsbListEntryNet) cbDeviceList.SelectedItem).SerialNumber.EndsWith("-B"))
            {
                other_receiver = 4; // bit 0/1 select the timeslot of: bit 2/3 = 0 receiver according to USB port, 1 receiver A, 2 receiver B
            }

            uint status = mea.Connect((CMcsUsbListEntryNet) cbDeviceList.SelectedItem, 63);
            if (status == 0)
            {
                int ChannelsInBlock;

                mea.SetDataMode(DataModeEnumNet.Signed_32bit, 0);
                //if (mea.GetDeviceId().IdProduct == ProductIdEnumNet.W2100)
                //{
                //    Samplerate = 20000;
                //}

                mea.SetNumberOfAnalogChannels(Channels, 0, Channels, AnalogChannels, 0); // Read raw data

                try
                {
                    mea.SetSamplerate(Samplerate, 1, 0);
                }
                catch (CUsbExceptionNet)
                {
                    Samplerate = mea.GetSamplerate(0);
                }

                mea.EnableDigitalIn((use_digital_in ? (DigitalDatastreamEnableEnumNet) 3 : 0), 0);

                // map feedback bit 0 to digital(in) stream bit 4
                mea.SetDigitalSource(DigitalTargetEnumNet.Digstream, 4, W2100DigitalSourceEnumNet.Feedback, 0);
                mea.SetDigitalSource(DigitalTargetEnumNet.Digout, 0, W2100DigitalSourceEnumNet.Feedback, 0);

                mea.EnableChecksum(true, 0);
                ChannelsInBlock = mea.GetChannelsInBlock(0);

                mea.GetChannelLayout(out int analogChannels, out int digitalChannels, out int checksumChannels, out int timestampChannels, out int channelsInBlock, 0);

                TotalChannels = channelsInBlock / 2;
                mea.SetSelectedData(TotalChannels, Samplerate * 10, Samplerate, SampleSizeNet.SampleSize32Signed, ChannelsInBlock);

                mea.ChannelBlock_SetCheckChecksum((uint) checksumChannels, (uint) timestampChannels);
                mea.StartDacq();
                if (mea.GetDeviceId().IdProduct == ProductIdEnumNet.W2100)
                {
                    CW2100_FunctionNet func = new CW2100_FunctionNet(mea);
                    w2100_hs_samling = func.GetHeadstageSamplingActive(other_receiver + 0);
                    func.SetHeadstageSamplingActive(true, other_receiver + 0);
                }
            }
            else
            {
                MessageBox.Show(CMcsUsbNet.GetErrorText(status));
                startDacq.Enabled = true;
                stopDacq.Enabled = false;
            }
        }

        private void stopDacq_Click(object sender, EventArgs e)
        {
            SaveToFileCheckBox.Enabled = true;
            if (mea.GetDeviceId().IdProduct == ProductIdEnumNet.W2100)
            {
                CW2100_FunctionNet func = new CW2100_FunctionNet(mea);
                if (!w2100_hs_samling)
                {
                    func.SetHeadstageSamplingActive(false, other_receiver + 0);
                }
            }

            startDacq.Enabled = true;
            stopDacq.Enabled = false;

            mea.StopDacq();
            mea.Disconnect();
        }

        private void SaveDataToFile(int[] data, string file, int numFrames)
        {
            if (SaveToFileCheckBox.Checked)
            {
                List<string> contents = new List<string>();
                for (int i = 0; i < numFrames; i += 1)
                {
                    List<string> row = new List<string>();
                    row.Add(data[i * TotalChannels + 0].ToString());
                    row.Add(data[i * TotalChannels + 1].ToString());
                    row.Add(data[i * TotalChannels + 2].ToString());
                    row.Add(data[i * TotalChannels + 3].ToString());
                    row.Add(data[i * TotalChannels + Channels + AnalogChannels + 0].ToString());
                    row.Add(data[i * TotalChannels + Channels + AnalogChannels + 1].ToString());
                    row.Add(data[i * TotalChannels + Channels + AnalogChannels + 2].ToString());
                    row.Add(data[i * TotalChannels + Channels + AnalogChannels + 3].ToString());
                    row.Add(data[i * TotalChannels + Channels + AnalogChannels + 4].ToString());
                    row.Add(data[i * TotalChannels + Channels + AnalogChannels + 5].ToString());
                    row.Add(data[i * TotalChannels + Channels + AnalogChannels + 6].ToString());
                    row.Add(data[i * TotalChannels + Channels + AnalogChannels + 7].ToString());
                    row.Add(data[i * TotalChannels + Channels + AnalogChannels + 8].ToString());
                    row.Add(data[i * TotalChannels + Channels + AnalogChannels + 9].ToString());
                    row.Add(data[i * TotalChannels + Channels + AnalogChannels + 10].ToString());
                    row.Add(data[i * TotalChannels + Channels + AnalogChannels + 11].ToString());
                    row.Add(data[i * TotalChannels + Channels + AnalogChannels + 12].ToString());
                    row.Add(data[i * TotalChannels + Channels + AnalogChannels + 13].ToString());
                    row.Add(data[i * TotalChannels + Channels + AnalogChannels + 14].ToString());
                    string rowString = string.Join(", ", row);
                    contents.Add(rowString);
                }
                File.AppendAllLines(file, contents);
            }
        }


        void mea_ChannelDataEvent(CMcsUsbDacqNet dacq, int CbHandle, int numFrames)
        {
            //Debug.WriteLine("data available " + numFrames);

            if (numFrames >= Samplerate)
            {
                int[] rawData = mea.ChannelBlock_ReadFramesI32(0, numFrames, out int frames_read);
                int[] data = new int[Samplerate * TotalChannels];
                Array.Copy(rawData, (numFrames - Samplerate) * TotalChannels, data, 0, Samplerate * TotalChannels);
                this.Invoke((MethodInvoker)delegate { SaveDataToFile(rawData, "data.txt", numFrames); });
                BeginInvoke(new DisplayDataAction(DisplayData), data);
                Thread.Sleep(250);
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

            double multiplierSeries0 = 1;
            double multiplierSeries1 = 1;

            if (DisplayInMicrovoltsChannel1.Checked) multiplierSeries0 = 0.381;
            if (DisplayInMicrovoltsChannel2.Checked) multiplierSeries1 = 0.381;

            int min = int.MaxValue;
            int max = int.MinValue;
            // the chart can not handle every datapoint
            //for (int i = 0; i < Samplerate; i += 1) // show each data point
            //for (int i = 0; i < Samplerate / 5; i += 20) // show only 1/10 data points
            for (int i = 0; i < Samplerate; i += 100) // show only each 100th data points
            {
                if (cbChart1.Checked) AddPoint(0, i, multiplierSeries0 * data[i * TotalChannels + series0Channel.SelectedIndex], ref min, ref max);
                if (cbChart2.Checked) AddPoint(1, i, multiplierSeries1 * data[i * TotalChannels + series1Channel.SelectedIndex], ref min, ref max);
            }

            if (!String.IsNullOrEmpty(minYChartInput.Text))
            {
                if (Int32.TryParse(minYChartInput.Text, out int minYValue))
                {
                    min = minYValue;
                }
            }
            
            if(!String.IsNullOrEmpty(maxYChartInput.Text))
            {
                if (Int32.TryParse(maxYChartInput.Text, out int maxYValue))
                {
                    max = maxYValue;
                }
            }

            if (min < max)
            {
                dspData.ChartAreas[0].AxisY.Minimum = min;
                dspData.ChartAreas[0].AxisY.Maximum = max;
            }
            else if (min == max)
            {
                dspData.ChartAreas[0].AxisY.Minimum = min - 5;
                dspData.ChartAreas[0].AxisY.Maximum = max + 5;
            }
        }

        private void AddPoint(int series, int i, int data, ref int min, ref int max)
        {
            dspData.Series[series].Points.AddXY((double) i / Samplerate, (double) data);
            if (data < min) min = data;
            if (data > max) max = data;
        }

        private void AddPoint(int series, int i, double data, ref int min, ref int max)
        {
            dspData.Series[series].Points.AddXY((double)i / Samplerate, data);
            if (data < min) min = (int) Math.Floor(data);
            if (data > max) max = (int) Math.Ceiling(data);
        }

        private void btResetSettings_Click(object sender, EventArgs e)
        {
            if (mea.Connect((CMcsUsbListEntryNet) cbDeviceList.SelectedItem) == 0)
            {
                if (mea.GetDeviceId().IdProduct == ProductIdEnumNet.W2100)
                {
                    mea.SetDataMode(DataModeEnumNet.Unsigned_16bit, 0);
                    mea.SetNumberOfAnalogChannels(32, 0, 0, AnalogChannels, 0); // Read raw data
                }

                mea.Disconnect();
            }
        }

        delegate void UploadDSBBinaryAction(CMcsUsbListEntryNet port);


        void UploadDSBBinary(CMcsUsbListEntryNet port)
        {
            // Define stimulation frequency and period
            int f_stim = 130;
            int T_stim = (int)((1.0 / f_stim) * 10E6);       // in us

            // Define on and off phases of stimulation pulse    (in us)
            int pulse_on_phase_dur = 60;
            int pulse_off_phase_dur = T_stim - 2 * pulse_on_phase_dur;

            // Define the upper and lower bounds for the controller output
            int MaxValue = maxAmplitudeValue * 1000;                //in nA
            const int MinValue = 0;                     //in nA

            // Define the step between pulses amplitude
            int delta_DBS_amp = (MaxValue - MinValue) / 16;    // in nA
#if true
            other_receiver = 0;
            if (((CMcsUsbListEntryNet)cbDeviceList.SelectedItem).SerialNumber.EndsWith("-B"))
            {
                other_receiver = 4; // bit 0/1 select the timeslot of: bit 2/3 = 0 receiver according to USB port, 1 receiver A, 2 receiver B
            }
            uint status = mea.Connect((CMcsUsbListEntryNet)cbDeviceList.SelectedItem, 63);
            if (status == 0 && mea.GetDeviceId().IdProduct == ProductIdEnumNet.W2100)
            {
                mea.SetDataMode(DataModeEnumNet.Signed_32bit, 0);

                mea.SetNumberOfAnalogChannels(Channels, 0, Channels, AnalogChannels, 0); // Read raw data

                try
                {
                    mea.SetSamplerate(Samplerate, 1, 0);
                }
                catch (CUsbExceptionNet)
                {
                    Samplerate = mea.GetSamplerate(0);
                }

                CW2100_FunctionNet func = new CW2100_FunctionNet(mea);
                w2100_hs_samling = func.GetHeadstageSamplingActive(other_receiver + 0);
                func.SetHeadstageSamplingActive(false, other_receiver + 0);

                // Send Stimulation pattern
                bool first = true;
                int preplegth = 0;
                CW2100_StimulatorFunctionNet stim = new CW2100_StimulatorFunctionNet(mea);
                stim.SelectTimeSlot(other_receiver + 0);
                // Different strength
                // Define the amplitude vector of the 3 segments of the biphasic pulse (in nA)
                int[] ampl = new[] { 10000, -10000, 0 };

                // Define the duraion vector of the 3 segments of the biphasic pulse (in us)
                ulong[] dur = new ulong[] { 100, 100, 7492 };

                // Define each pulse
                for (int i = 0; i < 16; i++)
                {
                    // Define the amplitude (nA) of each of the 3 segments
                    ampl[0] = delta_DBS_amp * (i + 1);
                    ampl[1] = -delta_DBS_amp * (i + 1);

                    // Define the duration (us) of each of the 3 segments
                    //dur[0] = (ulong)pulse_on_phase_dur;
                    //dur[1] = (ulong)pulse_on_phase_dur;
                    //dur[2] = (ulong)pulse_off_phase_dur;

                    // choose, if global repeat is desired
                    // Define the associated pulse
                    CStimulusFunctionNet.StimulusDeviceDataAndUnrolledData prep = stim.PrepareData(0, ampl, dur, STG_DestinationEnumNet.channeldata_current, 1);

                    // Check the available memory in the headstage  
                    if (first)
                    {
                        first = false;
                        preplegth = prep.DeviceDataLength;
                    }

                    // Check that the pulse fits into the designated memory
                    Debug.Assert(preplegth == prep.DeviceDataLength);
                    Debug.Assert(prep.DeviceDataLength <= 15);

                    // Store pulse into designated memory
                    stim.SendPreparedData(0x10 * i + 0, prep, STG_DestinationEnumNet.channeldata_current);
                }
                func.SetHeadstageSamplingActive(true, other_receiver + 0);
            }
            if (startDacq.Enabled)
            {
                mea.Disconnect();
            }            
#endif
            CMcsUsbFactoryNet factorydev = new CMcsUsbFactoryNet();
            if (factorydev.Connect(port, LockMask) == 0)
            {
                // uint stimThresholdDigits = (uint)Math.Floor((float)stimThresholdValue / 0.381);
                uint stimThresholdDigits = (uint)Math.Floor((float)stimThresholdValue);
                uint maxAmplitude = (uint)MaxValue;
                
                factorydev.WriteRegister(0x1000, stimThresholdDigits);
                factorydev.WriteRegister(0x1008, maxAmplitude);
                uint propGainModified = (uint)Math.Floor(proportionalGain * 1000);
                factorydev.WriteRegister(0x1018, propGainModified);

                string FirmwareFile;
                FirmwareFile = System.IO.Path.GetDirectoryName(System.Reflection.Assembly.GetExecutingAssembly().Location);
                FirmwareFile += @"\..\..\..\..\DSP\FB_W2100_SCU_MEA256\Release\";
                FirmwareFile += "FB_W2100_SCU_MEA256.bin";

                factorydev.Disconnect();

                bool success = factorydev.LoadUserFirmware(FirmwareFile, port, LockMask); // Code for uploading compiled binary
                if (!success)
                {
                    MessageBox.Show("Firmware upload failed!");
                }
            }
        }

        private void UploadDSPBinary_Click(object sender, EventArgs e)
        {
            if (! int.TryParse(MaxAmplitudeTextBox.Text, out maxAmplitudeValue))
            {
                MessageBox.Show("Max amplitude has to be an integer");
            }
            else if (maxAmplitudeValue > 300 || maxAmplitudeValue <= 0)
            {
                MessageBox.Show("Max amplitude has to be between 0 and 300 μA");
            }

            if (!uint.TryParse(StimThresholdTextBox.Text, out stimThresholdValue))
            {
                MessageBox.Show("Max amplitude has to be a positive integer");
            }
            else if (stimThresholdValue < 0)
            {
                MessageBox.Show("Stimulation threshold has to be positive");
            }

            if(! float.TryParse(ProportionalGainInput.Text, out proportionalGain))
            {
                MessageBox.Show("Proportional Gain should be a number with maximum 3 decimal places");
            }

            if (DspPort != null || RawPort != null)
            {
                CMcsUsbListEntryNet port = DspPort;
                if (port == null)
                {
                    port = RawPort;
                }
                BeginInvoke(new UploadDSBBinaryAction(UploadDSBBinary), port);
            }
            else
            {
                MessageBox.Show("No port available");
            }
        }

        private void StopDSP_Click(object sender, EventArgs e)
        {
            CMcsUsbFactoryNet factorydev = new CMcsUsbFactoryNet(); // Create object of class CMcsUsbFactoryNet (provides firmware upgrade and register access capabilities)

            if (DspPort != null || RawPort != null)
            {
                CMcsUsbListEntryNet port = DspPort;
                if (port == null)
                {
                    port = RawPort;
                }

                if (factorydev.Connect(port, LockMask) == 0) // if connect call returns zero, connect has been successful
                {
                    factorydev.Coldstart(CFirmwareDestinationNet.MCU1);
                    factorydev.WriteRegister(0x9A80, 0);
                    factorydev.Disconnect();
                }
            }
            else
            {
                MessageBox.Show("No port available");
            }
        }

        private void StartRandomStimButton_Click(object sender, EventArgs e)
        {
            if (!int.TryParse(MaxAmplitudeTextBox.Text, out maxAmplitudeValue))
            {
                MessageBox.Show("Max amplitude has to be an integer");
            }
            else if (maxAmplitudeValue > 300 || maxAmplitudeValue <= 0)
            {
                MessageBox.Show("Max amplitude has to be between 0 and 300 μA");
            }
            if (!int.TryParse(PercentageOnInputBox.Text, out int PercentageStimOn))
            {
                MessageBox.Show("Percentage has to be an integer");
            }
            else if (PercentageStimOn > 99 || PercentageStimOn < 0)
            {
                MessageBox.Show("Percentage has to be between 0 and 99");
            }

            if (DspPort != null || RawPort != null)
            {
                CMcsUsbListEntryNet port = DspPort;
                if (port == null)
                {
                    port = RawPort;
                }
                PercentageOnInputBox.Enabled = false;
                StopRandomStimButton.Enabled = true;
                Task.Run(() => RandomOnOffStimulation(port));
                //BeginInvoke(new RandomOnOffStimulationAction(RandomOnOffStimulation), port);
            }
            else
            {
                MessageBox.Show("No port available");
            }
        }

        delegate void RandomOnOffStimulationAction(CMcsUsbListEntryNet port);

        void RandomOnOffStimulation(CMcsUsbListEntryNet port)
        {
            int PercentageStimOn = Int32.Parse(PercentageOnInputBox.Text);

            // Define stimulation frequency and period
            int f_stim = 130;
            int T_stim = (int)((1.0 / f_stim) * 10E6);       // in us

            // Define on and off phases of stimulation pulse    (in us)
            int pulse_on_phase_dur = 60;
            int pulse_off_phase_dur = T_stim - 2 * pulse_on_phase_dur;

            // Define the upper and lower bounds for the controller output
            int MaxValue = maxAmplitudeValue * 1000;                //in nA
            const int MinValue = 0;                     //in nA

            // Define the step between pulses amplitude
            int delta_DBS_amp = (MaxValue - MinValue) / 16;    // in nA

            other_receiver = 0;
            if (port.SerialNumber.EndsWith("-B"))
            {
                other_receiver = 4; // bit 0/1 select the timeslot of: bit 2/3 = 0 receiver according to USB port, 1 receiver A, 2 receiver B
            }
            uint status = mea.Connect(port, 63);


            if (status == 0 && mea.GetDeviceId().IdProduct == ProductIdEnumNet.W2100)
            {
                mea.SetDataMode(DataModeEnumNet.Signed_32bit, 0);

                mea.SetNumberOfAnalogChannels(Channels, 0, Channels, AnalogChannels, 0); // Read raw data

                try
                {
                    mea.SetSamplerate(Samplerate, 1, 0);
                }
                catch (CUsbExceptionNet)
                {
                    Samplerate = mea.GetSamplerate(0);
                }

                CW2100_FunctionNet func = new CW2100_FunctionNet(mea);
                w2100_hs_samling = func.GetHeadstageSamplingActive(other_receiver + 0);
                func.SetHeadstageSamplingActive(false, other_receiver + 0);

                // Send Stimulation pattern
                bool first = true;
                int preplegth = 0;
                CW2100_StimulatorFunctionNet stim = new CW2100_StimulatorFunctionNet(mea);
                stim.SelectTimeSlot(other_receiver + 0);
                // Different strength
                // Define the amplitude vector of the 3 segments of the biphasic pulse (in nA)
                int[] ampl = new[] { 10000, -10000, 0 };

                // Define the duraion vector of the 3 segments of the biphasic pulse (in us)
                ulong[] dur = new ulong[] { 100, 100, 7492 };

                // Define each pulse
                for (int i = 0; i < 16; i++)
                {
                    // Define the amplitude (nA) of each of the 3 segments
                    ampl[0] = delta_DBS_amp * (i + 1);
                    ampl[1] = -delta_DBS_amp * (i + 1);

                    // Define the duration (us) of each of the 3 segments
                    //dur[0] = (ulong)pulse_on_phase_dur;
                    //dur[1] = (ulong)pulse_on_phase_dur;
                    //dur[2] = (ulong)pulse_off_phase_dur;

                    // choose, if global repeat is desired
                    // Define the associated pulse
                    CStimulusFunctionNet.StimulusDeviceDataAndUnrolledData prep = stim.PrepareData(0, ampl, dur, STG_DestinationEnumNet.channeldata_current, 1);

                    // Check the available memory in the headstage  
                    if (first)
                    {
                        first = false;
                        preplegth = prep.DeviceDataLength;
                    }

                    // Check that the pulse fits into the designated memory
                    Debug.Assert(preplegth == prep.DeviceDataLength);
                    Debug.Assert(prep.DeviceDataLength <= 15);

                    // Store pulse into designated memory
                    stim.SendPreparedData(0x10 * i + 0, prep, STG_DestinationEnumNet.channeldata_current);
                }
                func.SetHeadstageSamplingActive(true, other_receiver + 0);
            }
            if (startDacq.Enabled)
            {
                mea.Disconnect();
            }

            Random random = new Random();
            int maxOn = 220;
            int maxOff = Convert.ToInt32(maxOn * (100 - PercentageStimOn) / PercentageStimOn);

            CMcsUsbFactoryNet factorydev = new CMcsUsbFactoryNet(); // Create object of class CMcsUsbFactoryNet (provides firmware upgrade and register access capabilities)
            bool stimOn = false;
            double sleepTime = 0;
            if (factorydev.Connect(port, LockMask) == 0) // if connect call returns zero, connect has been successful
            {
                RandomStimOn = true;
                while (RandomStimOn)
                {
                    if (stimOn)
                    {
                        factorydev.WriteRegister(0x9A80, 0);
                        stimOn = false;
                        sleepTime = random.Next(1, maxOff);
                    } 
                    else
                    {
                        factorydev.WriteRegister(0x9A80, 0x1000 * 15 + 0x100);
                        stimOn = true;
                        //sleepTime = -1000 * Math.Log(1 - random.NextDouble()) / lambdaOn;
                        sleepTime = random.Next(1, maxOn);
                    }
                    Thread.Sleep(Convert.ToInt32(sleepTime));
                }
                factorydev.WriteRegister(0x9A80, 0);
                factorydev.Disconnect();
                MessageBox.Show("Random Stim Finished");
            }
        }

        private void StopRandomStimButton_Click(object sender, EventArgs e)
        {
            RandomStimOn = false;
            StopRandomStimButton.Enabled = false;
            PercentageOnInputBox.Enabled = true;
        }
    }
}
