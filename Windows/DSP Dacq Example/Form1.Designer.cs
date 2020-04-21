namespace MCS_USB_Windows_Forms_Application1
{
    partial class Form1
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
            System.Windows.Forms.DataVisualization.Charting.Series series3 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.Series series4 = new System.Windows.Forms.DataVisualization.Charting.Series();
            this.mcsdevices = new System.Windows.Forms.Label();
            this.cbDeviceList = new System.Windows.Forms.ComboBox();
            this.btnRefresh = new System.Windows.Forms.Button();
            this.btnConnect = new System.Windows.Forms.Button();
            this.startDacq = new System.Windows.Forms.Button();
            this.serialNumber = new System.Windows.Forms.TextBox();
            this.dspData = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.label1 = new System.Windows.Forms.Label();
            this.series0Channel = new System.Windows.Forms.ComboBox();
            this.series1Channel = new System.Windows.Forms.ComboBox();
            this.series2Channel = new System.Windows.Forms.ComboBox();
            this.series3Channel = new System.Windows.Forms.ComboBox();
            this.stopDacq = new System.Windows.Forms.Button();
            this.btStartTrigger = new System.Windows.Forms.Button();
            this.cbTriggerSegment = new System.Windows.Forms.ComboBox();
            this.cbChart3 = new System.Windows.Forms.CheckBox();
            this.cbChart4 = new System.Windows.Forms.CheckBox();
            this.cbChart1 = new System.Windows.Forms.CheckBox();
            this.cbChart2 = new System.Windows.Forms.CheckBox();
            this.btResetSettings = new System.Windows.Forms.Button();
            this.btStopTrigger = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.dspData)).BeginInit();
            this.SuspendLayout();
            // 
            // mcsdevices
            // 
            this.mcsdevices.AutoSize = true;
            this.mcsdevices.Location = new System.Drawing.Point(12, 16);
            this.mcsdevices.Name = "mcsdevices";
            this.mcsdevices.Size = new System.Drawing.Size(75, 13);
            this.mcsdevices.TabIndex = 0;
            this.mcsdevices.Text = "MCS Devices:";
            // 
            // cbDeviceList
            // 
            this.cbDeviceList.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbDeviceList.FormattingEnabled = true;
            this.cbDeviceList.Location = new System.Drawing.Point(93, 13);
            this.cbDeviceList.Name = "cbDeviceList";
            this.cbDeviceList.Size = new System.Drawing.Size(190, 21);
            this.cbDeviceList.TabIndex = 1;
            // 
            // btnRefresh
            // 
            this.btnRefresh.Location = new System.Drawing.Point(289, 12);
            this.btnRefresh.Name = "btnRefresh";
            this.btnRefresh.Size = new System.Drawing.Size(75, 23);
            this.btnRefresh.TabIndex = 2;
            this.btnRefresh.Text = "Refresh";
            this.btnRefresh.UseVisualStyleBackColor = true;
            this.btnRefresh.Click += new System.EventHandler(this.btnRefresh_Click);
            // 
            // btnConnect
            // 
            this.btnConnect.Location = new System.Drawing.Point(370, 12);
            this.btnConnect.Name = "btnConnect";
            this.btnConnect.Size = new System.Drawing.Size(93, 23);
            this.btnConnect.TabIndex = 3;
            this.btnConnect.Text = "Test Connection";
            this.btnConnect.UseVisualStyleBackColor = true;
            this.btnConnect.Click += new System.EventHandler(this.btnConnect_Click);
            // 
            // startDacq
            // 
            this.startDacq.Location = new System.Drawing.Point(18, 65);
            this.startDacq.Name = "startDacq";
            this.startDacq.Size = new System.Drawing.Size(146, 23);
            this.startDacq.TabIndex = 4;
            this.startDacq.Text = "Start Measurment";
            this.startDacq.UseVisualStyleBackColor = true;
            this.startDacq.Click += new System.EventHandler(this.startDacq_Click);
            // 
            // serialNumber
            // 
            this.serialNumber.Location = new System.Drawing.Point(548, 14);
            this.serialNumber.Name = "serialNumber";
            this.serialNumber.Size = new System.Drawing.Size(100, 20);
            this.serialNumber.TabIndex = 5;
            // 
            // dspData
            // 
            chartArea1.Name = "ChartArea1";
            this.dspData.ChartAreas.Add(chartArea1);
            legend1.Name = "Legend1";
            this.dspData.Legends.Add(legend1);
            this.dspData.Location = new System.Drawing.Point(15, 183);
            this.dspData.Name = "dspData";
            series1.ChartArea = "ChartArea1";
            series1.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.FastLine;
            series1.Legend = "Legend1";
            series1.Name = "Chart 1";
            series2.ChartArea = "ChartArea1";
            series2.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.FastLine;
            series2.Legend = "Legend1";
            series2.Name = "Chart 2";
            series3.ChartArea = "ChartArea1";
            series3.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.FastLine;
            series3.Legend = "Legend1";
            series3.Name = "Chart 3";
            series4.ChartArea = "ChartArea1";
            series4.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.FastLine;
            series4.Legend = "Legend1";
            series4.Name = "Chart 4";
            this.dspData.Series.Add(series1);
            this.dspData.Series.Add(series2);
            this.dspData.Series.Add(series3);
            this.dspData.Series.Add(series4);
            this.dspData.Size = new System.Drawing.Size(621, 312);
            this.dspData.TabIndex = 6;
            this.dspData.Text = "DSP Data";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(469, 17);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(73, 13);
            this.label1.TabIndex = 7;
            this.label1.Text = "Serial Number";
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
            this.stopDacq.Location = new System.Drawing.Point(197, 65);
            this.stopDacq.Name = "stopDacq";
            this.stopDacq.Size = new System.Drawing.Size(146, 23);
            this.stopDacq.TabIndex = 16;
            this.stopDacq.Text = "Stop Measurment";
            this.stopDacq.UseVisualStyleBackColor = true;
            this.stopDacq.Click += new System.EventHandler(this.stopDacq_Click);
            // 
            // btStartTrigger
            // 
            this.btStartTrigger.Location = new System.Drawing.Point(548, 107);
            this.btStartTrigger.Name = "btStartTrigger";
            this.btStartTrigger.Size = new System.Drawing.Size(75, 23);
            this.btStartTrigger.TabIndex = 18;
            this.btStartTrigger.Text = "Start Trigger";
            this.btStartTrigger.UseVisualStyleBackColor = true;
            this.btStartTrigger.Click += new System.EventHandler(this.btStartTrigger_Click);
            // 
            // cbTriggerSegment
            // 
            this.cbTriggerSegment.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbTriggerSegment.FormattingEnabled = true;
            this.cbTriggerSegment.Location = new System.Drawing.Point(491, 107);
            this.cbTriggerSegment.Name = "cbTriggerSegment";
            this.cbTriggerSegment.Size = new System.Drawing.Size(51, 21);
            this.cbTriggerSegment.TabIndex = 19;
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
            this.btResetSettings.Location = new System.Drawing.Point(388, 65);
            this.btResetSettings.Name = "btResetSettings";
            this.btResetSettings.Size = new System.Drawing.Size(154, 23);
            this.btResetSettings.TabIndex = 24;
            this.btResetSettings.Text = "Reset Settings";
            this.btResetSettings.UseVisualStyleBackColor = true;
            this.btResetSettings.Click += new System.EventHandler(this.btResetSettings_Click);
            // 
            // btStopTrigger
            // 
            this.btStopTrigger.Location = new System.Drawing.Point(548, 136);
            this.btStopTrigger.Name = "btStopTrigger";
            this.btStopTrigger.Size = new System.Drawing.Size(75, 23);
            this.btStopTrigger.TabIndex = 25;
            this.btStopTrigger.Text = "Stop Trigger";
            this.btStopTrigger.UseVisualStyleBackColor = true;
            this.btStopTrigger.Click += new System.EventHandler(this.btStopTrigger_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(658, 528);
            this.Controls.Add(this.btStopTrigger);
            this.Controls.Add(this.btResetSettings);
            this.Controls.Add(this.cbChart2);
            this.Controls.Add(this.cbChart1);
            this.Controls.Add(this.cbChart4);
            this.Controls.Add(this.cbChart3);
            this.Controls.Add(this.cbTriggerSegment);
            this.Controls.Add(this.btStartTrigger);
            this.Controls.Add(this.stopDacq);
            this.Controls.Add(this.series3Channel);
            this.Controls.Add(this.series2Channel);
            this.Controls.Add(this.series1Channel);
            this.Controls.Add(this.series0Channel);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.dspData);
            this.Controls.Add(this.serialNumber);
            this.Controls.Add(this.startDacq);
            this.Controls.Add(this.btnConnect);
            this.Controls.Add(this.btnRefresh);
            this.Controls.Add(this.cbDeviceList);
            this.Controls.Add(this.mcsdevices);
            this.Name = "Form1";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.dspData)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label mcsdevices;
        private System.Windows.Forms.ComboBox cbDeviceList;
        private System.Windows.Forms.Button btnRefresh;
        private System.Windows.Forms.Button btnConnect;
        private System.Windows.Forms.Button startDacq;
        private System.Windows.Forms.TextBox serialNumber;
        private System.Windows.Forms.DataVisualization.Charting.Chart dspData;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox series0Channel;
        private System.Windows.Forms.ComboBox series1Channel;
        private System.Windows.Forms.ComboBox series2Channel;
        private System.Windows.Forms.ComboBox series3Channel;
        private System.Windows.Forms.Button stopDacq;
        private System.Windows.Forms.Button btStartTrigger;
        private System.Windows.Forms.ComboBox cbTriggerSegment;
        private System.Windows.Forms.CheckBox cbChart3;
        private System.Windows.Forms.CheckBox cbChart4;
        private System.Windows.Forms.CheckBox cbChart1;
        private System.Windows.Forms.CheckBox cbChart2;
        private System.Windows.Forms.Button btResetSettings;
        private System.Windows.Forms.Button btStopTrigger;
    }
}

