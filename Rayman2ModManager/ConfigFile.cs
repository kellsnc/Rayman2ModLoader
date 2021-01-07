using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Rayman2ModManager
{
    class ConfigFile
    {
        [DefaultValue("GliVd1")]
        public string GLI_DllFile { get; set; } = "GliVd1";
        [DefaultValue("Glide2")]
        public string GLI_Dll { get; set; } = "Glide2";
        public string GLI_Driver { get; set; } = "";
        public string GLI_Device { get; set; } = "";
        [DefaultValue("1 - 800 x 600 x 16")]
        public string GLI_Mode { get; set; } = "1 - 800 x 600 x 16";
        [DefaultValue("English")]
        public string Language { get; set; } = "English";
        [DefaultValue("Agp8")]
        public string TexturesMem { get; set; } = "Agp8";
        [DefaultValue("High")]
        public string ParticuleRate { get; set; } = "High";
        [DefaultValue(false)]
        public bool SoundHD { get; set; } = false; // left unused
        [DefaultValue(false)]
        public bool Complete { get; set; } = false; // left unused
    }
}
