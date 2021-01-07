using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Reflection;
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
        private ConfigFile configFile;

        private const string ubiIni = "ubi.ini";
        private string loaderIniPath = "Rayman2ModLoader.ini";
        private bool loaderInstalled = false;

        private void InstallLoader()
        {
            loaderini.DllName = configFile.GLI_DllFile;
            configFile.GLI_DllFile = "modloader";
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

        private static void SetDoubleBuffered(Control control, bool enable)
        {
            PropertyInfo doubleBufferPropertyInfo = control.GetType().GetProperty("DoubleBuffered", BindingFlags.Instance | BindingFlags.NonPublic);
            doubleBufferPropertyInfo?.SetValue(control, enable, null);
        }

        private void MainForm_Load(object sender, EventArgs e)
        {
            SetDoubleBuffered(modListView, true);

            loaderini = File.Exists(loaderIniPath) ? IniSerializer.Deserialize<Rayman2LoaderInfo>(loaderIniPath) : new Rayman2LoaderInfo();
            configFile = File.Exists(ubiIni) ? IniSerializer.Deserialize<ConfigFile>(loaderIniPath) : new ConfigFile();

            if (configFile.GLI_DllFile == "modloader")
            {
                buttonInstall.Text = "Uninstall";
            }
#if DEBUG == false
            else
            {
                DialogResult result = MessageBox.Show("The Mod Loader is not installed, do you want to install it? \n It will modify \"ubi.ini\".", "Install Mod Loader", MessageBoxButtons.YesNo);

                if (result == DialogResult.Yes)
                {
                    InstallLoader();
                }
            }
#endif
        }

        private void addModButton_Click(object sender, EventArgs e)
        {

        }

        private void refreshButton_Click(object sender, EventArgs e)
        {

        }

        private void configModButton_Click(object sender, EventArgs e)
        {

        }
    }
}
