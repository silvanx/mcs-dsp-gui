
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
            this.panel1.SuspendLayout();
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
            this.panel1.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
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
            this.debugOutputBox.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
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
            this.meaConnectTestButton.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
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
            this.meaParamsTestButton.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
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
            this.MeaParamsButton.Location = new System.Drawing.Point(453, 98);
            this.MeaParamsButton.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
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
            this.MeaDisconnectButton.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.MeaDisconnectButton.Name = "MeaDisconnectButton";
            this.MeaDisconnectButton.Size = new System.Drawing.Size(138, 26);
            this.MeaDisconnectButton.TabIndex = 4;
            this.MeaDisconnectButton.Text = "MEA Disconnect";
            this.MeaDisconnectButton.UseVisualStyleBackColor = true;
            this.MeaDisconnectButton.Click += new System.EventHandler(this.MeaDisconnectButton_Click);
            // 
            // DebugControlsForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(600, 366);
            this.Controls.Add(this.MeaDisconnectButton);
            this.Controls.Add(this.MeaParamsButton);
            this.Controls.Add(this.meaParamsTestButton);
            this.Controls.Add(this.meaConnectTestButton);
            this.Controls.Add(this.panel1);
            this.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.Name = "DebugControlsForm";
            this.Text = "Debug Controls";
            this.panel1.ResumeLayout(false);
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
    }
}