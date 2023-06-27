using System;

namespace LIC_settings
{
    class Sensor
    {
        public Byte ID;
        public String Name;
        public Byte Address;
        public UInt32 PollPeriod;

        public Sensor(byte iD, string name, byte address, uint pollPeriod)
        {
            ID = iD;
            Name = name;
            Address = address;
            PollPeriod = pollPeriod;
        }
    }
}
