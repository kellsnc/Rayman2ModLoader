using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using IniFile;
using ModManagerCommon;

namespace Rayman2ModManager
{

	class Rayman2LoaderInfo : LoaderInfo
	{
		public string DllName { get; set; }
		public string APIName { get; set; }
		public bool DebugConsole { get; set; }
		public bool DebugFile { get; set; }
		public string ModsPath { get; set; }
		public string ModsList { get; set; }
		public string CodesList { get; set; }

		public Rayman2LoaderInfo()
		{
			// todo: read lists
		}
	}
}
