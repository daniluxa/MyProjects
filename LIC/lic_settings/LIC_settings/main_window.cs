using Force.Crc32;
using MQTTnet;
using MQTTnet.Client;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Data;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.IO;
using System.IO.Ports;
using System.Linq;
using System.Net;
using System.Net.NetworkInformation;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace LIC_settings
{
    public partial class Main_window : Form
    {
        const byte WRITECOMMAND = 0xA5;
        const byte READCOMMAND = 0xA4;
        const byte WRITESENSOR = 0x15;
        const byte READSENSOR = 0x14;
        const byte WRITEPORTSETTINGS = 0x25;
        const byte READPORTSETTINGS = 0x24;
        const byte UPDATESETTINGS = 0xA6;
        const byte READALLCONFIG = 0x44;
        const byte WRITEALLCONFIG = 0x45;

        const byte CONFIG_BLOCK_SIZE = 32;
        const int MAX_SENSORS_RS = 32;

        enum Interfaces : Byte
        {
            RS1 = 11,
            RS2 = 12,
            RS3 = 13,
            AN1 = 21,
            AS2 = 22,
            CAN = 31,
        }

        enum Devices : Byte
        {
            MainBoard = 0x54,
            ZigbeeBoard = 0x34,
        }
#if NOBORDER
        private Point mouseOffset;
        private bool isMouseDown = false;
#endif

        List<string> sensors_names = new List<string>();
        List<Sensor> sensor_config = new List<Sensor>();

        // MODULE PARAMETERS
        Dictionary<string, byte> ParamID = new Dictionary<string, byte>()
        {
            {"Main_DateOfProduction", 0xB2 },
            {"Main_SerialNumber", 0xB3 },
            {"_Main_StandbyTime", 0xBA },
            {"_Main_WorkTime", 0xBB },
            {"Main_FirmwareVersion", 0xBC },
            {"Main_BuildNumber", 0xBD },
            {"Main_BootloaderVersion", 0xBF },
            {"Main_BuildTimestamp", 0xBE },

            {"ETH_IP", 0xB4 },
            {"ETH_Mask", 0xB5 },
            {"ETH_Gateway", 0xB6 },
            {"ETH_MAC", 0xB7 },
            {"ETH_DHCP", 0xB8 },
            {"ETH_ACTIVATE", 0xAA },

            {"MQTT_Broker", 0xB9 },
            {"MQTT_DNS", 0xB0 },
            {"MQTT_Port", 0xC0 },
            {"MQTT_TopicOut", 0xC1 },
            {"_MQTT_TopicIn", 0xC2 },
            {"MQTT_ID", 0xC3 },
            {"MQTT_User", 0xC4 },
            {"MQTT_Password", 0xC5 },
            {"MQTT_ACTIVATE", 0xA6 },

            {"LORA_Dev_EUI", 0xC8 },
            {"LORA_App_EUI", 0xC9 },
            {"LORA_App_Key", 0xCA },
            {"LORA_App_Port", 0xCB },
            {"LORA_DataRate", 0xCC },
            {"LORA_AUTO_DEV_EUI", 0xCE },
            {"LORA_MESSAGE_TYPE", 0xCF},
            {"LORA_ACTIVATE", 0xAF },

            {"_ZIGBEE_DevId", 0xD0 },
            {"_ZIGBEE_CONNECT", 0xD1},
            {"ZIGBEE_ACTIVATE", 0xA2 },
        };

        byte[] f_bytes, f_bytes_zb, EPD_configBytes;
        DateTime t_start;
        UInt32 CRC = 0, EPD_configCRC, pEPD_config;
        bool transmit_checked = false, serialPortDisable = false;
        UInt32 frm_version, frm_build, frm_timestamp, boot_version;
        bool frm_paramReceived = false;
        bool dev_mode = false;


        public Main_window()
        {
            InitializeComponent();
        }

        public static GraphicsPath RoundedRect(Rectangle bounds, int radius)
        {
            int diameter = radius * 2;
            Size size = new Size(diameter, diameter);
            Rectangle arc = new Rectangle(bounds.Location, size);
            GraphicsPath path = new GraphicsPath();

            if (radius == 0)
            {
                path.AddRectangle(bounds);
                return path;
            }

            // top left arc  
            path.AddArc(arc, 180, 90);

            // top right arc  
            arc.X = bounds.Right - diameter;
            path.AddArc(arc, 270, 90);

            // bottom right arc  
            arc.Y = bounds.Bottom - diameter;
            path.AddArc(arc, 0, 90);

            // bottom left arc 
            arc.X = bounds.Left;
            path.AddArc(arc, 90, 90);

            path.CloseFigure();
            return path;
        }

        private void Main_window_Load(object sender, EventArgs e)
        {
#if NOBORDER
                GraphicsPath myPath = RoundedRect(new Rectangle(25, 42, this.Width-50, this.Height-68), 50);
                this.Region = new Region(myPath); ;
#endif
            this.Location = new Point((Screen.PrimaryScreen.WorkingArea.Width - this.Width) / 2, (Screen.PrimaryScreen.WorkingArea.Height - this.Height) / 2);

            string json_str;
            // make tabs invisible
            tabControl1.Appearance = TabAppearance.FlatButtons;
            tabControl1.ItemSize = new Size(0, 1);
            tabControl1.SizeMode = TabSizeMode.Fixed;

            try
            {

                if (File.Exists("sensors.txt"))
                {
                    json_str = File.ReadAllText("sensors.txt");
                }
                else
                {
                    json_str = Properties.Resources.sensors;
                }
                sensor_config = JsonConvert.DeserializeObject<List<Sensor>>(json_str);
            }
            catch
            {
                MessageBox.Show("Ошибка в файле sensors.txt\nБудут загружены параметры датчиков по умолчанию");
                json_str = Properties.Resources.sensors;
                sensor_config = JsonConvert.DeserializeObject<List<Sensor>>(json_str);
            }
            // Заполняем варианты датчиков для таблиц
            sensors_names.AddRange(sensor_config.Select(p => p.Name));
            foreach (DataGridView _control in new List<DataGridView> { dg_rs1_sensors, dg_rs2_sensors, dg_rs3_sensors })
            {
                (_control.Columns[0] as DataGridViewComboBoxColumn).DataSource = sensors_names;
            }

            // init status images
            pb_loraStatus.Image = Properties.Resources.failure;
            pb_zigbeeStatus.Image = Properties.Resources.failure;
            pb_EthStatus.Image = Properties.Resources.failure;

            // init comboBoxes
            cb_rs1_baudrate.SelectedIndex = 2;
            cb_rs1_stopbits.SelectedIndex = 0;
            cb_rs1_parity.SelectedIndex = 0;
            cb_rs1_databits.SelectedIndex = 0;

            cb_rs2_baudrate.SelectedIndex = 2;
            cb_rs2_stopbits.SelectedIndex = 0;
            cb_rs2_parity.SelectedIndex = 0;
            cb_rs2_databits.SelectedIndex = 0;

            cb_rs3_baudrate.SelectedIndex = 2;
            cb_rs3_stopbits.SelectedIndex = 0;
            cb_rs3_parity.SelectedIndex = 0;
            cb_rs3_databits.SelectedIndex = 0;

            cb_loraMessageType.SelectedIndex = 0;
            cb_loraDatarate.SelectedIndex = 0;
        }

        private void bt_back1_Click(object sender, EventArgs e)
        {
            tabControl1.SelectTab(tab_main);
        }

        private Sensor findSensorByName(String _name)
        {
            return sensor_config.Find(p => p.Name == _name);
        }

        private void USB_serial_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            try
            {
                byte[] serialBuf = new byte[1024];
                if (USB_serial.BytesToRead < 1) return;
                USB_serial.Read(serialBuf, 0, 1);

                switch (serialBuf[0])
                {
                    case READALLCONFIG:
                        USB_serial.Read(serialBuf, 1, 1);
                        byte payloadLength = serialBuf[1];                                       // в 1-м байте длина дальнейшего пакета
                        USB_serial.Read(serialBuf, 2, payloadLength);
                        payloadLength -= 3;
                        UInt16 numOfBlock = BitConverter.ToUInt16(serialBuf, 2);                // 2-3 байты - номер пакета
                        if (numOfBlock == 0)                                    // В нулевом пакете длина конфига в байтах (uint16) и crc32
                        {
                            pEPD_config = 0;
                            EPD_configBytes = new byte[BitConverter.ToUInt16(serialBuf, 4)];    // 4-5 байты - длина всего конфига в байтах
                            EPD_configCRC = BitConverter.ToUInt32(serialBuf, 6);                // 6-9 байты - CRC32 конфига
                            log_rtb1(String.Format("Считываю конфигурацию ОУ: {0} байт, CRC32 = {1}", EPD_configBytes.Length, EPD_configCRC.ToString("X8")));
                        }
                        else // все остальные пакеты складываем в массив
                        {
                            if (EPD_configBytes != null)
                            {

                                if (EPD_configBytes.Length >= (pEPD_config + payloadLength))
                                {
                                    Array.Copy(serialBuf, 4, EPD_configBytes, pEPD_config, payloadLength);
                                    log_debug("Принят пакет " + numOfBlock.ToString() + " длины " + payloadLength.ToString());
                                    pEPD_config += payloadLength;
                                    log_debug("pEPD_config = " + pEPD_config.ToString());
                                }
                                if (EPD_configBytes.Length == pEPD_config)
                                {   // если это последний пакет, то записывам в файл
                                    pEPD_config = 0;
                                    log_debug("Принят последний пакет");
                                    UInt32 _crc = Crc32Algorithm.Compute(EPD_configBytes, 0, EPD_configBytes.Length - 4);
                                    if (_crc == EPD_configCRC)
                                    {   // проверяем CRC массива и принятую в 0 пакете
                                        using (var dialog = new SaveFileDialog())
                                        {
                                            dialog.Filter = "Config files|*.cfb";
                                            if (dialog.ShowDialog(this) == DialogResult.OK)
                                            {
                                                File.WriteAllBytes(dialog.FileName, EPD_configBytes);
                                                log_rtb1("Конфигурация записана в файл " + dialog.FileName +
                                                    " CRC = " + _crc.ToString("X8"));
                                            }
                                        }
                                    }
                                    else
                                    {
                                        MessageBox.Show("Неверная контрольная сумма полученного файла");
                                        log_rtb1("Ошибка записи конфигурации в файл: непраильная контрольная сумма");
                                        log_debug("CRC = " + _crc.ToString("X8"));
                                    }
                                }
                            }
                        }
                        break;
                    case READSENSOR:
                        try
                        {
                            USB_serial.Read(serialBuf, 1, 23);
                            DataGridView tmp = new DataGridView();
                            switch (serialBuf[1])
                            {
                                case (byte)Interfaces.RS1:
                                    tmp = dg_rs1_sensors;
                                    break;
                                case (byte)Interfaces.RS2:
                                    tmp = dg_rs2_sensors;
                                    break;
                                case (byte)Interfaces.RS3:
                                    tmp = dg_rs3_sensors;
                                    break;
                            }
                            byte[] arr_name = new byte[16];
                            Array.Copy(serialBuf, 3, arr_name, 0, 16);
                            string sens_name = Encoding.ASCII.GetString(arr_name).Trim('\0');
                            if (!sensors_names.Contains(sens_name))
                            {
                                MessageBox.Show("Получено имя датчика " + sens_name +
                                                "\nТакой датчик не предусмотрен данной версией программы, поэтому будет проигнорирован");
                                return;
                            }
                            tmp.Invoke((MethodInvoker)delegate
                            {
                                if (serialBuf[2] == 0) tmp.Rows.Clear();      // Очищаем табличку, когда приходит первый датчик
                                tmp.Rows.Add(sens_name,                                         // Название
                                            BitConverter.ToUInt16(serialBuf, 21).ToString(),    // Период опроса
                                            serialBuf[23].ToString(),                           // Адрес Modbus
                                            BitConverter.ToUInt16(serialBuf, 19).ToString()     // ID
                                            );
                                tmp.Refresh();
                            });
                        }
                        catch (Exception ex)
                        {
                            MessageBox.Show(ex.ToString());
                        }
                        break;

                    case READPORTSETTINGS:
                        USB_serial.Read(serialBuf, 1, 11);
                        tabControl1.Invoke((MethodInvoker)delegate
                        {
                            ComboBox _baudrate, _databits, _parity, _stopbits;
                            CheckBox _state;
                            NumericUpDown _errors, _delay;
                            switch (serialBuf[1])
                            {
                                case (byte)Interfaces.RS1:
                                    _baudrate = cb_rs1_baudrate;
                                    _databits = cb_rs1_databits;
                                    _parity = cb_rs1_parity;
                                    _stopbits = cb_rs1_stopbits;
                                    _state = chb_rs1_activate;
                                    _errors = num_rs1Errors;
                                    _delay = num_rs1Delay;
                                    break;
                                case (byte)Interfaces.RS2:
                                    _baudrate = cb_rs2_baudrate;
                                    _databits = cb_rs2_databits;
                                    _parity = cb_rs2_parity;
                                    _stopbits = cb_rs2_stopbits;
                                    _state = chb_rs2_activate;
                                    _errors = num_rs2Errors;
                                    _delay = num_rs2Delay;
                                    break;
                                case (byte)Interfaces.RS3:
                                    _baudrate = cb_rs3_baudrate;
                                    _databits = cb_rs3_databits;
                                    _parity = cb_rs3_parity;
                                    _stopbits = cb_rs3_stopbits;
                                    _state = chb_rs3_activate;
                                    _errors = num_rs3Errors;
                                    _delay = num_rs3Delay;
                                    break;
                                default:
                                    return;
                            }
                            _state.Checked = (serialBuf[9] == 1);
                            _stopbits.SelectedIndex = serialBuf[8];
                            _parity.SelectedIndex = serialBuf[7];
                            _databits.SelectedIndex = serialBuf[6];
                            _baudrate.SelectedItem = BitConverter.ToUInt32(serialBuf, 2).ToString();
                            _delay.Value = serialBuf[10];
                            _errors.Value = serialBuf[11];
                        });
                        break;
                    case READCOMMAND:
                        int len = USB_serial.ReadByte();
                        USB_serial.Read(serialBuf, 1, len);
                        tabControl1.Invoke((MethodInvoker)delegate
                        {
                            readParamHandler(serialBuf, len);
                        });
                        if (frm_paramReceived)
                        {
                            byte[] frm_vers_bytes = BitConverter.GetBytes(frm_version);
                            byte[] bt_vers = BitConverter.GetBytes(boot_version);
                            DateTime dateTime = new DateTime(1970, 1, 1, 0, 0, 0, 0, DateTimeKind.Utc);
                            dateTime = dateTime.AddSeconds(frm_timestamp).ToLocalTime();
                            string _str = "v" + string.Join(".", frm_vers_bytes[2], frm_vers_bytes[1], frm_vers_bytes[0]) +
                                                    " b" + frm_build.ToString() +
                                                    dateTime.ToString(" - HH:mm dd/MM/yy") + " bootloader: v" +
                                                    string.Join(".", bt_vers[0], bt_vers[1], bt_vers[2]);
                            log_rtb1("Версия ПО, считанная по USB: " + _str, Color.Blue);
                            frm_paramReceived = false;
                        }
                        break;
                    case WRITECOMMAND:
                        if (USB_serial.ReadByte() == 0x5A)
                        {
                            transmit_checked = true;
                        }
                        break;
                    case 0x65:      // CRC main programm
                    case 0x66:      // CRC zigbee programm
                        USB_serial.Read(serialBuf, 1, 4);
                        UInt32 CRC_input = BitConverter.ToUInt32(serialBuf, 1);
                        log_rtb1("CRC32 полученная: " + CRC_input.ToString("X"));
                        if (CRC_input == CRC)
                        {
                            log_rtb1("Успешно (" + (DateTime.Now - t_start).TotalSeconds.ToString("F1") + " с)", Color.DarkGreen);
                            // Отключаем COM-порт, чтобы ОУ адекватно перезагрузилось
                            if (serialBuf[0] == 0x65) serialPortDisable = true;
                        }
                        else log_rtb1("Контрольные суммы не сошлись \\_(ツ)_/¯", Color.Red);
                        break;
                    default:
                        USB_serial.ReadExisting();
                        break;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }

        private void readParamHandler(byte[] serialBuf, int len)
        {
            byte[] param_data = new byte[len];
            byte[] tmp;
            Array.Copy(serialBuf, 1, param_data, 0, len);
            switch (param_data[0])
            {
                case 0xAA:      // ETH ACTIVATE FLAG
                    chb_ETH_Activate.Checked = (param_data[1] == 1);
                    pb_EthStatus.Image = (param_data[1] == 1) ? Properties.Resources.successuploaded : Properties.Resources.failure;
                    break;
                case 0xB2:      // Date of production
                    DateTime tmp_dt = new DateTime(param_data[3] + 2000, param_data[2], param_data[1]);
                    dt_DateOfProduction.Value = tmp_dt;
                    break;
                case 0xB3:      // Serial number
                    tmp = new byte[8];
                    Array.Copy(param_data, 1, tmp, 0, tmp.Length);
                    tb_ModuleSerialNumber.Text = BitConverter.ToUInt64(tmp, 0).ToString();
                    break;
                case 0xB4:      // Module IP
                    tmp = new byte[4];
                    Array.Copy(param_data, 1, tmp, 0, tmp.Length);
                    tb_IP.Text = new IPAddress(tmp).ToString();
                    break;
                case 0xB5:      // Module mask
                    tmp = new byte[4];
                    Array.Copy(param_data, 1, tmp, 0, tmp.Length);
                    tb_Mask.Text = new IPAddress(tmp).ToString();
                    break;
                case 0xB6:      // IP Gateway
                    tmp = new byte[4];
                    Array.Copy(param_data, 1, tmp, 0, tmp.Length);
                    tb_Gateway.Text = new IPAddress(tmp).ToString();
                    break;
                case 0xB7:      // IP Gateway
                    tmp = new byte[6];
                    Array.Copy(param_data, 1, tmp, 0, tmp.Length);
                    tb_MAC.Text = new PhysicalAddress(tmp).ToString();
                    break;
                case 0xB8:      // DHCP flag
                    chb_DHCP.Checked = (param_data[1] == 1);
                    break;
                case 0xB9:      // MQTT Broker IP
                    tmp = new byte[4];
                    Array.Copy(param_data, 1, tmp, 0, tmp.Length);
                    tb_BrokerIP.Text = new IPAddress(tmp).ToString();
                    break;
                case 0xBA:      // Stanby Time
                    tmp = new byte[len - 1];
                    Array.Copy(param_data, 1, tmp, 0, tmp.Length);
                    tb_stanbyTime.Text = BitConverter.ToUInt32(tmp, 0).ToString();
                    break;
                case 0xBB:      // Work Time
                    tmp = new byte[len - 1];
                    Array.Copy(param_data, 1, tmp, 0, tmp.Length);
                    tb_workTime.Text = BitConverter.ToUInt32(tmp, 0).ToString();
                    break;
                case 0xBC:      // Версия прошивки мк
                    tmp = new byte[len - 1];
                    Array.Copy(param_data, 1, tmp, 0, tmp.Length);
                    frm_version = BitConverter.ToUInt32(tmp, 0);
                    break;
                case 0xBD:      // Номер сборки прошивки мк
                    tmp = new byte[len - 1];
                    Array.Copy(param_data, 1, tmp, 0, tmp.Length);
                    frm_build = BitConverter.ToUInt32(tmp, 0);
                    break;
                case 0xBE:      // timestamp прошивки мк
                    tmp = new byte[len - 1];
                    Array.Copy(param_data, 1, tmp, 0, tmp.Length);
                    frm_timestamp = BitConverter.ToUInt32(tmp, 0);
                    frm_paramReceived = true;
                    break;
                case 0xBF:      // Версия прошивки загрузчика
                    tmp = new byte[len - 1];
                    Array.Copy(param_data, 1, tmp, 0, tmp.Length);
                    boot_version = BitConverter.ToUInt32(tmp, 0);
                    break;

                case 0xC0:      // MQTT Broker port
                    tmp = new byte[2];
                    Array.Copy(param_data, 1, tmp, 0, tmp.Length);
                    tb_BrokerPort.Text = BitConverter.ToUInt16(tmp, 0).ToString();
                    break;
                case 0xC1:      // MQTT topic output
                    tmp = new byte[len - 1];
                    Array.Copy(param_data, 1, tmp, 0, tmp.Length);
                    tb_MQQTTopicOutput.Text = System.Text.ASCIIEncoding.ASCII.GetString(tmp);
                    break;
                case 0xC3:      // MQTT ID
                    tmp = new byte[len - 1];
                    Array.Copy(param_data, 1, tmp, 0, tmp.Length);
                    tb_MQTT_ID.Text = System.Text.ASCIIEncoding.ASCII.GetString(tmp);
                    break;
                case 0xC4:      // MQTT User
                    tmp = new byte[len - 1];
                    Array.Copy(param_data, 1, tmp, 0, tmp.Length);
                    tb_MQTT_User.Text = System.Text.ASCIIEncoding.ASCII.GetString(tmp);
                    break;
                case 0xC5:      // MQTT password
                    tmp = new byte[len - 1];
                    Array.Copy(param_data, 1, tmp, 0, tmp.Length);
                    tb_MQTT_Password.Text = System.Text.ASCIIEncoding.ASCII.GetString(tmp);
                    break;
                case 0xA6:      // MQTT activate flag
                    chb_MQTT_Activate.Checked = (param_data[1] == 1);
                    break;

                // LoRa params:                
                case 0xC8:      // LoRa device EUI
                    tmp = new byte[len - 1];
                    Array.Copy(param_data, 1, tmp, 0, tmp.Length);
                    Array.Reverse(tmp);
                    UInt64 a = BitConverter.ToUInt64(tmp, 0);
                    tb_LORA_DevEUI.Text = a.ToString("X16");
                    if (a == 0) MessageBox.Show("Модуль LoRa не подключен");                    
                    break;
                case 0xC9:      // LoRa app EUI
                    tmp = new byte[len - 1];
                    Array.Copy(param_data, 1, tmp, 0, tmp.Length);
                    Array.Reverse(tmp);
                    tb_LORA_AppEUI.Text = BitConverter.ToUInt64(tmp, 0).ToString("X");
                    break;
                case 0xCA:      // LoRa app key
                    tmp = new byte[len - 1];
                    Array.Copy(param_data, 1, tmp, 0, tmp.Length);
                    byte[] prt1b = new byte[8];
                    byte[] prt2b = new byte[8];
                    Array.Copy(param_data, 1, prt1b, 0, 8);
                    Array.Copy(param_data, 9, prt2b, 0, 8);
                    Array.Reverse(prt1b);
                    Array.Reverse(prt2b);
                    UInt64 prt1 = BitConverter.ToUInt64(prt1b, 0);
                    UInt64 prt2 = BitConverter.ToUInt64(prt2b, 0);
                    tb_LORA_AppKey.Text = prt1.ToString("X16") + prt2.ToString("X16");
                    break;
                case 0xCB:      // LoRa app port
                    tmp = new byte[len - 1];
                    Array.Copy(param_data, 1, tmp, 0, tmp.Length);
                    tb_LORA_AppPort.Text = BitConverter.ToUInt16(tmp, 0).ToString();
                    break;
                case 0xCC:      // LoRa datarate                    
                    cb_loraDatarate.SelectedIndex = param_data[1] & 0x0F;
                    chb_LORA_ADR.Checked = ((param_data[1] >> 7) == 1);
                    break;
                case 0xCE:      // LoRa auto device eui flag
                    chb_AutoDevEUI.Checked = (param_data[1] == 1);
                    break;
                case 0xCF:      // LoRa message type
                    cb_loraMessageType.SelectedIndex = param_data[1];
                    break;
                case 0xAF:      // LoRa activate flag
                    chb_LoRa_activate.Checked = (param_data[1] == 1);
                    pb_loraStatus.Image = (param_data[1] == 1) ? Properties.Resources.successuploaded : Properties.Resources.failure;
                    break;


                // ZigBee params:

                //case 0xD0:
                //    tmp = new byte[len - 1];
                //    Array.Copy(param_data, 1, tmp, 0, tmp.Length);
                //    tb_ZIGBEE_DevID.Text = BitConverter.ToUInt64(tmp, 0).ToString("X");
                //    break;

                case 0xA2:
                    chb_ZigBee_Activate.Checked = (param_data[1] == 1);
                    pb_zigbeeStatus.Image = (param_data[1] == 1) ? Properties.Resources.successuploaded : Properties.Resources.failure;
                    break;
            }
        }

        private void bt_firmOpen_Click(object sender, EventArgs e)
        {
            progress_firmLoad.Value = progress_firmLoad.Minimum;
            using (var dialog = new OpenFileDialog())
            {
                dialog.Filter = "bin files (*.bin)|*.bin";
                if (dialog.ShowDialog(this) == DialogResult.OK)
                {
                    f_bytes = File.ReadAllBytes(dialog.FileName);
                    // check file
                    if (f_bytes[3] == 0x20)
                    {
                        // Print version
                        byte[] f_vers = new byte[4], f_build = new byte[4], f_timestamp = new byte[4];
                        Array.Copy(f_bytes, 0x188, f_vers, 0, 4);
                        Array.Copy(f_bytes, 0x18C, f_build, 0, 4);
                        Array.Copy(f_bytes, 0x190, f_timestamp, 0, 4);
                        DateTime dateTime = new DateTime(1970, 1, 1, 0, 0, 0, 0, DateTimeKind.Utc);
                        dateTime = dateTime.AddSeconds(BitConverter.ToUInt32(f_timestamp, 0)).ToLocalTime();
                        string _str = "v" + string.Join(".", f_vers[2], f_vers[1], f_vers[0]) +
                                                            " (build " + BitConverter.ToUInt32(f_build, 0).ToString() +
                                                            dateTime.ToString(" -- HH:mm dd/MM/yyyy)");
                        log_rtb1("Версия открытого файла: " + _str, Color.Blue);
                    }
                    else
                    {
                        f_bytes = new byte[1];
                        MessageBox.Show("Выбранный файл не поддерживается");
                    }
                }
            }
        }

        private async void SendFrmUsb(object i_obj)
        {   //byte[] file, byte deviceSelection, ProgressBar progressBar
            Frm obj = (Frm)i_obj;
            if (USB_serial.IsOpen)
            {
                if (await sendFirmware(obj))
                {
                    obj.progressBar.Value = obj.progressBar.Maximum;
                    MessageBox.Show("Успешный успех", "Успех");
                }
                else
                {
                    MessageBox.Show("Ошибка при передаче прошивки", "Error");
                    obj.progressBar.Value = obj.progressBar.Minimum;
                }
            }
            else
            {
                MessageBox.Show("Устройство не подключено", "Error");
            }
        }

        private void bt_sendFrm_Click(object sender, EventArgs e)
        {
            if (f_bytes != null && f_bytes.Length > 100)
            {
                Frm frm = new Frm(f_bytes, (byte)Devices.MainBoard, progress_firmLoad);
                Thread sendFrm = new Thread(new ParameterizedThreadStart(SendFrmUsb));
                sendFrm.Start(frm);
            }
            else
            {
                MessageBox.Show("Сначала выберите файл");
            }
        }

        private async Task<bool> sendFirmware(Frm obj)
        {   //byte[] file, byte deviceSelection, ProgressBar progressBar
            byte[] data = obj.file;
            try
            {
                byte[] sendBuff = new byte[64];
                ushort numOfPacket = 0;
                t_start = DateTime.Now;

                // Первая посылка с параметрами прошивки
                #region
                log_rtb1("Очистка памяти");
                // Команда
                sendBuff[0] = obj.device;
                // Длина текущего сообщения
                Array.Copy(UInt16ToByteArray(14), 0, sendBuff, 1, 2);

                // Длина прошивки в байтах
                Array.Copy(UInt32ToByteArray((UInt32)data.Length), 0, sendBuff, 3, 4);

                // Длина прошивки в страницах
                Array.Copy(UInt32ToByteArray((UInt32)Math.Ceiling((double)data.Length / 256.0)), 0, sendBuff, 7, 4);
                obj.progressBar.Invoke((MethodInvoker)delegate
                {
                    obj.progressBar.Value = 0;
                    obj.progressBar.Maximum = (int)Math.Ceiling((double)data.Length / 32.0);
                });

                // CRC32 всей прошивки
                CRC = Crc32Algorithm.Compute(data, 0, data.Length);
                Array.Copy(UInt32ToByteArray(CRC), 0, sendBuff, 11, 4);

                // Отправляем и ждем подтверждения
                if (!(await sendWithTimeout(USB_serial, sendBuff, 0, 15, 5000)))
                {
                    log_rtb1("Ошибка при передаче прошивки (таймаут)", Color.Red);
                    return false;
                }
                if ((DateTime.Now - t_start).TotalSeconds < 1.0)
                {
                    log_rtb1("Ошибка при очистке памяти", Color.Red);
                    return false;
                }
                log_rtb1("Успешно (" + (DateTime.Now - t_start).TotalSeconds.ToString("F1") + " с)", Color.DarkGreen);
                #endregion

                // Отправляем пачками саму прошивку
                #region
                // Команда
                sendBuff[0] = (byte)(obj.device + 1);
                if (obj.device == (byte)Devices.MainBoard) log_rtb1("Передача прошивки");
                else if (obj.device == (byte)Devices.ZigbeeBoard) log_rtb1("Передача прошивки ZigBee");
                t_start = DateTime.Now;
                // В пачке 32 байт
                for (int i = 0; i < data.Length; i += 32)
                {
                    // Длина текущего сообщения
                    int len = (data.Length - i) > 32 ? 32 : (data.Length - i);
                    Array.Copy(UInt16ToByteArray(2 + len), 0, sendBuff, 1, 2);

                    // Номер пакета
                    Array.Copy(UInt16ToByteArray(numOfPacket++), 0, sendBuff, 3, 2);

                    // Сами байтики
                    Array.Copy(data, i, sendBuff, 5, len);

                    // Отправляем и ждем подтверждения
                    if (!(await sendWithTimeout(USB_serial, sendBuff, 0, len + 5, 500)))
                    {
                        log_rtb1("Ошибка при передаче прошивки (таймаут)", Color.Red);
                        return false;
                    }
                    obj.progressBar.Invoke((MethodInvoker)delegate
                    {
                        obj.progressBar.PerformStep();
                    });
                }
                log_rtb1("Успешно (" + (DateTime.Now - t_start).TotalSeconds.ToString("F1") + " с)", Color.DarkGreen);
                #endregion
                // Запрос на проверку CRC записанной прошивки
                sendBuff[0] = (byte)(obj.device + 2);
                log_rtb1("Верификация прошивки");
                t_start = DateTime.Now;
                USB_serial.Write(sendBuff, 0, 1);
                log_rtb1("CRC32 переданной прошивки: " + CRC.ToString("X"));
                // Дальше принимаем в serialPort1.Data_Received (первый байт 0x65)

                return true;
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Ошибка при прошивке\n");
                return false;
            }
        }

        private byte[] UInt16ToByteArray(int a)
        {
            return UInt16ToByteArray((ushort)a);
        }
        private byte[] UInt16ToByteArray(UInt16 a)
        {
            return BitConverter.GetBytes(a);
        }

        private byte[] UInt32ToByteArray(UInt32 a)
        {
            return BitConverter.GetBytes(a);
        }
        private async Task<bool> sendWithTimeout(SerialPort serial, byte[] data, int offset, int len, int timeout_ms)
        {
            // Выставляем флаг подтверждения в false
            transmit_checked = false;
            // Отправляем посылку
            serial.Write(data, offset, len);
            // Узнаем текущее время и если подтверждение не успеет за указанное время, то вернем false
            DateTime time = DateTime.Now;
            while (!transmit_checked)
            {
                await Task.Delay(1);
                if ((DateTime.Now - time).TotalMilliseconds > timeout_ms) return false;
            }
            // ну а если подтверждение пришло вовремя, то вернем true
            return true;

        }

        private void bt_connect_Click(object sender, EventArgs e)
        {
            if (bt_connect.Tag.ToString() == "Connect") //Подключить
            {
                usb_connect();
            }
            else if (bt_connect.Tag.ToString() == "Disconnect") //Отключить
            {
                usb_disconnect();
            }
        }

        private void usb_disconnect()
        {
            if (USB_serial.IsOpen)
            {
                cb_portName.Enabled = true;
                bt_connect.Image = Properties.Resources.bt_connect;
                bt_connect.Tag = "Connect";
                try
                {
                    // init status images
                    pb_loraStatus.Image = Properties.Resources.failure;
                    pb_zigbeeStatus.Image = Properties.Resources.failure;
                    pb_EthStatus.Image = Properties.Resources.failure;

                    USB_serial.Close();
                    log_rtb1("Отключение от " + USB_serial.PortName);
                }
                catch
                {
                    // Игнорируем ошибку при отключении от несуществующего порта  
                }
            }
        }

        private void usb_connect()
        {
            if (cb_portName.Items.Count < 1) return;
            usb_connect(cb_portName.Text);
        }

        private bool usb_connect(string portname)
        {
            USB_serial.PortName = portname;
            try
            {
                USB_serial.Open();
                cb_portName.Enabled = false;
                bt_connect.Image = Properties.Resources.bt_disconnect;
                bt_connect.Tag = "Disconnect";
                log_rtb1("Подключение к " + USB_serial.PortName);
                USB_serial.DiscardInBuffer();
                transmit_checked = false;
                USB_serial.Write(new byte[] { 0xEE }, 0, 1);      // при подключении к ОУ переводим его в сервисный режим (прерываем циклы передачи данных)
                Thread.Sleep(50);
                if (transmit_checked)
                {
                    usb_reqModules();
                    return true;
                }
                log_rtb1("Устройсво " + USB_serial.PortName + " не отвечает.");
                return false;
            }
            catch { return false; }
        }

        private void usb_reqModules()
        {
            byte[] sendBuf = new byte[2] { READCOMMAND, 0 };
            sendBuf[1] = ParamID["ETH_ACTIVATE"];
            USB_serial.Write(sendBuf, 0, sendBuf.Length);
            Thread.Sleep(30);

            sendBuf[1] = ParamID["LORA_ACTIVATE"];
            USB_serial.Write(sendBuf, 0, sendBuf.Length);
            Thread.Sleep(30);

            sendBuf[1] = ParamID["ZIGBEE_ACTIVATE"];
            USB_serial.Write(sendBuf, 0, sendBuf.Length);
        }

        private void serialPortControl_Tick(object sender, EventArgs e)
        {
            verify_usb_connection();
            if (USB_serial.IsOpen)
            {
                image_status.Image = Properties.Resources.successuploaded;
                // Таймер для отключения serialPort после передачи прошивки в ОУ
                if (serialPortDisable)
                {
                    // Отправляем команду на перезагрузку ОУ
                    USB_serial.Write(new byte[] { 0x7A }, 0, 1);
                    serialPortDisable = false;
                    usb_disconnect();
                    log_rtb1("COM-порт отключен для перезагрузки ОУ.");
                }
            }
            else
            {
                image_status.Image = Properties.Resources.failure;
            }
            string[] sensors_strings = new string[3] { "датчик", "датчика", "датчиков" };
            lb_rs1_sensorsCount.Text = (dg_rs1_sensors.RowCount - 1).ToString() + " " + getNoun(dg_rs1_sensors.RowCount - 1, sensors_strings);
            lb_rs2_sensorsCount.Text = (dg_rs2_sensors.RowCount - 1).ToString() + " " + getNoun(dg_rs2_sensors.RowCount - 1, sensors_strings);
            lb_rs3_sensorsCount.Text = (dg_rs3_sensors.RowCount - 1).ToString() + " " + getNoun(dg_rs3_sensors.RowCount - 1, sensors_strings);
        }

        private string getNoun(int number, string[] Nouns)
        {
            int a = Math.Abs(number);
            a %= 100;
            if (a >= 5 && a <= 20) return Nouns[2];
            a %= 10;
            if (a == 1) return Nouns[0];
            else if (a >= 2 && a <= 4) return Nouns[1];
            return Nouns[2];
        }

        private void verify_usb_connection()
        {
            try
            {
                if (USB_serial.IsOpen)
                {
                    USB_serial.Write("?");
                }
            }
            catch
            {
                usb_disconnect();
            }
        }

        private void panel_eth_Click(object sender, EventArgs e)
        {
            tabControl1.SelectTab(tab_eth);
        }

        private void bt_refreshPort_Click(object sender, EventArgs e)
        {
            refresh_usb();
        }

        private void refresh_usb()
        {
            string[] portnames = SerialPort.GetPortNames();
            cb_portName.Items.Clear();
            cb_portName.Items.AddRange(portnames);
            cb_portName.SelectedIndex = portnames.Length - 1;
        }

        private void panel_lora_Click(object sender, EventArgs e)
        {
            tabControl1.SelectTab(tab_lora);
        }

        private void bt_LoRa_read_Click(object sender, EventArgs e)
        {
            byte[] sendBuf = new byte[2] { READCOMMAND, 0 };
            if (USB_serial.IsOpen)
            {
                // Очистка старых значений в полях
                Control[] controls = new Control[] { tb_LORA_DevEUI , tb_LORA_AppEUI , tb_LORA_AppKey , tb_LORA_AppPort , chb_AutoDevEUI ,
                                                    cb_loraDatarate, chb_LORA_ADR, chb_LoRa_activate, cb_loraMessageType};
                ClearControls(controls);
                // Запросы на считывание
                foreach (KeyValuePair<string, byte> param in ParamID.Where(p => p.Key.StartsWith("LORA")))
                {
                    sendBuf[1] = param.Value;
                    USB_serial.Write(sendBuf, 0, sendBuf.Length);
                    Thread.Sleep(50);
                }
            }
            else
            {
                MessageBox.Show("Устройство не подключено", "ERROR");
            }
        }

        private async void bt_LoRa_send_Click(object sender, EventArgs e)
        {
            byte[] sendMessage;
            if (USB_serial.IsOpen)
            {
                USB_serial.DiscardInBuffer();
                // LORA UID
                //{
                //    string tmp_text = tb_LORA_UID.Text.Replace("-", "");
                //    byte[] tmp = BitConverter.GetBytes(UInt64.Parse(tmp_text.ToUpper().Substring(tmp_text.Length < 16 ? 0 : tmp_text.Length - 16), System.Globalization.NumberStyles.AllowHexSpecifier));
                //    sendMessage = new byte[tmp.Length + 1];
                //    sendMessage[0] = ParamID["LORA_UID"];
                //    Array.Copy(tmp, 0, sendMessage, 1, tmp.Length);
                //    sendData(sendMessage);
                //}

                // LORA Device EUI
                #region
                string tmp_text = tb_LORA_DevEUI.Text.Replace("-", "");
                byte[] tmp = BitConverter.GetBytes(UInt64.Parse(tmp_text.ToUpper().Substring(tmp_text.Length < 16 ? 0 : tmp_text.Length - 16), System.Globalization.NumberStyles.AllowHexSpecifier));
                sendMessage = new byte[tmp.Length + 1];
                sendMessage[0] = ParamID["LORA_Dev_EUI"];
                Array.Reverse(tmp);
                Array.Copy(tmp, 0, sendMessage, 1, tmp.Length);
                if (!await sendData(sendMessage)) return;
                #endregion

                // LORA Application EUI
                #region
                tmp_text = tb_LORA_AppEUI.Text.Replace("-", "");
                tmp = BitConverter.GetBytes(UInt64.Parse(tmp_text.ToUpper().Substring(tmp_text.Length < 16 ? 0 : tmp_text.Length - 16), System.Globalization.NumberStyles.AllowHexSpecifier));
                sendMessage = new byte[tmp.Length + 1];
                sendMessage[0] = ParamID["LORA_App_EUI"];
                Array.Reverse(tmp);
                Array.Copy(tmp, 0, sendMessage, 1, tmp.Length);
                if (!await sendData(sendMessage)) return;
                #endregion

                // LORA Application Key
                #region
                String prt1, prt2, raw;
                raw = tb_LORA_AppKey.Text.Replace("-", "");
                prt1 = raw.ToUpper().Substring(0, 16);
                prt2 = raw.ToUpper().Substring(16, 16);
                byte[] tmp1 = BitConverter.GetBytes(UInt64.Parse(prt1, System.Globalization.NumberStyles.AllowHexSpecifier));
                byte[] tmp2 = BitConverter.GetBytes(UInt64.Parse(prt2, System.Globalization.NumberStyles.AllowHexSpecifier));
                sendMessage = new byte[tmp1.Length + tmp2.Length + 1];
                sendMessage[0] = ParamID["LORA_App_Key"];
                Array.Reverse(tmp1);
                Array.Reverse(tmp2);
                Array.Copy(tmp1, 0, sendMessage, 1, tmp1.Length);
                Array.Copy(tmp2, 0, sendMessage, 1 + tmp1.Length, tmp2.Length);
                if (!await sendData(sendMessage)) return;
                #endregion

                // LORA Application Port
                #region
                tmp = BitConverter.GetBytes(UInt16.Parse(tb_LORA_AppPort.Text));
                sendMessage = new byte[tmp.Length + 1];
                sendMessage[0] = ParamID["LORA_App_Port"];
                Array.Copy(tmp, 0, sendMessage, 1, tmp.Length);
                if (!await sendData(sendMessage)) return;
                #endregion

                // LORA Datarate
                #region
                sendMessage = new byte[2];
                sendMessage[0] = ParamID["LORA_DataRate"];
                sendMessage[1] = (byte)(cb_loraDatarate.SelectedIndex | (Convert.ToByte(chb_LORA_ADR.Checked) << 7));
                if (!await sendData(sendMessage)) return;
                #endregion

                // LORA AUTO DEVICE EUI
                #region
                sendMessage = new byte[2];
                sendMessage[0] = ParamID["LORA_AUTO_DEV_EUI"];
                sendMessage[1] = chb_AutoDevEUI.Checked ? (byte)1 : (byte)0;
                if (!await sendData(sendMessage)) return;
                #endregion
                // LORA MESSAGE TYPE
                #region
                sendMessage = new byte[2];
                sendMessage[0] = ParamID["LORA_MESSAGE_TYPE"];
                sendMessage[1] = (Byte)cb_loraMessageType.SelectedIndex;
                if (!await sendData(sendMessage)) return;
                #endregion
                // LORA ACTIVATE FLAG
                #region
                sendMessage = new byte[2];
                sendMessage[0] = ParamID["LORA_ACTIVATE"];
                sendMessage[1] = chb_LoRa_activate.Checked ? (byte)1 : (byte)0;
                if (!await sendData(sendMessage)) return;
                #endregion
                log_rtb1("Отправлены настройки LoRa");
                await sendCommandUpdateSettings(0xA7);
            }
            else
            {
                MessageBox.Show("Устройство не подключено", "ERROR");
            }
        }

        private void image_status_Click(object sender, EventArgs e)
        {
            tabControl1.SelectTab("tab_frm");
        }

        private void panel_RS1_Click(object sender, EventArgs e)
        {
            tabControl1.SelectTab("tab_rs1");
        }

        private void gb_rs1_VisibleChanged(object sender, EventArgs e)
        {
            cb_rs1_baudrate.SelectedIndex = 2;
            cb_rs1_databits.SelectedIndex = 0;
            cb_rs1_parity.SelectedIndex = 0;
            cb_rs1_stopbits.SelectedIndex = 0;
        }

        private async void bt_writeMainParams_Click(object sender, EventArgs e)
        {
            byte[] sendMessage;
            try
            {
                if (USB_serial.IsOpen)
                {
                    USB_serial.DiscardInBuffer();

                    // Date of production
                    #region
                    sendMessage = new byte[4];
                    sendMessage[0] = ParamID["Main_DateOfProduction"];
                    sendMessage[1] = (byte)dt_DateOfProduction.Value.Day;
                    sendMessage[2] = (byte)dt_DateOfProduction.Value.Month;
                    sendMessage[3] = (byte)(dt_DateOfProduction.Value.Year - 2000);
                    if (!await sendData(sendMessage)) return;
                    #endregion

                    // Module Serial Number
                    #region
                    byte[] temp_ser_bytes = BitConverter.GetBytes(UInt64.Parse(tb_ModuleSerialNumber.Text));
                    sendMessage = new byte[temp_ser_bytes.Length + 1];
                    sendMessage[0] = ParamID["Main_SerialNumber"];
                    Array.Copy(temp_ser_bytes, 0, sendMessage, 1, temp_ser_bytes.Length);
                    if (!await sendData(sendMessage)) return;
                    #endregion

                    //// Standby Time
                    //{
                    //    byte[] temp_ser_bytes = BitConverter.GetBytes(UInt32.Parse(tb_stanbyTime.Text));
                    //    sendMessage = new byte[temp_ser_bytes.Length + 1];
                    //    sendMessage[0] = ParamID["Main_StandbyTime"];
                    //    Array.Copy(temp_ser_bytes, 0, sendMessage, 1, temp_ser_bytes.Length);
                    //    if (!sendData(sendMessage)) return;
                    //}

                    //// Work Time
                    //{
                    //    byte[] temp_ser_bytes = BitConverter.GetBytes(UInt32.Parse(tb_workTime.Text));
                    //    sendMessage = new byte[temp_ser_bytes.Length + 1];
                    //    sendMessage[0] = ParamID["Main_WorkTime"];
                    //    Array.Copy(temp_ser_bytes, 0, sendMessage, 1, temp_ser_bytes.Length);
                    //    if (!sendData(sendMessage)) return;
                    //}
                    log_rtb1("Отправлены настройки основных параметров");
                    await sendCommandUpdateSettings();
                }
                else
                {
                    MessageBox.Show("Устройство не подключено", "Ошибка!");
                }
            }
            catch
            {
                MessageBox.Show("Значения полей имеют неверный формат", "Ошибка!");
            }
        }

        private void bt_readMainParams_Click(object sender, EventArgs e)
        {

            byte[] sendBuf = new byte[2] { READCOMMAND, 0 };
            if (USB_serial.IsOpen)
            {
                // Очистка старых значений в полях
                Control[] controls = new Control[] { tb_ModuleSerialNumber, tb_stanbyTime, tb_workTime };
                ClearControls(controls);
                // Отправка запросов
                foreach (KeyValuePair<string, byte> param in ParamID.Where(p => p.Key.StartsWith("Main")))
                {
                    sendBuf[1] = param.Value;
                    USB_serial.Write(sendBuf, 0, sendBuf.Length);
                    Thread.Sleep(50);
                }
            }
            else
            {
                MessageBox.Show("Устройство не подключено", "ERROR");
            }
        }

        private void dg_rs1_sensors_CellValidating(object sender, DataGridViewCellValidatingEventArgs e)
        {
            var view = (DataGridView)sender;
            if (e.RowIndex == (view.RowCount - 1)) return;
            switch (e.ColumnIndex)
            {
                case 0: // Тип датчика

                    break;
                case 1: // Период опроса
                case 3: // ID
                    if (UInt16.TryParse(Convert.ToString(e.FormattedValue), out ushort i))
                        view.Rows[e.RowIndex].Cells[e.ColumnIndex].ErrorText = "";
                    else
                        view.Rows[e.RowIndex].Cells[e.ColumnIndex].ErrorText = "Значение должно быть между 0 и 65535";
                    break;
                case 2: // Адрес
                    if (Byte.TryParse(Convert.ToString(e.FormattedValue), out byte q))
                        view.Rows[e.RowIndex].Cells[e.ColumnIndex].ErrorText = "";
                    else
                        view.Rows[e.RowIndex].Cells[e.ColumnIndex].ErrorText = "Значение должно быть между 0 и 255";
                    break;
            }

            // Подсчет ошибок в полях
            int errorCounter = 0;
            Parallel.ForEach(view.Rows.Cast<DataGridViewRow>(), row =>
            {
                foreach (DataGridViewCell gridCell in row.Cells)
                {
                    if (gridCell.ErrorText.Length > 0) errorCounter += 1;
                }
            });

            // блокируем кнопку отправки, если есть ошибки при валидации
            PictureBox bt_rsWrite = new PictureBox();
            if (view == dg_rs1_sensors) bt_rsWrite = bt_rs1_sensorsWrite;
            else if (view == dg_rs2_sensors) bt_rsWrite = bt_rs2_sensorsWrite;
            else if (view == dg_rs3_sensors) bt_rsWrite = bt_rs3_sensorsWrite;
            if (bt_rsWrite != null) bt_rsWrite.Enabled = (errorCounter == 0);
        }

        private async void bt_rs1_sensorsWrite_Click(object sender, EventArgs e)
        {
            await sendSensors(dg_rs1_sensors, Interfaces.RS1);
        }

        private async Task sendSensors(DataGridView dg_sensors, Interfaces ifc)
        {

            if (USB_serial.IsOpen)
            {
                if (dg_sensors.RowCount == 1)
                {
                    Byte[] sendBuff = new Byte[3];
                    sendBuff[0] = WRITESENSOR;
                    sendBuff[1] = (Byte)ifc;
                    sendBuff[2] = 0xFF;
                    USB_serial.Write(sendBuff, 0, sendBuff.Length);
                }
                for (int i = 0; i < Math.Min(dg_sensors.RowCount - 1, MAX_SENSORS_RS); i++)
                {
                    Byte[] sendBuff = new Byte[24];
                    sendBuff[0] = WRITESENSOR;
                    sendBuff[1] = (Byte)ifc;
                    DataGridViewRow item = dg_sensors.Rows[i];
                    // index
                    sendBuff[2] = (Byte)i;
                    // name
                    char[] sensor_name = item.Cells[0].Value.ToString().ToArray();
                    Array.Copy(sensor_name.Select(c => (byte)c).ToArray(), 0, sendBuff, 3, sensor_name.Length > 16 ? 16 : sensor_name.Length);
                    // ID
                    UInt16 _id = UInt16.Parse(item.Cells[3].Value.ToString());
                    Array.Copy(BitConverter.GetBytes(_id), 0, sendBuff, 19, 2);
                    // Poll period (seconds)
                    UInt16 pollPeriod = UInt16.Parse(item.Cells[1].Value.ToString());
                    Array.Copy(BitConverter.GetBytes(pollPeriod), 0, sendBuff, 21, 2);
                    // sensor address
                    sendBuff[23] = Byte.Parse(item.Cells[2].Value.ToString());
                    USB_serial.Write(sendBuff, 0, sendBuff.Length);         // send new sensor
                }
                await sendCommandUpdateSettings();
            }
            else
            {
                MessageBox.Show("Устройство не подключено", "ERROR");
            }
        }

        private async void bt_rs1SettingsWrite_Click(object sender, EventArgs e)
        {
            await sendRSSettings(Interfaces.RS1);
        }

        private async Task sendRSSettings(Interfaces ifc)
        {
            ComboBox _baudrate, _databits, _parity, _stopbits;
            CheckBox _state;
            NumericUpDown _errors, _delay;
            switch (ifc)
            {
                case Interfaces.RS1:
                    _baudrate = cb_rs1_baudrate;
                    _databits = cb_rs1_databits;
                    _parity = cb_rs1_parity;
                    _stopbits = cb_rs1_stopbits;
                    _state = chb_rs1_activate;
                    _errors = num_rs1Errors;
                    _delay = num_rs1Delay;
                    break;
                case Interfaces.RS2:
                    _baudrate = cb_rs2_baudrate;
                    _databits = cb_rs2_databits;
                    _parity = cb_rs2_parity;
                    _stopbits = cb_rs2_stopbits;
                    _state = chb_rs2_activate;
                    _errors = num_rs2Errors;
                    _delay = num_rs2Delay;
                    break;
                case Interfaces.RS3:
                    _baudrate = cb_rs3_baudrate;
                    _databits = cb_rs3_databits;
                    _parity = cb_rs3_parity;
                    _stopbits = cb_rs3_stopbits;
                    _state = chb_rs3_activate;
                    _errors = num_rs3Errors;
                    _delay = num_rs3Delay;
                    break;
                default:
                    return;
            }
            if (USB_serial.IsOpen)
            {

                Byte[] sendBuff = new Byte[12] { WRITEPORTSETTINGS, (Byte)ifc, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
                UInt32 baudrate = UInt32.Parse(_baudrate.SelectedItem.ToString());
                Array.Copy(BitConverter.GetBytes(baudrate), 0, sendBuff, 2, sizeof(UInt32));
                sendBuff[6] = (Byte)_databits.SelectedIndex;
                sendBuff[7] = (Byte)_parity.SelectedIndex;
                sendBuff[8] = (Byte)_stopbits.SelectedIndex;
                sendBuff[9] = (Byte)(_state.Checked ? 1 : 0);
                sendBuff[10] = (Byte)_delay.Value;
                sendBuff[11] = (Byte)_errors.Value;
                USB_serial.Write(sendBuff, 0, sendBuff.Length);
                await sendCommandUpdateSettings();
            }
            else
            {
                MessageBox.Show("Устройство не подключено", "ERROR");
            }
        }

        private void bt_rs1_sensorsRead_Click(object sender, EventArgs e)
        {
            dg_rs1_sensors.Rows.Clear();
            getSensors(Interfaces.RS1);
        }

        private void getSensors(Interfaces ifc)
        {
            Byte[] sendBuff = new Byte[2] { READSENSOR, (Byte)ifc };
            if (USB_serial.IsOpen)
            {
                USB_serial.Write(sendBuff, 0, sendBuff.Length);             // get sensors                
            }
            else
            {
                MessageBox.Show("Устройство не подключено", "ERROR");
            }
        }

        private void bt_rs1SettingsRead_Click(object sender, EventArgs e)
        {
            getPortSettings(Interfaces.RS1);
        }

        private void getPortSettings(Interfaces ifc)
        {
            Byte[] sendBuff = new Byte[2] { READPORTSETTINGS, (Byte)ifc };
            if (USB_serial.IsOpen)
            {
                USB_serial.Write(sendBuff, 0, sendBuff.Length);             // get sensors                
            }
            else
            {
                MessageBox.Show("Устройство не подключено", "ERROR");
            }
        }

        private void bt_rs2SettingsRead_Click(object sender, EventArgs e)
        {
            getPortSettings(Interfaces.RS2);
        }

        private async void bt_rs2SettingsWrite_Click(object sender, EventArgs e)
        {
            await sendRSSettings(Interfaces.RS2);
        }

        private void bt_rs2_sensorsRead_Click(object sender, EventArgs e)
        {
            dg_rs2_sensors.Rows.Clear();
            getSensors(Interfaces.RS2);
        }

        private async void bt_rs2_sensorsWrite_Click(object sender, EventArgs e)
        {
            await sendSensors(dg_rs2_sensors, Interfaces.RS2);
        }

        private void panel_rs2_Click(object sender, EventArgs e)
        {
            tabControl1.SelectTab("tab_rs2");
        }

        private void panel_rs3_Click(object sender, EventArgs e)
        {
            tabControl1.SelectTab("tab_rs3");
        }

        private void bt_rs3SettingsRead_Click(object sender, EventArgs e)
        {
            getPortSettings(Interfaces.RS3);
        }

        private async void bt_rs3SettingsWrite_Click(object sender, EventArgs e)
        {
            await sendRSSettings(Interfaces.RS3);
        }

        private void bt_rs3_sensorsRead_Click(object sender, EventArgs e)
        {
            dg_rs3_sensors.Rows.Clear();
            getSensors(Interfaces.RS3);
        }

        private async void bt_rs3_sensorsWrite_Click(object sender, EventArgs e)
        {
            await sendSensors(dg_rs3_sensors, Interfaces.RS3);
        }

        private async void sendFwMqtt()
        {
            Byte[] sendBuff = new Byte[264];
            UInt16 numOfPage = 0;
            var mqttFactory = new MqttFactory();

            bool mqttTransmitConfirmed = false;
            try
            {
                progress_firmLoad.Invoke((MethodInvoker)delegate
                {
                    progress_firmLoad.Value = 0;
                    progress_firmLoad.Maximum = (int)Math.Ceiling((double)f_bytes.Length / 256.0);
                });
                using (var mqttClient = mqttFactory.CreateMqttClient())
                {
                    // указываем брокера
                    var mqttClientOptions = new MqttClientOptionsBuilder()
                        .WithTcpServer(tb_mqttServer.Text)
                        .Build();

                    // коннектимся
                    await mqttClient.ConnectAsync(mqttClientOptions, CancellationToken.None);
                    // обработчик ответа
                    mqttClient.ApplicationMessageReceivedAsync += msg =>
                    {
                        String res = System.Text.ASCIIEncoding.ASCII.GetString(msg.ApplicationMessage.Payload);
                        if (res.StartsWith("OK:"))
                        {
                            mqttTransmitConfirmed = true;
                        }
                        return Task.CompletedTask;
                    };
                    // подписываемся на ответ
                    var mqttSubscribeOptions = mqttFactory.CreateSubscribeOptionsBuilder()
                        .WithTopicFilter(
                            f =>
                            {
                                f.WithTopic((tb_mqttTopic.Text.Trim('/') + "/CTRL/IN/Fw").Replace("IN", "OUT"));
                            })
                        .Build();
                    await mqttClient.SubscribeAsync(mqttSubscribeOptions, CancellationToken.None);
                    log_rtb1("Начало прошивки по MQTT", Color.Blue);
                    // Отправляем прошивку по 256 байт
                    for (int i = 0; i < f_bytes.Length; i += 256)
                    {
                        mqttTransmitConfirmed = false;
                        // Номер страницы
                        Array.Copy(UInt16ToByteArray(numOfPage++), 0, sendBuff, 0, 2);

                        // Длина текущего сообщения
                        int len = (f_bytes.Length - i) > 256 ? 256 : (f_bytes.Length - i);
                        Array.Copy(UInt16ToByteArray(len), 0, sendBuff, 2, 2);

                        // Сами байтики
                        Array.Copy(f_bytes, i, sendBuff, 4, len);

                        // Отправляем и ждем подтверждения
                        var frmMessage = new MqttApplicationMessageBuilder()
                        .WithTopic(tb_mqttTopic.Text.Trim('/') + "/CTRL/IN/Fw")
                        .WithPayload(sendBuff)
                        .Build();

                        await mqttClient.PublishAsync(frmMessage, CancellationToken.None);
                        DateTime startTime = DateTime.Now;
                        while (!mqttTransmitConfirmed)
                        {
                            if ((DateTime.Now - startTime).TotalSeconds > 6)
                            {
                                log_rtb1("Ошибка передачи прошивки по MQTT: answer timeout", Color.Red);
                                await mqttClient.DisconnectAsync();
                                return;
                            }
                        }
                        progress_firmLoad.Invoke((MethodInvoker)delegate
                        {
                            progress_firmLoad.PerformStep();
                        });
                    }

                    // Отправляем параметры прошивки
                    sendBuff = new Byte[16];
                    // Номер страницы (0xFFFF - страница с параметрами)
                    if (cb_restartAfterDownload.Checked)
                    {
                        Array.Copy(UInt16ToByteArray(0xFFFF), 0, sendBuff, 0, 2);
                    }
                    else
                    {
                        Array.Copy(UInt16ToByteArray(0xFFFE), 0, sendBuff, 0, 2);
                    }
                    // Длина текущего сообщения
                    Array.Copy(UInt16ToByteArray(14), 0, sendBuff, 2, 2);

                    // Длина прошивки в байтах
                    Array.Copy(UInt32ToByteArray((UInt32)f_bytes.Length), 0, sendBuff, 4, 4);

                    // Длина прошивки в страницах
                    Array.Copy(UInt32ToByteArray((UInt32)Math.Ceiling((double)f_bytes.Length / 256.0)), 0, sendBuff, 8, 4);

                    // CRC32 всей прошивки
                    CRC = Crc32Algorithm.Compute(f_bytes, 0, f_bytes.Length);
                    Array.Copy(UInt32ToByteArray(CRC), 0, sendBuff, 12, 4);

                    var paramMessage = new MqttApplicationMessageBuilder()
                        .WithTopic(tb_mqttTopic.Text.Trim('/') + "/CTRL/IN/Fw")
                        .WithPayload(sendBuff)
                        .Build();

                    await mqttClient.PublishAsync(paramMessage, CancellationToken.None);
                    DateTime startTime_1 = DateTime.Now;
                    while (!mqttTransmitConfirmed)
                    {
                        if ((DateTime.Now - startTime_1).TotalSeconds > 6)
                        {
                            log_rtb1("Ошибка передачи прошивки по MQTT: answer timeout", Color.Red);
                            await mqttClient.DisconnectAsync();
                            return;
                        }
                    }
                    log_rtb1("Передача прошивки по MQTT завершена", Color.Blue);
                    await mqttClient.DisconnectAsync();
                }
            }
            catch (MQTTnet.Exceptions.MqttCommunicationException ex)
            {
                MessageBox.Show(ex.Message);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void bt_sendFWMqtt_Click(object sender, EventArgs e)
        {
            if (f_bytes != null && f_bytes.Length > 100)
            {
                Thread sendFrm = new Thread(new ThreadStart(sendFwMqtt));
                sendFrm.Start();
            }
            else MessageBox.Show("Сначала выберите файл");
        }

        private async void bt_mqttReboot_Click(object sender, EventArgs e)
        {
            await sendMQTT("1", tb_mqttTopic.Text.Trim('/') + "/CTRL/IN/Reboot", tb_mqttServer.Text);
            log_rtb1("Отправлена команда на перезагрузку по MQTT");
#if RELEASE
            await clearTopic(tb_mqttTopic.Text.Trim('/') + "/CTRL/IN/Reboot", tb_mqttServer.Text);
#endif
        }

        public IEnumerable<Control> GetAllControls(Control control, Type type)
        {
            var controls = control.Controls.Cast<Control>();

            return controls.SelectMany(ctrl => GetAllControls(ctrl, type))
                                      .Concat(controls)
                                      .Where(c => c.GetType() == type);
        }

        private void LoadConfigFromfile()
        {
            try
            {
                string json_str;
                using (var dialog = new OpenFileDialog())
                {
                    dialog.Filter = "Config file|*.cfg";
                    if (dialog.ShowDialog(this) == DialogResult.OK)
                        json_str = File.ReadAllText(dialog.FileName);
                    else return;
                }
                List<Configs> cfgs = JsonConvert.DeserializeObject<List<Configs>>(json_str);
                foreach (Configs a in cfgs)
                {
                    if (a.ControlType != typeof(CheckBox))
                    {
                        this.Controls.Find(a.ControlName, true)[0].Text = a.ControlText;
                    }
                    else
                    {
                        ((CheckBox)this.Controls.Find(a.ControlName, true)[0]).Checked = a.ControlChecked;
                    }
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Не удалось извлечь данные из файла:\n" + ex.ToString(), "ERROR");
            }
        }

        private void SaveConfigToFile()
        {
            List<Configs> Cfg_list = new List<Configs>();
            Type[] ListOfSavedControls = new Type[] { typeof(TextBox),
                                                        typeof(MaskedTextBox),
                                                        typeof(CheckBox)};
            foreach (Type a in ListOfSavedControls)
            {
                foreach (Control ctrl in GetAllControls(this, a))
                {
                    if (a == typeof(CheckBox))
                    {
                        Cfg_list.Add(new Configs(a, ctrl.Name, "NULL", ((CheckBox)ctrl).Checked));
                    }
                    else
                    {
                        Cfg_list.Add(new Configs(a, ctrl.Name, ctrl.Text, false));
                    }
                }
            }

            string json_str = JsonConvert.SerializeObject(Cfg_list, Formatting.Indented);
            using (var dialog = new SaveFileDialog())
            {
                dialog.Filter = "Config files|*.cfg";
                if (dialog.ShowDialog(this) == DialogResult.OK)
                    File.WriteAllText(dialog.FileName, json_str);
            }
        }

        private void main_window_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.F1)                               // HELP
            {
                MessageBox.Show("Доступные комбинации клавиш:\n\n" +
                                "Ctrl + D\t- Режим разработчика\n" +
                                "Ctrl + W\t- Разрешить запись серийного номера\n" +
                                "Ctrl + S\t- Сохранить настройки\n" +
                                "Ctrl + A\t- Загрузить настройки\n" +
                                "Ctrl + Q\t- Отключить USB\n" +
                                "F2\t- Окно прошивки\n" +
                                "F3\t- Автоподключение к USB\n" +
                                "ESC\t- Назад\n" +
                                "");
            }
            else if (e.KeyCode == Keys.F3)       // Autoconnect to USB
            {
                if (!USB_serial.IsOpen)
                {
                    foreach (string portname in SerialPort.GetPortNames().Reverse())
                    {
                        if (usb_connect(portname)) return;
                        usb_disconnect();
                    }
                    MessageBox.Show("Устройство не обнаружено");
                }
            }
            else if (e.KeyCode == Keys.F2) tabControl1.SelectTab(tab_frm);
            else if (e.Control && (e.KeyCode == Keys.D))               // Toggle developer mode (extra buttons)
            {
                dev_mode ^= true;
                bt_reprogMqtt.Visible ^= true;
                bt_mqttReboot.Visible ^= true;
                bt_mqttFwVersion.Visible ^= true;
                bt_resetSettings.Visible ^= true;
            }
            else if (e.Control && (e.KeyCode == Keys.W) && dev_mode)          // enable write serial number
            {
                bt_writeMainParams.Visible ^= true;
                tb_ModuleSerialNumber.ReadOnly ^= true;
                dt_DateOfProduction.Enabled ^= true;
            }
            else if (e.Control && (e.KeyCode == Keys.S) && dev_mode)          // Save config to file
            {
                SaveConfigToFile();
            }
            else if (e.Control && (e.KeyCode == Keys.A) && dev_mode)          // Load config from file
            {
                LoadConfigFromfile();
            }
            else if (e.Control && (e.KeyCode == Keys.Q))          // Disconnect USB from any page
            {
                usb_disconnect();
            }
            else if (e.KeyCode == Keys.Escape)     // Close form (for non-border assembly)
            {
                if (tabControl1.SelectedTab != tab_main) tabControl1.SelectTab("tab_main");
                else
                {
                    if (MessageBox.Show("Закрыть приложение?", "Выход", MessageBoxButtons.YesNo) == DialogResult.Yes) Close();
                }
            }
        }

        private async Task<List<String>> MQTT_Transmit_ReceiveList(string sendbuf, string _topic, string _broker, int timeoutMilliseconds)
        {
            try
            {
                List<String> answer = new List<string>();
                var mqttFactory = new MqttFactory();
                using (var mqttClient = mqttFactory.CreateMqttClient())
                {
                    // указываем брокера
                    var mqttClientOptions = new MqttClientOptionsBuilder()
                        .WithTcpServer(_broker)
                        .Build();

                    // коннектимся
                    await mqttClient.ConnectAsync(mqttClientOptions, CancellationToken.None);
                    // обработчик ответа
                    mqttClient.ApplicationMessageReceivedAsync += msg =>
                    {
                        answer.Add(System.Text.ASCIIEncoding.ASCII.GetString(msg.ApplicationMessage.Payload));
                        return Task.CompletedTask;
                    };
                    // подписываемся на ответ
                    var mqttSubscribeOptions = mqttFactory.CreateSubscribeOptionsBuilder()
                        .WithTopicFilter(
                            f =>
                            {
                                f.WithTopic(_topic.Replace("IN", "OUT"));
                            })
                        .Build();
                    await mqttClient.SubscribeAsync(mqttSubscribeOptions, CancellationToken.None);

                    // Отправляем и ждем подтверждения
                    var frmMessage = new MqttApplicationMessageBuilder()
                    .WithTopic(_topic)
                    .WithPayload(sendbuf)
                    .Build();

                    DateTime startTime = DateTime.Now;
                    await mqttClient.PublishAsync(frmMessage, CancellationToken.None);
                    while (true)
                    {
                        if (((DateTime.Now - startTime).TotalMilliseconds > timeoutMilliseconds))
                        {
                            if (answer.Count == 0) MessageBox.Show("Answer timeout");
                            break;
                        }
                    }
                    await mqttClient.DisconnectAsync();
                    return answer;
                }
            }
            catch (MQTTnet.Exceptions.MqttCommunicationException ex)
            {
                MessageBox.Show(ex.Message);
                return new List<string>();
            }

        }
        private async Task<string> MQTT_Transmit_Receive(string sendbuf, string _topic, string _broker)
        {
            try
            {
                bool mqttTransmitConfirmed = false;
                string answer = "";
                var mqttFactory = new MqttFactory();
                using (var mqttClient = mqttFactory.CreateMqttClient())
                {
                    // указываем брокера
                    var mqttClientOptions = new MqttClientOptionsBuilder()
                        .WithTcpServer(_broker)
                        .Build();

                    // коннектимся
                    await mqttClient.ConnectAsync(mqttClientOptions, CancellationToken.None);
                    // обработчик ответа
                    mqttClient.ApplicationMessageReceivedAsync += msg =>
                    {
                        answer = System.Text.ASCIIEncoding.ASCII.GetString(msg.ApplicationMessage.Payload);
                        mqttTransmitConfirmed = true;
                        return Task.CompletedTask;
                    };
                    // подписываемся на ответ
                    var mqttSubscribeOptions = mqttFactory.CreateSubscribeOptionsBuilder()
                        .WithTopicFilter(
                            f =>
                            {
                                f.WithTopic(_topic.Replace("IN", "OUT"));
                            })
                        .Build();
                    await mqttClient.SubscribeAsync(mqttSubscribeOptions, CancellationToken.None);

                    // Отправляем и ждем подтверждения
                    var frmMessage = new MqttApplicationMessageBuilder()
                    .WithTopic(_topic)
                    .WithPayload(sendbuf)
                    .Build();

                    DateTime startTime = DateTime.Now;
                    await mqttClient.PublishAsync(frmMessage, CancellationToken.None);
                    while (!mqttTransmitConfirmed)
                    {
                        if ((DateTime.Now - startTime).TotalSeconds > 5)
                        {
                            MessageBox.Show("Answer timeout");
                            await mqttClient.DisconnectAsync();
                            return "";
                        }
                    }
                    await mqttClient.DisconnectAsync();
                    return answer;
                }
            }
            catch (MQTTnet.Exceptions.MqttCommunicationException ex)
            {
                MessageBox.Show(ex.Message);
                return "";
            }
        }
        private async Task clearTopic(string _topic, string _broker)
        {
            try
            {
                Thread.Sleep(50);
                var mqttFactory = new MqttFactory();
                using (var mqttClient = mqttFactory.CreateMqttClient())
                {
                    var mqttClientOptions = new MqttClientOptionsBuilder()
                        .WithTcpServer(_broker)
                        .Build();
                    await mqttClient.ConnectAsync(mqttClientOptions, CancellationToken.None);


                    var paramMessage = new MqttApplicationMessageBuilder()
                        .WithTopic(_topic)
                        .WithPayload(Stream.Null)
                        .Build();

                    await mqttClient.PublishAsync(paramMessage, CancellationToken.None);

                    await mqttClient.DisconnectAsync();
                }
            }
            catch (MQTTnet.Exceptions.MqttCommunicationException ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
        private async Task sendMQTT(Byte[] msg, string _topic, string _broker)
        {
            try
            {
                var mqttFactory = new MqttFactory();
                using (var mqttClient = mqttFactory.CreateMqttClient())
                {
                    var mqttClientOptions = new MqttClientOptionsBuilder()
                        .WithTcpServer(_broker)
                        .Build();
                    await mqttClient.ConnectAsync(mqttClientOptions, CancellationToken.None);


                    var paramMessage = new MqttApplicationMessageBuilder()
                        .WithTopic(_topic)
                        .WithPayload(msg)
                        .Build();

                    await mqttClient.PublishAsync(paramMessage, CancellationToken.None);

                    await mqttClient.DisconnectAsync();
                }
            }
            catch (MQTTnet.Exceptions.MqttCommunicationException ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private async Task sendMQTT(string msg, string _topic, string _broker)
        {
            try
            {
                var mqttFactory = new MqttFactory();
                using (var mqttClient = mqttFactory.CreateMqttClient())
                {
                    var mqttClientOptions = new MqttClientOptionsBuilder()
                        .WithTcpServer(_broker)
                        .Build();
                    await mqttClient.ConnectAsync(mqttClientOptions, CancellationToken.None);


                    var paramMessage = new MqttApplicationMessageBuilder()
                        .WithTopic(_topic)
                        .WithPayload(msg)
                        .Build();

                    await mqttClient.PublishAsync(paramMessage, CancellationToken.None);

                    await mqttClient.DisconnectAsync();
                }
            }
            catch (MQTTnet.Exceptions.MqttCommunicationException ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private async void bt_reprogMqtt_Click(object sender, EventArgs e)
        {
            await sendMQTT("1", tb_mqttTopic.Text.Trim('/') + "/CTRL/IN/Flashflag", tb_mqttServer.Text);
            log_rtb1("Отправлен флаг перепрошивки по MQTT");
#if RELEASE
            await clearTopic(tb_mqttTopic.Text.Trim('/') + "/CTRL/IN/Flashflag", tb_mqttServer.Text);
#endif
        }

        private async void bt_mqttFwVersion_Click(object sender, EventArgs e)
        {
            string _str = await MQTT_Transmit_Receive("?", tb_mqttTopic.Text.Trim('/') + "/CTRL/IN/Fwinfo", tb_mqttServer.Text);
            log_rtb1("Версия ПО, считанная по MQTT: " + _str, Color.Blue);
        }

        private void bt_resetSettings_Click(object sender, EventArgs e)
        {
            if (USB_serial.IsOpen)
            {
                USB_serial.Write(new byte[1] { 0xA0 }, 0, 1);
                log_rtb1("Установлены настройки устройства по умолчанию");
            }
            else
                MessageBox.Show("Устройство не подключено", "ERROR");
        }

        private void tab_frm_Enter(object sender, EventArgs e)
        {
            refresh_usb();
        }

        private void panel_zigbee_Click(object sender, EventArgs e)
        {
            tabControl1.SelectTab("tab_zigbee");
        }

        private async void bt_zigbee_send_Click(object sender, EventArgs e)
        {
            byte[] sendMessage;
            if (USB_serial.IsOpen)
            {
                USB_serial.DiscardInBuffer();
                // ZIGBEE ACTIVATE FLAG
                sendMessage = new byte[2];
                sendMessage[0] = ParamID["ZIGBEE_ACTIVATE"];
                sendMessage[1] = chb_ZigBee_Activate.Checked ? (byte)1 : (byte)0;
                if (!await sendData(sendMessage)) return;
                await sendCommandUpdateSettings();
            }
            else
            {
                MessageBox.Show("Устройство не подключено", "ERROR");
            }
        }

        private void bt_zigbee_read_Click(object sender, EventArgs e)
        {
            byte[] sendBuf = new byte[2] { READCOMMAND, 0 };
            if (USB_serial.IsOpen)
            {
                foreach (KeyValuePair<string, byte> param in ParamID.Where(p => p.Key.StartsWith("ZIGBEE")))
                {
                    sendBuf[1] = param.Value;
                    USB_serial.Write(sendBuf, 0, sendBuf.Length);
                    Thread.Sleep(50);
                }
            }
            else
            {
                MessageBox.Show("Устройство не подключено", "ERROR");
            }
        }

        private void pictureBox1_MouseDown(object sender, MouseEventArgs e)
        {
#if NOBORDER
            int xOffset;
            int yOffset;

            if (e.Button == MouseButtons.Right)
            {
                xOffset = -e.X - SystemInformation.FrameBorderSize.Width;
                yOffset = -e.Y - SystemInformation.CaptionHeight -
                    SystemInformation.FrameBorderSize.Height;
                mouseOffset = new Point(xOffset, yOffset);
                isMouseDown = true;
            }
#endif
        }

        private void pictureBox1_MouseMove(object sender, MouseEventArgs e)
        {
#if NOBORDER
            if (isMouseDown)
            {
                Point mousePos = Control.MousePosition;
                mousePos.Offset(mouseOffset.X, mouseOffset.Y);
                Location = mousePos;
            }
#endif
        }

        private void pictureBox1_MouseUp(object sender, MouseEventArgs e)
        {
#if NOBORDER
            if (e.Button == MouseButtons.Right)
            {
                isMouseDown = false;
            }
#endif
        }

        private void bt_zigbeeFrmSend_Click(object sender, EventArgs e)
        {
            Frm frm = new Frm(f_bytes_zb, (byte)Devices.ZigbeeBoard, pb_zigbee);
            Thread sendFrm = new Thread(new ParameterizedThreadStart(SendFrmUsb));
            sendFrm.Start(frm);
        }

        private void bt_zigbeeFrmGetFile_Click(object sender, EventArgs e)
        {
            pb_zigbee.Value = pb_zigbee.Minimum;
            // GET FILE
            using (var dialog = new OpenFileDialog())
            {
                dialog.Filter = "bin files (*.bin)|*.bin";
                if (dialog.ShowDialog(this) == DialogResult.OK)
                    f_bytes_zb = File.ReadAllBytes(dialog.FileName);
            }
        }


        private void richTextBox1_TextChanged(object sender, EventArgs e)
        {
            richTextBox1.SelectionStart = richTextBox1.Text.Length;
            richTextBox1.ScrollToCaret();
        }

        private void bt_MouseUp(object sender, MouseEventArgs e)
        {
            ((PictureBox)sender).BorderStyle = BorderStyle.None;
        }

        private void bt_MouseDown(object sender, MouseEventArgs e)
        {
            ((PictureBox)sender).BorderStyle = BorderStyle.Fixed3D;
        }

        private void bt_MouseLeave(object sender, EventArgs e)
        {
            ((PictureBox)sender).BorderStyle = BorderStyle.None;
        }

        private void dg_rs1_sensors_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            if (e.RowIndex >= 0 && e.ColumnIndex == 0)
            {
                // row
                DataGridViewRow _row = ((DataGridView)sender).Rows[e.RowIndex];
                // sensor type
                try
                {
                    Sensor s_sensor = findSensorByName(_row.Cells[0].Value.ToString());
                    _row.Cells[2].Value = s_sensor.Address.ToString();
                    _row.Cells[1].Value = s_sensor.PollPeriod.ToString();
                    _row.Cells[3].Value = s_sensor.ID.ToString();
                }
                catch
                {
                    // игнорим ошибку, если не получилось
                }
            }
        }

        private void clear_rsSensorsTable_Click(object sender, EventArgs e)
        {
            ((DataGridView)((ContextMenuStrip)((ToolStripMenuItem)sender).Owner).SourceControl).Rows.Clear();
        }

        private void loadRSSensorsConfig_Click(object sender, EventArgs e)
        {
            // Загрузка настроек из файла
            string json_str = null;
            try
            {
                // считываем файл
                using (var dialog = new OpenFileDialog())
                {
                    dialog.Filter = "Sensors list|*.snl";
                    if (dialog.ShowDialog(this) == DialogResult.OK)
                        json_str = File.ReadAllText(dialog.FileName);
                    else return;
                }
                // разбираем файл
                if (json_str.Length > 0)
                {
                    List<RSSensor> sensors = JsonConvert.DeserializeObject<List<RSSensor>>(json_str);
                    if (sensors != null)
                    {
                        // очищаем нужные таблицы
                        foreach (String viewName in sensors.Select(p => p.view).Distinct().ToList())
                        {
                            ((DataGridView)this.Controls.Find(viewName, true)[0]).Rows.Clear();
                        }
                        // заполняем таблицы
                        foreach (RSSensor rssensor in sensors)
                        {
                            ((DataGridView)this.Controls.Find(rssensor.view, true)[0]).Rows.Add(rssensor.sensor.Name.ToString(),
                                                                                                rssensor.sensor.PollPeriod.ToString(),
                                                                                                rssensor.sensor.Address.ToString());
                        }
                    }
                }
            }
            catch
            {
                MessageBox.Show("Файл поврежден", "Не удалось загрузить настройки");
            }
        }

        private void saveRSSensorsConfig_Click(object sender, EventArgs e)
        {
            // Сохранение настроек в файл
            DataGridView view = (DataGridView)((ContextMenuStrip)((ToolStripMenuItem)sender).Owner).SourceControl;
            saveSensorsConfig(new List<DataGridView> { view });
        }

        private void saveAllToolStripMenuItem_Click(object sender, EventArgs e)
        {
            // Сохранение настроек в файл
            List<DataGridView> views = new List<DataGridView> { dg_rs1_sensors, dg_rs2_sensors, dg_rs3_sensors };
            saveSensorsConfig(views);
        }

        private void saveSensorsConfig(List<DataGridView> views)
        {
            List<RSSensor> sensors = new List<RSSensor>();
            try
            {
                foreach (DataGridView view in views)
                {
                    foreach (DataGridViewRow row in view.Rows)
                    {
                        if (row.Index == (view.RowCount - 1)) break;
                        Sensor sensor = findSensorByName(row.Cells[0].Value.ToString());
                        sensor.PollPeriod = Convert.ToUInt32(row.Cells[1].Value);
                        sensors.Add(new RSSensor(view.Name, sensor));
                    }
                }
                string json_str = JsonConvert.SerializeObject(sensors, Formatting.Indented);
                using (var dialog = new SaveFileDialog())
                {
                    dialog.Filter = "Sensors list|*.snl";
                    if (dialog.ShowDialog(this) == DialogResult.OK)
                        File.WriteAllText(dialog.FileName, json_str);
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString(), "Не удалось сохранить настройки");
            }
        }

        private void dg_rs1_sensors_CurrentCellDirtyStateChanged(object sender, EventArgs e)
        {
            DataGridView view = ((DataGridView)sender);
            if (view.IsCurrentCellDirty)
            { view.CommitEdit(DataGridViewDataErrorContexts.Commit); }
        }

        private DataGridViewCellEventArgs theCellImHoveringOver;
        private void dg_rs1_sensors_CellMouseEnter(object sender, DataGridViewCellEventArgs e)
        {
            theCellImHoveringOver = e;
        }

        private void deleteRowToolStripMenuItem_Click(object sender, EventArgs e)
        {
            DataGridView view = (DataGridView)((ContextMenuStrip)((ToolStripMenuItem)sender).Owner).SourceControl;
            if (theCellImHoveringOver != null && theCellImHoveringOver.RowIndex < (view.Rows.Count - 1))
                view.Rows.RemoveAt(theCellImHoveringOver.RowIndex);
        }

        private void rebootUSB_Click(object sender, EventArgs e)
        {
            if (USB_serial.IsOpen)
            {
                USB_serial.Write(new byte[1] { 0xFF }, 0, 1);
                log_rtb1("Отправлена команда на перезагрузку по USB", Color.Blue);
                usb_disconnect();
            }
        }

        private void clear_Click(object sender, EventArgs e)
        {
            ((RichTextBox)((ContextMenuStrip)((ToolStripMenuItem)sender).Owner).SourceControl).Clear();
        }

        private void log_rtb1(string text, Color color)
        {
            richTextBox1.Invoke((MethodInvoker)delegate
            {
                richTextBox1.AppendTextRefresh(DateTime.Now.ToString("[HH:mm:ss] ") + text, color);
            });
        }

        private void log_rtb1(string text)
        {
            log_rtb1(text, Color.Black);
        }

        private void loadAllToolStripMenuItem_Click(object sender, EventArgs e)
        {
            LoadConfigFromfile();
        }

        private void saveAllSettingsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveConfigToFile();
        }

        private void readAllToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (USB_serial.IsOpen)
            {
                USB_serial.Write(new byte[] { READALLCONFIG }, 0, 1);
                // дальше обработка в datareceived
                log_rtb1("Запрос на чтение всей конфигурации ОУ");
            }
            else
            {
                MessageBox.Show("Устройство не подключено", "ERROR");
            }
        }

        private async void addSensorMQTTToolStripMenuItem_Click(object sender, EventArgs e)
        {
            DataGridView view = (DataGridView)((ContextMenuStrip)((ToolStripMenuItem)sender).Owner).SourceControl;
            if (theCellImHoveringOver != null && theCellImHoveringOver.RowIndex < (view.Rows.Count - 1))
            {
                DataGridViewRow row = view.Rows[theCellImHoveringOver.RowIndex];
                // topic
                string topic = tb_mqttTopic.Text + "/CTRL/IN/Add/";
                if (view == dg_rs1_sensors) topic += "RS1";
                else if (view == dg_rs2_sensors) topic += "RS2";
                else if (view == dg_rs3_sensors) topic += "RS3";
                // message
                string msg = row.Cells[2].Value.ToString() + " ";
                msg += row.Cells[3].Value.ToString() + " ";
                msg += row.Cells[0].Value.ToString() + " ";
                msg += row.Cells[1].Value.ToString();

                await sendMQTT(msg, topic, tb_mqttServer.Text);
            }
        }

        private async void delSensorMQTTToolStripMenuItem_Click(object sender, EventArgs e)
        {
            DataGridView view = (DataGridView)((ContextMenuStrip)((ToolStripMenuItem)sender).Owner).SourceControl;
            if (theCellImHoveringOver != null && theCellImHoveringOver.RowIndex < (view.Rows.Count - 1))
            {
                DataGridViewRow row = view.Rows[theCellImHoveringOver.RowIndex];
                // topic
                string topic = tb_mqttTopic.Text + "/CTRL/IN/Del/";
                if (view == dg_rs1_sensors) topic += "RS1";
                else if (view == dg_rs2_sensors) topic += "RS2";
                else if (view == dg_rs3_sensors) topic += "RS3";
                // message
                string msg = row.Cells[2].Value.ToString() + " ";
                msg += row.Cells[3].Value.ToString();

                await sendMQTT(msg, topic, tb_mqttServer.Text);
                view.Rows.RemoveAt(theCellImHoveringOver.RowIndex);
            }
        }

        private async void getSensorsMqtt(object i_obj)
        {
            DataGridView view = (DataGridView)i_obj;
            // topic
            string topic = tb_mqttTopic.Text + "/CTRL/IN/Info/";
            if (view == dg_rs1_sensors) topic += "RS1";
            else if (view == dg_rs2_sensors) topic += "RS2";
            else if (view == dg_rs3_sensors) topic += "RS3";
            List<String> rawRes = await MQTT_Transmit_ReceiveList("?", topic, tb_mqttServer.Text, 5000);
            AddSensorsToGrid(view, rawRes);
        }
        private void AddSensorsToGrid(DataGridView view, List<String> rawRes)
        {
            view.Invoke((MethodInvoker)delegate
            {
                view.Rows.Clear();
                foreach (String msg in rawRes)
                {
                    if (msg != "-")
                    {
                        string res = msg.Substring(4);
                        string[] rawSensors = res.Split(';');
                        foreach (string sensorParams in rawSensors)
                        {
                            if (sensorParams != "")
                            {
                                string[] a = sensorParams.Split(' ');
                                view.Rows.Add(a[2], a[3], a[0], a[1]);
                                view.Refresh();
                            }
                        }
                    }
                }
            });
        }

        private void reqMQTTToolStripMenuItem_Click(object sender, EventArgs e)
        {
            DataGridView view = (DataGridView)((ContextMenuStrip)((ToolStripMenuItem)sender).Owner).SourceControl;
            Thread reqSens = new Thread(new ParameterizedThreadStart(getSensorsMqtt));
            reqSens.Start(view);
        }

        private async void delAllMQTTToolStripMenuItem_Click(object sender, EventArgs e)
        {
            DataGridView view = (DataGridView)((ContextMenuStrip)((ToolStripMenuItem)sender).Owner).SourceControl;
            // topic
            string topic = tb_mqttTopic.Text + "/CTRL/IN/Del/";
            if (view == dg_rs1_sensors) topic += "RS1";
            else if (view == dg_rs2_sensors) topic += "RS2";
            else if (view == dg_rs3_sensors) topic += "RS3";
            await sendMQTT("*", topic, tb_mqttServer.Text);
            view.Rows.Clear();
        }

        private async void writeRSSettingsMQTTToolStripMenuItem_Click(object sender, EventArgs e)
        {
            GroupBox box = (GroupBox)((ContextMenuStrip)((ToolStripMenuItem)sender).Owner).SourceControl;
            ComboBox _baudrate, _databits, _parity, _stopbits;
            CheckBox _activate;
            string ifc;
            if (box == gb_rs1_settings)          // RS1
            {
                _baudrate = cb_rs1_baudrate;
                _databits = cb_rs1_databits;
                _parity = cb_rs1_parity;
                _stopbits = cb_rs1_stopbits;
                _activate = chb_rs1_activate;
                ifc = "RS1";
            }
            else if (box == gb_rs2_settings)     // RS2
            {
                _baudrate = cb_rs2_baudrate;
                _databits = cb_rs2_databits;
                _parity = cb_rs2_parity;
                _stopbits = cb_rs2_stopbits;
                _activate = chb_rs2_activate;
                ifc = "RS2";
            }
            else if (box == gb_rs3_settings)     // RS3
            {
                _baudrate = cb_rs3_baudrate;
                _databits = cb_rs3_databits;
                _parity = cb_rs3_parity;
                _stopbits = cb_rs3_stopbits;
                _activate = chb_rs3_activate;
                ifc = "RS3";
            }
            else return;

            string msg = _baudrate.Text;
            msg += " " + _databits.SelectedIndex.ToString();
            msg += " " + _parity.SelectedIndex.ToString();
            msg += " " + _stopbits.SelectedIndex.ToString();
            msg += " " + (_activate.Checked ? "1" : "0");

            await sendMQTT(msg, tb_mqttTopic.Text + "/CTRL/IN/Config/" + ifc, tb_mqttServer.Text);
        }

        private async void readRSSettingsMQTTToolStripMenuItem_Click(object sender, EventArgs e)
        {
            GroupBox box = (GroupBox)((ContextMenuStrip)((ToolStripMenuItem)sender).Owner).SourceControl;
            ComboBox _baudrate, _databits, _parity, _stopbits;
            CheckBox _activate;
            string ifc;
            if (box == gb_rs1_settings)          // RS1
            {
                _baudrate = cb_rs1_baudrate;
                _databits = cb_rs1_databits;
                _parity = cb_rs1_parity;
                _stopbits = cb_rs1_stopbits;
                _activate = chb_rs1_activate;
                ifc = "RS1";
            }
            else if (box == gb_rs2_settings)     // RS2
            {
                _baudrate = cb_rs2_baudrate;
                _databits = cb_rs2_databits;
                _parity = cb_rs2_parity;
                _stopbits = cb_rs2_stopbits;
                _activate = chb_rs2_activate;
                ifc = "RS2";
            }
            else if (box == gb_rs3_settings)     // RS3
            {
                _baudrate = cb_rs3_baudrate;
                _databits = cb_rs3_databits;
                _parity = cb_rs3_parity;
                _stopbits = cb_rs3_stopbits;
                _activate = chb_rs3_activate;
                ifc = "RS3";
            }
            else return;

            String rawRes = await MQTT_Transmit_Receive("?", tb_mqttTopic.Text + "/CTRL/IN/Config/" + ifc, tb_mqttServer.Text);
            if (rawRes.Length > 0)
            {
                String[] answer = rawRes.Split(' ');
                _baudrate.Text = answer[0];
                _databits.SelectedIndex = Byte.Parse(answer[1]);
                _parity.SelectedIndex = Byte.Parse(answer[2]);
                _stopbits.SelectedIndex = Byte.Parse(answer[3]);
                _activate.Checked = (Byte.Parse(answer[4]) == 1);
            }
        }

        private void chb_MQTT_Activate_CheckedChanged(object sender, EventArgs e)
        {
            Control[] controls = new Control[] { tb_BrokerIP, tb_BrokerPort, tb_MQQTTopicOutput, tb_MQTT_ID, tb_MQTT_User, tb_MQTT_Password };
            foreach (Control a in controls) a.Enabled = chb_MQTT_Activate.Checked;
        }

        private void chb_ETH_Activate_CheckedChanged(object sender, EventArgs e)
        {
            Control[] controls = new Control[] { tb_IP, tb_Mask, tb_Gateway, tb_MAC, chb_DHCP, chb_MQTT_Activate };
            foreach (Control a in controls) a.Enabled = chb_ETH_Activate.Checked;
            if (!chb_ETH_Activate.Checked) chb_MQTT_Activate.Checked = false;
        }

        private void chb_LoRa_activate_CheckedChanged(object sender, EventArgs e)
        {
            Control[] controls = new Control[] { tb_LORA_DevEUI, tb_LORA_AppEUI, tb_LORA_AppKey, tb_LORA_AppPort, chb_AutoDevEUI,
                cb_loraDatarate, chb_LORA_ADR, cb_loraMessageType};
            foreach (Control a in controls) a.Enabled = chb_LoRa_activate.Checked;
        }

        private void panel_main_Click(object sender, EventArgs e)
        {
            tabControl1.SelectTab(tab_frm);
        }

        private void panel_encryption_Click(object sender, EventArgs e)
        {
            tabControl1.SelectTab("tab_encryption");
        }

        private void bt_encWrite_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Функция достепна по премиум подписке");
        }

        private void bt_encRead_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Функция достепна по премиум подписке");
        }

        private async void writeAllToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (USB_serial.IsOpen)
            {
                using (var dialog = new OpenFileDialog())
                {
                    dialog.Filter = "Config files|*.cfb";
                    if (dialog.ShowDialog(this) == DialogResult.OK)
                    {
                        byte[] _config = File.ReadAllBytes(dialog.FileName);
                        UInt32 _crc = Crc32Algorithm.Compute(_config, 0, _config.Length - 4);
                        // отправка параметров конфига
                        log_rtb1("Передача конфигурации ОУ");
                        byte[] sendBuff = new byte[10];
                        sendBuff[0] = WRITEALLCONFIG;
                        sendBuff[1] = 7;
                        Array.Copy(BitConverter.GetBytes((short)_config.Length), 0, sendBuff, 4, 2);
                        Array.Copy(BitConverter.GetBytes(_crc), 0, sendBuff, 6, 4);
                        if (!(await sendWithTimeout(USB_serial, sendBuff, 0, 10, 500)))
                        {
                            MessageBox.Show("Ошибка при передаче конфигурации (таймаут ответа)");
                            log_rtb1("Ошибка при передаче конфигурации (таймаут ответа)");
                            return;
                        }
                        // отправка конфига пачками
                        sendBuff = new byte[CONFIG_BLOCK_SIZE + 4];
                        sendBuff[0] = WRITEALLCONFIG;
                        short numOfBlock = 0;
                        for (int i = 0; i < _config.Length; i += 32)
                        {
                            // Длина текущего сообщения
                            byte len = (byte)(((_config.Length - i) > 32 ? 32 : (_config.Length - i)) + 2);
                            sendBuff[1] = len;
                            // Номер пакета
                            Array.Copy(BitConverter.GetBytes(++numOfBlock), 0, sendBuff, 2, 2);
                            // Сами байтики
                            Array.Copy(_config, i, sendBuff, 4, len);
                            // Отправляем и ждем подтверждения
                            if (!(await sendWithTimeout(USB_serial, sendBuff, 0, len + 4, 500)))
                            {
                                MessageBox.Show("Ошибка при передаче конфигурации (таймаут ответа)");
                                log_rtb1("Ошибка при передаче конфигурации (таймаут ответа)");
                                return;
                            }
                        }
                        MessageBox.Show("Конфигурация передана успешно");
                        log_rtb1("Конфигурация передана успешно");
                    }
                }
            }
            else
            {
                MessageBox.Show("Устройство не подключено", "ERROR");
            }
        }

        private void log_debug(string text)
        {
#if DEBUG
            log_rtb1(text);
#endif
        }

        void ClearControls(Control[] controls)
        {
            foreach (Control a in controls)
            {
                if (a.GetType() == typeof(CheckBox)) ((CheckBox)a).Checked = false;
                else if (a.GetType() == typeof(ComboBox)) ((ComboBox)a).SelectedIndex = 0;
                else if (a.GetType() == typeof(TextBox)) a.Text = String.Empty;
                else if (a.GetType() == typeof(MaskedTextBox)) a.Text = String.Empty;
                a.Update();
            }
        }

        private void bt_eth_read_Click(object sender, EventArgs e)
        {
            byte[] sendBuf = new byte[2] { READCOMMAND, 0 };
            if (USB_serial.IsOpen)
            {
                // Очистка старых значений в полях
                Control[] controls = new Control[] { tb_IP, tb_Mask, tb_Gateway, tb_MAC, tb_BrokerIP, tb_BrokerPort, tb_MQQTTopicOutput,
                tb_MQTT_ID, tb_MQTT_User, tb_MQTT_Password, chb_DHCP, chb_ETH_Activate, chb_MQTT_Activate};
                ClearControls(controls);
                // Запросы на считывание
                foreach (KeyValuePair<string, byte> param in ParamID.Where(p => p.Key.StartsWith("MQTT") || p.Key.StartsWith("ETH")))
                {
                    sendBuf[1] = param.Value;
                    USB_serial.Write(sendBuf, 0, sendBuf.Length);
                    Thread.Sleep(50);
                }
            }
            else
            {
                MessageBox.Show("Устройство не подключено", "ERROR");
            }
        }

        private async void bt_eth_send_Click(object sender, EventArgs e)
        {
            byte[] sendMessage;
            if (USB_serial.IsOpen)
            {
                USB_serial.DiscardInBuffer();

                // MQTT
                #region
                // MQTT Broker IP
                #region
                byte[] tmp = IPAddress.Parse(tb_BrokerIP.Text).GetAddressBytes();
                sendMessage = new byte[tmp.Length + 1];
                sendMessage[0] = ParamID["MQTT_Broker"];
                Array.Copy(tmp, 0, sendMessage, 1, tmp.Length);
                if (!await sendData(sendMessage)) return;
                #endregion

                // MQTT Broker Port
                #region
                tmp = BitConverter.GetBytes(UInt16.Parse(tb_BrokerPort.Text));
                sendMessage = new byte[tmp.Length + 1];
                sendMessage[0] = ParamID["MQTT_Port"];
                Array.Copy(tmp, 0, sendMessage, 1, tmp.Length);
                if (!await sendData(sendMessage)) return;
                #endregion

                // MQTT Output topic
                #region
                tmp = Encoding.ASCII.GetBytes(tb_MQQTTopicOutput.Text);              // MQTT Topic Output
                sendMessage = new byte[33];
                sendMessage[0] = ParamID["MQTT_TopicOut"];
                Array.Copy(tmp, 0, sendMessage, 1, tmp.Length);
                if (!await sendData(sendMessage)) return;
                #endregion

                // MQTT ID
                #region
                byte[] tmp_char = Encoding.ASCII.GetBytes(tb_MQTT_ID.Text);                 // MQTT ID
                sendMessage = new byte[33];
                sendMessage[0] = ParamID["MQTT_ID"];
                Array.Copy(tmp_char, 0, sendMessage, 1, tmp_char.Length);
                if (!await sendData(sendMessage)) return;
                #endregion

                // MQTT USER
                #region
                tmp_char = Encoding.ASCII.GetBytes(tb_MQTT_User.Text);                 // MQTT USER
                sendMessage = new byte[33];
                sendMessage[0] = ParamID["MQTT_User"];
                Array.Copy(tmp_char, 0, sendMessage, 1, tmp_char.Length);
                if (!await sendData(sendMessage)) return;
                #endregion

                // MQTT Password
                #region
                tmp_char = Encoding.ASCII.GetBytes(tb_MQTT_Password.Text);                 // MQTT Password
                sendMessage = new byte[33];
                sendMessage[0] = ParamID["MQTT_Password"];
                Array.Copy(tmp_char, 0, sendMessage, 1, tmp_char.Length);
                if (!await sendData(sendMessage)) return;
                #endregion

                // MQTT ACTIVATE FLAG
                #region
                sendMessage = new byte[2];
                sendMessage[0] = ParamID["MQTT_ACTIVATE"];
                sendMessage[1] = chb_MQTT_Activate.Checked ? (byte)1 : (byte)0;
                if (!await sendData(sendMessage)) return;
                #endregion

                #endregion

                // Ethernet 
                #region
                // Ethernet IP
                #region
                byte[] ip_bytes = IPAddress.Parse(tb_IP.Text).GetAddressBytes();
                sendMessage = new byte[ip_bytes.Length + 1];
                sendMessage[0] = ParamID["ETH_IP"];
                Array.Copy(ip_bytes, 0, sendMessage, 1, ip_bytes.Length);
                if (!await sendData(sendMessage)) return;
                #endregion

                // Ethernet Mask
                #region
                byte[] mask_bytes = IPAddress.Parse(tb_Mask.Text).GetAddressBytes();
                sendMessage = new byte[mask_bytes.Length + 1];
                sendMessage[0] = ParamID["ETH_Mask"];
                Array.Copy(mask_bytes, 0, sendMessage, 1, mask_bytes.Length);
                if (!await sendData(sendMessage)) return;
                #endregion

                // Ethernet Gateway IP
                #region
                byte[] gateway_bytes = IPAddress.Parse(tb_Gateway.Text).GetAddressBytes();
                sendMessage = new byte[gateway_bytes.Length + 1];
                sendMessage[0] = ParamID["ETH_Gateway"];
                Array.Copy(gateway_bytes, 0, sendMessage, 1, gateway_bytes.Length);
                if (!await sendData(sendMessage)) return;
                #endregion

                // Ethernet MAC
                #region
                byte[] MAC_bytes = PhysicalAddress.Parse(tb_MAC.Text.ToUpper()).GetAddressBytes();
                if ((MAC_bytes[0] & 1) == 1)
                {
                    MAC_bytes[0] &= 0xFE;
                    string[] _mac = new string[MAC_bytes.Length];
                    for (int i = 0; i < MAC_bytes.Length; i++)
                    {
                        _mac[i] = MAC_bytes[i].ToString("X");
                    }
                    String newMac = String.Join("-", _mac);
                    tb_MAC.Text = newMac;
                }
                sendMessage = new byte[MAC_bytes.Length + 1];
                sendMessage[0] = ParamID["ETH_MAC"];
                Array.Copy(MAC_bytes, 0, sendMessage, 1, MAC_bytes.Length);
                if (!await sendData(sendMessage)) return;
                #endregion

                // Ethernet DHCP
                #region
                sendMessage = new byte[2];
                sendMessage[0] = ParamID["ETH_DHCP"];
                sendMessage[1] = chb_DHCP.Checked ? (byte)1 : (byte)0;
                if (!await sendData(sendMessage)) return;
                #endregion

                // ETH ACTIVATE FLAG
                #region
                sendMessage = new byte[2];
                sendMessage[0] = ParamID["ETH_ACTIVATE"];
                sendMessage[1] = chb_ETH_Activate.Checked ? (byte)1 : (byte)0;
                if (!await sendData(sendMessage)) return;
                #endregion

                #endregion
                log_rtb1("Отправлены настройки Ethernet и MQTT");
                await sendCommandUpdateSettings();
            }
            else
            {
                MessageBox.Show("Устройство не подключено", "ERROR");
            }
        }

        private async Task<bool> sendData(byte[] inputData)
        {
            transmit_checked = false;
            byte[] sendBuf = new byte[2 + inputData.Length];
            sendBuf[0] = WRITECOMMAND;
            sendBuf[1] = (byte)inputData.Length;
            Array.Copy(inputData, 0, sendBuf, 2, inputData.Length);
            USB_serial.Write(sendBuf, 0, sendBuf.Length);
            return await waitAnswerCheck(5);
        }

        private async Task<bool> sendCommandUpdateSettings(byte command = UPDATESETTINGS)
        {
            // команда МК записать структуру со всеми настройками во внешнюю  флешку
            transmit_checked = false;
            USB_serial.Write(new byte[] { command }, 0, 1);
            return await waitAnswerCheck(5);
        }

        private async Task<bool> waitAnswerCheck(int waitTimeSec)
        {
            DateTime startTime = DateTime.Now;
            while (!transmit_checked)
            {
                await Task.Delay(10);
                if ((DateTime.Now - startTime).TotalSeconds > waitTimeSec)
                {
                    MessageBox.Show("Answer timeout");
                    return false;
                }
            }
            return true;
        }

        private void checkIPFormat(object sender, KeyPressEventArgs e)
        {
            if (char.IsDigit(e.KeyChar)) return;
            if (char.IsControl(e.KeyChar)) return;
            if (e.KeyChar == '.') return;
            e.Handled = true;
        }
    }
    public class TransparentPanel : Panel
    {
        protected override CreateParams CreateParams
        {
            get
            {
                CreateParams cp = base.CreateParams;
                cp.ExStyle |= 0x00000020; // WS_EX_TRANSPARENT
                return cp;
            }
        }
        protected override void OnPaintBackground(PaintEventArgs e)
        {
            // Перегружаем функцию, чтобы не рисовать фон
        }
    }


    public static class RichTextBoxExtensions
    {
        public static void AppendText(this RichTextBox box, string text, Color color)
        {
            box.SelectionStart = box.TextLength;
            box.SelectionLength = 0;
            box.SelectionColor = color;
            box.AppendText(text + "\n");
            box.SelectionColor = box.ForeColor;
            box.Refresh();
        }
        public static void AppendTextRefresh(this RichTextBox box, string text, Color color)
        {
            box.AppendText(text, color);
            box.Refresh();
        }

        public static void AppendTextRefresh(this RichTextBox box, string text)
        {
            AppendTextRefresh(box, text, Color.Black);
        }
    }
}

