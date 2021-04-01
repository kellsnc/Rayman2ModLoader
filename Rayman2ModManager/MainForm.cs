using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Net;
using System.Reflection;
using System.Security.Cryptography;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using IniFile;
using ModManagerCommon;
using ModManagerCommon.Forms;
using Rayman2ModManager.Forms;
using Newtonsoft.Json;

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
        public string ModsPath = "Mods";
        private string ubiIni = "ubi.ini";
        private string loaderIniPath = "Rayman2ModLoader.ini";
        private string updatePath = ".updates";
        private const string lstcodespath = "Codes.lst";
        private bool loaderInstalled = false;
        private bool displayedManifestWarning = false;
        private bool updatingListView = false;

        private const float modloaderver = 1.7f;

        Dictionary<string, Rayman2ModInfo> mods;

        CodeList mainCodes;
        List<Code> codes;

        readonly ModUpdater modUpdater = new ModUpdater();
        BackgroundWorker updateChecker;
        private bool manualModUpdate;
        private bool checkedForUpdates;

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

        private void SaveLoaderConfig()
        {
            loaderini.DllName = comboBoxDLL.Text;
            loaderini.APIName = comboBoxAPI.Text;
            loaderini.DebugConsole = checkBoxConsole.Checked;
            loaderini.DebugFile = checkBoxLog.Checked;
            loaderini.PauseWhenInactive = checkBoxFocus.Checked;

            loaderini.UpdateCheck = updateCheckStartupCheckBox.Checked;
            loaderini.ModUpdateCheck = modUpdateCheckStartupCheckBox.Checked;
            loaderini.UpdateUnit = (UpdateUnit)frequencyComboBox.SelectedIndex;
            loaderini.UpdateFrequency = (int)frequencyNumericUpDown.Value;

            IniSerializer.Serialize(loaderini, loaderIniPath);
        }

        private void SaveGameConfig()
        {
            if (loaderInstalled == false)
            {
                configFile.GameConfig.GLI_DllFile = comboBoxDLL.Text;
                configFile.GameConfig.GLI_Dll = comboBoxAPI.Text;
            }

            configFile.GameConfig.ParticuleRate = comboBoxParticules.Text;
            configFile.GameConfig.TexturesMem = comboBoxTexMem.Text;

            string fs = checkBoxFullScreen.Checked == true ? "1" : "0";

            configFile.GameConfig.GLI_Mode = fs + " - " + numericUpDown_Width.Value.ToString() + " x " + numericUpDown_Height.Value.ToString() + " x " + comboBoxDepth.Text;

            IniSerializer.Serialize(configFile, ubiIni);
        }

        void SaveConfigs()
        {
            SaveLoaderConfig();
            SaveGameConfig();
        }

        private void SaveAll()
        {
            SaveCodes();
            SaveMods();
            SaveConfigs();
        }

        private void InstallLoader()
        {
            if (configFile.GameConfig.GLI_DllFile != "modloader")
            {
                loaderini.DllName = configFile.GameConfig.GLI_DllFile;
            }
            else
            {
                // Default value if something went wrong.
                loaderini.DllName = "GliVd1";
                loaderini.APIName = "Glide2";
            }
            
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
            checkBoxFocus.Checked = loaderini.PauseWhenInactive;

            updateCheckStartupCheckBox.Checked = loaderini.UpdateCheck;
            modUpdateCheckStartupCheckBox.Checked = loaderini.ModUpdateCheck;
            frequencyComboBox.SelectedIndex = (int)loaderini.UpdateUnit;
            frequencyNumericUpDown.Value = loaderini.UpdateFrequency;
        }

        private void ReadGameConfig()
        {
            bool error_ini = false;

            if (File.Exists(ubiIni))
            {
                configFile = IniSerializer.Deserialize<ConfigFile>(ubiIni);
            } 
            else
            { 
                if (File.Exists("C:\\Windows\\Ubisoft\\ubi.ini"))
                {
                    string ubiIni_ = "C:\\Windows\\Ubisoft\\ubi.ini";
                    configFile = IniSerializer.Deserialize<ConfigFile>(ubiIni_);

                    if (configFile.GameConfig.GLI_Device == null)
                    {
                        error_ini = true;
                    } else
                    {
                        ubiIni = ubiIni_;
                    }
                } 
                else
                {
                    error_ini = true;
                }
            }

            if (error_ini == true)
            {
                DialogResult result = MessageBox.Show(this, "Cannot find the game's configuration, do you want to create one in this directory?", "Rayman2 Mod Loader", MessageBoxButtons.YesNo, MessageBoxIcon.Error);
                
                if (result == DialogResult.Yes)
                {
                    configFile = new ConfigFile();
                } else
                {
                    Close();
                    return;
                }
            }

            loaderInstalled = configFile.GameConfig.GLI_DllFile == "modloader";

            comboBoxTexMem.Text = configFile.GameConfig.TexturesMem;
            comboBoxParticules.Text = configFile.GameConfig.ParticuleRate;

            checkBoxFullScreen.Checked = Convert.ToBoolean(Convert.ToInt32(configFile.GameConfig.GLI_Mode.ElementAt(0)));

            try
            {
                string[] stringSeparators = new string[] { " x " };
                string mode = configFile.GameConfig.GLI_Mode.Remove(0, 4);
                string[] subStrings = mode.Split(stringSeparators, StringSplitOptions.None);

                numericUpDown_Width.Value = decimal.Parse(subStrings[0]);
                numericUpDown_Height.Value = decimal.Parse(subStrings[1]);
                comboBoxDepth.Text = subStrings[2];
            }
            catch
            {
                numericUpDown_Width.Value = 1280;
                numericUpDown_Height.Value = 1024;
                comboBoxDepth.Text = "16";
            }
           
            if (loaderInstalled == true)
            {
                buttonInstall.Text = "Uninstall";
            }
        }

        private void LoadCodesFile()
        {
            try
            {
                string codespath = ModsPath + "\\" + lstcodespath;
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

        private string GetModCategory(Rayman2ModInfo inf)
        {
            if (string.IsNullOrEmpty(inf.Category) == false)
            {
                return inf.Category.First().ToString().ToUpper() + inf.Category.Substring(1);
            } 
            else if (string.IsNullOrEmpty(inf.GameBananaItemType) == false)
            {
                return inf.GameBananaItemType.First().ToString().ToUpper() + inf.GameBananaItemType.Substring(1);
            }
            else
            {
                return string.Empty;
            }
        }

        private void LoadModList(string path)
        {
            updatingListView = true;

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
                    modListView.Items.Add(new ListViewItem(new[] { inf.Name, inf.Author, inf.Version, GetModCategory(inf) }) { Checked = true, Tag = mod });
                    
                    if (string.IsNullOrEmpty(inf.Codes) == false)
                    {
                        codes.AddRange(CodeList.Load(Path.Combine(Path.Combine(path, mod), inf.Codes)).Codes);
                    }

                    if (string.IsNullOrEmpty(inf.GLI_DllFile) == false)
                    {
                        comboBoxDLL.Items.Add(inf.GLI_DllFile);
                    }

                    if (string.IsNullOrEmpty(inf.GLI_Dll) == false)
                    {
                        comboBoxAPI.Items.Add(inf.GLI_Dll);
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
                    modListView.Items.Add(new ListViewItem(new[] { inf.Value.Name, inf.Value.Author, inf.Value.Version, GetModCategory(inf.Value) }) { Tag = inf.Key });
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
            updatingListView = false;
        }

        private void RefreshModList()
        {
            upmostButton.Enabled = upButton.Enabled = downButton.Enabled = downmostButton.Enabled = configModButton.Enabled = false;
            
            comboBoxDLL.Items.Clear();
            comboBoxDLL.Items.Add("GliVd1");
            comboBoxDLL.Items.Add("GliDX6");

            comboBoxAPI.Items.Clear();
            comboBoxAPI.Items.Add("Glide2");
            comboBoxAPI.Items.Add("DirectX6");
            
            LoadModList(ModsPath);
        }

        private void MainForm_Load(object sender, EventArgs e)
        {
            SetDoubleBuffered(modListView, true);
            SetDoubleBuffered(checkedListBoxCodes, true);

            verLabel.Text = System.Reflection.Assembly.GetExecutingAssembly().GetName().Version.ToString();

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
            ReadGameConfig();

            ModsPath = loaderini.ModsPath;

            if (Path.IsPathRooted(ModsPath) == false)
            {
                ModsPath = GamePath + "\\" + ModsPath;
            }

            if (Directory.Exists(ModsPath) == false)
            {
                Directory.CreateDirectory(ModsPath);
            }

            updatePath = ModsPath + "\\" + updatePath;

            LoadCodesFile();
            LoadModList(ModsPath);
        }

        private void addModButton_Click(object sender, EventArgs e)
        {
            using (var ModDialog = new AddModForm(ModsPath))
            {
                if (ModDialog.ShowDialog() == DialogResult.OK)
                    RefreshModList();
            }
        }

        private void refreshButton_Click(object sender, EventArgs e)
        {
            RefreshModList();
        }

        private void configModButton_Click(object sender, EventArgs e)
        {
            using (ModConfigDialog dlg = new ModConfigDialog(Path.Combine("mods", (string)modListView.SelectedItems[0].Tag), modListView.SelectedItems[0].Text))
                dlg.ShowDialog(this);
        }

        private void buttonSave_Click(object sender, EventArgs e)
        {
            SaveAll();
            RefreshModList();
        }

        private void buttonSaveAndPlay_Click(object sender, EventArgs e)
        {
            SaveAll();

            if (loaderInstalled == false)
            {
                switch (MessageBox.Show(this, "Looks like you're starting the game without the mod loader installed. Without the mod loader, the mods and codes you've selected won't be used, and some settings may not work.\n\nDo you want to install the mod loader now?", "Rayman2 Mod Manager", MessageBoxButtons.YesNoCancel, MessageBoxIcon.Warning, MessageBoxDefaultButton.Button1))
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

        private void modListView_SelectedIndexChanged(object sender, EventArgs e)
        {
            int count = modListView.SelectedIndices.Count;

            if (count == 0)
            {
                upmostButton.Enabled = upButton.Enabled = downButton.Enabled = downmostButton.Enabled = configModButton.Enabled = false;
                labelModDescription.Text = "Description: No mod selected.";
            }
            else if (count == 1)
            {
                labelModDescription.Text = "Description: " + mods[(string)modListView.SelectedItems[0].Tag].Description;
                upmostButton.Enabled = modListView.SelectedIndices[0] != 0;
                upButton.Enabled = modListView.SelectedIndices[0] > 0;
                downButton.Enabled = modListView.SelectedIndices[0] < modListView.Items.Count - 1;
                downmostButton.Enabled = modListView.SelectedIndices[0] != modListView.Items.Count - 1;
                configModButton.Enabled = File.Exists(Path.Combine("mods", (string)modListView.SelectedItems[0].Tag, "configschema.xml"));
            }
            else if (count > 1)
            {
                labelModDescription.Text = "Description: Multiple mods selected.";
                upmostButton.Enabled = upButton.Enabled = downButton.Enabled = downmostButton.Enabled = true;
                configModButton.Enabled = false;
            }
        }

        private void upmostButton_Click(object sender, EventArgs e)
        {
            if (modListView.SelectedItems.Count < 1)
                return;

            modListView.BeginUpdate();

            for (int i = 0; i < modListView.SelectedItems.Count; i++)
            {
                int index = modListView.SelectedItems[i].Index;

                if (index > 0)
                {
                    ListViewItem item = modListView.SelectedItems[i];
                    modListView.Items.Remove(item);
                    modListView.Items.Insert(i, item);
                }
            }

            modListView.SelectedItems[0].EnsureVisible();
            modListView.EndUpdate();
        }

        private void upButton_Click(object sender, EventArgs e)
        {
            if (modListView.SelectedItems.Count < 1)
                return;

            modListView.BeginUpdate();

            for (int i = 0; i < modListView.SelectedItems.Count; i++)
            {
                int index = modListView.SelectedItems[i].Index;

                if (index-- > 0 && !modListView.Items[index].Selected)
                {
                    ListViewItem item = modListView.SelectedItems[i];
                    modListView.Items.Remove(item);
                    modListView.Items.Insert(index, item);
                }
            }

            modListView.SelectedItems[0].EnsureVisible();
            modListView.EndUpdate();
        }

        private void downButton_Click(object sender, EventArgs e)
        {
            if (modListView.SelectedItems.Count < 1)
                return;

            modListView.BeginUpdate();

            for (int i = modListView.SelectedItems.Count - 1; i >= 0; i--)
            {
                int index = modListView.SelectedItems[i].Index + 1;

                if (index != modListView.Items.Count && !modListView.Items[index].Selected)
                {
                    ListViewItem item = modListView.SelectedItems[i];
                    modListView.Items.Remove(item);
                    modListView.Items.Insert(index, item);
                }
            }

            modListView.SelectedItems[modListView.SelectedItems.Count - 1].EnsureVisible();
            modListView.EndUpdate();
        }

        private void downmostButton_Click(object sender, EventArgs e)
        {
            if (modListView.SelectedItems.Count < 1)
                return;

            modListView.BeginUpdate();

            for (int i = modListView.SelectedItems.Count - 1; i >= 0; i--)
            {
                int index = modListView.SelectedItems[i].Index;

                if (index != modListView.Items.Count - 1)
                {
                    ListViewItem item = modListView.SelectedItems[i];
                    modListView.Items.Remove(item);
                    modListView.Items.Insert(modListView.Items.Count, item);
                }
            }

            modListView.SelectedItems[modListView.SelectedItems.Count - 1].EnsureVisible();
            modListView.EndUpdate();
        }

        private void modListView_MouseClick(object sender, MouseEventArgs e)
        {
            if (e.Button != MouseButtons.Right)
            {
                return;
            }

            if (modListView.FocusedItem.Bounds.Contains(e.Location))
            {
                modContextMenu.Show(Cursor.Position);
            }
        }

        private void openFolderToolStripMenuItem_Click(object sender, EventArgs e)
        {
            foreach (ListViewItem item in modListView.SelectedItems)
            {
                Process.Start(Path.Combine("mods", (string)item.Tag));
            }
        }

        private void uninstallToolStripMenuItem_Click(object sender, EventArgs e)
        {
            DialogResult result = MessageBox.Show(this, "This will uninstall all selected mods."
                + "\n\nAre you sure you wish to continue?", "Warning", MessageBoxButtons.YesNo, MessageBoxIcon.Warning);

            if (result != DialogResult.Yes)
            {
                return;
            }

            result = MessageBox.Show(this, "Would you like to keep mod user data where possible? (Save files, config files, etc)",
                "User Data", MessageBoxButtons.YesNoCancel, MessageBoxIcon.Question);

            if (result == DialogResult.Cancel)
            {
                return;
            }

            foreach (ListViewItem item in modListView.SelectedItems)
            {
                var dir = (string)item.Tag;
                var modDir = Path.Combine("mods", dir);
                var manpath = Path.Combine(modDir, "mod.manifest");

                try
                {
                    if (result == DialogResult.Yes && File.Exists(manpath))
                    {
                        List<ModManifestEntry> manifest = ModManifest.FromFile(manpath);
                        foreach (var entry in manifest)
                        {
                            var path = Path.Combine(modDir, entry.FilePath);
                            if (File.Exists(path))
                            {
                                File.Delete(path);
                            }
                        }

                        File.Delete(manpath);
                        var version = Path.Combine(modDir, "mod.version");
                        if (File.Exists(version))
                        {
                            File.Delete(version);
                        }
                    }
                    else
                    {
                        if (result == DialogResult.Yes)
                        {
                            var retain = MessageBox.Show(this, $"The mod \"{ mods[dir].Name }\" (\"mods\\{ dir }\") does not have a manifest, so mod user data cannot be retained."
                                + " Do you want to uninstall it anyway?", "Cannot Retain User Data", MessageBoxButtons.YesNo, MessageBoxIcon.Warning);

                            if (retain == DialogResult.No)
                            {
                                continue;
                            }
                        }

                        Directory.Delete(modDir, true);
                    }
                }
                catch (Exception ex)
                {
                    MessageBox.Show(this, $"Failed to uninstall mod \"{ mods[dir].Name }\" from \"{ dir }\": { ex.Message }", "Failed",
                        MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }

            RefreshModList();
        }

        private void installURLHandlerButton_Click(object sender, EventArgs e)
        {
            Process.Start(new ProcessStartInfo(Application.ExecutablePath, "urlhandler") { UseShellExecute = true, Verb = "runas" }).WaitForExit();
            MessageBox.Show(this, "URL handler installed!", Text);
        }

        private void frequencyComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            frequencyNumericUpDown.Enabled = frequencyComboBox.SelectedIndex > 0;
        }

        private static bool UpdateTimeElapsed(UpdateUnit unit, int amount, DateTime start)
        {
            if (unit == UpdateUnit.Always)
            {
                return true;
            }

            TimeSpan span = DateTime.UtcNow - start;

            switch (unit)
            {
                case UpdateUnit.Hours:
                    return span.TotalHours >= amount;

                case UpdateUnit.Days:
                    return span.TotalDays >= amount;

                case UpdateUnit.Weeks:
                    return span.TotalDays / 7.0 >= amount;

                default:
                    throw new ArgumentOutOfRangeException(nameof(unit), unit, null);
            }
        }
        private void UpdateChecker_EnableControls(object sender, RunWorkerCompletedEventArgs runWorkerCompletedEventArgs)
        {
            updateCheckNowButton.Enabled = true;
            checkForUpdatesToolStripMenuItem.Enabled = true;
            verifyIntegrityToolStripMenuItem.Enabled = true;
            forceUpdateToolStripMenuItem.Enabled = true;
            uninstallToolStripMenuItem.Enabled = true;
            developerToolStripMenuItem.Enabled = true;
        }

        private void InitializeWorker()
        {
            if (updateChecker != null)
            {
                return;
            }

            updateChecker = new BackgroundWorker { WorkerSupportsCancellation = true };
            updateChecker.DoWork += UpdateChecker_DoWork;
            updateChecker.RunWorkerCompleted += UpdateChecker_RunWorkerCompleted;
            updateChecker.RunWorkerCompleted += UpdateChecker_EnableControls;
        }

        private void CheckForModUpdates(bool force = false)
        {
            if (!force && !loaderini.ModUpdateCheck)
            {
                return;
            }

            InitializeWorker();

            if (!force && !UpdateTimeElapsed(loaderini.UpdateUnit, loaderini.UpdateFrequency, DateTime.FromFileTimeUtc(loaderini.ModUpdateTime)))
            {
                return;
            }

            checkedForUpdates = true;
            loaderini.ModUpdateTime = DateTime.UtcNow.ToFileTimeUtc();
            updateChecker.RunWorkerAsync(mods.Select(x => new KeyValuePair<string, ModInfo>(x.Key, x.Value)).ToList());
            updateCheckNowButton.Enabled = false;
        }

        private void UpdateChecker_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            if (modUpdater.ForceUpdate)
            {
                updateChecker?.Dispose();
                updateChecker = null;
                modUpdater.ForceUpdate = false;
                modUpdater.Clear();
            }

            if (e.Cancelled)
            {
                return;
            }

            if (!(e.Result is Tuple<List<ModDownload>, List<string>> data))
            {
                return;
            }

            List<string> errors = data.Item2;
            if (errors.Count != 0)
            {
                MessageBox.Show(this, "The following errors occurred while checking for updates:\n\n" + string.Join("\n", errors),
                    "Update Errors", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }

            bool manual = manualModUpdate;
            manualModUpdate = false;

            List<ModDownload> updates = data.Item1;
            if (updates.Count == 0)
            {
                if (manual)
                {
                    MessageBox.Show(this, "Mods are up to date.",
                        "No Updates", MessageBoxButtons.OK, MessageBoxIcon.Information);
                }
                return;
            }

            using (var dialog = new ModUpdatesDialog(updates))
            {
                if (dialog.ShowDialog(this) != DialogResult.OK)
                {
                    return;
                }

                updates = dialog.SelectedMods;
            }

            if (updates.Count == 0)
            {
                return;
            }

            DialogResult result;

            do
            {
                try
                {
                    result = DialogResult.Cancel;
                    if (!Directory.Exists(updatePath))
                    {
                        Directory.CreateDirectory(updatePath);
                    }
                }
                catch (Exception ex)
                {
                    result = MessageBox.Show(this, "Failed to create temporary update directory:\n" + ex.Message
                        + "\n\nWould you like to retry?", "Directory Creation Failed", MessageBoxButtons.RetryCancel);
                }
            } while (result == DialogResult.Retry);

            using (var progress = new ModDownloadDialog(updates, updatePath))
            {
                progress.ShowDialog(this);
            }

            do
            {
                try
                {
                    result = DialogResult.Cancel;
                    Directory.Delete(updatePath, true);
                }
                catch (Exception ex)
                {
                    result = MessageBox.Show(this, "Failed to remove temporary update directory:\n" + ex.Message
                        + "\n\nWould you like to retry? You can remove the directory manually later.",
                        "Directory Deletion Failed", MessageBoxButtons.RetryCancel);
                }
            } while (result == DialogResult.Retry);

            RefreshModList();
        }

        private void UpdateChecker_DoWork(object sender, DoWorkEventArgs e)
        {
            if (!(sender is BackgroundWorker worker))
            {
                throw new Exception("what");
            }

            Invoke(new Action(() =>
            {
                updateCheckNowButton.Enabled = false;
                checkForUpdatesToolStripMenuItem.Enabled = false;
                verifyIntegrityToolStripMenuItem.Enabled = false;
                forceUpdateToolStripMenuItem.Enabled = false;
                uninstallToolStripMenuItem.Enabled = false;
                developerToolStripMenuItem.Enabled = false;
            }));

            var updatableMods = e.Argument as List<KeyValuePair<string, ModInfo>>;
            List<ModDownload> updates = null;
            List<string> errors = null;

            var tokenSource = new CancellationTokenSource();
            CancellationToken token = tokenSource.Token;

            using (var task = new Task(() => modUpdater.GetModUpdates(updatableMods, out updates, out errors, token), token))
            {
                task.Start();

                while (!task.IsCompleted && !task.IsCanceled)
                {
                    Application.DoEvents();

                    if (worker.CancellationPending)
                    {
                        tokenSource.Cancel();
                    }
                }

                task.Wait(token);
            }

            e.Result = new Tuple<List<ModDownload>, List<string>>(updates, errors);
        }

        private void UpdateChecker_DoWorkForced(object sender, DoWorkEventArgs e)
        {
            if (!(sender is BackgroundWorker worker))
            {
                throw new Exception("what");
            }

            if (!(e.Argument is List<Tuple<string, ModInfo, List<ModManifestDiff>>> updatableMods) || updatableMods.Count == 0)
            {
                return;
            }

            var updates = new List<ModDownload>();
            var errors = new List<string>();

            using (var client = new UpdaterWebClient())
            {
                foreach (Tuple<string, ModInfo, List<ModManifestDiff>> info in updatableMods)
                {
                    if (worker.CancellationPending)
                    {
                        e.Cancel = true;
                        break;
                    }

                    ModInfo mod = info.Item2;
                    if (!string.IsNullOrEmpty(mod.GitHubRepo))
                    {
                        if (string.IsNullOrEmpty(mod.GitHubAsset))
                        {
                            errors.Add($"[{ mod.Name }] GitHubRepo specified, but GitHubAsset is missing.");
                            continue;
                        }

                        ModDownload d = modUpdater.GetGitHubReleases(mod, info.Item1, client, errors);
                        if (d != null)
                        {
                            updates.Add(d);
                        }
                    }
                    else if (!string.IsNullOrEmpty(mod.GameBananaItemType) && mod.GameBananaItemId.HasValue)
                    {
                        ModDownload d = modUpdater.GetGameBananaReleases(mod, info.Item1, errors);
                        if (d != null)
                        {
                            updates.Add(d);
                        }
                    }
                    else if (!string.IsNullOrEmpty(mod.UpdateUrl))
                    {
                        List<ModManifestEntry> localManifest = info.Item3
                            .Where(x => x.State == ModManifestState.Unchanged)
                            .Select(x => x.Current).ToList();

                        ModDownload d = modUpdater.CheckModularVersion(mod, info.Item1, localManifest, client, errors);
                        if (d != null)
                        {
                            updates.Add(d);
                        }
                    }
                }
            }

            e.Result = new Tuple<List<ModDownload>, List<string>>(updates, errors);
        }

        private readonly Dictionary<string, List<GitHubRelease>> gitHubCache = new Dictionary<string, List<GitHubRelease>>();

        private bool CheckForUpdates(bool force = false)
        {
            if (!force && !loaderini.UpdateCheck)
            {
                return false;
            }

            if (!force && !UpdateTimeElapsed(loaderini.UpdateUnit, loaderini.UpdateFrequency, DateTime.FromFileTimeUtc(loaderini.UpdateTime)))
            {
                return false;
            }

            checkedForUpdates = true;
            loaderini.UpdateTime = DateTime.UtcNow.ToFileTimeUtc();

            // Check for Mod Loader updates

            List<GitHubRelease> releases = null;
            string url = "https://api.github.com/repos/kellsnc/Rayman2ModLoader/releases";

            UpdaterWebClient client = new UpdaterWebClient();

            if (!gitHubCache.ContainsKey(url))
            {
                try
                {
                    string text = client.DownloadString(url);
                    releases = JsonConvert.DeserializeObject<List<GitHubRelease>>(text)
                        .Where(x => !x.Draft && !x.PreRelease)
                        .ToList();

                    if (releases.Count > 0)
                    {
                        gitHubCache[url] = releases;
                    }
                }
                catch (Exception ex)
                {
                    
                }
            }
            else
            {
                releases = gitHubCache[url];
            }

            if (releases == null || releases.Count == 0)
            {
                return false;
            }

            foreach (GitHubRelease release in releases)
            {
                if (float.Parse(release.Name, System.Globalization.CultureInfo.InvariantCulture) > modloaderver)
                {
                    GitHubAsset asset = release.Assets
                    .FirstOrDefault(x => x.Name.Equals("Rayman2ModLoader.7z", StringComparison.OrdinalIgnoreCase));

                    if (asset == null)
                    {
                        continue;
                    }

                    using (var dlg = new UpdateMessageDialog("Rayman2 Mod Manager Update", release.Body))
                    {
                        if (dlg.ShowDialog(this) == DialogResult.Yes)
                        {
                            DialogResult result = DialogResult.OK;
                            do
                            {
                                try
                                {
                                    if (!Directory.Exists(updatePath))
                                    {
                                        Directory.CreateDirectory(updatePath);
                                    }
                                }
                                catch (Exception ex)
                                {
                                    result = MessageBox.Show(this, "Failed to create temporary update directory:\n" + ex.Message
                                                                   + "\n\nWould you like to retry?", "Directory Creation Failed", MessageBoxButtons.RetryCancel);
                                    if (result == DialogResult.Cancel) return false;
                                }
                            } while (result == DialogResult.Retry);

                            using (var dlg2 = new LoaderDownloadDialog(asset.DownloadUrl, updatePath))
                                if (dlg2.ShowDialog(this) == DialogResult.OK)
                                {
                                    Close();
                                    return true;
                                }
                        }
                    }

                    break;
                }
            }

            return false;
        }

        private void updateCheckNowButton_Click(object sender, EventArgs e)
        {
            updateCheckNowButton.Enabled = false;

            if (CheckForUpdates(true))
            {
                return;
            }

            manualModUpdate = true;
            CheckForModUpdates(true);
        }

        private void MainForm_Shown(object sender, EventArgs e)
        {
            if (CheckForUpdates())
                return;

            if (loaderInstalled == false)
            {
                DialogResult result = MessageBox.Show("The Mod Loader is not installed, do you want to install it?\nIt will modify \"ubi.ini\".", "Install Mod Loader", MessageBoxButtons.YesNo);

                if (result == DialogResult.Yes)
                {
                    InstallLoader();
                }
            }

            List<string> uris = Program.UriQueue.GetUris();

            foreach (string str in uris)
            {
                HandleUri(str);
            }

            Program.UriQueue.UriEnqueued += UriQueueOnUriEnqueued;

            CheckForModUpdates();

            // If we've checked for updates, save the modified
            // last update times without requiring the user to
            // click the save button.
            if (checkedForUpdates)
            {
                SaveLoaderConfig();
            }
        }

        private void HandleUri(string uri)
        {
            if (WindowState == FormWindowState.Minimized)
            {
                WindowState = FormWindowState.Normal;
            }

            Activate();

            var fields = uri.Substring("rm2mm:".Length).Split(',');

            // TODO: lib-ify
            string itemType = fields.FirstOrDefault(x => x.StartsWith("gb_itemtype", StringComparison.InvariantCultureIgnoreCase));
            itemType = itemType.Substring(itemType.IndexOf(":") + 1);

            string itemId = fields.FirstOrDefault(x => x.StartsWith("gb_itemid", StringComparison.InvariantCultureIgnoreCase));
            itemId = itemId.Substring(itemId.IndexOf(":") + 1);

            var dummyInfo = new ModInfo();

            GameBananaItem gbi = GameBananaItem.Load(itemType, long.Parse(itemId));

            dummyInfo.Name = gbi.Name;

            dummyInfo.Author = gbi.OwnerName;

            DialogResult result = MessageBox.Show(this, $"Do you want to install mod \"{dummyInfo.Name}\" by {dummyInfo.Author} from {new Uri(fields[0]).DnsSafeHost}?", "Mod Download", MessageBoxButtons.YesNo, MessageBoxIcon.Question);

            if (result != DialogResult.Yes)
            {
                return;
            }

            #region create update folder
            do
            {
                try
                {
                    result = DialogResult.Cancel;
                    if (!Directory.Exists(updatePath))
                    {
                        Directory.CreateDirectory(updatePath);
                    }
                }
                catch (Exception ex)
                {
                    result = MessageBox.Show(this, "Failed to create temporary update directory:\n" + ex.Message
                                                   + "\n\nWould you like to retry?", "Directory Creation Failed", MessageBoxButtons.RetryCancel);
                }
            } while (result == DialogResult.Retry);
            #endregion

            string dummyPath = dummyInfo.Name;

            foreach (char c in Path.GetInvalidFileNameChars())
            {
                dummyPath = dummyPath.Replace(c, '_');
            }

            dummyPath = Path.Combine("mods", dummyPath);

            var updates = new List<ModDownload>
            {
                new ModDownload(dummyInfo, dummyPath, fields[0], null, 0)
            };

            using (var progress = new ModDownloadDialog(updates, updatePath))
            {
                progress.ShowDialog(this);
            }

            do
            {
                try
                {
                    result = DialogResult.Cancel;
                    Directory.Delete(updatePath, true);
                }
                catch (Exception ex)
                {
                    result = MessageBox.Show(this, "Failed to remove temporary update directory:\n" + ex.Message
                                                   + "\n\nWould you like to retry? You can remove the directory manually later.",
                        "Directory Deletion Failed", MessageBoxButtons.RetryCancel);
                }
            } while (result == DialogResult.Retry);

            RefreshModList();
        }

        private void UriQueueOnUriEnqueued(object sender, OnUriEnqueuedArgs args)
        {
            args.Handled = true;

            if (InvokeRequired)
            {
                Invoke((Action<object, OnUriEnqueuedArgs>)UriQueueOnUriEnqueued, sender, args);
                return;
            }

            HandleUri(args.Uri);
        }

        private void UpdateSelectedMods()
        {
            InitializeWorker();
            manualModUpdate = true;
            updateChecker?.RunWorkerAsync(modListView.SelectedItems.Cast<ListViewItem>()
                .Select(x => (string)x.Tag)
                .Select(x => new KeyValuePair<string, ModInfo>(x, mods[x]))
                .ToList());
        }

        private void forceUpdateToolStripMenuItem_Click(object sender, EventArgs e)
        {
            var result = MessageBox.Show(this, "This will force all selected mods to be completely re-downloaded."
                + " Are you sure you want to continue?",
                "Force Update", MessageBoxButtons.YesNo, MessageBoxIcon.Warning);

            if (result != DialogResult.Yes)
            {
                return;
            }

            modUpdater.ForceUpdate = true;
            UpdateSelectedMods();
        }

        private void checkForUpdatesToolStripMenuItem_Click(object sender, EventArgs e)
        {
            UpdateSelectedMods();
        }

        private void verifyIntegrityToolStripMenuItem_Click(object sender, EventArgs e)
        {
            List<Tuple<string, ModInfo>> items = modListView.SelectedItems.Cast<ListViewItem>()
                .Select(x => (string)x.Tag)
                .Where(x => File.Exists(Path.Combine("mods", x, "mod.manifest")))
                .Select(x => new Tuple<string, ModInfo>(x, mods[x]))
                .ToList();

            if (items.Count < 1)
            {
                MessageBox.Show(this, "None of the selected mods have manifests, so they cannot be verified.",
                    "Missing mod.manifest", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }

            using (var progress = new VerifyModDialog(items))
            {
                var result = progress.ShowDialog(this);
                if (result == DialogResult.Cancel)
                {
                    return;
                }

                List<Tuple<string, ModInfo, List<ModManifestDiff>>> failed = progress.Failed;
                if (failed.Count < 1)
                {
                    MessageBox.Show(this, "All selected mods passed verification.", "Integrity Pass",
                        MessageBoxButtons.OK, MessageBoxIcon.Information);
                }
                else
                {
                    result = MessageBox.Show(this, "The following mods failed verification:\n"
                        + string.Join("\n", failed.Select(x => $"{x.Item2.Name}: {x.Item3.Count(y => y.State != ModManifestState.Unchanged)} file(s)"))
                        + "\n\nWould you like to attempt repairs?",
                        "Integrity Fail", MessageBoxButtons.YesNo, MessageBoxIcon.Warning);

                    if (result != DialogResult.Yes)
                    {
                        return;
                    }

                    InitializeWorker();

                    updateChecker.DoWork -= UpdateChecker_DoWork;
                    updateChecker.DoWork += UpdateChecker_DoWorkForced;

                    updateChecker.RunWorkerAsync(failed);

                    modUpdater.ForceUpdate = true;
                    updateCheckNowButton.Enabled = false;
                }
            }
        }

        private void generateManifestToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (!displayedManifestWarning)
            {
                DialogResult result = MessageBox.Show(this, "This is a developer functionality, are you sure?",
                    "Warning", MessageBoxButtons.YesNo, MessageBoxIcon.Warning);

                if (result != DialogResult.Yes)
                {
                    return;
                }

                displayedManifestWarning = true;
            }

            foreach (ListViewItem item in modListView.SelectedItems)
            {
                var modPath = Path.Combine("mods", (string)item.Tag);
                var manifestPath = Path.Combine(modPath, "mod.manifest");

                List<ModManifestEntry> manifest;
                List<ModManifestDiff> diff;

                using (var progress = new ManifestDialog(modPath, $"Generating manifest: {(string)item.Tag}", true))
                {
                    progress.SetTask("Generating file index...");
                    if (progress.ShowDialog(this) == DialogResult.Cancel)
                    {
                        continue;
                    }

                    diff = progress.Diff;
                }

                if (diff == null)
                {
                    continue;
                }

                if (diff.Count(x => x.State != ModManifestState.Unchanged) <= 0)
                {
                    continue;
                }

                using (var dialog = new ManifestDiffDialog(diff))
                {
                    if (dialog.ShowDialog(this) == DialogResult.Cancel)
                    {
                        continue;
                    }

                    manifest = dialog.MakeNewManifest();
                }

                ModManifest.ToFile(manifest, manifestPath);
            }
        }

        private void modListView_ItemChecked(object sender, ItemCheckedEventArgs e)
        {
            if (updatingListView == false)
            {
                Rayman2ModInfo inf = mods[(string)e.Item.Tag];

                if (e.Item.Checked == false)
                {
                    if (string.IsNullOrEmpty(inf.GLI_DllFile) == false && comboBoxDLL.Text == inf.GLI_DllFile)
                    {
                        comboBoxDLL.Text = comboBoxDLL.Items[0].ToString();
                    }

                    if (string.IsNullOrEmpty(inf.GLI_Dll) == false && comboBoxDLL.Text == inf.GLI_Dll)
                    {
                        comboBoxAPI.Text = comboBoxAPI.Items[0].ToString();
                    }
                }
                else if (e.Item.Checked == true)
                {
                    if (string.IsNullOrEmpty(inf.GLI_DllFile) == false)
                    {
                        comboBoxDLL.Text = inf.GLI_DllFile;
                    }

                    if (string.IsNullOrEmpty(inf.GLI_Dll) == false)
                    {
                        comboBoxAPI.Text = inf.GLI_Dll;
                    }
                }
            }
        }
    }
}
