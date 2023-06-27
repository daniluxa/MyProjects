using System.Windows.Forms;

namespace LIC_settings
{
    class Frm
    {
        public byte[] file;
        public byte device;
        public ProgressBar progressBar;

        public Frm(byte[] file, byte device, ProgressBar progressBar)
        {
            this.file = file;
            this.device = device;
            this.progressBar = progressBar;
        }
    }
}
