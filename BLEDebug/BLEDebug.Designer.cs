namespace BLEDebug {
    partial class BLEDebug {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing) {
            if (disposing && (components != null)) {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent() {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(BLEDebug));
            this.comboBoxDevices = new System.Windows.Forms.ComboBox();
            this.statusStrip = new System.Windows.Forms.StatusStrip();
            this.toolStripStatusLog = new System.Windows.Forms.ToolStripStatusLabel();
            this.panel1 = new System.Windows.Forms.Panel();
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.groupBoxDebug = new System.Windows.Forms.GroupBox();
            this.richTextBoxBLEDebug = new System.Windows.Forms.RichTextBox();
            this.splitContainer2 = new System.Windows.Forms.SplitContainer();
            this.groupBoxUARTDebug = new System.Windows.Forms.GroupBox();
            this.richTextBoxUARTDebug = new System.Windows.Forms.RichTextBox();
            this.groupBoxATDebug = new System.Windows.Forms.GroupBox();
            this.buttonSendAT = new System.Windows.Forms.Button();
            this.textBoxAT = new System.Windows.Forms.TextBox();
            this.richTextBoxATDebug = new System.Windows.Forms.RichTextBox();
            this.buttonReconnect = new System.Windows.Forms.Button();
            this.comboBoxAT = new System.Windows.Forms.ComboBox();
            this.statusStrip.SuspendLayout();
            this.panel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            this.groupBoxDebug.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer2)).BeginInit();
            this.splitContainer2.Panel1.SuspendLayout();
            this.splitContainer2.Panel2.SuspendLayout();
            this.splitContainer2.SuspendLayout();
            this.groupBoxUARTDebug.SuspendLayout();
            this.groupBoxATDebug.SuspendLayout();
            this.SuspendLayout();
            // 
            // comboBoxDevices
            // 
            this.comboBoxDevices.FormattingEnabled = true;
            this.comboBoxDevices.Location = new System.Drawing.Point(12, 12);
            this.comboBoxDevices.Name = "comboBoxDevices";
            this.comboBoxDevices.Size = new System.Drawing.Size(235, 24);
            this.comboBoxDevices.TabIndex = 2;
            this.comboBoxDevices.TabStop = false;
            this.comboBoxDevices.SelectedIndexChanged += new System.EventHandler(this.comboBoxDevices_SelectedIndexChanged);
            // 
            // statusStrip
            // 
            this.statusStrip.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.statusStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripStatusLog});
            this.statusStrip.Location = new System.Drawing.Point(0, 449);
            this.statusStrip.Name = "statusStrip";
            this.statusStrip.Size = new System.Drawing.Size(1085, 22);
            this.statusStrip.TabIndex = 1;
            this.statusStrip.Text = "statusStrip";
            // 
            // toolStripStatusLog
            // 
            this.toolStripStatusLog.Name = "toolStripStatusLog";
            this.toolStripStatusLog.Size = new System.Drawing.Size(0, 17);
            // 
            // panel1
            // 
            this.panel1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.panel1.Controls.Add(this.splitContainer1);
            this.panel1.Location = new System.Drawing.Point(13, 43);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(1060, 403);
            this.panel1.TabIndex = 2;
            // 
            // splitContainer1
            // 
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer1.Location = new System.Drawing.Point(0, 0);
            this.splitContainer1.Name = "splitContainer1";
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.groupBoxDebug);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.splitContainer2);
            this.splitContainer1.Size = new System.Drawing.Size(1060, 403);
            this.splitContainer1.SplitterDistance = 500;
            this.splitContainer1.TabIndex = 0;
            this.splitContainer1.TabStop = false;
            // 
            // groupBoxDebug
            // 
            this.groupBoxDebug.Controls.Add(this.richTextBoxBLEDebug);
            this.groupBoxDebug.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupBoxDebug.Location = new System.Drawing.Point(0, 0);
            this.groupBoxDebug.Name = "groupBoxDebug";
            this.groupBoxDebug.Size = new System.Drawing.Size(500, 403);
            this.groupBoxDebug.TabIndex = 0;
            this.groupBoxDebug.TabStop = false;
            this.groupBoxDebug.Text = "BLE Debug";
            // 
            // richTextBoxBLEDebug
            // 
            this.richTextBoxBLEDebug.Dock = System.Windows.Forms.DockStyle.Fill;
            this.richTextBoxBLEDebug.Font = new System.Drawing.Font("Monospac821 BT", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.richTextBoxBLEDebug.Location = new System.Drawing.Point(3, 18);
            this.richTextBoxBLEDebug.Name = "richTextBoxBLEDebug";
            this.richTextBoxBLEDebug.ReadOnly = true;
            this.richTextBoxBLEDebug.Size = new System.Drawing.Size(494, 382);
            this.richTextBoxBLEDebug.TabIndex = 0;
            this.richTextBoxBLEDebug.TabStop = false;
            this.richTextBoxBLEDebug.Text = "";
            this.richTextBoxBLEDebug.TextChanged += new System.EventHandler(this.richTextBoxBLEDebug_TextChanged);
            // 
            // splitContainer2
            // 
            this.splitContainer2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer2.Location = new System.Drawing.Point(0, 0);
            this.splitContainer2.Name = "splitContainer2";
            this.splitContainer2.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainer2.Panel1
            // 
            this.splitContainer2.Panel1.Controls.Add(this.groupBoxUARTDebug);
            // 
            // splitContainer2.Panel2
            // 
            this.splitContainer2.Panel2.Controls.Add(this.groupBoxATDebug);
            this.splitContainer2.Size = new System.Drawing.Size(556, 403);
            this.splitContainer2.SplitterDistance = 234;
            this.splitContainer2.TabIndex = 0;
            this.splitContainer2.TabStop = false;
            // 
            // groupBoxUARTDebug
            // 
            this.groupBoxUARTDebug.Controls.Add(this.richTextBoxUARTDebug);
            this.groupBoxUARTDebug.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupBoxUARTDebug.Location = new System.Drawing.Point(0, 0);
            this.groupBoxUARTDebug.Name = "groupBoxUARTDebug";
            this.groupBoxUARTDebug.Size = new System.Drawing.Size(556, 234);
            this.groupBoxUARTDebug.TabIndex = 0;
            this.groupBoxUARTDebug.TabStop = false;
            this.groupBoxUARTDebug.Text = "UART 0/1 Debug";
            // 
            // richTextBoxUARTDebug
            // 
            this.richTextBoxUARTDebug.Dock = System.Windows.Forms.DockStyle.Fill;
            this.richTextBoxUARTDebug.Font = new System.Drawing.Font("Monospac821 BT", 9F);
            this.richTextBoxUARTDebug.Location = new System.Drawing.Point(3, 18);
            this.richTextBoxUARTDebug.Name = "richTextBoxUARTDebug";
            this.richTextBoxUARTDebug.ReadOnly = true;
            this.richTextBoxUARTDebug.Size = new System.Drawing.Size(550, 213);
            this.richTextBoxUARTDebug.TabIndex = 0;
            this.richTextBoxUARTDebug.TabStop = false;
            this.richTextBoxUARTDebug.Text = "";
            this.richTextBoxUARTDebug.TextChanged += new System.EventHandler(this.richTextBoxUARTDebug_TextChanged);
            // 
            // groupBoxATDebug
            // 
            this.groupBoxATDebug.Controls.Add(this.comboBoxAT);
            this.groupBoxATDebug.Controls.Add(this.buttonSendAT);
            this.groupBoxATDebug.Controls.Add(this.textBoxAT);
            this.groupBoxATDebug.Controls.Add(this.richTextBoxATDebug);
            this.groupBoxATDebug.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupBoxATDebug.Location = new System.Drawing.Point(0, 0);
            this.groupBoxATDebug.Name = "groupBoxATDebug";
            this.groupBoxATDebug.Size = new System.Drawing.Size(556, 165);
            this.groupBoxATDebug.TabIndex = 0;
            this.groupBoxATDebug.TabStop = false;
            this.groupBoxATDebug.Text = "AT Debug";
            // 
            // buttonSendAT
            // 
            this.buttonSendAT.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonSendAT.Location = new System.Drawing.Point(308, 136);
            this.buttonSendAT.Name = "buttonSendAT";
            this.buttonSendAT.Size = new System.Drawing.Size(115, 26);
            this.buttonSendAT.TabIndex = 1;
            this.buttonSendAT.Text = "Send";
            this.buttonSendAT.UseVisualStyleBackColor = true;
            this.buttonSendAT.Click += new System.EventHandler(this.buttonSendAT_Click);
            // 
            // textBoxAT
            // 
            this.textBoxAT.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.textBoxAT.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.textBoxAT.Location = new System.Drawing.Point(7, 137);
            this.textBoxAT.Name = "textBoxAT";
            this.textBoxAT.Size = new System.Drawing.Size(295, 22);
            this.textBoxAT.TabIndex = 0;
            // 
            // richTextBoxATDebug
            // 
            this.richTextBoxATDebug.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.richTextBoxATDebug.Font = new System.Drawing.Font("Monospac821 BT", 9F);
            this.richTextBoxATDebug.Location = new System.Drawing.Point(7, 22);
            this.richTextBoxATDebug.Name = "richTextBoxATDebug";
            this.richTextBoxATDebug.ReadOnly = true;
            this.richTextBoxATDebug.Size = new System.Drawing.Size(543, 109);
            this.richTextBoxATDebug.TabIndex = 0;
            this.richTextBoxATDebug.TabStop = false;
            this.richTextBoxATDebug.Text = "";
            this.richTextBoxATDebug.TextChanged += new System.EventHandler(this.richTextBoxATDebug_TextChanged);
            // 
            // buttonReconnect
            // 
            this.buttonReconnect.Location = new System.Drawing.Point(253, 12);
            this.buttonReconnect.Name = "buttonReconnect";
            this.buttonReconnect.Size = new System.Drawing.Size(104, 25);
            this.buttonReconnect.TabIndex = 3;
            this.buttonReconnect.TabStop = false;
            this.buttonReconnect.Text = "Reconnect";
            this.buttonReconnect.UseVisualStyleBackColor = true;
            this.buttonReconnect.Click += new System.EventHandler(this.buttonReconnect_Click);
            // 
            // comboBoxAT
            // 
            this.comboBoxAT.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.comboBoxAT.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxAT.FormattingEnabled = true;
            this.comboBoxAT.Location = new System.Drawing.Point(429, 136);
            this.comboBoxAT.Name = "comboBoxAT";
            this.comboBoxAT.Size = new System.Drawing.Size(121, 24);
            this.comboBoxAT.TabIndex = 2;
            this.comboBoxAT.SelectedIndexChanged += new System.EventHandler(this.comboBoxAT_SelectedIndexChanged);
            // 
            // BLEDebug
            // 
            this.AcceptButton = this.buttonSendAT;
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1085, 471);
            this.Controls.Add(this.buttonReconnect);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.statusStrip);
            this.Controls.Add(this.comboBoxDevices);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.KeyPreview = true;
            this.Name = "BLEDebug";
            this.Text = "BLE Debug";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.BLEDebug_FormClosed);
            this.Load += new System.EventHandler(this.BLEDebug_Load);
            this.Shown += new System.EventHandler(this.BLEDebug_Shown);
            this.KeyUp += new System.Windows.Forms.KeyEventHandler(this.BLEDebug_KeyUp);
            this.statusStrip.ResumeLayout(false);
            this.statusStrip.PerformLayout();
            this.panel1.ResumeLayout(false);
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).EndInit();
            this.splitContainer1.ResumeLayout(false);
            this.groupBoxDebug.ResumeLayout(false);
            this.splitContainer2.Panel1.ResumeLayout(false);
            this.splitContainer2.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer2)).EndInit();
            this.splitContainer2.ResumeLayout(false);
            this.groupBoxUARTDebug.ResumeLayout(false);
            this.groupBoxATDebug.ResumeLayout(false);
            this.groupBoxATDebug.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox comboBoxDevices;
        private System.Windows.Forms.StatusStrip statusStrip;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLog;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.GroupBox groupBoxDebug;
        private System.Windows.Forms.RichTextBox richTextBoxBLEDebug;
        private System.Windows.Forms.SplitContainer splitContainer2;
        private System.Windows.Forms.GroupBox groupBoxUARTDebug;
        private System.Windows.Forms.RichTextBox richTextBoxUARTDebug;
        private System.Windows.Forms.GroupBox groupBoxATDebug;
        private System.Windows.Forms.Button buttonSendAT;
        private System.Windows.Forms.TextBox textBoxAT;
        private System.Windows.Forms.RichTextBox richTextBoxATDebug;
        private System.Windows.Forms.Button buttonReconnect;
        private System.Windows.Forms.ComboBox comboBoxAT;
    }
}

