namespace BMP2H
{
    partial class MainForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
            this.panel1 = new System.Windows.Forms.Panel();
            this.CreateBtn = new System.Windows.Forms.Button();
            this.LoadBtn = new System.Windows.Forms.Button();
            this.MainPictureBox = new System.Windows.Forms.PictureBox();
            this.PictureOpenDlg = new System.Windows.Forms.OpenFileDialog();
            this.VerLabel = new System.Windows.Forms.Label();
            this.panel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.MainPictureBox)).BeginInit();
            this.SuspendLayout();
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.VerLabel);
            this.panel1.Controls.Add(this.CreateBtn);
            this.panel1.Controls.Add(this.LoadBtn);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.panel1.Location = new System.Drawing.Point(0, 272);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(449, 45);
            this.panel1.TabIndex = 0;
            // 
            // CreateBtn
            // 
            this.CreateBtn.Location = new System.Drawing.Point(149, 10);
            this.CreateBtn.Name = "CreateBtn";
            this.CreateBtn.Size = new System.Drawing.Size(135, 23);
            this.CreateBtn.TabIndex = 1;
            this.CreateBtn.Text = "Create header file";
            this.CreateBtn.UseVisualStyleBackColor = true;
            this.CreateBtn.Click += new System.EventHandler(this.CreateBtn_Click);
            // 
            // LoadBtn
            // 
            this.LoadBtn.Location = new System.Drawing.Point(12, 10);
            this.LoadBtn.Name = "LoadBtn";
            this.LoadBtn.Size = new System.Drawing.Size(131, 23);
            this.LoadBtn.TabIndex = 0;
            this.LoadBtn.Text = "Load image file...";
            this.LoadBtn.UseVisualStyleBackColor = true;
            this.LoadBtn.Click += new System.EventHandler(this.LoadBtn_Click);
            // 
            // MainPictureBox
            // 
            this.MainPictureBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.MainPictureBox.Location = new System.Drawing.Point(0, 0);
            this.MainPictureBox.Name = "MainPictureBox";
            this.MainPictureBox.Size = new System.Drawing.Size(449, 272);
            this.MainPictureBox.TabIndex = 1;
            this.MainPictureBox.TabStop = false;
            // 
            // PictureOpenDlg
            // 
            this.PictureOpenDlg.Filter = "Image files (*.bmp;*.png)|*.bmp;*png";
            // 
            // VerLabel
            // 
            this.VerLabel.AutoSize = true;
            this.VerLabel.Location = new System.Drawing.Point(306, 14);
            this.VerLabel.Name = "VerLabel";
            this.VerLabel.Size = new System.Drawing.Size(44, 12);
            this.VerLabel.TabIndex = 2;
            this.VerLabel.Text = "Version";
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(449, 317);
            this.Controls.Add(this.MainPictureBox);
            this.Controls.Add(this.panel1);
            this.DataBindings.Add(new System.Windows.Forms.Binding("Text", global::BMP2H.Properties.Settings.Default, "BMP2H", true, System.Windows.Forms.DataSourceUpdateMode.OnPropertyChanged));
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MinimumSize = new System.Drawing.Size(400, 300);
            this.Name = "MainForm";
            this.Text = global::BMP2H.Properties.Settings.Default.BMP2H;
            this.Activated += new System.EventHandler(this.MainForm_Activated);
            this.Load += new System.EventHandler(this.MainForm_Load);
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.MainPictureBox)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.PictureBox MainPictureBox;
        private System.Windows.Forms.Button CreateBtn;
        private System.Windows.Forms.Button LoadBtn;
        private System.Windows.Forms.OpenFileDialog PictureOpenDlg;
        private System.Windows.Forms.Label VerLabel;
    }
}

