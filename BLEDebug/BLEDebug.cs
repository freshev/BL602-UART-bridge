using System;
using System.Text;
using System.Windows.Forms;
using BLEDevice;
using System.Collections.Generic;
using System.Threading.Tasks;

namespace BLEDebug {
    public partial class BLEDebug : Form {
        private BLEDevice.BLEDevice ble;
        private static int DiscoverTimeout = 3000;
        private static string ServiceUUID = "2B00";
        private static int MaxDebugLineCount = 1000;
        private const int ATHistoryLength = 20;
        private int currentHistory = 0;
        private static Characteristic ntf = null;
        private static Characteristic ind = null;
        private static Characteristic atcmd = null;
        private List<string> ATHistory = new List<string>();
        private List<string> ATCommands = new List<string>();

        public BLEDebug() {
            InitializeComponent();
            ATCommands.AddRange(new string[] { "", "AT+UART=0", "AT+UART=1", "AT+UARTTM", "AT+UARTBUF", "AT+WEL", "AT+TMODE", "AT+ENTM", "AT+MID", "AT+NDBGL", "AT+SMEM", "AT+FLASH", "AT+VER", "AT+BLE", "AT+BLENAME", "AT+BLENTFUUIDS", "" });
        }

        private void BLEDebug_Load(object sender, EventArgs e) {
            comboBoxDevices.Items.Clear();
            comboBoxDevices.Items.AddRange(BLEDevice.BLEDevice.Discover(DiscoverTimeout).ToArray());
            foreach (string name in comboBoxDevices.Items) {
                if (name != null && name.StartsWith("EG41B")) {
                    comboBoxDevices.SelectedItem = name;
                }
            }
            comboBoxAT.Items.AddRange(ATCommands.ToArray());
        }

        private void OpenDevice(string name) {
            ble = new BLEDevice.BLEDevice();
            ble.Name = name;
            Cursor = Cursors.WaitCursor;
            ble.ServiceUUID = ServiceUUID;
            if(ble.Open()) { 
                foreach (Characteristic ch in ble.Characteristics) {
                    if (ch.UUID.ToString().ToUpper().StartsWith("00002B10") && ch.CanRead && ch.CanNotify) ntf = ch;
                    if (ch.UUID.ToString().ToUpper().StartsWith("0000FED6") && ch.CanIndicate) ind = ch;
                    if (ch.UUID.ToString().ToUpper().StartsWith("0000FED4") && ch.CanRead && ch.CanWriteAsync && ch.CanNotify) atcmd = ch;
                }
                if (ntf != null && ind != null && atcmd != null) {
                    toolStripStatusLog.Text = "Open " + ble.Name + " success";
                    ntf.DataReceived += Ntf_DataReceived;
                    ind.DataReceived += Ind_DataReceived;
                    atcmd.DataReceived += Atcmd_DataReceived;
                    textBoxAT.Enabled = true;
                    buttonSendAT.Enabled = true;
                } else {
                    textBoxAT.Enabled = false;
                    buttonSendAT.Enabled = false;
                    toolStripStatusLog.Text = "Open " + ble.Name + " failed (can not get all characteristics)";
                }
            } else {
                textBoxAT.Enabled = false;
                buttonSendAT.Enabled = false;
                toolStripStatusLog.Text = "Open " + ble.Name + " failed. " + ble.LastError;
                ble = null;
            }
            Cursor = Cursors.Arrow;
        }        

        private void Ntf_DataReceived(object sender, BLEDataReceivedEventArgs e) {
            Characteristic ch = sender as Characteristic;
            if (ch != null && e.BytesToRead > 0) {
                StringBuilder sb = new StringBuilder();
                sb.Append(Encoding.UTF8.GetString(ch.ReadBytes(e.BytesToRead))).Append("\n");
                if (sb.Length > 0) {
                    string s = sb.ToString().Replace("\r\n", "\n").Replace("\n\n", "\n").Replace("\n\n", "\n");
                    if (!"\n".Equals(s)) AddBLEDebugText(s);
                }
            }
        }

        private void Ind_DataReceived(object sender, BLEDataReceivedEventArgs e) {
            Characteristic ch = sender as Characteristic;
            if(ch != null && e.BytesToRead > 0) {
                StringBuilder sb = new StringBuilder();
                sb.Append(Encoding.UTF8.GetString(ch.ReadBytes(e.BytesToRead))).Append("\n");
                if (sb.Length > 0) {
                    string s = sb.ToString().Replace("\r\n", "\n").Replace("\n\n", "\n").Replace("\n\n", "\n");
                    if (!"\n".Equals(s)) AddUARTDebugText(s);
                }
            }
        }

        private void Atcmd_DataReceived(object sender, BLEDataReceivedEventArgs e) {
            Characteristic ch = sender as Characteristic;
            if (ch != null && e.BytesToRead > 0) {
                StringBuilder sb = new StringBuilder();
                sb.Append(Encoding.UTF8.GetString(ch.ReadBytes(e.BytesToRead)));
                if (sb.Length > 0) {
                    string s = sb.ToString().Replace("\r\n", "\n").Replace("\n\n", "\n").Replace("\n\n", "\n");
                    if (!"\n".Equals(s)) AddATDebugText("<- " + s);
                }
            }
        }

        private void comboBoxDevices_SelectedIndexChanged(object sender, EventArgs e) {
            if(comboBoxDevices.SelectedItem != null && !"".Equals(comboBoxDevices.SelectedItem.ToString())) OpenDevice(comboBoxDevices.SelectedItem.ToString());
        }

        private void BLEDebug_FormClosed(object sender, FormClosedEventArgs e) {
            if (ble != null) ble.Close();
        }

        public delegate void SetStatusTextDelegate(string text);
        public void SetStatusText(string text) {
            if (statusStrip.InvokeRequired) {
                statusStrip.BeginInvoke(new SetStatusTextDelegate(SetStatusText), new object[] { text });
            } else {
                toolStripStatusLog.Text = text;
                statusStrip.Update();
            }
        }

        public delegate void AddBLEDebugTextDelegate(string text);
        public void AddBLEDebugText(string text) {
            if (richTextBoxBLEDebug.InvokeRequired) {
                richTextBoxBLEDebug.BeginInvoke(new AddBLEDebugTextDelegate(AddBLEDebugText), new object[] { text });
            } else {
                if (richTextBoxBLEDebug.Lines.Length > MaxDebugLineCount) {
                    List<string> lines = new List<String>(richTextBoxBLEDebug.Lines);
                    lines.RemoveRange(0, text.Split('\n').Length + richTextBoxBLEDebug.Lines.Length - MaxDebugLineCount);
                    richTextBoxBLEDebug.Lines = lines.ToArray();
                }
                richTextBoxBLEDebug.AppendText(text);
            }
        }

        public delegate void AddUARTDebugTextDelegate(string text);
        public void AddUARTDebugText(string text) {
            if (richTextBoxUARTDebug.InvokeRequired) {
                richTextBoxUARTDebug.BeginInvoke(new AddUARTDebugTextDelegate(AddUARTDebugText), new object[] { text });
            } else {
                if (richTextBoxUARTDebug.Lines.Length > MaxDebugLineCount) {
                    List<string> lines = new List<String>(richTextBoxUARTDebug.Lines);
                    lines.RemoveRange(0, text.Split('\n').Length + richTextBoxUARTDebug.Lines.Length - MaxDebugLineCount);
                    richTextBoxUARTDebug.Lines = lines.ToArray();
                }
                richTextBoxUARTDebug.AppendText(text);
            }
        }

        public delegate void AddATDebugTextDelegate(string text);
        public void AddATDebugText(string text) {
            if (richTextBoxATDebug.InvokeRequired) {
                richTextBoxATDebug.BeginInvoke(new AddATDebugTextDelegate(AddATDebugText), new object[] { text });
            } else {
                if(richTextBoxATDebug.Lines.Length > MaxDebugLineCount) {
                    List<string> lines = new List<String>(richTextBoxATDebug.Lines);
                    lines.RemoveRange(0, text.Split('\n').Length + richTextBoxATDebug.Lines.Length - MaxDebugLineCount);
                    richTextBoxATDebug.Lines = lines.ToArray();
                }                
                richTextBoxATDebug.AppendText(text);
            }
        }

        private void BLEDebug_KeyUp(object sender, KeyEventArgs e) {
            if (e.KeyCode == Keys.Enter) {
                buttonSendAT_Click(null, null);
            }
            if (e.KeyCode == Keys.Up) {
                textBoxAT.Text = ATHistory[currentHistory];
                if (currentHistory < ATHistoryLength - 1 && currentHistory < ATHistory.Count - 1) currentHistory++;
                e.SuppressKeyPress = true;
                e.Handled = true;
            } else if (e.KeyCode == Keys.Down) {
                textBoxAT.Text = ATHistory[currentHistory];                
                if (currentHistory > 0) currentHistory--;
                e.SuppressKeyPress = true;
                e.Handled = true;
            } else {
                currentHistory = 0;
            }
        }
    
        private void buttonSendAT_Click(object sender, EventArgs e) {
            if (!"".Equals(textBoxAT.Text)) {
                RunCommand(textBoxAT.Text + "\n");
                textBoxAT.Text = "";
            }
        }

        private void comboBoxAT_SelectedIndexChanged(object sender, EventArgs e) {
            if (!"".Equals(comboBoxAT.Text)) {
                RunCommand(comboBoxAT.Text + "\n");
                comboBoxAT.SelectedIndex = 0;
            }
        }

        private void BLEDebug_Shown(object sender, EventArgs e) {
            textBoxAT.Focus();
        }

        private void richTextBoxBLEDebug_TextChanged(object sender, EventArgs e) {
            richTextBoxBLEDebug.SelectionStart = richTextBoxBLEDebug.Text.Length;
            richTextBoxBLEDebug.ScrollToCaret();
        }

        private void richTextBoxUARTDebug_TextChanged(object sender, EventArgs e) {
            richTextBoxUARTDebug.SelectionStart = richTextBoxUARTDebug.Text.Length;
            richTextBoxUARTDebug.ScrollToCaret();
        }

        private void richTextBoxATDebug_TextChanged(object sender, EventArgs e) {
            richTextBoxATDebug.SelectionStart = richTextBoxATDebug.Text.Length;
            richTextBoxATDebug.ScrollToCaret();
        }

        private void buttonReconnect_Click(object sender, EventArgs e) {
            if (ble != null) {
                Cursor = Cursors.WaitCursor;
                if (ble.Reconnect()) {
                    ntf.DataReceived -= Ntf_DataReceived;
                    ind.DataReceived -= Ind_DataReceived;
                    atcmd.DataReceived -= Atcmd_DataReceived;
                    ntf = null;
                    ind = null;
                    atcmd = null;
                    foreach (Characteristic ch in ble.Characteristics) {
                        if (ch.UUID.ToString().ToUpper().StartsWith("00002B10") && ch.CanRead && ch.CanNotify) ntf = ch;
                        if (ch.UUID.ToString().ToUpper().StartsWith("0000FED6") && ch.CanIndicate) ind = ch;
                        if (ch.UUID.ToString().ToUpper().StartsWith("0000FED4") && ch.CanRead && ch.CanWriteAsync && ch.CanNotify) atcmd = ch;
                    }
                    if (ntf != null && ind != null && atcmd != null) {
                        toolStripStatusLog.Text = "Reconnect " + ble.Name + " success";
                        ntf.DataReceived += Ntf_DataReceived;
                        ind.DataReceived += Ind_DataReceived;
                        atcmd.DataReceived += Atcmd_DataReceived;
                        textBoxAT.Enabled = true;
                        buttonSendAT.Enabled = true;
                    } else {
                        textBoxAT.Enabled = false;
                        buttonSendAT.Enabled = false;
                        toolStripStatusLog.Text = "Open " + ble.Name + " failed (can not get all characteristics)";
                    }                    
                } else {
                    textBoxAT.Enabled = false;
                    buttonSendAT.Enabled = false;
                    toolStripStatusLog.Text = "Open " + ble.Name + " failed. " + ble.LastError;
                    ble = null;
                }
                Cursor = Cursors.Arrow;
            }
        }

        #region RunCommand
        private bool RunCommand(string s) {
            bool finalres = false;
            AddATDebugText("-> " + s);
            if (atcmd != null) {
                bool res = atcmd.Write(Encoding.UTF8.GetBytes(s));
                if (res == false) {
                    // try to reopen device
                    if (ble != null) ble.Close();
                    OpenDevice(comboBoxDevices.SelectedItem.ToString());
                    bool res2 = atcmd.Write(Encoding.UTF8.GetBytes(s));
                    if (res2 == true) {
                        SetStatusText("AT command sent");
                        finalres = true;
                    } else SetStatusText("AT command NOT sent");
                } else {
                    SetStatusText("AT command sent");
                    finalres = true;
                }
            }
            if (ATHistory.Count > ATHistoryLength) ATHistory.RemoveAt(ATHistory.Count - 1);
            ATHistory.Insert(0, textBoxAT.Text);
            return finalres;
        }
        #endregion

        private void buttonClear_Click(object sender, EventArgs e) {
            richTextBoxATDebug.ResetText();
            richTextBoxBLEDebug.ResetText();
            richTextBoxUARTDebug.ResetText();
        }
    }
}
