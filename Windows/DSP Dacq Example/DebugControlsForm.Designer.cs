
namespace MCS_USB_Windows_Forms_Application1
{
    partial class DebugControlsForm
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
            this.panel1 = new System.Windows.Forms.Panel();
            this.debugOutputBox = new System.Windows.Forms.RichTextBox();
            this.meaConnectTestButton = new System.Windows.Forms.Button();
            this.meaParamsTestButton = new System.Windows.Forms.Button();
            this.MeaParamsButton = new System.Windows.Forms.Button();
            this.MeaDisconnectButton = new System.Windows.Forms.Button();
            this.Read9A80RegisterButton = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.Write9A80RegisterButton = new System.Windows.Forms.Button();
            this.radioButton17 = new System.Windows.Forms.RadioButton();
            this.radioButton16 = new System.Windows.Forms.RadioButton();
            this.radioButton13 = new System.Windows.Forms.RadioButton();
            this.radioButton14 = new System.Windows.Forms.RadioButton();
            this.radioButton15 = new System.Windows.Forms.RadioButton();
            this.radioButton10 = new System.Windows.Forms.RadioButton();
            this.radioButton11 = new System.Windows.Forms.RadioButton();
            this.radioButton12 = new System.Windows.Forms.RadioButton();
            this.radioButton7 = new System.Windows.Forms.RadioButton();
            this.radioButton8 = new System.Windows.Forms.RadioButton();
            this.radioButton9 = new System.Windows.Forms.RadioButton();
            this.radioButton4 = new System.Windows.Forms.RadioButton();
            this.radioButton5 = new System.Windows.Forms.RadioButton();
            this.radioButton6 = new System.Windows.Forms.RadioButton();
            this.radioButton3 = new System.Windows.Forms.RadioButton();
            this.radioButton2 = new System.Windows.Forms.RadioButton();
            this.radioButton1 = new System.Windows.Forms.RadioButton();
            this.panel1.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // panel1
            // 
            this.panel1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.panel1.AutoSize = true;
            this.panel1.BackColor = System.Drawing.SystemColors.MenuHighlight;
            this.panel1.Controls.Add(this.debugOutputBox);
            this.panel1.Location = new System.Drawing.Point(9, 10);
            this.panel1.Margin = new System.Windows.Forms.Padding(2);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(440, 346);
            this.panel1.TabIndex = 0;
            // 
            // debugOutputBox
            // 
            this.debugOutputBox.BackColor = System.Drawing.Color.White;
            this.debugOutputBox.Cursor = System.Windows.Forms.Cursors.Arrow;
            this.debugOutputBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.debugOutputBox.Location = new System.Drawing.Point(0, 0);
            this.debugOutputBox.Margin = new System.Windows.Forms.Padding(2);
            this.debugOutputBox.Name = "debugOutputBox";
            this.debugOutputBox.ReadOnly = true;
            this.debugOutputBox.Size = new System.Drawing.Size(440, 346);
            this.debugOutputBox.TabIndex = 0;
            this.debugOutputBox.Text = "";
            // 
            // meaConnectTestButton
            // 
            this.meaConnectTestButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.meaConnectTestButton.Location = new System.Drawing.Point(453, 10);
            this.meaConnectTestButton.Margin = new System.Windows.Forms.Padding(2);
            this.meaConnectTestButton.Name = "meaConnectTestButton";
            this.meaConnectTestButton.Size = new System.Drawing.Size(138, 26);
            this.meaConnectTestButton.TabIndex = 1;
            this.meaConnectTestButton.Text = "MEA Connect";
            this.meaConnectTestButton.UseVisualStyleBackColor = true;
            this.meaConnectTestButton.Click += new System.EventHandler(this.Button1_Click);
            // 
            // meaParamsTestButton
            // 
            this.meaParamsTestButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.meaParamsTestButton.Location = new System.Drawing.Point(453, 68);
            this.meaParamsTestButton.Margin = new System.Windows.Forms.Padding(2);
            this.meaParamsTestButton.Name = "meaParamsTestButton";
            this.meaParamsTestButton.Size = new System.Drawing.Size(138, 26);
            this.meaParamsTestButton.TabIndex = 2;
            this.meaParamsTestButton.Text = "MEA Connection Status";
            this.meaParamsTestButton.UseVisualStyleBackColor = true;
            this.meaParamsTestButton.Click += new System.EventHandler(this.Button2_Click);
            // 
            // MeaParamsButton
            // 
            this.MeaParamsButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.MeaParamsButton.Location = new System.Drawing.Point(453, 97);
            this.MeaParamsButton.Margin = new System.Windows.Forms.Padding(2);
            this.MeaParamsButton.Name = "MeaParamsButton";
            this.MeaParamsButton.Size = new System.Drawing.Size(138, 26);
            this.MeaParamsButton.TabIndex = 3;
            this.MeaParamsButton.Text = "MEA Params";
            this.MeaParamsButton.UseVisualStyleBackColor = true;
            this.MeaParamsButton.Click += new System.EventHandler(this.MeaParamsButton_Click);
            // 
            // MeaDisconnectButton
            // 
            this.MeaDisconnectButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.MeaDisconnectButton.Location = new System.Drawing.Point(453, 39);
            this.MeaDisconnectButton.Margin = new System.Windows.Forms.Padding(2);
            this.MeaDisconnectButton.Name = "MeaDisconnectButton";
            this.MeaDisconnectButton.Size = new System.Drawing.Size(138, 26);
            this.MeaDisconnectButton.TabIndex = 4;
            this.MeaDisconnectButton.Text = "MEA Disconnect";
            this.MeaDisconnectButton.UseVisualStyleBackColor = true;
            this.MeaDisconnectButton.Click += new System.EventHandler(this.MeaDisconnectButton_Click);
            // 
            // Read9A80RegisterButton
            // 
            this.Read9A80RegisterButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.Read9A80RegisterButton.Location = new System.Drawing.Point(453, 127);
            this.Read9A80RegisterButton.Margin = new System.Windows.Forms.Padding(2);
            this.Read9A80RegisterButton.Name = "Read9A80RegisterButton";
            this.Read9A80RegisterButton.Size = new System.Drawing.Size(138, 26);
            this.Read9A80RegisterButton.TabIndex = 5;
            this.Read9A80RegisterButton.Text = "Read 0x9A80 register";
            this.Read9A80RegisterButton.UseVisualStyleBackColor = true;
            this.Read9A80RegisterButton.Click += new System.EventHandler(this.Read9A80RegisterButton_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBox1.Controls.Add(this.Write9A80RegisterButton);
            this.groupBox1.Controls.Add(this.radioButton17);
            this.groupBox1.Controls.Add(this.radioButton16);
            this.groupBox1.Controls.Add(this.radioButton13);
            this.groupBox1.Controls.Add(this.radioButton14);
            this.groupBox1.Controls.Add(this.radioButton15);
            this.groupBox1.Controls.Add(this.radioButton10);
            this.groupBox1.Controls.Add(this.radioButton11);
            this.groupBox1.Controls.Add(this.radioButton12);
            this.groupBox1.Controls.Add(this.radioButton7);
            this.groupBox1.Controls.Add(this.radioButton8);
            this.groupBox1.Controls.Add(this.radioButton9);
            this.groupBox1.Controls.Add(this.radioButton4);
            this.groupBox1.Controls.Add(this.radioButton5);
            this.groupBox1.Controls.Add(this.radioButton6);
            this.groupBox1.Controls.Add(this.radioButton3);
            this.groupBox1.Controls.Add(this.radioButton2);
            this.groupBox1.Controls.Add(this.radioButton1);
            this.groupBox1.Location = new System.Drawing.Point(453, 156);
            this.groupBox1.Margin = new System.Windows.Forms.Padding(1);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Padding = new System.Windows.Forms.Padding(1);
            this.groupBox1.Size = new System.Drawing.Size(138, 184);
            this.groupBox1.TabIndex = 6;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Write 0x9A80 register";
            // 
            // Write9A80RegisterButton
            // 
            this.Write9A80RegisterButton.Location = new System.Drawing.Point(4, 155);
            this.Write9A80RegisterButton.Name = "Write9A80RegisterButton";
            this.Write9A80RegisterButton.Size = new System.Drawing.Size(130, 23);
            this.Write9A80RegisterButton.TabIndex = 17;
            this.Write9A80RegisterButton.Text = "Write";
            this.Write9A80RegisterButton.UseVisualStyleBackColor = true;
            this.Write9A80RegisterButton.Click += new System.EventHandler(this.Write9A80RegisterButton_Click);
            // 
            // radioButton17
            // 
            this.radioButton17.AutoSize = true;
            this.radioButton17.Location = new System.Drawing.Point(41, 132);
            this.radioButton17.Name = "radioButton17";
            this.radioButton17.Size = new System.Drawing.Size(37, 17);
            this.radioButton17.TabIndex = 16;
            this.radioButton17.TabStop = true;
            this.radioButton17.Text = "16";
            this.radioButton17.UseVisualStyleBackColor = true;
            this.radioButton17.CheckedChanged += new System.EventHandler(this.radioButton_CheckedChanged);
            // 
            // radioButton16
            // 
            this.radioButton16.AutoSize = true;
            this.radioButton16.Location = new System.Drawing.Point(4, 132);
            this.radioButton16.Name = "radioButton16";
            this.radioButton16.Size = new System.Drawing.Size(37, 17);
            this.radioButton16.TabIndex = 15;
            this.radioButton16.TabStop = true;
            this.radioButton16.Text = "15";
            this.radioButton16.UseVisualStyleBackColor = true;
            this.radioButton16.CheckedChanged += new System.EventHandler(this.radioButton_CheckedChanged);
            // 
            // radioButton13
            // 
            this.radioButton13.AutoSize = true;
            this.radioButton13.Location = new System.Drawing.Point(78, 109);
            this.radioButton13.Name = "radioButton13";
            this.radioButton13.Size = new System.Drawing.Size(37, 17);
            this.radioButton13.TabIndex = 14;
            this.radioButton13.TabStop = true;
            this.radioButton13.Text = "14";
            this.radioButton13.UseVisualStyleBackColor = true;
            this.radioButton13.CheckedChanged += new System.EventHandler(this.radioButton_CheckedChanged);
            // 
            // radioButton14
            // 
            this.radioButton14.AutoSize = true;
            this.radioButton14.Location = new System.Drawing.Point(41, 109);
            this.radioButton14.Name = "radioButton14";
            this.radioButton14.Size = new System.Drawing.Size(37, 17);
            this.radioButton14.TabIndex = 13;
            this.radioButton14.TabStop = true;
            this.radioButton14.Text = "13";
            this.radioButton14.UseVisualStyleBackColor = true;
            this.radioButton14.CheckedChanged += new System.EventHandler(this.radioButton_CheckedChanged);
            // 
            // radioButton15
            // 
            this.radioButton15.AutoSize = true;
            this.radioButton15.Location = new System.Drawing.Point(4, 109);
            this.radioButton15.Name = "radioButton15";
            this.radioButton15.Size = new System.Drawing.Size(37, 17);
            this.radioButton15.TabIndex = 12;
            this.radioButton15.TabStop = true;
            this.radioButton15.Text = "12";
            this.radioButton15.UseVisualStyleBackColor = true;
            this.radioButton15.CheckedChanged += new System.EventHandler(this.radioButton_CheckedChanged);
            // 
            // radioButton10
            // 
            this.radioButton10.AutoSize = true;
            this.radioButton10.Location = new System.Drawing.Point(78, 86);
            this.radioButton10.Name = "radioButton10";
            this.radioButton10.Size = new System.Drawing.Size(37, 17);
            this.radioButton10.TabIndex = 11;
            this.radioButton10.TabStop = true;
            this.radioButton10.Text = "11";
            this.radioButton10.UseVisualStyleBackColor = true;
            this.radioButton10.CheckedChanged += new System.EventHandler(this.radioButton_CheckedChanged);
            // 
            // radioButton11
            // 
            this.radioButton11.AutoSize = true;
            this.radioButton11.Location = new System.Drawing.Point(41, 86);
            this.radioButton11.Name = "radioButton11";
            this.radioButton11.Size = new System.Drawing.Size(37, 17);
            this.radioButton11.TabIndex = 10;
            this.radioButton11.TabStop = true;
            this.radioButton11.Text = "10";
            this.radioButton11.UseVisualStyleBackColor = true;
            this.radioButton11.CheckedChanged += new System.EventHandler(this.radioButton_CheckedChanged);
            // 
            // radioButton12
            // 
            this.radioButton12.AutoSize = true;
            this.radioButton12.Location = new System.Drawing.Point(4, 86);
            this.radioButton12.Name = "radioButton12";
            this.radioButton12.Size = new System.Drawing.Size(31, 17);
            this.radioButton12.TabIndex = 9;
            this.radioButton12.TabStop = true;
            this.radioButton12.Text = "9";
            this.radioButton12.UseVisualStyleBackColor = true;
            this.radioButton12.CheckedChanged += new System.EventHandler(this.radioButton_CheckedChanged);
            // 
            // radioButton7
            // 
            this.radioButton7.AutoSize = true;
            this.radioButton7.Location = new System.Drawing.Point(78, 63);
            this.radioButton7.Name = "radioButton7";
            this.radioButton7.Size = new System.Drawing.Size(31, 17);
            this.radioButton7.TabIndex = 8;
            this.radioButton7.TabStop = true;
            this.radioButton7.Text = "8";
            this.radioButton7.UseVisualStyleBackColor = true;
            this.radioButton7.CheckedChanged += new System.EventHandler(this.radioButton_CheckedChanged);
            // 
            // radioButton8
            // 
            this.radioButton8.AutoSize = true;
            this.radioButton8.Location = new System.Drawing.Point(41, 63);
            this.radioButton8.Name = "radioButton8";
            this.radioButton8.Size = new System.Drawing.Size(31, 17);
            this.radioButton8.TabIndex = 7;
            this.radioButton8.TabStop = true;
            this.radioButton8.Text = "7";
            this.radioButton8.UseVisualStyleBackColor = true;
            this.radioButton8.CheckedChanged += new System.EventHandler(this.radioButton_CheckedChanged);
            // 
            // radioButton9
            // 
            this.radioButton9.AutoSize = true;
            this.radioButton9.Location = new System.Drawing.Point(4, 63);
            this.radioButton9.Name = "radioButton9";
            this.radioButton9.Size = new System.Drawing.Size(31, 17);
            this.radioButton9.TabIndex = 6;
            this.radioButton9.TabStop = true;
            this.radioButton9.Text = "6";
            this.radioButton9.UseVisualStyleBackColor = true;
            this.radioButton9.CheckedChanged += new System.EventHandler(this.radioButton_CheckedChanged);
            // 
            // radioButton4
            // 
            this.radioButton4.AutoSize = true;
            this.radioButton4.Location = new System.Drawing.Point(78, 40);
            this.radioButton4.Name = "radioButton4";
            this.radioButton4.Size = new System.Drawing.Size(31, 17);
            this.radioButton4.TabIndex = 5;
            this.radioButton4.TabStop = true;
            this.radioButton4.Text = "5";
            this.radioButton4.UseVisualStyleBackColor = true;
            this.radioButton4.CheckedChanged += new System.EventHandler(this.radioButton_CheckedChanged);
            // 
            // radioButton5
            // 
            this.radioButton5.AutoSize = true;
            this.radioButton5.Location = new System.Drawing.Point(41, 40);
            this.radioButton5.Name = "radioButton5";
            this.radioButton5.Size = new System.Drawing.Size(31, 17);
            this.radioButton5.TabIndex = 4;
            this.radioButton5.TabStop = true;
            this.radioButton5.Text = "4";
            this.radioButton5.UseVisualStyleBackColor = true;
            this.radioButton5.CheckedChanged += new System.EventHandler(this.radioButton_CheckedChanged);
            // 
            // radioButton6
            // 
            this.radioButton6.AutoSize = true;
            this.radioButton6.Location = new System.Drawing.Point(4, 40);
            this.radioButton6.Name = "radioButton6";
            this.radioButton6.Size = new System.Drawing.Size(31, 17);
            this.radioButton6.TabIndex = 3;
            this.radioButton6.TabStop = true;
            this.radioButton6.Text = "3";
            this.radioButton6.UseVisualStyleBackColor = true;
            this.radioButton6.CheckedChanged += new System.EventHandler(this.radioButton_CheckedChanged);
            // 
            // radioButton3
            // 
            this.radioButton3.AutoSize = true;
            this.radioButton3.Location = new System.Drawing.Point(78, 17);
            this.radioButton3.Name = "radioButton3";
            this.radioButton3.Size = new System.Drawing.Size(31, 17);
            this.radioButton3.TabIndex = 2;
            this.radioButton3.TabStop = true;
            this.radioButton3.Text = "2";
            this.radioButton3.UseVisualStyleBackColor = true;
            this.radioButton3.CheckedChanged += new System.EventHandler(this.radioButton_CheckedChanged);
            // 
            // radioButton2
            // 
            this.radioButton2.AutoSize = true;
            this.radioButton2.Location = new System.Drawing.Point(41, 17);
            this.radioButton2.Name = "radioButton2";
            this.radioButton2.Size = new System.Drawing.Size(31, 17);
            this.radioButton2.TabIndex = 1;
            this.radioButton2.TabStop = true;
            this.radioButton2.Text = "1";
            this.radioButton2.UseVisualStyleBackColor = true;
            this.radioButton2.CheckedChanged += new System.EventHandler(this.radioButton_CheckedChanged);
            // 
            // radioButton1
            // 
            this.radioButton1.AutoSize = true;
            this.radioButton1.Location = new System.Drawing.Point(4, 17);
            this.radioButton1.Name = "radioButton1";
            this.radioButton1.Size = new System.Drawing.Size(31, 17);
            this.radioButton1.TabIndex = 0;
            this.radioButton1.TabStop = true;
            this.radioButton1.Text = "0";
            this.radioButton1.UseVisualStyleBackColor = true;
            this.radioButton1.CheckedChanged += new System.EventHandler(this.radioButton_CheckedChanged);
            // 
            // DebugControlsForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(600, 366);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.Read9A80RegisterButton);
            this.Controls.Add(this.MeaDisconnectButton);
            this.Controls.Add(this.MeaParamsButton);
            this.Controls.Add(this.meaParamsTestButton);
            this.Controls.Add(this.meaConnectTestButton);
            this.Controls.Add(this.panel1);
            this.Margin = new System.Windows.Forms.Padding(2);
            this.Name = "DebugControlsForm";
            this.Text = "Debug Controls";
            this.panel1.ResumeLayout(false);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.RichTextBox debugOutputBox;
        private System.Windows.Forms.Button meaConnectTestButton;
        private System.Windows.Forms.Button meaParamsTestButton;
        private System.Windows.Forms.Button MeaParamsButton;
        private System.Windows.Forms.Button MeaDisconnectButton;
        private System.Windows.Forms.Button Read9A80RegisterButton;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.RadioButton radioButton16;
        private System.Windows.Forms.RadioButton radioButton13;
        private System.Windows.Forms.RadioButton radioButton14;
        private System.Windows.Forms.RadioButton radioButton15;
        private System.Windows.Forms.RadioButton radioButton10;
        private System.Windows.Forms.RadioButton radioButton11;
        private System.Windows.Forms.RadioButton radioButton12;
        private System.Windows.Forms.RadioButton radioButton7;
        private System.Windows.Forms.RadioButton radioButton8;
        private System.Windows.Forms.RadioButton radioButton9;
        private System.Windows.Forms.RadioButton radioButton4;
        private System.Windows.Forms.RadioButton radioButton5;
        private System.Windows.Forms.RadioButton radioButton6;
        private System.Windows.Forms.RadioButton radioButton3;
        private System.Windows.Forms.RadioButton radioButton2;
        private System.Windows.Forms.RadioButton radioButton1;
        private System.Windows.Forms.Button Write9A80RegisterButton;
        private System.Windows.Forms.RadioButton radioButton17;
    }
}