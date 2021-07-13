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
            this.StartRandomStimButton = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.dspData)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // startDacq
            // 
            this.startDacq.Location = new System.Drawing.Point(28, 108);
            this.startDacq.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.startDacq.Name = "startDacq";
            this.startDacq.Size = new System.Drawing.Size(219, 35);
            this.startDacq.TabIndex = 4;
            this.startDacq.Text = "Start Measurment";
            this.startDacq.UseVisualStyleBackColor = true;
            this.startDacq.Click += new System.EventHandler(this.startDacq_Click);
            // 
            // dspData
            // 
            chartArea1.Name = "ChartArea1";
            this.dspData.ChartAreas.Add(chartArea1);
            legend1.Name = "Legend1";
            this.dspData.Legends.Add(legend1);
            this.dspData.Location = new System.Drawing.Point(18, 254);
            this.dspData.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
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
            this.dspData.Size = new System.Drawing.Size(1428, 578);
            this.dspData.TabIndex = 6;
            this.dspData.Text = "DSP Data";
            // 
            // series0Channel
            // 
            this.series0Channel.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.series0Channel.FormattingEnabled = true;
            this.series0Channel.Location = new System.Drawing.Point(132, 165);
            this.series0Channel.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.series0Channel.Name = "series0Channel";
            this.series0Channel.Size = new System.Drawing.Size(180, 28);
            this.series0Channel.TabIndex = 9;
            // 
            // series1Channel
            // 
            this.series1Channel.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.series1Channel.FormattingEnabled = true;
            this.series1Channel.Location = new System.Drawing.Point(132, 206);
            this.series1Channel.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.series1Channel.Name = "series1Channel";
            this.series1Channel.Size = new System.Drawing.Size(180, 28);
            this.series1Channel.TabIndex = 11;
            // 
            // stopDacq
            // 
            this.stopDacq.Location = new System.Drawing.Point(279, 108);
            this.stopDacq.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.stopDacq.Name = "stopDacq";
            this.stopDacq.Size = new System.Drawing.Size(219, 35);
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
            this.cbChart1.Location = new System.Drawing.Point(28, 169);
            this.cbChart1.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.cbChart1.Name = "cbChart1";
            this.cbChart1.Size = new System.Drawing.Size(91, 24);
            this.cbChart1.TabIndex = 22;
            this.cbChart1.Text = "Chart 1:";
            this.cbChart1.UseVisualStyleBackColor = true;
            // 
            // cbChart2
            // 
            this.cbChart2.AutoSize = true;
            this.cbChart2.Checked = true;
            this.cbChart2.CheckState = System.Windows.Forms.CheckState.Checked;
            this.cbChart2.Location = new System.Drawing.Point(28, 209);
            this.cbChart2.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.cbChart2.Name = "cbChart2";
            this.cbChart2.Size = new System.Drawing.Size(91, 24);
            this.cbChart2.TabIndex = 23;
            this.cbChart2.Text = "Chart 2:";
            this.cbChart2.UseVisualStyleBackColor = true;
            // 
            // btnDeviceOK
            // 
            this.btnDeviceOK.Location = new System.Drawing.Point(369, 18);
            this.btnDeviceOK.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.btnDeviceOK.Name = "btnDeviceOK";
            this.btnDeviceOK.Size = new System.Drawing.Size(120, 69);
            this.btnDeviceOK.TabIndex = 31;
            this.btnDeviceOK.UseVisualStyleBackColor = true;
            // 
            // dspSerial
            // 
            this.dspSerial.Location = new System.Drawing.Point(210, 57);
            this.dspSerial.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.dspSerial.Name = "dspSerial";
            this.dspSerial.Size = new System.Drawing.Size(148, 26);
            this.dspSerial.TabIndex = 30;
            // 
            // rawSerial
            // 
            this.rawSerial.Location = new System.Drawing.Point(210, 18);
            this.rawSerial.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.rawSerial.Name = "rawSerial";
            this.rawSerial.Size = new System.Drawing.Size(148, 26);
            this.rawSerial.TabIndex = 29;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(27, 62);
            this.label8.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(143, 20);
            this.label8.TabIndex = 28;
            this.label8.Text = "DSP Port (USB-B):";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(27, 23);
            this.label7.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(142, 20);
            this.label7.TabIndex = 27;
            this.label7.Text = "Raw Port (USB-A):";
            // 
            // cbDeviceList
            // 
            this.cbDeviceList.FormattingEnabled = true;
            this.cbDeviceList.Location = new System.Drawing.Point(516, 55);
            this.cbDeviceList.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.cbDeviceList.Name = "cbDeviceList";
            this.cbDeviceList.Size = new System.Drawing.Size(180, 28);
            this.cbDeviceList.TabIndex = 32;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(498, 29);
            this.label1.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(228, 20);
            this.label1.TabIndex = 33;
            this.label1.Text = "Select device for measurement";
            // 
            // StopDSP
            // 
            this.StopDSP.Location = new System.Drawing.Point(1170, 165);
            this.StopDSP.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.StopDSP.Name = "StopDSP";
            this.StopDSP.Size = new System.Drawing.Size(276, 62);
            this.StopDSP.TabIndex = 35;
            this.StopDSP.Text = "Stop DSP";
            this.StopDSP.UseVisualStyleBackColor = true;
            this.StopDSP.Click += new System.EventHandler(this.StopDSP_Click);
            // 
            // UploadDSPBinary
            // 
            this.UploadDSPBinary.Location = new System.Drawing.Point(1170, 94);
            this.UploadDSPBinary.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.UploadDSPBinary.Name = "UploadDSPBinary";
            this.UploadDSPBinary.Size = new System.Drawing.Size(276, 62);
            this.UploadDSPBinary.TabIndex = 34;
            this.UploadDSPBinary.Text = "Threshold ON/OFF";
            this.UploadDSPBinary.UseVisualStyleBackColor = true;
            this.UploadDSPBinary.Click += new System.EventHandler(this.UploadDSPBinary_Click);
            // 
            // SaveToFileCheckBox
            // 
            this.SaveToFileCheckBox.AutoSize = true;
            this.SaveToFileCheckBox.Location = new System.Drawing.Point(525, 114);
            this.SaveToFileCheckBox.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.SaveToFileCheckBox.Name = "SaveToFileCheckBox";
            this.SaveToFileCheckBox.Size = new System.Drawing.Size(113, 24);
            this.SaveToFileCheckBox.TabIndex = 36;
            this.SaveToFileCheckBox.Text = "Save to file";
            this.SaveToFileCheckBox.UseVisualStyleBackColor = true;
            // 
            // MaxAmplitudeTextBox
            // 
            this.MaxAmplitudeTextBox.Location = new System.Drawing.Point(1324, 15);
            this.MaxAmplitudeTextBox.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.MaxAmplitudeTextBox.Name = "MaxAmplitudeTextBox";
            this.MaxAmplitudeTextBox.Size = new System.Drawing.Size(120, 26);
            this.MaxAmplitudeTextBox.TabIndex = 38;
            this.MaxAmplitudeTextBox.Text = "10";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(1176, 20);
            this.label2.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(145, 20);
            this.label2.TabIndex = 39;
            this.label2.Text = "Max amplitude (μA)";
            // 
            // DisplayInMicrovoltsChannel1
            // 
            this.DisplayInMicrovoltsChannel1.AutoSize = true;
            this.DisplayInMicrovoltsChannel1.Location = new System.Drawing.Point(322, 169);
            this.DisplayInMicrovoltsChannel1.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.DisplayInMicrovoltsChannel1.Name = "DisplayInMicrovoltsChannel1";
            this.DisplayInMicrovoltsChannel1.Size = new System.Drawing.Size(176, 24);
            this.DisplayInMicrovoltsChannel1.TabIndex = 37;
            this.DisplayInMicrovoltsChannel1.Text = "Display in microvolts";
            this.DisplayInMicrovoltsChannel1.UseVisualStyleBackColor = true;
            // 
            // DisplayInMicrovoltsChannel2
            // 
            this.DisplayInMicrovoltsChannel2.AutoSize = true;
            this.DisplayInMicrovoltsChannel2.Location = new System.Drawing.Point(322, 209);
            this.DisplayInMicrovoltsChannel2.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.DisplayInMicrovoltsChannel2.Name = "DisplayInMicrovoltsChannel2";
            this.DisplayInMicrovoltsChannel2.Size = new System.Drawing.Size(176, 24);
            this.DisplayInMicrovoltsChannel2.TabIndex = 40;
            this.DisplayInMicrovoltsChannel2.Text = "Display in microvolts";
            this.DisplayInMicrovoltsChannel2.UseVisualStyleBackColor = true;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(1180, 58);
            this.label3.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(111, 20);
            this.label3.TabIndex = 42;
            this.label3.Text = "Stim threshold";
            // 
            // StimThresholdTextBox
            // 
            this.StimThresholdTextBox.Location = new System.Drawing.Point(1324, 54);
            this.StimThresholdTextBox.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.StimThresholdTextBox.Name = "StimThresholdTextBox";
            this.StimThresholdTextBox.Size = new System.Drawing.Size(120, 26);
            this.StimThresholdTextBox.TabIndex = 41;
            this.StimThresholdTextBox.Text = "100000";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(48, 28);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(38, 20);
            this.label4.TabIndex = 43;
            this.label4.Text = "max";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(52, 60);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(34, 20);
            this.label5.TabIndex = 44;
            this.label5.Text = "min";
            // 
            // maxYChartInput
            // 
            this.maxYChartInput.Location = new System.Drawing.Point(98, 28);
            this.maxYChartInput.Name = "maxYChartInput";
            this.maxYChartInput.Size = new System.Drawing.Size(116, 26);
            this.maxYChartInput.TabIndex = 45;
            // 
            // minYChartInput
            // 
            this.minYChartInput.Location = new System.Drawing.Point(98, 60);
            this.minYChartInput.Name = "minYChartInput";
            this.minYChartInput.Size = new System.Drawing.Size(116, 26);
            this.minYChartInput.TabIndex = 46;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.minYChartInput);
            this.groupBox1.Controls.Add(this.maxYChartInput);
            this.groupBox1.Controls.Add(this.label5);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Location = new System.Drawing.Point(510, 158);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(240, 90);
            this.groupBox1.TabIndex = 47;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Vertical plot limits";
            // 
            // StartRandomStimButton
            // 
            this.StartRandomStimButton.Location = new System.Drawing.Point(886, 94);
            this.StartRandomStimButton.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.StartRandomStimButton.Name = "StartRandomStimButton";
            this.StartRandomStimButton.Size = new System.Drawing.Size(276, 62);
            this.StartRandomStimButton.TabIndex = 48;
            this.StartRandomStimButton.Text = "Random ON/OFF";
            this.StartRandomStimButton.UseVisualStyleBackColor = true;
            this.StartRandomStimButton.Click += new System.EventHandler(this.StartRandomStimButton_Click);
            // 
            // Dacq
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1459, 851);
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
            this.Controls.Add(this.dspData);
            this.Controls.Add(this.startDacq);
            this.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.Name = "Dacq";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.dspData)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
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
    }
}

