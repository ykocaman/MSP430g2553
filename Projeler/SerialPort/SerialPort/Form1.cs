using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Threading;

namespace SerialPort
{
    // Yusuf KOCAMAN

    public partial class frmMain : Form
    {
        public String RxString;

        public frmMain()
        {
            InitializeComponent();
        }

        private void port_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            RxString = port.ReadExisting();
            this.Invoke(new EventHandler(DisplayText));
        }

        private void DisplayText(object sender, EventArgs e)
        {
            txtLog.AppendText(RxString);
        }

        private void btnStart_Click(object sender, EventArgs e)
        {
            if (!port.IsOpen)
            {
                port.PortName = cmbList.Text;
                port.Open();
                btnStart.Enabled = false;
                btnStop.Enabled = true;
                btnSend.Enabled = true;
                txtData.Enabled = true;
             }
        }

        private void btnStop_Click(object sender, EventArgs e)
        {
            if (port.IsOpen)
            {
                ThreadPool.QueueUserWorkItem(new WaitCallback(ClosePort));
                btnStop.Enabled = false;
                btnSend.Enabled = false;
                btnStart.Enabled = true;
                txtData.Enabled = false;
            }
        }

        private void ClosePort(Object stateInfo)
        {
            port.Close();
        }

        private void btnSend_Click(object sender, EventArgs e)
        {
            if (txtData.Text.Length > 0)
            {
                port.Write(txtData.Text + "\n");
                txtLog.AppendText("Gönderilen : " + txtData.Text + "\n");
                txtData.Text = String.Empty;
            }
        }

        private void txtData_KeyUp(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter && btnSend.Enabled)
                this.btnSend_Click(sender, e);
            return;
        }
    }
}
