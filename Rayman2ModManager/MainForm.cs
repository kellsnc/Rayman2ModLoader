using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using IniFile;
using ModManagerCommon;
using ModManagerCommon.Forms;

namespace Rayman2ModManager
{
    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();
        }

        private Rayman2LoaderInfo loaderini;
        //private ConfigFile configFile;

        private const string ubiIni = "ubi.ini";
        private string loaderIniPath = "Rayman2ModLoader.ini";
        private bool loaderInstalled = false;

        private void InstallLoader()
        {
            buttonInstall.Text = "Uninstall";
            loaderInstalled = true;
        }

        private void UninstallLoader()
        {
            buttonInstall.Text = "Install";
            loaderInstalled = false;
        }

        private void buttonInstall_Click(object sender, EventArgs e)
        {
            if (loaderInstalled == false)
            {
                InstallLoader();
            } 
            else
            {
                UninstallLoader();
            }
        }

        private void MainForm_Load(object sender, EventArgs e)
        {
            loaderini = File.Exists(loaderIniPath) ? IniSerializer.Deserialize<Rayman2LoaderInfo>(loaderIniPath) : new Rayman2LoaderInfo();
        }
    }
}
