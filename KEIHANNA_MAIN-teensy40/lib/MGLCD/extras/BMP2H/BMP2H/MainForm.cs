using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace BMP2H
{
    public partial class MainForm : Form
    {
        public const double version = 1.00;

        public MainForm()
        {
            InitializeComponent();
        }

        private void EnableButtons()
        {
            CreateBtn.Enabled = MainPictureBox.Image != null;
        } // EnableButtons

        private void LoadBtn_Click(object sender, EventArgs e)
        {
            try {
                if (PictureOpenDlg.ShowDialog() == DialogResult.OK) {
                    if (Path.GetExtension(PictureOpenDlg.FileName).ToLower() == ".h") {
                        MessageBox.Show("File extension cannot be .h.", Text, MessageBoxButtons.OK, MessageBoxIcon.Hand);
                        return;
                    } // if
                    try {
                        MainPictureBox.Load(PictureOpenDlg.FileName);
                    } catch (Exception) {
                        MessageBox.Show("Could not open picture file.", Text, MessageBoxButtons.OK, MessageBoxIcon.Hand);
                    } // try
                } // if
            } finally {
                EnableButtons();
            }
        } // LoadBtn_Click

        private void CreateHeaderFile()
        {
            Bitmap bmp = new Bitmap(MainPictureBox.Image);
            string FileName = Path.ChangeExtension(PictureOpenDlg.FileName, ".h");
            string FileMacro = Path.GetFileNameWithoutExtension(FileName).ToUpper() + "_H";
            StreamWriter sw = null;
            try {
                sw = new StreamWriter(FileName, false);

                int PageNum = ((bmp.Height) + 7) / 8;

                sw.WriteLine("// {0}", Path.GetFileName(FileName));
                sw.WriteLine();
                sw.WriteLine("#ifndef {0}", FileMacro);
                sw.WriteLine("#define {0}", FileMacro);
                sw.WriteLine();
                sw.WriteLine("PROGMEM const uint8_t BMP_{0}[] = {{", Path.GetFileNameWithoutExtension(FileName));
                sw.WriteLine("\t{0}, // width", bmp.Width);
                sw.WriteLine("\t{0}, // height", bmp.Height);

                for (int page = 0; page < PageNum; page++) {
                    int ItemCnt = 0;
                    for (int x = 0; x < bmp.Width; x++) {
                        byte data = 0;
                        for (int i = 0; i < 8; i++) {
                            if (page * 8 + i >= bmp.Height) break;
                            Color p = bmp.GetPixel(x, page * 8 + i);
                            if ((p.R + p.G + p.B) < 256 * 3 / 2) data += (byte)(1 << i);
                        } // for i
                        if (ItemCnt == 0) sw.Write("\t");
                        sw.Write("0x{0:x2}", data);
                        if (x < bmp.Width - 1 || page < PageNum - 1) {
                            sw.Write(",");
                        } else {
                            sw.Write(" ");
                        } // if
                        if (++ItemCnt >= 16 || x == bmp.Width - 1) {
                            ItemCnt = 0;
                            if (x == bmp.Width - 1) sw.Write(" // page{0}", page);
                            sw.WriteLine();
                        } // if
                    } // for x
                } // for page
                sw.WriteLine("};");
                sw.WriteLine();
                sw.WriteLine("#endif");
                MessageBox.Show(string.Format("Created \"{0}\".", Path.GetFileName(FileName)), Text, MessageBoxButtons.OK, MessageBoxIcon.Information);
            } catch (Exception) {
                if (sw == null) {
                    MessageBox.Show("Could not open:" + FileName, Text, MessageBoxButtons.OK, MessageBoxIcon.Hand);
                } else {
                    MessageBox.Show("Failed to Create:" + FileName, Text, MessageBoxButtons.OK, MessageBoxIcon.Hand);
                } // if
            } finally {
                if(sw!=null) sw.Close();
            } // try
        } // CreateHeaderFile

        private void CreateBtn_Click(object sender, EventArgs e)
        {
            try {
                Cursor.Current = Cursors.WaitCursor;
                CreateHeaderFile();
            } finally {
                Cursor.Current = Cursors.Default;
                EnableButtons();
            }
        } // CreateBtn_Click

        private void MainForm_Activated(object sender, EventArgs e)
        {
            EnableButtons();
        }

        private void MainForm_Load(object sender, EventArgs e)
        {
            VerLabel.Text = string.Format("{0} Version {1:0.00}",Text,version);
        }
    }
}
