using System;

namespace LIC_settings
{
    class Configs
    {
        public Type ControlType;
        public String ControlName;
        public String ControlText;
        public bool ControlChecked;

        public Configs(Type controlType, string controlName, string controlText, bool controlChecked)
        {
            ControlType = controlType;
            ControlName = controlName;
            ControlText = controlText;
            ControlChecked = controlChecked;
        }
    }

}
