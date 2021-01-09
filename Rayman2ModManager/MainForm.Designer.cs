
namespace Rayman2ModManager
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
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
            this.buttonSaveAndPlay = new System.Windows.Forms.Button();
            this.buttonSave = new System.Windows.Forms.Button();
            this.buttonInstall = new System.Windows.Forms.Button();
            this.tabControl = new System.Windows.Forms.TabControl();
            this.modTab = new System.Windows.Forms.TabPage();
            this.splitContainerMods = new System.Windows.Forms.SplitContainer();
            this.modListView = new System.Windows.Forms.ListView();
            this.nameColumnHeader = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.authorColumnHeader = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.versionColumnHeader = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.configModButton = new System.Windows.Forms.Button();
            this.upmostButton = new System.Windows.Forms.Button();
            this.addModButton = new System.Windows.Forms.Button();
            this.upButton = new System.Windows.Forms.Button();
            this.refreshButton = new System.Windows.Forms.Button();
            this.downButton = new System.Windows.Forms.Button();
            this.downmostButton = new System.Windows.Forms.Button();
            this.labelModDescription = new System.Windows.Forms.Label();
            this.codesTab = new System.Windows.Forms.TabPage();
            this.optionsTab = new System.Windows.Forms.TabPage();
            this.groupBoxDebug = new System.Windows.Forms.GroupBox();
            this.checkBoxLog = new System.Windows.Forms.CheckBox();
            this.checkBoxConsole = new System.Windows.Forms.CheckBox();
            this.groupBoxVisual = new System.Windows.Forms.GroupBox();
            this.comboBoxParticules = new System.Windows.Forms.ComboBox();
            this.labelParticules = new System.Windows.Forms.Label();
            this.graphicGroupBox = new System.Windows.Forms.GroupBox();
            this.comboBoxTexMem = new System.Windows.Forms.ComboBox();
            this.labelTexsMem = new System.Windows.Forms.Label();
            this.comboBoxDepth = new System.Windows.Forms.ComboBox();
            this.labelDepth = new System.Windows.Forms.Label();
            this.comboBoxResolutions = new System.Windows.Forms.ComboBox();
            this.xLabel1 = new System.Windows.Forms.Label();
            this.numericUpDown_Height = new System.Windows.Forms.NumericUpDown();
            this.numericUpDown_Width = new System.Windows.Forms.NumericUpDown();
            this.resolutionLabel = new System.Windows.Forms.Label();
            this.comboBoxAPI = new System.Windows.Forms.ComboBox();
            this.graphicsAPILabel = new System.Windows.Forms.Label();
            this.comboBoxDLL = new System.Windows.Forms.ComboBox();
            this.graphicsDLLLabel = new System.Windows.Forms.Label();
            this.toolTip = new System.Windows.Forms.ToolTip(this.components);
            this.checkedListBoxMods = new System.Windows.Forms.CheckedListBox();
            this.tabControl.SuspendLayout();
            this.modTab.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainerMods)).BeginInit();
            this.splitContainerMods.Panel1.SuspendLayout();
            this.splitContainerMods.Panel2.SuspendLayout();
            this.splitContainerMods.SuspendLayout();
            this.codesTab.SuspendLayout();
            this.optionsTab.SuspendLayout();
            this.groupBoxDebug.SuspendLayout();
            this.groupBoxVisual.SuspendLayout();
            this.graphicGroupBox.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_Height)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_Width)).BeginInit();
            this.SuspendLayout();
            // 
            // buttonSaveAndPlay
            // 
            this.buttonSaveAndPlay.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.buttonSaveAndPlay.Location = new System.Drawing.Point(12, 646);
            this.buttonSaveAndPlay.Name = "buttonSaveAndPlay";
            this.buttonSaveAndPlay.Size = new System.Drawing.Size(128, 44);
            this.buttonSaveAndPlay.TabIndex = 0;
            this.buttonSaveAndPlay.Text = "Save and play";
            this.toolTip.SetToolTip(this.buttonSaveAndPlay, "Save the configuration and launch the game.\r\nYou can also launch the game directl" +
        "y.");
            this.buttonSaveAndPlay.UseVisualStyleBackColor = true;
            this.buttonSaveAndPlay.Click += new System.EventHandler(this.buttonSaveAndPlay_Click);
            // 
            // buttonSave
            // 
            this.buttonSave.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.buttonSave.Location = new System.Drawing.Point(146, 646);
            this.buttonSave.Name = "buttonSave";
            this.buttonSave.Size = new System.Drawing.Size(128, 44);
            this.buttonSave.TabIndex = 1;
            this.buttonSave.Text = "Save";
            this.toolTip.SetToolTip(this.buttonSave, "Save the Mod Loader\'s and the game\'s configurations.");
            this.buttonSave.UseVisualStyleBackColor = true;
            this.buttonSave.Click += new System.EventHandler(this.buttonSave_Click);
            // 
            // buttonInstall
            // 
            this.buttonInstall.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.buttonInstall.Location = new System.Drawing.Point(280, 646);
            this.buttonInstall.Name = "buttonInstall";
            this.buttonInstall.Size = new System.Drawing.Size(128, 44);
            this.buttonInstall.TabIndex = 2;
            this.buttonInstall.Text = "Install";
            this.toolTip.SetToolTip(this.buttonInstall, "Install the Mod Loader (will save the game\'s configuration.)");
            this.buttonInstall.UseVisualStyleBackColor = true;
            this.buttonInstall.Click += new System.EventHandler(this.buttonInstall_Click);
            // 
            // tabControl
            // 
            this.tabControl.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.tabControl.Controls.Add(this.modTab);
            this.tabControl.Controls.Add(this.codesTab);
            this.tabControl.Controls.Add(this.optionsTab);
            this.tabControl.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tabControl.ItemSize = new System.Drawing.Size(100, 30);
            this.tabControl.Location = new System.Drawing.Point(0, 0);
            this.tabControl.Name = "tabControl";
            this.tabControl.SelectedIndex = 0;
            this.tabControl.Size = new System.Drawing.Size(580, 640);
            this.tabControl.TabIndex = 3;
            // 
            // modTab
            // 
            this.modTab.Controls.Add(this.splitContainerMods);
            this.modTab.Font = new System.Drawing.Font("Microsoft Sans Serif", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.modTab.Location = new System.Drawing.Point(4, 34);
            this.modTab.Name = "modTab";
            this.modTab.Padding = new System.Windows.Forms.Padding(3);
            this.modTab.Size = new System.Drawing.Size(572, 602);
            this.modTab.TabIndex = 0;
            this.modTab.Text = "Mods";
            this.modTab.UseVisualStyleBackColor = true;
            // 
            // splitContainerMods
            // 
            this.splitContainerMods.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainerMods.Location = new System.Drawing.Point(3, 3);
            this.splitContainerMods.Name = "splitContainerMods";
            this.splitContainerMods.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainerMods.Panel1
            // 
            this.splitContainerMods.Panel1.Controls.Add(this.modListView);
            this.splitContainerMods.Panel1.Controls.Add(this.configModButton);
            this.splitContainerMods.Panel1.Controls.Add(this.upmostButton);
            this.splitContainerMods.Panel1.Controls.Add(this.addModButton);
            this.splitContainerMods.Panel1.Controls.Add(this.upButton);
            this.splitContainerMods.Panel1.Controls.Add(this.refreshButton);
            this.splitContainerMods.Panel1.Controls.Add(this.downButton);
            this.splitContainerMods.Panel1.Controls.Add(this.downmostButton);
            this.splitContainerMods.Panel1MinSize = 440;
            // 
            // splitContainerMods.Panel2
            // 
            this.splitContainerMods.Panel2.Controls.Add(this.labelModDescription);
            this.splitContainerMods.Panel2MinSize = 60;
            this.splitContainerMods.Size = new System.Drawing.Size(566, 596);
            this.splitContainerMods.SplitterDistance = 460;
            this.splitContainerMods.TabIndex = 8;
            // 
            // modListView
            // 
            this.modListView.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.modListView.AutoArrange = false;
            this.modListView.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.modListView.CheckBoxes = true;
            this.modListView.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.nameColumnHeader,
            this.authorColumnHeader,
            this.versionColumnHeader});
            this.modListView.HeaderStyle = System.Windows.Forms.ColumnHeaderStyle.Nonclickable;
            this.modListView.HideSelection = false;
            this.modListView.Location = new System.Drawing.Point(5, 3);
            this.modListView.Name = "modListView";
            this.modListView.Size = new System.Drawing.Size(496, 450);
            this.modListView.TabIndex = 0;
            this.modListView.UseCompatibleStateImageBehavior = false;
            this.modListView.View = System.Windows.Forms.View.Details;
            // 
            // nameColumnHeader
            // 
            this.nameColumnHeader.Text = "Name";
            this.nameColumnHeader.Width = 160;
            // 
            // authorColumnHeader
            // 
            this.authorColumnHeader.Text = "Author";
            this.authorColumnHeader.Width = 80;
            // 
            // versionColumnHeader
            // 
            this.versionColumnHeader.Text = "Version";
            this.versionColumnHeader.Width = 80;
            // 
            // configModButton
            // 
            this.configModButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.configModButton.Enabled = false;
            this.configModButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 11F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.configModButton.Location = new System.Drawing.Point(507, 285);
            this.configModButton.Name = "configModButton";
            this.configModButton.Size = new System.Drawing.Size(52, 52);
            this.configModButton.TabIndex = 5;
            this.configModButton.Text = "⚙";
            this.toolTip.SetToolTip(this.configModButton, "Configure the mod\'s custom settings.");
            this.configModButton.UseVisualStyleBackColor = true;
            this.configModButton.Click += new System.EventHandler(this.configModButton_Click);
            // 
            // upmostButton
            // 
            this.upmostButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.upmostButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 14F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.upmostButton.Location = new System.Drawing.Point(507, 3);
            this.upmostButton.Name = "upmostButton";
            this.upmostButton.Size = new System.Drawing.Size(52, 52);
            this.upmostButton.TabIndex = 1;
            this.upmostButton.Text = "⤒";
            this.toolTip.SetToolTip(this.upmostButton, "Move selected mods to topmost.");
            this.upmostButton.UseVisualStyleBackColor = true;
            // 
            // addModButton
            // 
            this.addModButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.addModButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.addModButton.Location = new System.Drawing.Point(507, 401);
            this.addModButton.Name = "addModButton";
            this.addModButton.Size = new System.Drawing.Size(52, 52);
            this.addModButton.TabIndex = 7;
            this.addModButton.Text = "＋";
            this.toolTip.SetToolTip(this.addModButton, "Add/create a mod.");
            this.addModButton.UseVisualStyleBackColor = true;
            this.addModButton.Click += new System.EventHandler(this.addModButton_Click);
            // 
            // upButton
            // 
            this.upButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.upButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.upButton.Location = new System.Drawing.Point(507, 61);
            this.upButton.Name = "upButton";
            this.upButton.Size = new System.Drawing.Size(52, 52);
            this.upButton.TabIndex = 2;
            this.upButton.Text = "↑";
            this.toolTip.SetToolTip(this.upButton, "Move selected mods up.");
            this.upButton.UseVisualStyleBackColor = true;
            // 
            // refreshButton
            // 
            this.refreshButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.refreshButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 16F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.refreshButton.Location = new System.Drawing.Point(507, 343);
            this.refreshButton.Name = "refreshButton";
            this.refreshButton.Size = new System.Drawing.Size(52, 52);
            this.refreshButton.TabIndex = 6;
            this.refreshButton.Text = "🗘";
            this.toolTip.SetToolTip(this.refreshButton, "Refresh the mod list.");
            this.refreshButton.UseVisualStyleBackColor = true;
            this.refreshButton.Click += new System.EventHandler(this.refreshButton_Click);
            // 
            // downButton
            // 
            this.downButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.downButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.downButton.Location = new System.Drawing.Point(507, 119);
            this.downButton.Name = "downButton";
            this.downButton.Size = new System.Drawing.Size(52, 52);
            this.downButton.TabIndex = 3;
            this.downButton.Text = "↓";
            this.toolTip.SetToolTip(this.downButton, "Move selected mods down.");
            this.downButton.UseVisualStyleBackColor = true;
            // 
            // downmostButton
            // 
            this.downmostButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.downmostButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 14F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.downmostButton.Location = new System.Drawing.Point(507, 177);
            this.downmostButton.Name = "downmostButton";
            this.downmostButton.Size = new System.Drawing.Size(52, 52);
            this.downmostButton.TabIndex = 4;
            this.downmostButton.Text = "⤓";
            this.toolTip.SetToolTip(this.downmostButton, "Move selected mods to bottom-most");
            this.downmostButton.UseVisualStyleBackColor = true;
            // 
            // labelModDescription
            // 
            this.labelModDescription.AutoSize = true;
            this.labelModDescription.Location = new System.Drawing.Point(5, 0);
            this.labelModDescription.Name = "labelModDescription";
            this.labelModDescription.Size = new System.Drawing.Size(220, 20);
            this.labelModDescription.TabIndex = 0;
            this.labelModDescription.Text = "Description: No mod selected.";
            // 
            // codesTab
            // 
            this.codesTab.Controls.Add(this.checkedListBoxMods);
            this.codesTab.Location = new System.Drawing.Point(4, 34);
            this.codesTab.Name = "codesTab";
            this.codesTab.Padding = new System.Windows.Forms.Padding(3);
            this.codesTab.Size = new System.Drawing.Size(572, 602);
            this.codesTab.TabIndex = 1;
            this.codesTab.Text = "Codes";
            this.codesTab.UseVisualStyleBackColor = true;
            // 
            // optionsTab
            // 
            this.optionsTab.Controls.Add(this.groupBoxDebug);
            this.optionsTab.Controls.Add(this.groupBoxVisual);
            this.optionsTab.Controls.Add(this.graphicGroupBox);
            this.optionsTab.Location = new System.Drawing.Point(4, 34);
            this.optionsTab.Name = "optionsTab";
            this.optionsTab.Size = new System.Drawing.Size(572, 602);
            this.optionsTab.TabIndex = 2;
            this.optionsTab.Text = "Options";
            this.optionsTab.UseVisualStyleBackColor = true;
            // 
            // groupBoxDebug
            // 
            this.groupBoxDebug.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBoxDebug.Controls.Add(this.checkBoxLog);
            this.groupBoxDebug.Controls.Add(this.checkBoxConsole);
            this.groupBoxDebug.Location = new System.Drawing.Point(8, 269);
            this.groupBoxDebug.Name = "groupBoxDebug";
            this.groupBoxDebug.Size = new System.Drawing.Size(554, 90);
            this.groupBoxDebug.TabIndex = 13;
            this.groupBoxDebug.TabStop = false;
            this.groupBoxDebug.Text = "Debugging";
            // 
            // checkBoxLog
            // 
            this.checkBoxLog.AutoSize = true;
            this.checkBoxLog.Location = new System.Drawing.Point(10, 59);
            this.checkBoxLog.Name = "checkBoxLog";
            this.checkBoxLog.Size = new System.Drawing.Size(149, 26);
            this.checkBoxLog.TabIndex = 1;
            this.checkBoxLog.Text = "Enable log file";
            this.toolTip.SetToolTip(this.checkBoxLog, "This will output debug information in a log file.");
            this.checkBoxLog.UseVisualStyleBackColor = true;
            // 
            // checkBoxConsole
            // 
            this.checkBoxConsole.AutoSize = true;
            this.checkBoxConsole.Location = new System.Drawing.Point(10, 27);
            this.checkBoxConsole.Name = "checkBoxConsole";
            this.checkBoxConsole.Size = new System.Drawing.Size(159, 26);
            this.checkBoxConsole.TabIndex = 0;
            this.checkBoxConsole.Text = "Enable console";
            this.toolTip.SetToolTip(this.checkBoxConsole, "This will open a console outputting debug information from the game and from mods" +
        ".");
            this.checkBoxConsole.UseVisualStyleBackColor = true;
            // 
            // groupBoxVisual
            // 
            this.groupBoxVisual.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBoxVisual.Controls.Add(this.comboBoxParticules);
            this.groupBoxVisual.Controls.Add(this.labelParticules);
            this.groupBoxVisual.Location = new System.Drawing.Point(8, 193);
            this.groupBoxVisual.Name = "groupBoxVisual";
            this.groupBoxVisual.Size = new System.Drawing.Size(554, 70);
            this.groupBoxVisual.TabIndex = 12;
            this.groupBoxVisual.TabStop = false;
            this.groupBoxVisual.Text = "Visuals";
            // 
            // comboBoxParticules
            // 
            this.comboBoxParticules.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxParticules.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.comboBoxParticules.FormattingEnabled = true;
            this.comboBoxParticules.Items.AddRange(new object[] {
            "Null",
            "Low",
            "Medium",
            "High"});
            this.comboBoxParticules.Location = new System.Drawing.Point(140, 27);
            this.comboBoxParticules.Name = "comboBoxParticules";
            this.comboBoxParticules.Size = new System.Drawing.Size(135, 30);
            this.comboBoxParticules.TabIndex = 11;
            // 
            // labelParticules
            // 
            this.labelParticules.AutoSize = true;
            this.labelParticules.Location = new System.Drawing.Point(6, 35);
            this.labelParticules.Name = "labelParticules";
            this.labelParticules.Size = new System.Drawing.Size(128, 22);
            this.labelParticules.TabIndex = 11;
            this.labelParticules.Text = "Particule Rate:";
            // 
            // graphicGroupBox
            // 
            this.graphicGroupBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.graphicGroupBox.Controls.Add(this.comboBoxTexMem);
            this.graphicGroupBox.Controls.Add(this.labelTexsMem);
            this.graphicGroupBox.Controls.Add(this.comboBoxDepth);
            this.graphicGroupBox.Controls.Add(this.labelDepth);
            this.graphicGroupBox.Controls.Add(this.comboBoxResolutions);
            this.graphicGroupBox.Controls.Add(this.xLabel1);
            this.graphicGroupBox.Controls.Add(this.numericUpDown_Height);
            this.graphicGroupBox.Controls.Add(this.numericUpDown_Width);
            this.graphicGroupBox.Controls.Add(this.resolutionLabel);
            this.graphicGroupBox.Controls.Add(this.comboBoxAPI);
            this.graphicGroupBox.Controls.Add(this.graphicsAPILabel);
            this.graphicGroupBox.Controls.Add(this.comboBoxDLL);
            this.graphicGroupBox.Controls.Add(this.graphicsDLLLabel);
            this.graphicGroupBox.Location = new System.Drawing.Point(8, 12);
            this.graphicGroupBox.Name = "graphicGroupBox";
            this.graphicGroupBox.Size = new System.Drawing.Size(554, 175);
            this.graphicGroupBox.TabIndex = 0;
            this.graphicGroupBox.TabStop = false;
            this.graphicGroupBox.Text = "Graphics";
            // 
            // comboBoxTexMem
            // 
            this.comboBoxTexMem.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.comboBoxTexMem.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxTexMem.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.comboBoxTexMem.FormattingEnabled = true;
            this.comboBoxTexMem.Items.AddRange(new object[] {
            "Vram",
            "Vram+",
            "Vram4",
            "Vram8",
            "Agp",
            "Agp4",
            "Agp8"});
            this.comboBoxTexMem.Location = new System.Drawing.Point(399, 133);
            this.comboBoxTexMem.Name = "comboBoxTexMem";
            this.comboBoxTexMem.Size = new System.Drawing.Size(149, 30);
            this.comboBoxTexMem.TabIndex = 13;
            this.toolTip.SetToolTip(this.comboBoxTexMem, "Memory allocated for textures.");
            // 
            // labelTexsMem
            // 
            this.labelTexsMem.AutoSize = true;
            this.labelTexsMem.Location = new System.Drawing.Point(239, 141);
            this.labelTexsMem.Name = "labelTexsMem";
            this.labelTexsMem.Size = new System.Drawing.Size(154, 22);
            this.labelTexsMem.TabIndex = 12;
            this.labelTexsMem.Text = "Textures Memory:";
            // 
            // comboBoxDepth
            // 
            this.comboBoxDepth.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxDepth.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.comboBoxDepth.FormattingEnabled = true;
            this.comboBoxDepth.Items.AddRange(new object[] {
            "8",
            "16",
            "24"});
            this.comboBoxDepth.Location = new System.Drawing.Point(75, 133);
            this.comboBoxDepth.Name = "comboBoxDepth";
            this.comboBoxDepth.Size = new System.Drawing.Size(137, 30);
            this.comboBoxDepth.TabIndex = 10;
            this.toolTip.SetToolTip(this.comboBoxDepth, "The color depth resolution.");
            // 
            // labelDepth
            // 
            this.labelDepth.AutoSize = true;
            this.labelDepth.Location = new System.Drawing.Point(6, 141);
            this.labelDepth.Name = "labelDepth";
            this.labelDepth.Size = new System.Drawing.Size(63, 22);
            this.labelDepth.TabIndex = 9;
            this.labelDepth.Text = "Depth:";
            // 
            // comboBoxResolutions
            // 
            this.comboBoxResolutions.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.comboBoxResolutions.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxResolutions.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.comboBoxResolutions.FormattingEnabled = true;
            this.comboBoxResolutions.Items.AddRange(new object[] {
            "800x600",
            "1024x768",
            "1280x720",
            "1280x1024",
            "1600x1200",
            "1920x1080"});
            this.comboBoxResolutions.Location = new System.Drawing.Point(349, 97);
            this.comboBoxResolutions.Name = "comboBoxResolutions";
            this.comboBoxResolutions.Size = new System.Drawing.Size(199, 30);
            this.comboBoxResolutions.TabIndex = 8;
            this.toolTip.SetToolTip(this.comboBoxResolutions, "Choose a predefined set of resolution.");
            this.comboBoxResolutions.SelectedValueChanged += new System.EventHandler(this.comboBoxResolutions_SelectedValueChanged);
            // 
            // xLabel1
            // 
            this.xLabel1.AutoSize = true;
            this.xLabel1.Location = new System.Drawing.Point(218, 105);
            this.xLabel1.Name = "xLabel1";
            this.xLabel1.Size = new System.Drawing.Size(19, 22);
            this.xLabel1.TabIndex = 7;
            this.xLabel1.Text = "x";
            // 
            // numericUpDown_Height
            // 
            this.numericUpDown_Height.Location = new System.Drawing.Point(243, 99);
            this.numericUpDown_Height.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.numericUpDown_Height.Name = "numericUpDown_Height";
            this.numericUpDown_Height.Size = new System.Drawing.Size(100, 28);
            this.numericUpDown_Height.TabIndex = 6;
            this.toolTip.SetToolTip(this.numericUpDown_Height, "The height resolution.");
            // 
            // numericUpDown_Width
            // 
            this.numericUpDown_Width.Location = new System.Drawing.Point(112, 99);
            this.numericUpDown_Width.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.numericUpDown_Width.Name = "numericUpDown_Width";
            this.numericUpDown_Width.Size = new System.Drawing.Size(100, 28);
            this.numericUpDown_Width.TabIndex = 5;
            this.toolTip.SetToolTip(this.numericUpDown_Width, "The width resolution.");
            // 
            // resolutionLabel
            // 
            this.resolutionLabel.AutoSize = true;
            this.resolutionLabel.Location = new System.Drawing.Point(6, 105);
            this.resolutionLabel.Name = "resolutionLabel";
            this.resolutionLabel.Size = new System.Drawing.Size(100, 22);
            this.resolutionLabel.TabIndex = 4;
            this.resolutionLabel.Text = "Resolution:";
            // 
            // comboBoxAPI
            // 
            this.comboBoxAPI.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.comboBoxAPI.FormattingEnabled = true;
            this.comboBoxAPI.Items.AddRange(new object[] {
            "Glide2",
            "DirectX6"});
            this.comboBoxAPI.Location = new System.Drawing.Point(132, 63);
            this.comboBoxAPI.Name = "comboBoxAPI";
            this.comboBoxAPI.Size = new System.Drawing.Size(416, 30);
            this.comboBoxAPI.TabIndex = 3;
            this.toolTip.SetToolTip(this.comboBoxAPI, "The graphics API the game will use, this needs to be set according to the DLL.");
            // 
            // graphicsAPILabel
            // 
            this.graphicsAPILabel.AutoSize = true;
            this.graphicsAPILabel.Location = new System.Drawing.Point(6, 71);
            this.graphicsAPILabel.Name = "graphicsAPILabel";
            this.graphicsAPILabel.Size = new System.Drawing.Size(120, 22);
            this.graphicsAPILabel.TabIndex = 2;
            this.graphicsAPILabel.Text = "Graphics API:";
            // 
            // comboBoxDLL
            // 
            this.comboBoxDLL.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.comboBoxDLL.FormattingEnabled = true;
            this.comboBoxDLL.Items.AddRange(new object[] {
            "GliVd1",
            "GliDX6"});
            this.comboBoxDLL.Location = new System.Drawing.Point(137, 27);
            this.comboBoxDLL.Name = "comboBoxDLL";
            this.comboBoxDLL.Size = new System.Drawing.Size(411, 30);
            this.comboBoxDLL.TabIndex = 1;
            this.toolTip.SetToolTip(this.comboBoxDLL, "The Graphics DLL the game will use, you can also use a custom one.");
            // 
            // graphicsDLLLabel
            // 
            this.graphicsDLLLabel.AutoSize = true;
            this.graphicsDLLLabel.Location = new System.Drawing.Point(6, 35);
            this.graphicsDLLLabel.Name = "graphicsDLLLabel";
            this.graphicsDLLLabel.Size = new System.Drawing.Size(125, 22);
            this.graphicsDLLLabel.TabIndex = 0;
            this.graphicsDLLLabel.Text = "Graphics DLL:";
            // 
            // checkedListBoxMods
            // 
            this.checkedListBoxMods.Dock = System.Windows.Forms.DockStyle.Fill;
            this.checkedListBoxMods.FormattingEnabled = true;
            this.checkedListBoxMods.Location = new System.Drawing.Point(3, 3);
            this.checkedListBoxMods.Name = "checkedListBoxMods";
            this.checkedListBoxMods.Size = new System.Drawing.Size(566, 596);
            this.checkedListBoxMods.TabIndex = 1;
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(578, 744);
            this.Controls.Add(this.tabControl);
            this.Controls.Add(this.buttonInstall);
            this.Controls.Add(this.buttonSave);
            this.Controls.Add(this.buttonSaveAndPlay);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MinimumSize = new System.Drawing.Size(500, 700);
            this.Name = "MainForm";
            this.Text = "Rayman2 Mod Manager";
            this.Load += new System.EventHandler(this.MainForm_Load);
            this.tabControl.ResumeLayout(false);
            this.modTab.ResumeLayout(false);
            this.splitContainerMods.Panel1.ResumeLayout(false);
            this.splitContainerMods.Panel2.ResumeLayout(false);
            this.splitContainerMods.Panel2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainerMods)).EndInit();
            this.splitContainerMods.ResumeLayout(false);
            this.codesTab.ResumeLayout(false);
            this.optionsTab.ResumeLayout(false);
            this.groupBoxDebug.ResumeLayout(false);
            this.groupBoxDebug.PerformLayout();
            this.groupBoxVisual.ResumeLayout(false);
            this.groupBoxVisual.PerformLayout();
            this.graphicGroupBox.ResumeLayout(false);
            this.graphicGroupBox.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_Height)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_Width)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button buttonSaveAndPlay;
        private System.Windows.Forms.Button buttonSave;
        private System.Windows.Forms.Button buttonInstall;
        private System.Windows.Forms.TabControl tabControl;
        private System.Windows.Forms.TabPage modTab;
        private System.Windows.Forms.TabPage codesTab;
        private System.Windows.Forms.TabPage optionsTab;
        private System.Windows.Forms.ListView modListView;
        private System.Windows.Forms.ColumnHeader nameColumnHeader;
        private System.Windows.Forms.ColumnHeader authorColumnHeader;
        private System.Windows.Forms.ColumnHeader versionColumnHeader;
        private System.Windows.Forms.Button upmostButton;
        private System.Windows.Forms.Button downmostButton;
        private System.Windows.Forms.Button downButton;
        private System.Windows.Forms.Button upButton;
        private System.Windows.Forms.Button refreshButton;
        private System.Windows.Forms.Button addModButton;
        private System.Windows.Forms.Button configModButton;
        private System.Windows.Forms.SplitContainer splitContainerMods;
        private System.Windows.Forms.Label labelModDescription;
        private System.Windows.Forms.GroupBox graphicGroupBox;
        private System.Windows.Forms.ComboBox comboBoxResolutions;
        private System.Windows.Forms.Label xLabel1;
        private System.Windows.Forms.NumericUpDown numericUpDown_Height;
        private System.Windows.Forms.NumericUpDown numericUpDown_Width;
        private System.Windows.Forms.Label resolutionLabel;
        private System.Windows.Forms.ComboBox comboBoxAPI;
        private System.Windows.Forms.Label graphicsAPILabel;
        private System.Windows.Forms.ComboBox comboBoxDLL;
        private System.Windows.Forms.Label graphicsDLLLabel;
        private System.Windows.Forms.Label labelDepth;
        private System.Windows.Forms.ComboBox comboBoxDepth;
        private System.Windows.Forms.GroupBox groupBoxVisual;
        private System.Windows.Forms.ComboBox comboBoxParticules;
        private System.Windows.Forms.Label labelParticules;
        private System.Windows.Forms.ComboBox comboBoxTexMem;
        private System.Windows.Forms.Label labelTexsMem;
        private System.Windows.Forms.GroupBox groupBoxDebug;
        private System.Windows.Forms.CheckBox checkBoxLog;
        private System.Windows.Forms.CheckBox checkBoxConsole;
        private System.Windows.Forms.ToolTip toolTip;
        private System.Windows.Forms.CheckedListBox checkedListBoxMods;
    }
}

