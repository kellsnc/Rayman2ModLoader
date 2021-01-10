
namespace Rayman2ModManager.Forms
{
    partial class AddModForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(AddModForm));
            this.addButton = new System.Windows.Forms.Button();
            this.cancelButton = new System.Windows.Forms.Button();
            this.newModTabControl = new System.Windows.Forms.TabControl();
            this.generalTab = new System.Windows.Forms.TabPage();
            this.updateTab = new System.Windows.Forms.TabPage();
            this.textModName = new System.Windows.Forms.TextBox();
            this.nameLabel = new System.Windows.Forms.Label();
            this.authorLabel = new System.Windows.Forms.Label();
            this.textModAuthor = new System.Windows.Forms.TextBox();
            this.textModDescription = new System.Windows.Forms.TextBox();
            this.descLabel = new System.Windows.Forms.Label();
            this.textModVersion = new System.Windows.Forms.TextBox();
            this.versionLabel = new System.Windows.Forms.Label();
            this.exeCheckBox = new System.Windows.Forms.CheckBox();
            this.textModExe = new System.Windows.Forms.TextBox();
            this.gitRadioButton = new System.Windows.Forms.RadioButton();
            this.gbRadioButton = new System.Windows.Forms.RadioButton();
            this.urlRadioButton = new System.Windows.Forms.RadioButton();
            this.noneRadioButton = new System.Windows.Forms.RadioButton();
            this.updateInfo1Label = new System.Windows.Forms.Label();
            this.updateInfo2Label = new System.Windows.Forms.Label();
            this.updateInfo1 = new System.Windows.Forms.TextBox();
            this.updateInfo2 = new System.Windows.Forms.TextBox();
            this.dllCheckBox = new System.Windows.Forms.CheckBox();
            this.textModDLL = new System.Windows.Forms.TextBox();
            this.newModTabControl.SuspendLayout();
            this.generalTab.SuspendLayout();
            this.updateTab.SuspendLayout();
            this.SuspendLayout();
            // 
            // addButton
            // 
            this.addButton.Location = new System.Drawing.Point(468, 342);
            this.addButton.Name = "addButton";
            this.addButton.Size = new System.Drawing.Size(96, 40);
            this.addButton.TabIndex = 0;
            this.addButton.Text = "Add";
            this.addButton.UseVisualStyleBackColor = true;
            this.addButton.Click += new System.EventHandler(this.addButton_Click);
            // 
            // cancelButton
            // 
            this.cancelButton.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.cancelButton.Location = new System.Drawing.Point(570, 342);
            this.cancelButton.Name = "cancelButton";
            this.cancelButton.Size = new System.Drawing.Size(96, 40);
            this.cancelButton.TabIndex = 1;
            this.cancelButton.Text = "Cancel";
            this.cancelButton.UseVisualStyleBackColor = true;
            this.cancelButton.Click += new System.EventHandler(this.cancelButton_Click);
            // 
            // newModTabControl
            // 
            this.newModTabControl.Controls.Add(this.generalTab);
            this.newModTabControl.Controls.Add(this.updateTab);
            this.newModTabControl.Location = new System.Drawing.Point(0, 0);
            this.newModTabControl.Name = "newModTabControl";
            this.newModTabControl.SelectedIndex = 0;
            this.newModTabControl.Size = new System.Drawing.Size(680, 336);
            this.newModTabControl.TabIndex = 2;
            // 
            // generalTab
            // 
            this.generalTab.Controls.Add(this.textModDLL);
            this.generalTab.Controls.Add(this.dllCheckBox);
            this.generalTab.Controls.Add(this.textModExe);
            this.generalTab.Controls.Add(this.exeCheckBox);
            this.generalTab.Controls.Add(this.versionLabel);
            this.generalTab.Controls.Add(this.textModVersion);
            this.generalTab.Controls.Add(this.descLabel);
            this.generalTab.Controls.Add(this.textModDescription);
            this.generalTab.Controls.Add(this.textModAuthor);
            this.generalTab.Controls.Add(this.authorLabel);
            this.generalTab.Controls.Add(this.nameLabel);
            this.generalTab.Controls.Add(this.textModName);
            this.generalTab.Location = new System.Drawing.Point(4, 29);
            this.generalTab.Name = "generalTab";
            this.generalTab.Padding = new System.Windows.Forms.Padding(3);
            this.generalTab.Size = new System.Drawing.Size(672, 303);
            this.generalTab.TabIndex = 0;
            this.generalTab.Text = "General";
            this.generalTab.UseVisualStyleBackColor = true;
            // 
            // updateTab
            // 
            this.updateTab.Controls.Add(this.updateInfo2);
            this.updateTab.Controls.Add(this.updateInfo1);
            this.updateTab.Controls.Add(this.updateInfo2Label);
            this.updateTab.Controls.Add(this.updateInfo1Label);
            this.updateTab.Controls.Add(this.noneRadioButton);
            this.updateTab.Controls.Add(this.urlRadioButton);
            this.updateTab.Controls.Add(this.gbRadioButton);
            this.updateTab.Controls.Add(this.gitRadioButton);
            this.updateTab.Location = new System.Drawing.Point(4, 29);
            this.updateTab.Name = "updateTab";
            this.updateTab.Padding = new System.Windows.Forms.Padding(3);
            this.updateTab.Size = new System.Drawing.Size(672, 303);
            this.updateTab.TabIndex = 1;
            this.updateTab.Text = "Update";
            this.updateTab.UseVisualStyleBackColor = true;
            // 
            // textModName
            // 
            this.textModName.Location = new System.Drawing.Point(69, 6);
            this.textModName.MaxLength = 50;
            this.textModName.Name = "textModName";
            this.textModName.Size = new System.Drawing.Size(593, 26);
            this.textModName.TabIndex = 0;
            // 
            // nameLabel
            // 
            this.nameLabel.AutoSize = true;
            this.nameLabel.Location = new System.Drawing.Point(8, 9);
            this.nameLabel.Name = "nameLabel";
            this.nameLabel.Size = new System.Drawing.Size(55, 20);
            this.nameLabel.TabIndex = 1;
            this.nameLabel.Text = "Name:";
            // 
            // authorLabel
            // 
            this.authorLabel.AutoSize = true;
            this.authorLabel.Location = new System.Drawing.Point(8, 41);
            this.authorLabel.Name = "authorLabel";
            this.authorLabel.Size = new System.Drawing.Size(61, 20);
            this.authorLabel.TabIndex = 2;
            this.authorLabel.Text = "Author:";
            // 
            // textModAuthor
            // 
            this.textModAuthor.Location = new System.Drawing.Point(75, 38);
            this.textModAuthor.MaxLength = 120;
            this.textModAuthor.Name = "textModAuthor";
            this.textModAuthor.Size = new System.Drawing.Size(587, 26);
            this.textModAuthor.TabIndex = 3;
            // 
            // textModDescription
            // 
            this.textModDescription.Location = new System.Drawing.Point(107, 70);
            this.textModDescription.MaxLength = 255;
            this.textModDescription.Name = "textModDescription";
            this.textModDescription.Size = new System.Drawing.Size(555, 26);
            this.textModDescription.TabIndex = 4;
            // 
            // descLabel
            // 
            this.descLabel.AutoSize = true;
            this.descLabel.Location = new System.Drawing.Point(8, 73);
            this.descLabel.Name = "descLabel";
            this.descLabel.Size = new System.Drawing.Size(93, 20);
            this.descLabel.TabIndex = 5;
            this.descLabel.Text = "Description:";
            // 
            // textModVersion
            // 
            this.textModVersion.Location = new System.Drawing.Point(81, 102);
            this.textModVersion.MaxLength = 8;
            this.textModVersion.Name = "textModVersion";
            this.textModVersion.Size = new System.Drawing.Size(581, 26);
            this.textModVersion.TabIndex = 6;
            // 
            // versionLabel
            // 
            this.versionLabel.AutoSize = true;
            this.versionLabel.Location = new System.Drawing.Point(8, 105);
            this.versionLabel.Name = "versionLabel";
            this.versionLabel.Size = new System.Drawing.Size(67, 20);
            this.versionLabel.TabIndex = 7;
            this.versionLabel.Text = "Version:";
            // 
            // exeCheckBox
            // 
            this.exeCheckBox.AutoSize = true;
            this.exeCheckBox.Location = new System.Drawing.Point(12, 175);
            this.exeCheckBox.Name = "exeCheckBox";
            this.exeCheckBox.Size = new System.Drawing.Size(173, 24);
            this.exeCheckBox.TabIndex = 8;
            this.exeCheckBox.Text = "Custom Executable";
            this.exeCheckBox.UseVisualStyleBackColor = true;
            // 
            // textModExe
            // 
            this.textModExe.Location = new System.Drawing.Point(191, 173);
            this.textModExe.MaxLength = 50;
            this.textModExe.Name = "textModExe";
            this.textModExe.Size = new System.Drawing.Size(471, 26);
            this.textModExe.TabIndex = 9;
            // 
            // gitRadioButton
            // 
            this.gitRadioButton.AutoSize = true;
            this.gitRadioButton.Location = new System.Drawing.Point(8, 36);
            this.gitRadioButton.Name = "gitRadioButton";
            this.gitRadioButton.Size = new System.Drawing.Size(139, 24);
            this.gitRadioButton.TabIndex = 0;
            this.gitRadioButton.Text = "GitHub update";
            this.gitRadioButton.UseVisualStyleBackColor = true;
            this.gitRadioButton.CheckedChanged += new System.EventHandler(this.gitRadioButton_CheckedChanged);
            // 
            // gbRadioButton
            // 
            this.gbRadioButton.AutoSize = true;
            this.gbRadioButton.Location = new System.Drawing.Point(8, 66);
            this.gbRadioButton.Name = "gbRadioButton";
            this.gbRadioButton.Size = new System.Drawing.Size(188, 24);
            this.gbRadioButton.TabIndex = 1;
            this.gbRadioButton.Text = "GameBanana update";
            this.gbRadioButton.UseVisualStyleBackColor = true;
            this.gbRadioButton.CheckedChanged += new System.EventHandler(this.gbRadioButton_CheckedChanged);
            // 
            // urlRadioButton
            // 
            this.urlRadioButton.AutoSize = true;
            this.urlRadioButton.Location = new System.Drawing.Point(8, 96);
            this.urlRadioButton.Name = "urlRadioButton";
            this.urlRadioButton.Size = new System.Drawing.Size(124, 24);
            this.urlRadioButton.TabIndex = 2;
            this.urlRadioButton.Text = "URL Update";
            this.urlRadioButton.UseVisualStyleBackColor = true;
            this.urlRadioButton.CheckedChanged += new System.EventHandler(this.urlRadioButton_CheckedChanged);
            // 
            // noneRadioButton
            // 
            this.noneRadioButton.AutoSize = true;
            this.noneRadioButton.Checked = true;
            this.noneRadioButton.Location = new System.Drawing.Point(8, 6);
            this.noneRadioButton.Name = "noneRadioButton";
            this.noneRadioButton.Size = new System.Drawing.Size(72, 24);
            this.noneRadioButton.TabIndex = 3;
            this.noneRadioButton.TabStop = true;
            this.noneRadioButton.Text = "None";
            this.noneRadioButton.UseVisualStyleBackColor = true;
            this.noneRadioButton.CheckedChanged += new System.EventHandler(this.noneRadioButton_CheckedChanged);
            // 
            // updateInfo1Label
            // 
            this.updateInfo1Label.AutoSize = true;
            this.updateInfo1Label.Location = new System.Drawing.Point(6, 138);
            this.updateInfo1Label.Name = "updateInfo1Label";
            this.updateInfo1Label.Size = new System.Drawing.Size(44, 20);
            this.updateInfo1Label.TabIndex = 4;
            this.updateInfo1Label.Text = "info1";
            this.updateInfo1Label.Visible = false;
            // 
            // updateInfo2Label
            // 
            this.updateInfo2Label.AutoSize = true;
            this.updateInfo2Label.Location = new System.Drawing.Point(4, 190);
            this.updateInfo2Label.Name = "updateInfo2Label";
            this.updateInfo2Label.Size = new System.Drawing.Size(44, 20);
            this.updateInfo2Label.TabIndex = 5;
            this.updateInfo2Label.Text = "info2";
            this.updateInfo2Label.Visible = false;
            // 
            // updateInfo1
            // 
            this.updateInfo1.Location = new System.Drawing.Point(8, 161);
            this.updateInfo1.Name = "updateInfo1";
            this.updateInfo1.Size = new System.Drawing.Size(654, 26);
            this.updateInfo1.TabIndex = 6;
            this.updateInfo1.Visible = false;
            // 
            // updateInfo2
            // 
            this.updateInfo2.Location = new System.Drawing.Point(8, 213);
            this.updateInfo2.Name = "updateInfo2";
            this.updateInfo2.Size = new System.Drawing.Size(654, 26);
            this.updateInfo2.TabIndex = 7;
            this.updateInfo2.Visible = false;
            // 
            // dllCheckBox
            // 
            this.dllCheckBox.AutoSize = true;
            this.dllCheckBox.Location = new System.Drawing.Point(12, 143);
            this.dllCheckBox.Name = "dllCheckBox";
            this.dllCheckBox.Size = new System.Drawing.Size(94, 24);
            this.dllCheckBox.TabIndex = 10;
            this.dllCheckBox.Text = "DLL File";
            this.dllCheckBox.UseVisualStyleBackColor = true;
            // 
            // textModDLL
            // 
            this.textModDLL.Location = new System.Drawing.Point(112, 141);
            this.textModDLL.MaxLength = 50;
            this.textModDLL.Name = "textModDLL";
            this.textModDLL.Size = new System.Drawing.Size(550, 26);
            this.textModDLL.TabIndex = 11;
            // 
            // AddModForm
            // 
            this.AcceptButton = this.addButton;
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CancelButton = this.cancelButton;
            this.ClientSize = new System.Drawing.Size(678, 394);
            this.Controls.Add(this.newModTabControl);
            this.Controls.Add(this.cancelButton);
            this.Controls.Add(this.addButton);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MaximumSize = new System.Drawing.Size(700, 450);
            this.MinimizeBox = false;
            this.MinimumSize = new System.Drawing.Size(700, 450);
            this.Name = "AddModForm";
            this.ShowIcon = false;
            this.ShowInTaskbar = false;
            this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Hide;
            this.Text = "AddModForm";
            this.newModTabControl.ResumeLayout(false);
            this.generalTab.ResumeLayout(false);
            this.generalTab.PerformLayout();
            this.updateTab.ResumeLayout(false);
            this.updateTab.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button addButton;
        private System.Windows.Forms.Button cancelButton;
        private System.Windows.Forms.TabControl newModTabControl;
        private System.Windows.Forms.TabPage generalTab;
        private System.Windows.Forms.Label nameLabel;
        private System.Windows.Forms.TextBox textModName;
        private System.Windows.Forms.TabPage updateTab;
        private System.Windows.Forms.TextBox textModExe;
        private System.Windows.Forms.CheckBox exeCheckBox;
        private System.Windows.Forms.Label versionLabel;
        private System.Windows.Forms.TextBox textModVersion;
        private System.Windows.Forms.Label descLabel;
        private System.Windows.Forms.TextBox textModDescription;
        private System.Windows.Forms.TextBox textModAuthor;
        private System.Windows.Forms.Label authorLabel;
        private System.Windows.Forms.RadioButton urlRadioButton;
        private System.Windows.Forms.RadioButton gbRadioButton;
        private System.Windows.Forms.RadioButton gitRadioButton;
        private System.Windows.Forms.TextBox updateInfo1;
        private System.Windows.Forms.Label updateInfo2Label;
        private System.Windows.Forms.Label updateInfo1Label;
        private System.Windows.Forms.RadioButton noneRadioButton;
        private System.Windows.Forms.TextBox updateInfo2;
        private System.Windows.Forms.TextBox textModDLL;
        private System.Windows.Forms.CheckBox dllCheckBox;
    }
}