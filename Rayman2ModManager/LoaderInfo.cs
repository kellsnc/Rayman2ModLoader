using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using IniFile;
using ModManagerCommon;

namespace Rayman2ModManager
{
	public class Rayman2LoaderInfo : LoaderInfo
	{
		[IniName("Rayman2ModLoader")]
		public LoaderConfig LoaderConfig { get; set; }

		public Rayman2LoaderInfo()
		{
			// todo: read lists
		}
	}

	public class LoaderConfig
    {
		[IniAlwaysInclude]
		[DefaultValue("GliVd1")]
		public string DllName { get; set; } = "GliVd1";

		[IniAlwaysInclude]
		[DefaultValue("Glide2")]
		public string APIName { get; set; } = "Glide2";

		[DefaultValue(false)]
		public bool DebugConsole { get; set; } = false;

		[DefaultValue(false)]
		public bool DebugFile { get; set; } = false;

		[DefaultValue("Mods")]
		[IniAlwaysInclude]
		public string ModsPath { get; set; } = "Mods";

		public string ModsList { get; set; }
		public string CodesList { get; set; }
	}
}
