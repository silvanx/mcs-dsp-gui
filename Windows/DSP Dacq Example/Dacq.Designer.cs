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
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea2 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Legend legend2 = new System.Windows.Forms.DataVisualization.Charting.Legend();
            System.Windows.Forms.DataVisualization.Charting.Series series5 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.Series series6 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.Series series7 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.Series series8 = new System.Windows.Forms.DataVisualization.Charting.Series();
            this.startDacq = new System.Windows.Forms.Button();
            this.dspData = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.series0Channel = new System.Windows.Forms.ComboBox();
            this.series1Channel = new System.Windows.Forms.ComboBox();
            this.series2Channel = new System.Windows.Forms.ComboBox();
            this.series3Channel = new System.Windows.Forms.ComboBox();
            this.stopDacq = new System.Windows.Forms.Button();
            this.cbChart3 = new System.Windows.Forms.CheckBox();
            this.cbChart4 = new System.Windows.Forms.CheckBox();
            this.cbChart1 = new System.Windows.Forms.CheckBox();
            this.cbChart2 = new System.Windows.Forms.CheckBox();
            this.btResetSettings = new System.Windows.Forms.Button();
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
            this.DisplayInMicrovoltsCheckbox = new System.Windows.Forms.CheckBox();
            ((System.ComponentModel.ISupportInitialize)(this.dspData)).BeginInit();
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
            chartArea2.Name = "ChartArea1";
            this.dspData.ChartAreas.Add(chartArea2);
            legend2.Name = "Legend1";
            this.dspData.Legends.Add(legend2);
            this.dspData.Location = new System.Drawing.Point(12, 165);
            this.dspData.Name = "dspData";
            series5.ChartArea = "ChartArea1";
            series5.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.FastLine;
            series5.Legend = "Legend1";
            series5.Name = "Chart 1";
            series6.ChartArea = "ChartArea1";
            series6.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.FastLine;
            series6.Legend = "Legend1";
            series6.Name = "Chart 2";
            series7.ChartArea = "ChartArea1";
            series7.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.FastLine;
            series7.Legend = "Legend1";
            series7.Name = "Chart 3";
            series8.ChartArea = "ChartArea1";
            series8.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.FastLine;
            series8.Legend = "Legend1";
            series8.Name = "Chart 4";
            this.dspData.Series.Add(series5);
            this.dspData.Series.Add(series6);
            this.dspData.Series.Add(series7);
            this.dspData.Series.Add(series8);
            this.dspData.Size = new System.Drawing.Size(806, 376);
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
            // series2Channel
            // 
            this.series2Channel.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.series2Channel.FormattingEnabled = true;
            this.series2Channel.Location = new System.Drawing.Point(308, 107);
            this.series2Channel.Name = "series2Channel";
            this.series2Channel.Size = new System.Drawing.Size(121, 21);
            this.series2Channel.TabIndex = 13;
            // 
            // series3Channel
            // 
            this.series3Channel.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.series3Channel.FormattingEnabled = true;
            this.series3Channel.Location = new System.Drawing.Point(308, 134);
            this.series3Channel.Name = "series3Channel";
            this.series3Channel.Size = new System.Drawing.Size(121, 21);
            this.series3Channel.TabIndex = 15;
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
            // cbChart3
            // 
            this.cbChart3.AutoSize = true;
            this.cbChart3.Checked = true;
            this.cbChart3.CheckState = System.Windows.Forms.CheckState.Checked;
            this.cbChart3.Location = new System.Drawing.Point(239, 109);
            this.cbChart3.Name = "cbChart3";
            this.cbChart3.Size = new System.Drawing.Size(63, 17);
            this.cbChart3.TabIndex = 20;
            this.cbChart3.Text = "Chart 3:";
            this.cbChart3.UseVisualStyleBackColor = true;
            // 
            // cbChart4
            // 
            this.cbChart4.AutoSize = true;
            this.cbChart4.Checked = true;
            this.cbChart4.CheckState = System.Windows.Forms.CheckState.Checked;
            this.cbChart4.Location = new System.Drawing.Point(239, 136);
            this.cbChart4.Name = "cbChart4";
            this.cbChart4.Size = new System.Drawing.Size(63, 17);
            this.cbChart4.TabIndex = 21;
            this.cbChart4.Text = "Chart 4:";
            this.cbChart4.UseVisualStyleBackColor = true;
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
            // btResetSettings
            // 
            this.btResetSettings.Location = new System.Drawing.Point(652, 127);
            this.btResetSettings.Name = "btResetSettings";
            this.btResetSettings.Size = new System.Drawing.Size(154, 23);
            this.btResetSettings.TabIndex = 24;
            this.btResetSettings.Text = "Reset Settings";
            this.btResetSettings.UseVisualStyleBackColor = true;
            this.btResetSettings.Click += new System.EventHandler(this.btResetSettings_Click);
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
            this.StopDSP.Location = new System.Drawing.Point(634, 69);
            this.StopDSP.Name = "StopDSP";
            this.StopDSP.Size = new System.Drawing.Size(184, 49);
            this.StopDSP.TabIndex = 35;
            this.StopDSP.Text = "Stop DSP";
            this.StopDSP.UseVisualStyleBackColor = true;
            this.StopDSP.Click += new System.EventHandler(this.StopDSP_Click);
            // 
            // UploadDSPBinary
            // 
            this.UploadDSPBinary.Location = new System.Drawing.Point(634, 7);
            this.UploadDSPBinary.Name = "UploadDSPBinary";
            this.UploadDSPBinary.Size = new System.Drawing.Size(184, 50);
            this.UploadDSPBinary.TabIndex = 34;
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
            // DisplayInMicrovoltsCheckbox
            // 
            this.DisplayInMicrovoltsCheckbox.AutoSize = true;
            this.DisplayInMicrovoltsCheckbox.Location = new System.Drawing.Point(446, 138);
            this.DisplayInMicrovoltsCheckbox.Name = "DisplayInMicrovoltsCheckbox";
            this.DisplayInMicrovoltsCheckbox.Size = new System.Drawing.Size(180, 17);
            this.DisplayInMicrovoltsCheckbox.TabIndex = 37;
            this.DisplayInMicrovoltsCheckbox.Text = "Display all channels in microvolts";
            this.DisplayInMicrovoltsCheckbox.UseVisualStyleBackColor = true;
            // 
            // Dacq
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(830, 553);
            this.Controls.Add(this.DisplayInMicrovoltsCheckbox);
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
            this.Controls.Add(this.btResetSettings);
            this.Controls.Add(this.cbChart2);
            this.Controls.Add(this.cbChart1);
            this.Controls.Add(this.cbChart4);
            this.Controls.Add(this.cbChart3);
            this.Controls.Add(this.stopDacq);
            this.Controls.Add(this.series3Channel);
            this.Controls.Add(this.series2Channel);
            this.Controls.Add(this.series1Channel);
            this.Controls.Add(this.series0Channel);
            this.Controls.Add(this.dspData);
            this.Controls.Add(this.startDacq);
            this.Name = "Dacq";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.dspData)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Button startDacq;
        private System.Windows.Forms.DataVisualization.Charting.Chart dspData;
        private System.Windows.Forms.ComboBox series0Channel;
        private System.Windows.Forms.ComboBox series1Channel;
        private System.Windows.Forms.ComboBox series2Channel;
        private System.Windows.Forms.ComboBox series3Channel;
        private System.Windows.Forms.Button stopDacq;
        private System.Windows.Forms.CheckBox cbChart3;
        private System.Windows.Forms.CheckBox cbChart4;
        private System.Windows.Forms.CheckBox cbChart1;
        private System.Windows.Forms.CheckBox cbChart2;
        private System.Windows.Forms.Button btResetSettings;
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
        private System.Windows.Forms.CheckBox DisplayInMicrovoltsCheckbox;
    }
}

