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
    [Serializable]

    public class ConfigFile
    {
        [IniName("Rayman2")]
        public GameConfig GameConfig { get; set; }
    }

    public class GameConfig
    {
        [DefaultValue("GliVd1")]
        [IniAlwaysInclude]
        public string GLI_DllFile { get; set; } = "GliVd1";
        [DefaultValue("Glide2")]
        [IniAlwaysInclude]
        public string GLI_Dll { get; set; } = "Glide2";
        [IniAlwaysInclude]
        public string GLI_Driver { get; set; } = "";
        [IniAlwaysInclude]
        public string GLI_Device { get; set; } = "";
        [DefaultValue("1 - 800 x 600 x 16")]
        [IniAlwaysInclude]
        public string GLI_Mode { get; set; } = "1 - 800 x 600 x 16";
        [DefaultValue("English")]
        [IniAlwaysInclude]
        public string Language { get; set; } = "English";
        [DefaultValue("Agp8")]
        public string TexturesMem { get; set; } = "Agp8";
        [DefaultValue("High")]
        [IniAlwaysInclude]
        public string ParticuleRate { get; set; } = "High";
        [DefaultValue(false)]
        public bool SoundHD { get; set; } = false; // left unused
        [DefaultValue(false)]
        public bool Complete { get; set; } = false; // left unused
    }
}
