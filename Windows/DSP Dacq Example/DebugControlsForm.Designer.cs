
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
            this.panel1.Location = new System.Drawing.Point(12, 12);
            this.panel1.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(587, 426);
            this.panel1.TabIndex = 0;
            // 
            // debugOutputBox
            // 
            this.debugOutputBox.BackColor = System.Drawing.Color.White;
            this.debugOutputBox.Cursor = System.Windows.Forms.Cursors.Arrow;
            this.debugOutputBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.debugOutputBox.Location = new System.Drawing.Point(0, 0);
            this.debugOutputBox.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.debugOutputBox.Name = "debugOutputBox";
            this.debugOutputBox.ReadOnly = true;
            this.debugOutputBox.Size = new System.Drawing.Size(587, 426);
            this.debugOutputBox.TabIndex = 0;
            this.debugOutputBox.Text = "";
            // 
            // meaConnectTestButton
            // 
            this.meaConnectTestButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.meaConnectTestButton.Location = new System.Drawing.Point(604, 12);
            this.meaConnectTestButton.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.meaConnectTestButton.Name = "meaConnectTestButton";
            this.meaConnectTestButton.Size = new System.Drawing.Size(184, 32);
            this.meaConnectTestButton.TabIndex = 1;
            this.meaConnectTestButton.Text = "MEA Connect";
            this.meaConnectTestButton.UseVisualStyleBackColor = true;
            this.meaConnectTestButton.Click += new System.EventHandler(this.Button1_Click);
            // 
            // meaParamsTestButton
            // 
            this.meaParamsTestButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.meaParamsTestButton.Location = new System.Drawing.Point(604, 84);
            this.meaParamsTestButton.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.meaParamsTestButton.Name = "meaParamsTestButton";
            this.meaParamsTestButton.Size = new System.Drawing.Size(184, 32);
            this.meaParamsTestButton.TabIndex = 2;
            this.meaParamsTestButton.Text = "MEA Connection Status";
            this.meaParamsTestButton.UseVisualStyleBackColor = true;
            this.meaParamsTestButton.Click += new System.EventHandler(this.Button2_Click);
            // 
            // MeaParamsButton
            // 
            this.MeaParamsButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.MeaParamsButton.Location = new System.Drawing.Point(604, 120);
            this.MeaParamsButton.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.MeaParamsButton.Name = "MeaParamsButton";
            this.MeaParamsButton.Size = new System.Drawing.Size(184, 32);
            this.MeaParamsButton.TabIndex = 3;
            this.MeaParamsButton.Text = "MEA Params";
            this.MeaParamsButton.UseVisualStyleBackColor = true;
            this.MeaParamsButton.Click += new System.EventHandler(this.MeaParamsButton_Click);
            // 
            // MeaDisconnectButton
            // 
            this.MeaDisconnectButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.MeaDisconnectButton.Location = new System.Drawing.Point(604, 48);
            this.MeaDisconnectButton.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.MeaDisconnectButton.Name = "MeaDisconnectButton";
            this.MeaDisconnectButton.Size = new System.Drawing.Size(184, 32);
            this.MeaDisconnectButton.TabIndex = 4;
            this.MeaDisconnectButton.Text = "MEA Disconnect";
            this.MeaDisconnectButton.UseVisualStyleBackColor = true;
            this.MeaDisconnectButton.Click += new System.EventHandler(this.MeaDisconnectButton_Click);
            // 
            // Read9A80RegisterButton
            // 
            this.Read9A80RegisterButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.Read9A80RegisterButton.Location = new System.Drawing.Point(604, 156);
            this.Read9A80RegisterButton.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.Read9A80RegisterButton.Name = "Read9A80RegisterButton";
            this.Read9A80RegisterButton.Size = new System.Drawing.Size(184, 32);
            this.Read9A80RegisterButton.TabIndex = 5;
            this.Read9A80RegisterButton.Text = "Read 0x9A80 register";
            this.Read9A80RegisterButton.UseVisualStyleBackColor = true;
            this.Read9A80RegisterButton.Click += new System.EventHandler(this.Read9A80RegisterButton_Click);
            // 
            // DebugControlsForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.Read9A80RegisterButton);
            this.Controls.Add(this.MeaDisconnectButton);
            this.Controls.Add(this.MeaParamsButton);
            this.Controls.Add(this.meaParamsTestButton);
            this.Controls.Add(this.meaConnectTestButton);
            this.Controls.Add(this.panel1);
            this.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
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
        private System.Windows.Forms.Button Read9A80RegisterButton;
    }
}