namespace MCS_USB_Windows_Forms_Application1
{
    partial class Dacq
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea1 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Legend legend1 = new System.Windows.Forms.DataVisualization.Charting.Legend();
            System.Windows.Forms.DataVisualization.Charting.Series series1 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.Series series2 = new System.Windows.Forms.DataVisualization.Charting.Series();
            this.startDacq = new System.Windows.Forms.Button();
            this.dspData = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.series0Channel = new System.Windows.Forms.ComboBox();
            this.series1Channel = new System.Windows.Forms.ComboBox();
            this.stopDacq = new System.Windows.Forms.Button();
            this.cbChart1 = new System.Windows.Forms.CheckBox();
            this.cbChart2 = new System.Windows.Forms.CheckBox();
            this.btnDeviceOK = new System.Windows.Forms.Button();
            this.dspSerial = new System.Windows.Forms.TextBox();
            this.rawSerial = new System.Windows.Forms.TextBox();
            this.label8 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.cbDeviceList = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.StopDSP = new System.Windows.Forms.Button();
            this.UploadDSPBinary = new System.Windows.Forms.Button();
            this.SaveToFileCheckBox = new System.Windows.Forms.CheckBox();
            this.MaxAmplitudeTextBox = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.DisplayInMicrovoltsChannel1 = new System.Windows.Forms.CheckBox();
            this.DisplayInMicrovoltsChannel2 = new System.Windows.Forms.CheckBox();
            this.label3 = new System.Windows.Forms.Label();
            this.StimThresholdTextBox = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.maxYChartInput = new System.Windows.Forms.TextBox();
            this.minYChartInput = new System.Windows.Forms.TextBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.ApplyYLimitChangesButton = new System.Windows.Forms.Button();
            this.StartRandomStimButton = new System.Windows.Forms.Button();
            this.StopRandomStimButton = new System.Windows.Forms.Button();
            this.label6 = new System.Windows.Forms.Label();
            this.PercentageOnInputBox = new System.Windows.Forms.TextBox();
            this.ProportionalGainInput = new System.Windows.Forms.TextBox();
            this.label9 = new System.Windows.Forms.Label();
            this.OpenDebugFormButton = new System.Windows.Forms.Button();
            this.panel1 = new System.Windows.Forms.Panel();
            this.feedbackChannelComboBox = new System.Windows.Forms.ComboBox();
            this.label10 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.dspData)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.panel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // startDacq
            // 
            this.startDacq.Location = new System.Drawing.Point(19, 70);
            this.startDacq.Name = "startDacq";
            this.startDacq.Size = new System.Drawing.Size(146, 23);
            this.startDacq.TabIndex = 4;
            this.startDacq.Text = "Start Measurment";
            this.startDacq.UseVisualStyleBackColor = true;
            this.startDacq.Click += new System.EventHandler(this.startDacq_Click);
            // 
            // dspData
            // 
            chartArea1.Name = "ChartArea1";
            this.dspData.ChartAreas.Add(chartArea1);
            this.dspData.Dock = System.Windows.Forms.DockStyle.Fill;
            legend1.Name = "Legend1";
            this.dspData.Legends.Add(legend1);
            this.dspData.Location = new System.Drawing.Point(0, 0);
            this.dspData.Name = "dspData";
            series1.ChartArea = "ChartArea1";
            series1.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.FastLine;
            series1.Legend = "Legend1";
            series1.Name = "Chart 1";
            series2.ChartArea = "ChartArea1";
            series2.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.FastLine;
            series2.Legend = "Legend1";
            series2.Name = "Chart 2";
            this.dspData.Series.Add(series1);
            this.dspData.Series.Add(series2);
            this.dspData.Size = new System.Drawing.Size(957, 375);
            this.dspData.TabIndex = 6;
            this.dspData.Text = "DSP Data";
            // 
            // series0Channel
            // 
            this.series0Channel.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.series0Channel.FormattingEnabled = true;
            this.series0Channel.Location = new System.Drawing.Point(88, 107);
            this.series0Channel.Name = "series0Channel";
            this.series0Channel.Size = new System.Drawing.Size(121, 21);
            this.series0Channel.TabIndex = 9;
            // 
            // series1Channel
            // 
            this.series1Channel.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.series1Channel.FormattingEnabled = true;
            this.series1Channel.Location = new System.Drawing.Point(88, 134);
            this.series1Channel.Name = "series1Channel";
            this.series1Channel.Size = new System.Drawing.Size(121, 21);
            this.series1Channel.TabIndex = 11;
            // 
            // stopDacq
            // 
            this.stopDacq.Location = new System.Drawing.Point(186, 70);
            this.stopDacq.Name = "stopDacq";
            this.stopDacq.Size = new System.Drawing.Size(146, 23);
            this.stopDacq.TabIndex = 16;
            this.stopDacq.Text = "Stop Measurment";
            this.stopDacq.UseVisualStyleBackColor = true;
            this.stopDacq.Click += new System.EventHandler(this.stopDacq_Click);
            // 
            // cbChart1
            // 
            this.cbChart1.AutoSize = true;
            this.cbChart1.Checked = true;
            this.cbChart1.CheckState = System.Windows.Forms.CheckState.Checked;
            this.cbChart1.Location = new System.Drawing.Point(19, 110);
            this.cbChart1.Name = "cbChart1";
            this.cbChart1.Size = new System.Drawing.Size(63, 17);
            this.cbChart1.TabIndex = 22;
            this.cbChart1.Text = "Chart 1:";
            this.cbChart1.UseVisualStyleBackColor = true;
            // 
            // cbChart2
            // 
            this.cbChart2.AutoSize = true;
            this.cbChart2.Checked = true;
            this.cbChart2.CheckState = System.Windows.Forms.CheckState.Checked;
            this.cbChart2.Location = new System.Drawing.Point(19, 136);
            this.cbChart2.Name = "cbChart2";
            this.cbChart2.Size = new System.Drawing.Size(63, 17);
            this.cbChart2.TabIndex = 23;
            this.cbChart2.Text = "Chart 2:";
            this.cbChart2.UseVisualStyleBackColor = true;
            // 
            // btnDeviceOK
            // 
            this.btnDeviceOK.Location = new System.Drawing.Point(246, 12);
            this.btnDeviceOK.Name = "btnDeviceOK";
            this.btnDeviceOK.Size = new System.Drawing.Size(80, 45);
            this.btnDeviceOK.TabIndex = 31;
            this.btnDeviceOK.UseVisualStyleBackColor = true;
            // 
            // dspSerial
            // 
            this.dspSerial.Location = new System.Drawing.Point(140, 37);
            this.dspSerial.Name = "dspSerial";
            this.dspSerial.Size = new System.Drawing.Size(100, 20);
            this.dspSerial.TabIndex = 30;
            // 
            // rawSerial
            // 
            this.rawSerial.Location = new System.Drawing.Point(140, 12);
            this.rawSerial.Name = "rawSerial";
            this.rawSerial.Size = new System.Drawing.Size(100, 20);
            this.rawSerial.TabIndex = 29;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(18, 40);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(95, 13);
            this.label8.TabIndex = 28;
            this.label8.Text = "DSP Port (USB-B):";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(18, 15);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(95, 13);
            this.label7.TabIndex = 27;
            this.label7.Text = "Raw Port (USB-A):";
            // 
            // cbDeviceList
            // 
            this.cbDeviceList.FormattingEnabled = true;
            this.cbDeviceList.Location = new System.Drawing.Point(344, 36);
            this.cbDeviceList.Name = "cbDeviceList";
            this.cbDeviceList.Size = new System.Drawing.Size(121, 21);
            this.cbDeviceList.TabIndex = 32;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(332, 19);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(153, 13);
            this.label1.TabIndex = 33;
            this.label1.Text = "Select device for measurement";
            // 
            // StopDSP
            // 
            this.StopDSP.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.StopDSP.Location = new System.Drawing.Point(780, 155);
            this.StopDSP.Name = "StopDSP";
            this.StopDSP.Size = new System.Drawing.Size(184, 40);
            this.StopDSP.TabIndex = 56;
            this.StopDSP.Text = "Stop DSP";
            this.StopDSP.UseVisualStyleBackColor = true;
            this.StopDSP.Click += new System.EventHandler(this.StopDSP_Click);
            // 
            // UploadDSPBinary
            // 
            this.UploadDSPBinary.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.UploadDSPBinary.Location = new System.Drawing.Point(780, 109);
            this.UploadDSPBinary.Name = "UploadDSPBinary";
            this.UploadDSPBinary.Size = new System.Drawing.Size(184, 40);
            this.UploadDSPBinary.TabIndex = 55;
            this.UploadDSPBinary.Text = "Upload DSP Binary";
            this.UploadDSPBinary.UseVisualStyleBackColor = true;
            this.UploadDSPBinary.Click += new System.EventHandler(this.UploadDSPBinary_Click);
            // 
            // SaveToFileCheckBox
            // 
            this.SaveToFileCheckBox.AutoSize = true;
            this.SaveToFileCheckBox.Location = new System.Drawing.Point(350, 74);
            this.SaveToFileCheckBox.Name = "SaveToFileCheckBox";
            this.SaveToFileCheckBox.Size = new System.Drawing.Size(79, 17);
            this.SaveToFileCheckBox.TabIndex = 36;
            this.SaveToFileCheckBox.Text = "Save to file";
            this.SaveToFileCheckBox.UseVisualStyleBackColor = true;
            // 
            // MaxAmplitudeTextBox
            // 
            this.MaxAmplitudeTextBox.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.MaxAmplitudeTextBox.Location = new System.Drawing.Point(883, 58);
            this.MaxAmplitudeTextBox.Name = "MaxAmplitudeTextBox";
            this.MaxAmplitudeTextBox.Size = new System.Drawing.Size(81, 20);
            this.MaxAmplitudeTextBox.TabIndex = 53;
            this.MaxAmplitudeTextBox.Text = "10";
            // 
            // label2
            // 
            this.label2.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(784, 61);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(97, 13);
            this.label2.TabIndex = 39;
            this.label2.Text = "Max amplitude (μA)";
            // 
            // DisplayInMicrovoltsChannel1
            // 
            this.DisplayInMicrovoltsChannel1.AutoSize = true;
            this.DisplayInMicrovoltsChannel1.Location = new System.Drawing.Point(215, 110);
            this.DisplayInMicrovoltsChannel1.Name = "DisplayInMicrovoltsChannel1";
            this.DisplayInMicrovoltsChannel1.Size = new System.Drawing.Size(121, 17);
            this.DisplayInMicrovoltsChannel1.TabIndex = 37;
            this.DisplayInMicrovoltsChannel1.Text = "Display in microvolts";
            this.DisplayInMicrovoltsChannel1.UseVisualStyleBackColor = true;
            // 
            // DisplayInMicrovoltsChannel2
            // 
            this.DisplayInMicrovoltsChannel2.AutoSize = true;
            this.DisplayInMicrovoltsChannel2.Location = new System.Drawing.Point(215, 136);
            this.DisplayInMicrovoltsChannel2.Name = "DisplayInMicrovoltsChannel2";
            this.DisplayInMicrovoltsChannel2.Size = new System.Drawing.Size(121, 17);
            this.DisplayInMicrovoltsChannel2.TabIndex = 40;
            this.DisplayInMicrovoltsChannel2.Text = "Display in microvolts";
            this.DisplayInMicrovoltsChannel2.UseVisualStyleBackColor = true;
            // 
            // label3
            // 
            this.label3.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(784, 86);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(73, 13);
            this.label3.TabIndex = 42;
            this.label3.Text = "Stim threshold";
            // 
            // StimThresholdTextBox
            // 
            this.StimThresholdTextBox.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.StimThresholdTextBox.Location = new System.Drawing.Point(883, 83);
            this.StimThresholdTextBox.Name = "StimThresholdTextBox";
            this.StimThresholdTextBox.Size = new System.Drawing.Size(81, 20);
            this.StimThresholdTextBox.TabIndex = 54;
            this.StimThresholdTextBox.Text = "100000";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Enabled = false;
            this.label4.Location = new System.Drawing.Point(7, 18);
            this.label4.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(26, 13);
            this.label4.TabIndex = 43;
            this.label4.Text = "max";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Enabled = false;
            this.label5.Location = new System.Drawing.Point(10, 39);
            this.label5.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(23, 13);
            this.label5.TabIndex = 44;
            this.label5.Text = "min";
            // 
            // maxYChartInput
            // 
            this.maxYChartInput.Enabled = false;
            this.maxYChartInput.Location = new System.Drawing.Point(40, 18);
            this.maxYChartInput.Margin = new System.Windows.Forms.Padding(2);
            this.maxYChartInput.Name = "maxYChartInput";
            this.maxYChartInput.Size = new System.Drawing.Size(79, 20);
            this.maxYChartInput.TabIndex = 45;
            // 
            // minYChartInput
            // 
            this.minYChartInput.Enabled = false;
            this.minYChartInput.Location = new System.Drawing.Point(40, 39);
            this.minYChartInput.Margin = new System.Windows.Forms.Padding(2);
            this.minYChartInput.Name = "minYChartInput";
            this.minYChartInput.Size = new System.Drawing.Size(79, 20);
            this.minYChartInput.TabIndex = 46;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.ApplyYLimitChangesButton);
            this.groupBox1.Controls.Add(this.minYChartInput);
            this.groupBox1.Controls.Add(this.maxYChartInput);
            this.groupBox1.Controls.Add(this.label5);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Enabled = false;
            this.groupBox1.Location = new System.Drawing.Point(340, 103);
            this.groupBox1.Margin = new System.Windows.Forms.Padding(2);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Padding = new System.Windows.Forms.Padding(2);
            this.groupBox1.Size = new System.Drawing.Size(203, 68);
            this.groupBox1.TabIndex = 47;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Vertical plot limits";
            // 
            // ApplyYLimitChangesButton
            // 
            this.ApplyYLimitChangesButton.Enabled = false;
            this.ApplyYLimitChangesButton.Location = new System.Drawing.Point(124, 37);
            this.ApplyYLimitChangesButton.Name = "ApplyYLimitChangesButton";
            this.ApplyYLimitChangesButton.Size = new System.Drawing.Size(75, 23);
            this.ApplyYLimitChangesButton.TabIndex = 47;
            this.ApplyYLimitChangesButton.Text = "Apply";
            this.ApplyYLimitChangesButton.UseVisualStyleBackColor = true;
            this.ApplyYLimitChangesButton.Click += new System.EventHandler(this.ApplyYLimitChangesButton_Click);
            // 
            // StartRandomStimButton
            // 
            this.StartRandomStimButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.StartRandomStimButton.Location = new System.Drawing.Point(591, 109);
            this.StartRandomStimButton.Name = "StartRandomStimButton";
            this.StartRandomStimButton.Size = new System.Drawing.Size(184, 40);
            this.StartRandomStimButton.TabIndex = 48;
            this.StartRandomStimButton.Text = "Random ON/OFF";
            this.StartRandomStimButton.UseVisualStyleBackColor = true;
            this.StartRandomStimButton.Click += new System.EventHandler(this.StartRandomStimButton_Click);
            // 
            // StopRandomStimButton
            // 
            this.StopRandomStimButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.StopRandomStimButton.Enabled = false;
            this.StopRandomStimButton.Location = new System.Drawing.Point(591, 155);
            this.StopRandomStimButton.Name = "StopRandomStimButton";
            this.StopRandomStimButton.Size = new System.Drawing.Size(184, 40);
            this.StopRandomStimButton.TabIndex = 49;
            this.StopRandomStimButton.Text = "Stop Random Stim";
            this.StopRandomStimButton.UseVisualStyleBackColor = true;
            this.StopRandomStimButton.Click += new System.EventHandler(this.StopRandomStimButton_Click);
            // 
            // label6
            // 
            this.label6.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(637, 63);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(103, 13);
            this.label6.TabIndex = 50;
            this.label6.Text = "Percentage time ON";
            // 
            // PercentageOnInputBox
            // 
            this.PercentageOnInputBox.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.PercentageOnInputBox.Location = new System.Drawing.Point(661, 83);
            this.PercentageOnInputBox.Name = "PercentageOnInputBox";
            this.PercentageOnInputBox.Size = new System.Drawing.Size(53, 20);
            this.PercentageOnInputBox.TabIndex = 51;
            this.PercentageOnInputBox.Text = "15";
            // 
            // ProportionalGainInput
            // 
            this.ProportionalGainInput.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.ProportionalGainInput.Location = new System.Drawing.Point(883, 32);
            this.ProportionalGainInput.Name = "ProportionalGainInput";
            this.ProportionalGainInput.Size = new System.Drawing.Size(81, 20);
            this.ProportionalGainInput.TabIndex = 52;
            this.ProportionalGainInput.Text = "0";
            // 
            // label9
            // 
            this.label9.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(784, 35);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(86, 13);
            this.label9.TabIndex = 53;
            this.label9.Text = "Proportional gain";
            // 
            // OpenDebugFormButton
            // 
            this.OpenDebugFormButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.OpenDebugFormButton.Location = new System.Drawing.Point(641, 12);
            this.OpenDebugFormButton.Margin = new System.Windows.Forms.Padding(2);
            this.OpenDebugFormButton.Name = "OpenDebugFormButton";
            this.OpenDebugFormButton.Size = new System.Drawing.Size(92, 23);
            this.OpenDebugFormButton.TabIndex = 57;
            this.OpenDebugFormButton.Text = "Debug Window";
            this.OpenDebugFormButton.UseVisualStyleBackColor = true;
            this.OpenDebugFormButton.Click += new System.EventHandler(this.OpenDebugFormButton_Click);
            // 
            // panel1
            // 
            this.panel1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.panel1.AutoSize = true;
            this.panel1.Controls.Add(this.dspData);
            this.panel1.Location = new System.Drawing.Point(9, 201);
            this.panel1.Margin = new System.Windows.Forms.Padding(2);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(957, 375);
            this.panel1.TabIndex = 58;
            // 
            // feedbackChannelComboBox
            // 
            this.feedbackChannelComboBox.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.feedbackChannelComboBox.FormattingEnabled = true;
            this.feedbackChannelComboBox.Items.AddRange(new object[] {
            "mean",
            "1",
            "2",
            "3",
            "4",
            "1-2",
            "1-3",
            "1-4",
            "2-3",
            "2-4",
            "3-4"});
            this.feedbackChannelComboBox.Location = new System.Drawing.Point(883, 6);
            this.feedbackChannelComboBox.Name = "feedbackChannelComboBox";
            this.feedbackChannelComboBox.Size = new System.Drawing.Size(81, 21);
            this.feedbackChannelComboBox.TabIndex = 59;
            // 
            // label10
            // 
            this.label10.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(784, 9);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(96, 13);
            this.label10.TabIndex = 60;
            this.label10.Text = "Feedback channel";
            // 
            // Dacq
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(974, 585);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.feedbackChannelComboBox);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.OpenDebugFormButton);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.ProportionalGainInput);
            this.Controls.Add(this.PercentageOnInputBox);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.StopRandomStimButton);
            this.Controls.Add(this.StartRandomStimButton);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.StimThresholdTextBox);
            this.Controls.Add(this.DisplayInMicrovoltsChannel2);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.MaxAmplitudeTextBox);
            this.Controls.Add(this.DisplayInMicrovoltsChannel1);
            this.Controls.Add(this.SaveToFileCheckBox);
            this.Controls.Add(this.StopDSP);
            this.Controls.Add(this.UploadDSPBinary);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.cbDeviceList);
            this.Controls.Add(this.btnDeviceOK);
            this.Controls.Add(this.dspSerial);
            this.Controls.Add(this.rawSerial);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.cbChart2);
            this.Controls.Add(this.cbChart1);
            this.Controls.Add(this.stopDacq);
            this.Controls.Add(this.series1Channel);
            this.Controls.Add(this.series0Channel);
            this.Controls.Add(this.startDacq);
            this.Name = "Dacq";
            this.Text = "Closed-loop feedback GUI";
            ((System.ComponentModel.ISupportInitialize)(this.dspData)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.panel1.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Button startDacq;
        private System.Windows.Forms.DataVisualization.Charting.Chart dspData;
        private System.Windows.Forms.ComboBox series0Channel;
        private System.Windows.Forms.ComboBox series1Channel;
        private System.Windows.Forms.Button stopDacq;
        private System.Windows.Forms.CheckBox cbChart1;
        private System.Windows.Forms.CheckBox cbChart2;
        private System.Windows.Forms.Button btnDeviceOK;
        private System.Windows.Forms.TextBox dspSerial;
        private System.Windows.Forms.TextBox rawSerial;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.ComboBox cbDeviceList;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button StopDSP;
        private System.Windows.Forms.Button UploadDSPBinary;
        private System.Windows.Forms.CheckBox SaveToFileCheckBox;
        private System.Windows.Forms.TextBox MaxAmplitudeTextBox;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.CheckBox DisplayInMicrovoltsChannel1;
        private System.Windows.Forms.CheckBox DisplayInMicrovoltsChannel2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox StimThresholdTextBox;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox maxYChartInput;
        private System.Windows.Forms.TextBox minYChartInput;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button StartRandomStimButton;
        private System.Windows.Forms.Button StopRandomStimButton;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox PercentageOnInputBox;
        private System.Windows.Forms.TextBox ProportionalGainInput;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Button ApplyYLimitChangesButton;
        private System.Windows.Forms.Button OpenDebugFormButton;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.ComboBox feedbackChannelComboBox;
        private System.Windows.Forms.Label label10;
    }
}

