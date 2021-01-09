using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Diagnostics;
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

            // WORKAROUND: Windows 7's system fonts don't have
            // U+2912 or U+2913. Use Cambria instead.
            // TODO: Check the actual font to see if it has the glyphs.
            Font boldFont = null;
            OperatingSystem os = Environment.OSVersion;

            if ((os.Platform == PlatformID.Win32NT || os.Platform == PlatformID.Win32Windows) &&
                (os.Version.Major < 6 || (os.Version.Major == 6 && os.Version.Minor < 2)))
            {
                // Windows 7 or earlier.
                // TODO: Make sure this font exists.
                // NOTE: U+2912 and U+2913 are missing in Bold, so use Regular.
                boldFont = new Font("Cambria", this.Font.Size * 1.25f, FontStyle.Regular);
            }
            else
            {
                // Newer than Windows 7, or not Windows.
                // Use the default font.
                boldFont = new Font(this.Font.FontFamily, this.Font.Size * 1.25f, FontStyle.Bold);
            }

            upmostButton.Font = boldFont;
            upButton.Font = boldFont;
            downButton.Font = boldFont;
            downmostButton.Font = boldFont;
        }

        private static void SetDoubleBuffered(Control control, bool enable)
        {
            PropertyInfo doubleBufferPropertyInfo = control.GetType().GetProperty("DoubleBuffered", BindingFlags.Instance | BindingFlags.NonPublic);
            doubleBufferPropertyInfo?.SetValue(control, enable, null);
        }

        private Rayman2LoaderInfo loaderini;
        private ConfigFile configFile;

        private string GamePath = "";
        private string ModsPath = "Mods";
        private string ubiIni = "ubi.ini";
        private string loaderIniPath = "Rayman2ModLoader.ini";
        private const string lstcodespath = "Codes.lst";
        private bool loaderInstalled = false;

        Dictionary<string, Rayman2ModInfo> mods;

        CodeList mainCodes;
        List<Code> codes;

        private void SaveCodes()
        {
            List<Code> selectedCodes = new List<Code>();
            List<Code> selectedPatches = new List<Code>();

            loaderini.EnabledCodes.Clear();

            foreach (Code item in checkedListBoxCodes.CheckedIndices.OfType<int>().Select(a => codes[a]))
            {
                if (item.Patch)
                {
                    selectedPatches.Add(item);
                } else
                {
                    selectedCodes.Add(item);
                }

                loaderini.EnabledCodes.Add(item.Name);
            }

            CodeList.WriteDatFile(ModsPath + "\\Patches.dat", selectedPatches);
            CodeList.WriteDatFile(ModsPath + "\\Codes.dat", selectedCodes);
        }

        private void SaveMods()
        {
            loaderini.Mods.Clear();

            foreach (ListViewItem item in modListView.CheckedItems)
            {
                loaderini.Mods.Add((string)item.Tag);
            }
        }

        private void SaveLoaderConfig(string path)
        {
            loaderini.DllName = comboBoxDLL.Text;
            loaderini.APIName = comboBoxAPI.Text;
            loaderini.DebugConsole = checkBoxConsole.Checked;
            loaderini.DebugFile = checkBoxLog.Checked;

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

        void SaveConfigs()
        {
            SaveLoaderConfig(loaderIniPath);
            SaveGameConfig(ubiIni);
        }

        private void SaveAll()
        {
            SaveCodes();
            SaveMods();
            SaveConfigs();
        }

        private void InstallLoader()
        {
            loaderini.DllName = configFile.GameConfig.GLI_DllFile;
            configFile.GameConfig.GLI_DllFile = "modloader";
            buttonInstall.Text = "Uninstall";
            loaderInstalled = true;
            SaveConfigs();
        }

        private void UninstallLoader()
        {
            buttonInstall.Text = "Install";
            configFile.GameConfig.GLI_DllFile = loaderini.DllName;
            loaderInstalled = false;
            SaveConfigs();
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
            checkBoxConsole.Checked = loaderini.DebugConsole;
            checkBoxLog.Checked = loaderini.DebugFile;
            comboBoxDLL.Text = loaderini.DllName;
            comboBoxAPI.Text = loaderini.APIName;
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

        private void LoadCodesFile(string path)
        {
            try
            {
                string codespath = path + lstcodespath;
                if (File.Exists(codespath))
                {
                    mainCodes = CodeList.Load(codespath);
                }
                else
                {
                    mainCodes = new CodeList();
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(this, $"Error loading code list: {ex.Message}", "Rayman2 Mod Loader", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                mainCodes = new CodeList();
            }
        }

        private void LoadModList(string path)
        {
            upmostButton.Enabled = upButton.Enabled = downButton.Enabled = downmostButton.Enabled = configModButton.Enabled = false;
            labelModDescription.Text = "Description: No mod selected.";
            modListView.Items.Clear();
            mods = new Dictionary<string, Rayman2ModInfo>();
            codes = new List<Code>(mainCodes.Codes);

            foreach (string filename in Rayman2ModInfo.GetModFiles(new DirectoryInfo(path)))
            {
                mods.Add((Path.GetDirectoryName(filename) ?? string.Empty).Substring(path.Length + 1), IniSerializer.Deserialize<Rayman2ModInfo>(filename));
            }

            modListView.BeginUpdate();

            foreach (string mod in new List<string>(loaderini.Mods))
            {
                if (mods.ContainsKey(mod))
                {
                    Rayman2ModInfo inf = mods[mod];
                    modListView.Items.Add(new ListViewItem(new[] { inf.Name, inf.Author, inf.Version }) { Checked = true, Tag = mod });
                    
                    if (!string.IsNullOrEmpty(inf.Codes))
                    {
                        codes.AddRange(CodeList.Load(Path.Combine(Path.Combine(path, mod), inf.Codes)).Codes);
                    }
                }
                else
                {
                    MessageBox.Show(this, "Mod \"" + mod + "\" could not be found.\n\nThis mod will be removed from the list.",
                        Text, MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    loaderini.Mods.Remove(mod);
                }
            }

            foreach (KeyValuePair<string, Rayman2ModInfo> inf in mods.OrderBy(x => x.Value.Name))
            {
                if (!loaderini.Mods.Contains(inf.Key))
                {
                    modListView.Items.Add(new ListViewItem(new[] { inf.Value.Name, inf.Value.Author, inf.Value.Version }) { Tag = inf.Key });
                }
            }

            modListView.EndUpdate();

            loaderini.EnabledCodes = new List<string>(loaderini.EnabledCodes.Where(a => codes.Any(c => c.Name == a)));
            foreach (Code item in codes.Where(a => a.Required && !loaderini.EnabledCodes.Contains(a.Name)))
                loaderini.EnabledCodes.Add(item.Name);

            checkedListBoxCodes.BeginUpdate();
            checkedListBoxCodes.Items.Clear();

            foreach (Code item in codes)
                checkedListBoxCodes.Items.Add(item.Name, loaderini.EnabledCodes.Contains(item.Name));

            checkedListBoxCodes.EndUpdate();
        }

        private void MainForm_Load(object sender, EventArgs e)
        {
            SetDoubleBuffered(modListView, true);

            string[] args = Environment.GetCommandLineArgs();

            int i = 0;
            foreach (string arg in args)
            {
                if (arg == "-gamepath")
                {
                    GamePath = args[i + 1];

                    break;
                }

                ++i;
            }

            if (GamePath == "")
            {
                GamePath = Environment.CurrentDirectory;
            }

            ubiIni = GamePath + "\\" + ubiIni;

            ReadLoaderConfig(loaderIniPath);
            ReadGameConfig(ubiIni);

            ModsPath = loaderini.ModsPath;

            if (Path.IsPathRooted(ModsPath) == false)
            {
                ModsPath = GamePath + "\\" + ModsPath;
            }

            if (Directory.Exists(ModsPath) == false)
            {
                Directory.CreateDirectory(ModsPath);
            }

            LoadCodesFile(ModsPath + "\\");
            LoadModList(ModsPath);
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
            LoadModList(ModsPath);
        }

        private void buttonSaveAndPlay_Click(object sender, EventArgs e)
        {
            SaveAll();

            if (loaderInstalled == false)
            {
                switch (MessageBox.Show(this, "Looks like you're starting the game without the mod loader installed. Without the mod loader, the mods and codes you've selected won't be used, and some settings may not work.\n\nDo you want to install the mod loader now?", "SADX Mod Manager", MessageBoxButtons.YesNoCancel, MessageBoxIcon.Warning, MessageBoxDefaultButton.Button1))
                {
                    case DialogResult.Cancel:
                        return;
                    case DialogResult.Yes:
                        InstallLoader();
                        break;
                }
            }
            
            Process process = Process.Start(loaderini.Mods.Select((item) => mods[item].EXEFile)
                                                .FirstOrDefault((item) => !string.IsNullOrEmpty(item)) ?? "rayman2.exe");
            process?.WaitForInputIdle(10000);
            Close();
        }

        private void comboBoxResolutions_SelectedValueChanged(object sender, EventArgs e)
        {
            string[] subStrings = comboBoxResolutions.Text.Split('x');
            numericUpDown_Width.Value = decimal.Parse(subStrings[0]);
            numericUpDown_Height.Value = decimal.Parse(subStrings[1]);
        }
    }
}
