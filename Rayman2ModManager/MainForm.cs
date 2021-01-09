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

        private static void SetDoubleBuffered(Control control, bool enable)
        {
            PropertyInfo doubleBufferPropertyInfo = control.GetType().GetProperty("DoubleBuffered", BindingFlags.Instance | BindingFlags.NonPublic);
            doubleBufferPropertyInfo?.SetValue(control, enable, null);
        }

        private Rayman2LoaderInfo loaderini;
        private ConfigFile configFile;

        private const string ubiIni = "ubi.ini";
        private string loaderIniPath = "Rayman2ModLoader.ini";
        private bool loaderInstalled = false;

        private void SaveLoaderConfig(string path)
        {
            loaderini.LoaderConfig.DllName = comboBoxDLL.Text;
            loaderini.LoaderConfig.APIName = comboBoxAPI.Text;
            loaderini.LoaderConfig.DebugConsole = checkBoxConsole.Checked;
            loaderini.LoaderConfig.DebugFile = checkBoxLog.Checked;

            IniSerializer.Serialize(loaderini, path);
        }

        private void SaveGameConfig(string path)
        {
            if (loaderInstalled == false)
            {
                configFile.GameConfig.GLI_DllFile = comboBoxDLL.Text;
                configFile.GameConfig.GLI_Dll = comboBoxAPI.Text;
            }

            configFile.GameConfig.ParticuleRate = comboBoxParticules.Text;
            configFile.GameConfig.TexturesMem = comboBoxTexMem.Text;
            configFile.GameConfig.GLI_Mode = "1 - " + numericUpDown_Width.Value.ToString() + " x " + numericUpDown_Height.Value.ToString() + " x " + comboBoxDepth.Text;

            IniSerializer.Serialize(configFile, path);
        }

        private void SaveAll()
        {
            SaveLoaderConfig(loaderIniPath);
            SaveGameConfig(ubiIni);
        }

        private void InstallLoader()
        {
            loaderini.LoaderConfig.DllName = configFile.GameConfig.GLI_DllFile;
            configFile.GameConfig.GLI_DllFile = "modloader";
            buttonInstall.Text = "Uninstall";
            loaderInstalled = true;
            SaveAll();
        }

        private void UninstallLoader()
        {
            buttonInstall.Text = "Install";
            configFile.GameConfig.GLI_DllFile = loaderini.LoaderConfig.DllName;
            loaderInstalled = false;
            SaveAll();
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

        private void ReadLoaderConfig(string path)
        {
            loaderini = File.Exists(path) ? IniSerializer.Deserialize<Rayman2LoaderInfo>(path) : new Rayman2LoaderInfo();
            checkBoxConsole.Checked = loaderini.LoaderConfig.DebugConsole;
            checkBoxLog.Checked = loaderini.LoaderConfig.DebugFile;
            comboBoxDLL.Text = loaderini.LoaderConfig.DllName;
            comboBoxAPI.Text = loaderini.LoaderConfig.APIName;
        }

        private void ReadGameConfig(string path)
        {
            configFile = File.Exists(path) ? IniSerializer.Deserialize<ConfigFile>(path) : new ConfigFile();
            loaderInstalled = configFile.GameConfig.GLI_DllFile == "modloader";

            comboBoxTexMem.Text = configFile.GameConfig.TexturesMem;
            comboBoxParticules.Text = configFile.GameConfig.ParticuleRate;

            string[] stringSeparators = new string[] { " x " };
            string mode = configFile.GameConfig.GLI_Mode.Remove(0, 4);
            string[] subStrings = mode.Split(stringSeparators, StringSplitOptions.None);

            numericUpDown_Width.Value = decimal.Parse(subStrings[0]);
            numericUpDown_Height.Value = decimal.Parse(subStrings[1]);
            comboBoxDepth.Text = subStrings[2];
            
            if (loaderInstalled == true)
            {
                buttonInstall.Text = "Uninstall";
            }
            else
            {
                DialogResult result = MessageBox.Show("The Mod Loader is not installed, do you want to install it? \n It will modify \"ubi.ini\".", "Install Mod Loader", MessageBoxButtons.YesNo);

                if (result == DialogResult.Yes)
                {
                    InstallLoader();
                }

                comboBoxDLL.Text = configFile.GameConfig.GLI_DllFile;
                comboBoxAPI.Text = configFile.GameConfig.GLI_Dll;
            }
        }

        private void MainForm_Load(object sender, EventArgs e)
        {
            SetDoubleBuffered(modListView, true);

            ReadLoaderConfig(loaderIniPath);
            ReadGameConfig(ubiIni);
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

        private void buttonSave_Click(object sender, EventArgs e)
        {
            SaveAll();
        }

        private void buttonSaveAndPlay_Click(object sender, EventArgs e)
        {
            SaveAll();
        }

        private void comboBoxResolutions_SelectedValueChanged(object sender, EventArgs e)
        {
            string[] subStrings = comboBoxResolutions.Text.Split('x');
            numericUpDown_Width.Value = decimal.Parse(subStrings[0]);
            numericUpDown_Height.Value = decimal.Parse(subStrings[1]);
        }
    }
}
