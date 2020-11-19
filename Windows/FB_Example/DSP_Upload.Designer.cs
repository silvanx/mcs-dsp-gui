namespace my_interface
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
            this.ConnectMEA = new System.Windows.Forms.Button();
            this.UploadDSPBinary = new System.Windows.Forms.Button();
            this.StopDSP = new System.Windows.Forms.Button();
            this.SpikeThresh = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.Deadtime = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.BoxStimAmplitude = new System.Windows.Forms.TextBox();
            this.BoxStimDuration = new System.Windows.Forms.TextBox();
            this.BoxStimStepsize = new System.Windows.Forms.TextBox();
            this.BoxStimRepeats = new System.Windows.Forms.TextBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.rawSerial = new System.Windows.Forms.TextBox();
            this.dspSerial = new System.Windows.Forms.TextBox();
            this.btnDeviceOK = new System.Windows.Forms.Button();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // ConnectMEA
            // 
            this.ConnectMEA.Location = new System.Drawing.Point(298, 191);
            this.ConnectMEA.Name = "ConnectMEA";
            this.ConnectMEA.Size = new System.Drawing.Size(119, 59);
            this.ConnectMEA.TabIndex = 0;
            this.ConnectMEA.Text = "Set Parameters on MEA2100";
            this.ConnectMEA.UseVisualStyleBackColor = true;
            this.ConnectMEA.Click += new System.EventHandler(this.ConnectMEA_Click);
            // 
            // UploadDSPBinary
            // 
            this.UploadDSPBinary.Location = new System.Drawing.Point(43, 76);
            this.UploadDSPBinary.Name = "UploadDSPBinary";
            this.UploadDSPBinary.Size = new System.Drawing.Size(184, 86);
            this.UploadDSPBinary.TabIndex = 1;
            this.UploadDSPBinary.Text = "Upload DSP Binary";
            this.UploadDSPBinary.UseVisualStyleBackColor = true;
            this.UploadDSPBinary.Click += new System.EventHandler(this.UploadDSPBinary_Click);
            // 
            // StopDSP
            // 
            this.StopDSP.Location = new System.Drawing.Point(233, 76);
            this.StopDSP.Name = "StopDSP";
            this.StopDSP.Size = new System.Drawing.Size(184, 86);
            this.StopDSP.TabIndex = 2;
            this.StopDSP.Text = "Stop DSP";
            this.StopDSP.UseVisualStyleBackColor = true;
            this.StopDSP.Click += new System.EventHandler(this.StopDSP_Click);
            // 
            // SpikeThresh
            // 
            this.SpikeThresh.Location = new System.Drawing.Point(187, 188);
            this.SpikeThresh.Name = "SpikeThresh";
            this.SpikeThresh.Size = new System.Drawing.Size(88, 20);
            this.SpikeThresh.TabIndex = 3;
            this.SpikeThresh.Text = "100";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(40, 192);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(127, 13);
            this.label1.TabIndex = 4;
            this.label1.Text = "Analog Input Thresh [mV]";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(40, 215);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(74, 13);
            this.label2.TabIndex = 5;
            this.label2.Text = "Deadtime [ms]";
            this.label2.Visible = false;
            // 
            // Deadtime
            // 
            this.Deadtime.Location = new System.Drawing.Point(187, 211);
            this.Deadtime.Name = "Deadtime";
            this.Deadtime.Size = new System.Drawing.Size(88, 20);
            this.Deadtime.TabIndex = 6;
            this.Deadtime.Text = "1";
            this.Deadtime.Visible = false;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(6, 22);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(77, 13);
            this.label3.TabIndex = 7;
            this.label3.Text = "Amplitude [mV]";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(6, 44);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(67, 13);
            this.label4.TabIndex = 8;
            this.label4.Text = "Duration [µs]";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(6, 66);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(47, 13);
            this.label5.TabIndex = 9;
            this.label5.Text = "Repeats";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(6, 88);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(71, 13);
            this.label6.TabIndex = 10;
            this.label6.Text = "Stepsize [mV]";
            this.label6.Visible = false;
            // 
            // BoxStimAmplitude
            // 
            this.BoxStimAmplitude.Location = new System.Drawing.Point(122, 15);
            this.BoxStimAmplitude.Name = "BoxStimAmplitude";
            this.BoxStimAmplitude.Size = new System.Drawing.Size(88, 20);
            this.BoxStimAmplitude.TabIndex = 11;
            this.BoxStimAmplitude.Text = "300";
            // 
            // BoxStimDuration
            // 
            this.BoxStimDuration.Location = new System.Drawing.Point(122, 40);
            this.BoxStimDuration.Name = "BoxStimDuration";
            this.BoxStimDuration.Size = new System.Drawing.Size(88, 20);
            this.BoxStimDuration.TabIndex = 12;
            this.BoxStimDuration.Text = "100";
            // 
            // BoxStimStepsize
            // 
            this.BoxStimStepsize.Location = new System.Drawing.Point(122, 84);
            this.BoxStimStepsize.Name = "BoxStimStepsize";
            this.BoxStimStepsize.Size = new System.Drawing.Size(88, 20);
            this.BoxStimStepsize.TabIndex = 14;
            this.BoxStimStepsize.Text = "10";
            this.BoxStimStepsize.Visible = false;
            // 
            // BoxStimRepeats
            // 
            this.BoxStimRepeats.Location = new System.Drawing.Point(122, 62);
            this.BoxStimRepeats.Name = "BoxStimRepeats";
            this.BoxStimRepeats.Size = new System.Drawing.Size(88, 20);
            this.BoxStimRepeats.TabIndex = 13;
            this.BoxStimRepeats.Text = "1";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.BoxStimStepsize);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.BoxStimRepeats);
            this.groupBox1.Controls.Add(this.label5);
            this.groupBox1.Controls.Add(this.BoxStimDuration);
            this.groupBox1.Controls.Add(this.label6);
            this.groupBox1.Controls.Add(this.BoxStimAmplitude);
            this.groupBox1.Location = new System.Drawing.Point(45, 260);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(236, 111);
            this.groupBox1.TabIndex = 15;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Stimulation";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(45, 25);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(95, 13);
            this.label7.TabIndex = 16;
            this.label7.Text = "Raw Port (USB-A):";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(45, 50);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(95, 13);
            this.label8.TabIndex = 17;
            this.label8.Text = "DSP Port (USB-B):";
            // 
            // rawSerial
            // 
            this.rawSerial.Location = new System.Drawing.Point(167, 22);
            this.rawSerial.Name = "rawSerial";
            this.rawSerial.Size = new System.Drawing.Size(100, 20);
            this.rawSerial.TabIndex = 18;
            // 
            // dspSerial
            // 
            this.dspSerial.Location = new System.Drawing.Point(167, 47);
            this.dspSerial.Name = "dspSerial";
            this.dspSerial.Size = new System.Drawing.Size(100, 20);
            this.dspSerial.TabIndex = 19;
            // 
            // btnDeviceOK
            // 
            this.btnDeviceOK.Location = new System.Drawing.Point(298, 22);
            this.btnDeviceOK.Name = "btnDeviceOK";
            this.btnDeviceOK.Size = new System.Drawing.Size(119, 45);
            this.btnDeviceOK.TabIndex = 20;
            this.btnDeviceOK.UseVisualStyleBackColor = true;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(454, 423);
            this.Controls.Add(this.btnDeviceOK);
            this.Controls.Add(this.dspSerial);
            this.Controls.Add(this.rawSerial);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.Deadtime);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.SpikeThresh);
            this.Controls.Add(this.StopDSP);
            this.Controls.Add(this.UploadDSPBinary);
            this.Controls.Add(this.ConnectMEA);
            this.Name = "Form1";
            this.Text = "Control MEA2100 DSP";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button ConnectMEA;
        private System.Windows.Forms.Button UploadDSPBinary;
        private System.Windows.Forms.Button StopDSP;
        private System.Windows.Forms.TextBox SpikeThresh;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox Deadtime;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox BoxStimAmplitude;
        private System.Windows.Forms.TextBox BoxStimDuration;
        private System.Windows.Forms.TextBox BoxStimStepsize;
        private System.Windows.Forms.TextBox BoxStimRepeats;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.TextBox rawSerial;
        private System.Windows.Forms.TextBox dspSerial;
        private System.Windows.Forms.Button btnDeviceOK;
    }
}

