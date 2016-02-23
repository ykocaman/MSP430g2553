namespace SerialPort
{
    partial class frmMain
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
            this.components = new System.ComponentModel.Container();
            this.btnStart = new System.Windows.Forms.Button();
            this.port = new System.IO.Ports.SerialPort(this.components);
            this.txtLog = new System.Windows.Forms.TextBox();
            this.btnStop = new System.Windows.Forms.Button();
            this.cmbList = new System.Windows.Forms.ComboBox();
            this.txtData = new System.Windows.Forms.TextBox();
            this.btnSend = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // btnStart
            // 
            this.btnStart.Location = new System.Drawing.Point(299, 14);
            this.btnStart.Name = "btnStart";
            this.btnStart.Size = new System.Drawing.Size(75, 23);
            this.btnStart.TabIndex = 0;
            this.btnStart.Text = "Başla";
            this.btnStart.UseVisualStyleBackColor = true;
            this.btnStart.Click += new System.EventHandler(this.btnStart_Click);
            // 
            // port
            // 
            this.port.PortName = "COM12";
            this.port.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.port_DataReceived);
            // 
            // txtLog
            // 
            this.txtLog.BackColor = System.Drawing.SystemColors.Window;
            this.txtLog.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.txtLog.Location = new System.Drawing.Point(12, 43);
            this.txtLog.Multiline = true;
            this.txtLog.Name = "txtLog";
            this.txtLog.ReadOnly = true;
            this.txtLog.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.txtLog.Size = new System.Drawing.Size(489, 238);
            this.txtLog.TabIndex = 1;
            // 
            // btnStop
            // 
            this.btnStop.Enabled = false;
            this.btnStop.Location = new System.Drawing.Point(218, 14);
            this.btnStop.Name = "btnStop";
            this.btnStop.Size = new System.Drawing.Size(75, 23);
            this.btnStop.TabIndex = 2;
            this.btnStop.Text = "Dur";
            this.btnStop.UseVisualStyleBackColor = true;
            this.btnStop.Click += new System.EventHandler(this.btnStop_Click);
            // 
            // cmbList
            // 
            this.cmbList.FormattingEnabled = true;
            this.cmbList.Items.AddRange(new object[] {
            "COM1",
            "COM2",
            "COM3",
            "COM4",
            "COM5",
            "COM6",
            "COM7",
            "COM8",
            "COM9",
            "COM10",
            "COM11",
            "COM12",
            "COM13",
            "COM14",
            "COM15"});
            this.cmbList.Location = new System.Drawing.Point(380, 14);
            this.cmbList.Name = "cmbList";
            this.cmbList.Size = new System.Drawing.Size(121, 21);
            this.cmbList.TabIndex = 3;
            this.cmbList.Text = "COM12";
            // 
            // txtData
            // 
            this.txtData.Enabled = false;
            this.txtData.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.txtData.Location = new System.Drawing.Point(12, 287);
            this.txtData.MaxLength = 16;
            this.txtData.Name = "txtData";
            this.txtData.Size = new System.Drawing.Size(418, 23);
            this.txtData.TabIndex = 4;
            this.txtData.KeyUp += new System.Windows.Forms.KeyEventHandler(this.txtData_KeyUp);
            // 
            // btnSend
            // 
            this.btnSend.Enabled = false;
            this.btnSend.Location = new System.Drawing.Point(436, 287);
            this.btnSend.Name = "btnSend";
            this.btnSend.Size = new System.Drawing.Size(65, 23);
            this.btnSend.TabIndex = 5;
            this.btnSend.Text = "Gönder";
            this.btnSend.UseVisualStyleBackColor = true;
            this.btnSend.Click += new System.EventHandler(this.btnSend_Click);
            // 
            // frmMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(513, 319);
            this.Controls.Add(this.btnSend);
            this.Controls.Add(this.txtData);
            this.Controls.Add(this.cmbList);
            this.Controls.Add(this.btnStop);
            this.Controls.Add(this.txtLog);
            this.Controls.Add(this.btnStart);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.Name = "frmMain";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Seri Port İstemcisi";
            this.TopMost = true;
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnStart;
        private System.IO.Ports.SerialPort port;
        private System.Windows.Forms.TextBox txtLog;
        private System.Windows.Forms.Button btnStop;
        private System.Windows.Forms.ComboBox cmbList;
        private System.Windows.Forms.TextBox txtData;
        private System.Windows.Forms.Button btnSend;
    }
}

