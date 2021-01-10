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

namespace Rayman2ModManager.Forms
{
    public partial class AddModForm : Form
    {
        private string ModsPath;

        public AddModForm(string modsPath)
        {
            InitializeComponent();
            ModsPath = modsPath;
        }

        private void cancelButton_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.Cancel;
            Close();
        }

        private void addButton_Click(object sender, EventArgs e)
        {
            string moddir = Path.Combine(ModsPath, ValidateFilename(textModName.Text));

            Directory.CreateDirectory(moddir);

            Rayman2ModInfo newMod = new Rayman2ModInfo
            {
                Name = textModName.Text,
                Author = textModAuthor.Text,
                Description = textModDescription.Text,
                Version = textModVersion.Text
            };

            if (dllCheckBox.Checked == true)
            {
                newMod.DLLFile = textModDLL.Text;
            }

            if (exeCheckBox.Checked == true)
            {
                newMod.EXEFile = textModExe.Text;
            }

            if (noneRadioButton.Checked == false)
            {
                if (gitRadioButton.Checked == true)
                {
                    newMod.GitHubRepo = updateInfo1.Text;
                    newMod.GitHubAsset = updateInfo2.Text;
                }
                else if (gbRadioButton.Checked == true)
                {
                    newMod.GameBananaItemType = updateInfo1.Text;
                    newMod.GameBananaItemId = long.Parse(updateInfo2.Text);
                }
                else if (urlRadioButton.Checked == true)
                {
                    newMod.UpdateUrl = updateInfo1.Text;
                    newMod.ChangelogUrl = updateInfo2.Text;
                }
            }

            IniSerializer.Serialize(newMod, Path.Combine(moddir, "mod.ini"));

            DialogResult = DialogResult.OK;
            Close();
        }

        static string ValidateFilename(string filename)
        {
            string result = filename;

            foreach (char c in Path.GetInvalidFileNameChars())
                result = result.Replace(c, '_');

            return result;
        }

        private void noneRadioButton_CheckedChanged(object sender, EventArgs e)
        {
            if (noneRadioButton.Checked == true)
            {
                updateInfo1.Visible = false;
                updateInfo1Label.Visible = false;
                updateInfo2.Visible = false;
                updateInfo2Label.Visible = false;
            } 
            else
            {
                updateInfo1.Visible = true;
                updateInfo1Label.Visible = true;
                updateInfo2.Visible = true;
                updateInfo2Label.Visible = true;
            }
        }

        private void gitRadioButton_CheckedChanged(object sender, EventArgs e)
        {
            if (gitRadioButton.Checked == true)
            {
                updateInfo1Label.Text = "GitHub repository (\"name/repo\")";
                updateInfo2Label.Text = "GitHub asset name";
            }
        }

        private void gbRadioButton_CheckedChanged(object sender, EventArgs e)
        {
            if (gbRadioButton.Checked == true)
            {
                updateInfo1Label.Text = "Type (\"Gamefile\" for example)";
                updateInfo2Label.Text = "ID";
            }
        }

        private void urlRadioButton_CheckedChanged(object sender, EventArgs e)
        {
            if (urlRadioButton.Checked == true)
            {
                updateInfo1Label.Text = "URL";
                updateInfo2Label.Text = "Changelog URL";
            }
        }
    }
}
