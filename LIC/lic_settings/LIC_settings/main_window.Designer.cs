
namespace LIC_settings
{
    partial class Main_window
    {
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Main_window));
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tab_main = new System.Windows.Forms.TabPage();
            this.pb_EthStatus = new System.Windows.Forms.PictureBox();
            this.pb_loraStatus = new System.Windows.Forms.PictureBox();
            this.pb_zigbeeStatus = new System.Windows.Forms.PictureBox();
            this.panel_zigbee = new LIC_settings.TransparentPanel();
            this.panel_rs3 = new LIC_settings.TransparentPanel();
            this.panel_rs2 = new LIC_settings.TransparentPanel();
            this.panel_RS1 = new LIC_settings.TransparentPanel();
            this.image_status = new System.Windows.Forms.PictureBox();
            this.panel_lora = new LIC_settings.TransparentPanel();
            this.panel_main = new LIC_settings.TransparentPanel();
            this.panel_eth = new LIC_settings.TransparentPanel();
            this.panel_encryption = new LIC_settings.TransparentPanel();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.main_window_menu = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.readAllToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.writeAllToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.сепToolStripMenuItem = new System.Windows.Forms.ToolStripSeparator();
            this.loadAllToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveAllSettingsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.tab_frm = new System.Windows.Forms.TabPage();
            this.rebootUSB = new System.Windows.Forms.PictureBox();
            this.bt_connect = new System.Windows.Forms.PictureBox();
            this.bt_refreshPort = new System.Windows.Forms.PictureBox();
            this.bt_readMainParams = new System.Windows.Forms.PictureBox();
            this.bt_writeMainParams = new System.Windows.Forms.PictureBox();
            this.pb_bt_back1 = new System.Windows.Forms.PictureBox();
            this.tb_workTime = new System.Windows.Forms.TextBox();
            this.label26 = new System.Windows.Forms.Label();
            this.tb_stanbyTime = new System.Windows.Forms.TextBox();
            this.label25 = new System.Windows.Forms.Label();
            this.dt_DateOfProduction = new System.Windows.Forms.DateTimePicker();
            this.tb_ModuleSerialNumber = new System.Windows.Forms.TextBox();
            this.label22 = new System.Windows.Forms.Label();
            this.label23 = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.bt_sendFWMqtt = new System.Windows.Forms.PictureBox();
            this.bt_sendFrm = new System.Windows.Forms.PictureBox();
            this.bt_firmOpen = new System.Windows.Forms.PictureBox();
            this.bt_resetSettings = new System.Windows.Forms.Button();
            this.bt_mqttFwVersion = new System.Windows.Forms.Button();
            this.bt_reprogMqtt = new System.Windows.Forms.Button();
            this.cb_restartAfterDownload = new System.Windows.Forms.CheckBox();
            this.bt_mqttReboot = new System.Windows.Forms.Button();
            this.label35 = new System.Windows.Forms.Label();
            this.label34 = new System.Windows.Forms.Label();
            this.richTextBox1 = new System.Windows.Forms.RichTextBox();
            this.rtb1_menu = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.clear = new System.Windows.Forms.ToolStripMenuItem();
            this.tb_mqttTopic = new System.Windows.Forms.TextBox();
            this.tb_mqttServer = new System.Windows.Forms.TextBox();
            this.progress_firmLoad = new System.Windows.Forms.ProgressBar();
            this.l_portName = new System.Windows.Forms.Label();
            this.cb_portName = new System.Windows.Forms.ComboBox();
            this.tab_eth = new System.Windows.Forms.TabPage();
            this.bt_eth_read = new System.Windows.Forms.PictureBox();
            this.bt_eth_write = new System.Windows.Forms.PictureBox();
            this.pb_bt_back2 = new System.Windows.Forms.PictureBox();
            this.gb_MQTT = new System.Windows.Forms.GroupBox();
            this.chb_MQTT_Activate = new System.Windows.Forms.CheckBox();
            this.tb_MQTT_Password = new System.Windows.Forms.TextBox();
            this.tb_MQTT_User = new System.Windows.Forms.TextBox();
            this.label14 = new System.Windows.Forms.Label();
            this.tb_MQTT_ID = new System.Windows.Forms.TextBox();
            this.label13 = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.tb_MQQTTopicOutput = new System.Windows.Forms.TextBox();
            this.tb_BrokerPort = new System.Windows.Forms.TextBox();
            this.label10 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.tb_BrokerIP = new System.Windows.Forms.TextBox();
            this.label8 = new System.Windows.Forms.Label();
            this.gb_WebSettings = new System.Windows.Forms.GroupBox();
            this.chb_ETH_Activate = new System.Windows.Forms.CheckBox();
            this.chb_DHCP = new System.Windows.Forms.CheckBox();
            this.tb_IP = new System.Windows.Forms.TextBox();
            this.tb_MAC = new System.Windows.Forms.MaskedTextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.tb_Gateway = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.tb_Mask = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.tab_lora = new System.Windows.Forms.TabPage();
            this.cb_loraDatarate = new System.Windows.Forms.ComboBox();
            this.label41 = new System.Windows.Forms.Label();
            this.cb_loraMessageType = new System.Windows.Forms.ComboBox();
            this.bt_LoRa_read = new System.Windows.Forms.PictureBox();
            this.bt_LoRa_send = new System.Windows.Forms.PictureBox();
            this.pb_bt_back3 = new System.Windows.Forms.PictureBox();
            this.chb_LoRa_activate = new System.Windows.Forms.CheckBox();
            this.image_LoRa_logo = new System.Windows.Forms.PictureBox();
            this.chb_AutoDevEUI = new System.Windows.Forms.CheckBox();
            this.tb_LORA_AppPort = new System.Windows.Forms.NumericUpDown();
            this.tb_LORA_AppEUI = new System.Windows.Forms.MaskedTextBox();
            this.tb_LORA_DevEUI = new System.Windows.Forms.MaskedTextBox();
            this.tb_LORA_AppKey = new System.Windows.Forms.MaskedTextBox();
            this.chb_LORA_ADR = new System.Windows.Forms.CheckBox();
            this.label21 = new System.Windows.Forms.Label();
            this.label20 = new System.Windows.Forms.Label();
            this.label19 = new System.Windows.Forms.Label();
            this.label18 = new System.Windows.Forms.Label();
            this.label17 = new System.Windows.Forms.Label();
            this.tab_zigbee = new System.Windows.Forms.TabPage();
            this.pb_bt_back4 = new System.Windows.Forms.PictureBox();
            this.groupBox7 = new System.Windows.Forms.GroupBox();
            this.bt_zigbeeFrmGetFile = new System.Windows.Forms.PictureBox();
            this.bt_zigbeeFrmSend = new System.Windows.Forms.PictureBox();
            this.pb_zigbee = new System.Windows.Forms.ProgressBar();
            this.groupBox6 = new System.Windows.Forms.GroupBox();
            this.bt_zigbee_read = new System.Windows.Forms.PictureBox();
            this.bt_zigbee_send = new System.Windows.Forms.PictureBox();
            this.chb_ZigBee_Activate = new System.Windows.Forms.CheckBox();
            this.bt_zigbeeSensors = new System.Windows.Forms.Button();
            this.bt_zigbeeConnect = new System.Windows.Forms.Button();
            this.rtb_zigbee = new System.Windows.Forms.RichTextBox();
            this.image_zigbee_logo = new System.Windows.Forms.PictureBox();
            this.tab_rs1 = new System.Windows.Forms.TabPage();
            this.pb_bt_back5 = new System.Windows.Forms.PictureBox();
            this.gb_rs1_sensors = new System.Windows.Forms.GroupBox();
            this.lb_rs1_sensorsCount = new System.Windows.Forms.Label();
            this.bt_rs1_sensorsWrite = new System.Windows.Forms.PictureBox();
            this.bt_rs1_sensorsRead = new System.Windows.Forms.PictureBox();
            this.dg_rs1_sensors = new System.Windows.Forms.DataGridView();
            this.c_sensorType = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.c_reqPeriod = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.c_address = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.c_id = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.rs_sensors_menu = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.loadRSSensorsConfig = new System.Windows.Forms.ToolStripMenuItem();
            this.saveRSSensorsConfig = new System.Windows.Forms.ToolStripMenuItem();
            this.saveAllToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.sepToolStripMenuItem = new System.Windows.Forms.ToolStripSeparator();
            this.reqMQTTToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.addSensorMQTTToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.delSensorMQTTToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.delAllMQTTToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.rrToolStripMenuItem = new System.Windows.Forms.ToolStripSeparator();
            this.deleteRowToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.clear_rsSensorsTable = new System.Windows.Forms.ToolStripMenuItem();
            this.gb_rs1_settings = new System.Windows.Forms.GroupBox();
            this.rs_settings_menu = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.readRSSettingsMQTTToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.writeRSSettingsMQTTToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.label36 = new System.Windows.Forms.Label();
            this.num_rs1Errors = new System.Windows.Forms.NumericUpDown();
            this.label11 = new System.Windows.Forms.Label();
            this.num_rs1Delay = new System.Windows.Forms.NumericUpDown();
            this.bt_rs1SettingsWrite = new System.Windows.Forms.PictureBox();
            this.bt_rs1SettingsRead = new System.Windows.Forms.PictureBox();
            this.chb_rs1_activate = new System.Windows.Forms.CheckBox();
            this.cb_rs1_stopbits = new System.Windows.Forms.ComboBox();
            this.cb_rs1_parity = new System.Windows.Forms.ComboBox();
            this.cb_rs1_databits = new System.Windows.Forms.ComboBox();
            this.cb_rs1_baudrate = new System.Windows.Forms.ComboBox();
            this.label15 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.tab_rs2 = new System.Windows.Forms.TabPage();
            this.pb_bt_back6 = new System.Windows.Forms.PictureBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.lb_rs2_sensorsCount = new System.Windows.Forms.Label();
            this.bt_rs2_sensorsWrite = new System.Windows.Forms.PictureBox();
            this.bt_rs2_sensorsRead = new System.Windows.Forms.PictureBox();
            this.dg_rs2_sensors = new System.Windows.Forms.DataGridView();
            this.c_rs2_name = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.c_rs2_pollPeriod = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.c_rs2_address = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.c_rs2_id = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.gb_rs2_settings = new System.Windows.Forms.GroupBox();
            this.label37 = new System.Windows.Forms.Label();
            this.num_rs2Errors = new System.Windows.Forms.NumericUpDown();
            this.label38 = new System.Windows.Forms.Label();
            this.num_rs2Delay = new System.Windows.Forms.NumericUpDown();
            this.bt_rs2SettingsWrite = new System.Windows.Forms.PictureBox();
            this.bt_rs2SettingsRead = new System.Windows.Forms.PictureBox();
            this.chb_rs2_activate = new System.Windows.Forms.CheckBox();
            this.cb_rs2_stopbits = new System.Windows.Forms.ComboBox();
            this.cb_rs2_parity = new System.Windows.Forms.ComboBox();
            this.cb_rs2_databits = new System.Windows.Forms.ComboBox();
            this.cb_rs2_baudrate = new System.Windows.Forms.ComboBox();
            this.label24 = new System.Windows.Forms.Label();
            this.label27 = new System.Windows.Forms.Label();
            this.label28 = new System.Windows.Forms.Label();
            this.label29 = new System.Windows.Forms.Label();
            this.tab_rs3 = new System.Windows.Forms.TabPage();
            this.pb_bt_back7 = new System.Windows.Forms.PictureBox();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.lb_rs3_sensorsCount = new System.Windows.Forms.Label();
            this.bt_rs3_sensorsWrite = new System.Windows.Forms.PictureBox();
            this.bt_rs3_sensorsRead = new System.Windows.Forms.PictureBox();
            this.dg_rs3_sensors = new System.Windows.Forms.DataGridView();
            this.c_rs3_name = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.c_rs3_pollPeriod = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.c_rs3_address = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.c_rs3_id = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.gb_rs3_settings = new System.Windows.Forms.GroupBox();
            this.label39 = new System.Windows.Forms.Label();
            this.num_rs3Errors = new System.Windows.Forms.NumericUpDown();
            this.label40 = new System.Windows.Forms.Label();
            this.num_rs3Delay = new System.Windows.Forms.NumericUpDown();
            this.bt_rs3SettingsWrite = new System.Windows.Forms.PictureBox();
            this.bt_rs3SettingsRead = new System.Windows.Forms.PictureBox();
            this.chb_rs3_activate = new System.Windows.Forms.CheckBox();
            this.cb_rs3_stopbits = new System.Windows.Forms.ComboBox();
            this.cb_rs3_parity = new System.Windows.Forms.ComboBox();
            this.cb_rs3_databits = new System.Windows.Forms.ComboBox();
            this.cb_rs3_baudrate = new System.Windows.Forms.ComboBox();
            this.label30 = new System.Windows.Forms.Label();
            this.label31 = new System.Windows.Forms.Label();
            this.label32 = new System.Windows.Forms.Label();
            this.label33 = new System.Windows.Forms.Label();
            this.tab_encryption = new System.Windows.Forms.TabPage();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.bt_encWrite = new System.Windows.Forms.PictureBox();
            this.chb_enc_hard = new System.Windows.Forms.CheckBox();
            this.bt_encRead = new System.Windows.Forms.PictureBox();
            this.chb_enc_soft = new System.Windows.Forms.CheckBox();
            this.bt_back_8 = new System.Windows.Forms.PictureBox();
            this.USB_serial = new System.IO.Ports.SerialPort(this.components);
            this.serialPortControl = new System.Windows.Forms.Timer(this.components);
            this.toolTip = new System.Windows.Forms.ToolTip(this.components);
            this.tabControl1.SuspendLayout();
            this.tab_main.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pb_EthStatus)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pb_loraStatus)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pb_zigbeeStatus)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.image_status)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.main_window_menu.SuspendLayout();
            this.tab_frm.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.rebootUSB)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.bt_connect)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.bt_refreshPort)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.bt_readMainParams)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.bt_writeMainParams)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pb_bt_back1)).BeginInit();
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.bt_sendFWMqtt)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.bt_sendFrm)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.bt_firmOpen)).BeginInit();
            this.rtb1_menu.SuspendLayout();
            this.tab_eth.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.bt_eth_read)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.bt_eth_write)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pb_bt_back2)).BeginInit();
            this.gb_MQTT.SuspendLayout();
            this.gb_WebSettings.SuspendLayout();
            this.tab_lora.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.bt_LoRa_read)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.bt_LoRa_send)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pb_bt_back3)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.image_LoRa_logo)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.tb_LORA_AppPort)).BeginInit();
            this.tab_zigbee.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pb_bt_back4)).BeginInit();
            this.groupBox7.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.bt_zigbeeFrmGetFile)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.bt_zigbeeFrmSend)).BeginInit();
            this.groupBox6.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.bt_zigbee_read)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.bt_zigbee_send)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.image_zigbee_logo)).BeginInit();
            this.tab_rs1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pb_bt_back5)).BeginInit();
            this.gb_rs1_sensors.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.bt_rs1_sensorsWrite)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.bt_rs1_sensorsRead)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dg_rs1_sensors)).BeginInit();
            this.rs_sensors_menu.SuspendLayout();
            this.gb_rs1_settings.SuspendLayout();
            this.rs_settings_menu.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.num_rs1Errors)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.num_rs1Delay)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.bt_rs1SettingsWrite)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.bt_rs1SettingsRead)).BeginInit();
            this.tab_rs2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pb_bt_back6)).BeginInit();
            this.groupBox2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.bt_rs2_sensorsWrite)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.bt_rs2_sensorsRead)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dg_rs2_sensors)).BeginInit();
            this.gb_rs2_settings.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.num_rs2Errors)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.num_rs2Delay)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.bt_rs2SettingsWrite)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.bt_rs2SettingsRead)).BeginInit();
            this.tab_rs3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pb_bt_back7)).BeginInit();
            this.groupBox4.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.bt_rs3_sensorsWrite)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.bt_rs3_sensorsRead)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dg_rs3_sensors)).BeginInit();
            this.gb_rs3_settings.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.num_rs3Errors)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.num_rs3Delay)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.bt_rs3SettingsWrite)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.bt_rs3SettingsRead)).BeginInit();
            this.tab_encryption.SuspendLayout();
            this.groupBox3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.bt_encWrite)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.bt_encRead)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.bt_back_8)).BeginInit();
            this.SuspendLayout();
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tab_main);
            this.tabControl1.Controls.Add(this.tab_frm);
            this.tabControl1.Controls.Add(this.tab_eth);
            this.tabControl1.Controls.Add(this.tab_lora);
            this.tabControl1.Controls.Add(this.tab_zigbee);
            this.tabControl1.Controls.Add(this.tab_rs1);
            this.tabControl1.Controls.Add(this.tab_rs2);
            this.tabControl1.Controls.Add(this.tab_rs3);
            this.tabControl1.Controls.Add(this.tab_encryption);
            this.tabControl1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tabControl1.ItemSize = new System.Drawing.Size(0, 20);
            this.tabControl1.Location = new System.Drawing.Point(0, 0);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(434, 591);
            this.tabControl1.TabIndex = 5;
            // 
            // tab_main
            // 
            this.tab_main.Controls.Add(this.pb_EthStatus);
            this.tab_main.Controls.Add(this.pb_loraStatus);
            this.tab_main.Controls.Add(this.pb_zigbeeStatus);
            this.tab_main.Controls.Add(this.panel_zigbee);
            this.tab_main.Controls.Add(this.panel_rs3);
            this.tab_main.Controls.Add(this.panel_rs2);
            this.tab_main.Controls.Add(this.panel_RS1);
            this.tab_main.Controls.Add(this.image_status);
            this.tab_main.Controls.Add(this.panel_lora);
            this.tab_main.Controls.Add(this.panel_main);
            this.tab_main.Controls.Add(this.panel_eth);
            this.tab_main.Controls.Add(this.panel_encryption);
            this.tab_main.Controls.Add(this.pictureBox1);
            this.tab_main.Location = new System.Drawing.Point(4, 24);
            this.tab_main.Name = "tab_main";
            this.tab_main.Padding = new System.Windows.Forms.Padding(3);
            this.tab_main.Size = new System.Drawing.Size(426, 563);
            this.tab_main.TabIndex = 0;
            this.tab_main.Text = "Главная";
            this.tab_main.UseVisualStyleBackColor = true;
            // 
            // pb_EthStatus
            // 
            this.pb_EthStatus.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
            this.pb_EthStatus.BackColor = System.Drawing.Color.White;
            this.pb_EthStatus.Cursor = System.Windows.Forms.Cursors.Hand;
            this.pb_EthStatus.Location = new System.Drawing.Point(93, 433);
            this.pb_EthStatus.Name = "pb_EthStatus";
            this.pb_EthStatus.Size = new System.Drawing.Size(23, 23);
            this.pb_EthStatus.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.pb_EthStatus.TabIndex = 13;
            this.pb_EthStatus.TabStop = false;
            // 
            // pb_loraStatus
            // 
            this.pb_loraStatus.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
            this.pb_loraStatus.BackColor = System.Drawing.Color.White;
            this.pb_loraStatus.Cursor = System.Windows.Forms.Cursors.Hand;
            this.pb_loraStatus.Location = new System.Drawing.Point(227, 120);
            this.pb_loraStatus.Name = "pb_loraStatus";
            this.pb_loraStatus.Size = new System.Drawing.Size(23, 23);
            this.pb_loraStatus.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.pb_loraStatus.TabIndex = 12;
            this.pb_loraStatus.TabStop = false;
            // 
            // pb_zigbeeStatus
            // 
            this.pb_zigbeeStatus.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
            this.pb_zigbeeStatus.BackColor = System.Drawing.Color.White;
            this.pb_zigbeeStatus.Cursor = System.Windows.Forms.Cursors.Hand;
            this.pb_zigbeeStatus.Location = new System.Drawing.Point(93, 120);
            this.pb_zigbeeStatus.Name = "pb_zigbeeStatus";
            this.pb_zigbeeStatus.Size = new System.Drawing.Size(23, 23);
            this.pb_zigbeeStatus.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.pb_zigbeeStatus.TabIndex = 11;
            this.pb_zigbeeStatus.TabStop = false;
            // 
            // panel_zigbee
            // 
            this.panel_zigbee.Cursor = System.Windows.Forms.Cursors.Hand;
            this.panel_zigbee.Location = new System.Drawing.Point(128, 133);
            this.panel_zigbee.Name = "panel_zigbee";
            this.panel_zigbee.Size = new System.Drawing.Size(58, 32);
            this.panel_zigbee.TabIndex = 10;
            this.panel_zigbee.Click += new System.EventHandler(this.panel_zigbee_Click);
            // 
            // panel_rs3
            // 
            this.panel_rs3.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.panel_rs3.Cursor = System.Windows.Forms.Cursors.Hand;
            this.panel_rs3.Location = new System.Drawing.Point(361, 91);
            this.panel_rs3.Name = "panel_rs3";
            this.panel_rs3.Size = new System.Drawing.Size(57, 90);
            this.panel_rs3.TabIndex = 9;
            this.panel_rs3.Click += new System.EventHandler(this.panel_rs3_Click);
            // 
            // panel_rs2
            // 
            this.panel_rs2.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.panel_rs2.Cursor = System.Windows.Forms.Cursors.Hand;
            this.panel_rs2.Location = new System.Drawing.Point(361, 221);
            this.panel_rs2.Name = "panel_rs2";
            this.panel_rs2.Size = new System.Drawing.Size(57, 100);
            this.panel_rs2.TabIndex = 8;
            this.panel_rs2.Click += new System.EventHandler(this.panel_rs2_Click);
            // 
            // panel_RS1
            // 
            this.panel_RS1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.panel_RS1.Cursor = System.Windows.Forms.Cursors.Hand;
            this.panel_RS1.Location = new System.Drawing.Point(361, 357);
            this.panel_RS1.Name = "panel_RS1";
            this.panel_RS1.Size = new System.Drawing.Size(57, 94);
            this.panel_RS1.TabIndex = 7;
            this.panel_RS1.Click += new System.EventHandler(this.panel_RS1_Click);
            // 
            // image_status
            // 
            this.image_status.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
            this.image_status.BackColor = System.Drawing.Color.White;
            this.image_status.Cursor = System.Windows.Forms.Cursors.Hand;
            this.image_status.Location = new System.Drawing.Point(93, 385);
            this.image_status.Name = "image_status";
            this.image_status.Size = new System.Drawing.Size(23, 23);
            this.image_status.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.image_status.TabIndex = 6;
            this.image_status.TabStop = false;
            this.image_status.Click += new System.EventHandler(this.image_status_Click);
            // 
            // panel_lora
            // 
            this.panel_lora.Cursor = System.Windows.Forms.Cursors.Hand;
            this.panel_lora.Location = new System.Drawing.Point(253, 133);
            this.panel_lora.Name = "panel_lora";
            this.panel_lora.Size = new System.Drawing.Size(68, 32);
            this.panel_lora.TabIndex = 5;
            this.panel_lora.Click += new System.EventHandler(this.panel_lora_Click);
            // 
            // panel_main
            // 
            this.panel_main.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)));
            this.panel_main.Cursor = System.Windows.Forms.Cursors.Hand;
            this.panel_main.Location = new System.Drawing.Point(253, 384);
            this.panel_main.Name = "panel_main";
            this.panel_main.Size = new System.Drawing.Size(77, 83);
            this.panel_main.TabIndex = 4;
            this.panel_main.Click += new System.EventHandler(this.panel_main_Click);
            // 
            // panel_eth
            // 
            this.panel_eth.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
            this.panel_eth.Cursor = System.Windows.Forms.Cursors.Hand;
            this.panel_eth.Location = new System.Drawing.Point(85, 514);
            this.panel_eth.Name = "panel_eth";
            this.panel_eth.Size = new System.Drawing.Size(101, 49);
            this.panel_eth.TabIndex = 3;
            this.panel_eth.Click += new System.EventHandler(this.panel_eth_Click);
            // 
            // panel_encryption
            // 
            this.panel_encryption.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)));
            this.panel_encryption.Cursor = System.Windows.Forms.Cursors.Hand;
            this.panel_encryption.Location = new System.Drawing.Point(173, 248);
            this.panel_encryption.Name = "panel_encryption";
            this.panel_encryption.Size = new System.Drawing.Size(77, 73);
            this.panel_encryption.TabIndex = 2;
            this.panel_encryption.Click += new System.EventHandler(this.panel_encryption_Click);
            // 
            // pictureBox1
            // 
            this.pictureBox1.ContextMenuStrip = this.main_window_menu;
            this.pictureBox1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pictureBox1.Image = global::LIC_settings.Properties.Resources.face_panel;
            this.pictureBox1.InitialImage = null;
            this.pictureBox1.Location = new System.Drawing.Point(3, 3);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(420, 557);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.CenterImage;
            this.pictureBox1.TabIndex = 1;
            this.pictureBox1.TabStop = false;
            this.pictureBox1.MouseDown += new System.Windows.Forms.MouseEventHandler(this.pictureBox1_MouseDown);
            this.pictureBox1.MouseMove += new System.Windows.Forms.MouseEventHandler(this.pictureBox1_MouseMove);
            this.pictureBox1.MouseUp += new System.Windows.Forms.MouseEventHandler(this.pictureBox1_MouseUp);
            // 
            // main_window_menu
            // 
            this.main_window_menu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.readAllToolStripMenuItem,
            this.writeAllToolStripMenuItem,
            this.сепToolStripMenuItem,
            this.loadAllToolStripMenuItem,
            this.saveAllSettingsToolStripMenuItem});
            this.main_window_menu.Name = "main_window_menu";
            this.main_window_menu.Size = new System.Drawing.Size(243, 98);
            // 
            // readAllToolStripMenuItem
            // 
            this.readAllToolStripMenuItem.Image = global::LIC_settings.Properties.Resources.read;
            this.readAllToolStripMenuItem.Name = "readAllToolStripMenuItem";
            this.readAllToolStripMenuItem.Size = new System.Drawing.Size(242, 22);
            this.readAllToolStripMenuItem.Text = "Считать все настройки с ОУ";
            this.readAllToolStripMenuItem.Click += new System.EventHandler(this.readAllToolStripMenuItem_Click);
            // 
            // writeAllToolStripMenuItem
            // 
            this.writeAllToolStripMenuItem.Image = global::LIC_settings.Properties.Resources.write;
            this.writeAllToolStripMenuItem.Name = "writeAllToolStripMenuItem";
            this.writeAllToolStripMenuItem.Size = new System.Drawing.Size(242, 22);
            this.writeAllToolStripMenuItem.Text = "Записать все настройки в ОУ";
            this.writeAllToolStripMenuItem.Click += new System.EventHandler(this.writeAllToolStripMenuItem_Click);
            // 
            // сепToolStripMenuItem
            // 
            this.сепToolStripMenuItem.Name = "сепToolStripMenuItem";
            this.сепToolStripMenuItem.Size = new System.Drawing.Size(239, 6);
            // 
            // loadAllToolStripMenuItem
            // 
            this.loadAllToolStripMenuItem.Image = global::LIC_settings.Properties.Resources.open;
            this.loadAllToolStripMenuItem.Name = "loadAllToolStripMenuItem";
            this.loadAllToolStripMenuItem.Size = new System.Drawing.Size(242, 22);
            this.loadAllToolStripMenuItem.Text = "Загрузить настройки из файла";
            this.loadAllToolStripMenuItem.Click += new System.EventHandler(this.loadAllToolStripMenuItem_Click);
            // 
            // saveAllSettingsToolStripMenuItem
            // 
            this.saveAllSettingsToolStripMenuItem.Image = global::LIC_settings.Properties.Resources.save;
            this.saveAllSettingsToolStripMenuItem.Name = "saveAllSettingsToolStripMenuItem";
            this.saveAllSettingsToolStripMenuItem.Size = new System.Drawing.Size(242, 22);
            this.saveAllSettingsToolStripMenuItem.Text = "Сохранить настройки в файл";
            this.saveAllSettingsToolStripMenuItem.Click += new System.EventHandler(this.saveAllSettingsToolStripMenuItem_Click);
            // 
            // tab_frm
            // 
            this.tab_frm.BackColor = System.Drawing.Color.WhiteSmoke;
            this.tab_frm.Controls.Add(this.rebootUSB);
            this.tab_frm.Controls.Add(this.bt_connect);
            this.tab_frm.Controls.Add(this.bt_refreshPort);
            this.tab_frm.Controls.Add(this.bt_readMainParams);
            this.tab_frm.Controls.Add(this.bt_writeMainParams);
            this.tab_frm.Controls.Add(this.pb_bt_back1);
            this.tab_frm.Controls.Add(this.tb_workTime);
            this.tab_frm.Controls.Add(this.label26);
            this.tab_frm.Controls.Add(this.tb_stanbyTime);
            this.tab_frm.Controls.Add(this.label25);
            this.tab_frm.Controls.Add(this.dt_DateOfProduction);
            this.tab_frm.Controls.Add(this.tb_ModuleSerialNumber);
            this.tab_frm.Controls.Add(this.label22);
            this.tab_frm.Controls.Add(this.label23);
            this.tab_frm.Controls.Add(this.groupBox1);
            this.tab_frm.Controls.Add(this.l_portName);
            this.tab_frm.Controls.Add(this.cb_portName);
            this.tab_frm.Location = new System.Drawing.Point(4, 24);
            this.tab_frm.Name = "tab_frm";
            this.tab_frm.Padding = new System.Windows.Forms.Padding(3);
            this.tab_frm.Size = new System.Drawing.Size(426, 563);
            this.tab_frm.TabIndex = 1;
            this.tab_frm.Tag = "";
            this.tab_frm.Text = "Прошивка";
            this.tab_frm.Enter += new System.EventHandler(this.tab_frm_Enter);
            // 
            // rebootUSB
            // 
            this.rebootUSB.Cursor = System.Windows.Forms.Cursors.Hand;
            this.rebootUSB.Image = global::LIC_settings.Properties.Resources.bt_reboot;
            this.rebootUSB.Location = new System.Drawing.Point(292, 156);
            this.rebootUSB.Name = "rebootUSB";
            this.rebootUSB.Size = new System.Drawing.Size(120, 25);
            this.rebootUSB.SizeMode = System.Windows.Forms.PictureBoxSizeMode.CenterImage;
            this.rebootUSB.TabIndex = 57;
            this.rebootUSB.TabStop = false;
            this.rebootUSB.Click += new System.EventHandler(this.rebootUSB_Click);
            this.rebootUSB.MouseDown += new System.Windows.Forms.MouseEventHandler(this.bt_MouseDown);
            this.rebootUSB.MouseLeave += new System.EventHandler(this.bt_MouseLeave);
            this.rebootUSB.MouseUp += new System.Windows.Forms.MouseEventHandler(this.bt_MouseUp);
            // 
            // bt_connect
            // 
            this.bt_connect.BackColor = System.Drawing.Color.WhiteSmoke;
            this.bt_connect.Cursor = System.Windows.Forms.Cursors.Hand;
            this.bt_connect.Image = global::LIC_settings.Properties.Resources.bt_connect;
            this.bt_connect.Location = new System.Drawing.Point(312, 20);
            this.bt_connect.Name = "bt_connect";
            this.bt_connect.Size = new System.Drawing.Size(100, 25);
            this.bt_connect.SizeMode = System.Windows.Forms.PictureBoxSizeMode.CenterImage;
            this.bt_connect.TabIndex = 55;
            this.bt_connect.TabStop = false;
            this.bt_connect.Tag = "Connect";
            this.bt_connect.Click += new System.EventHandler(this.bt_connect_Click);
            this.bt_connect.MouseDown += new System.Windows.Forms.MouseEventHandler(this.bt_MouseDown);
            this.bt_connect.MouseLeave += new System.EventHandler(this.bt_MouseLeave);
            this.bt_connect.MouseUp += new System.Windows.Forms.MouseEventHandler(this.bt_MouseUp);
            // 
            // bt_refreshPort
            // 
            this.bt_refreshPort.BackColor = System.Drawing.Color.WhiteSmoke;
            this.bt_refreshPort.Cursor = System.Windows.Forms.Cursors.Hand;
            this.bt_refreshPort.Image = global::LIC_settings.Properties.Resources.bt_refresh;
            this.bt_refreshPort.Location = new System.Drawing.Point(260, 22);
            this.bt_refreshPort.Name = "bt_refreshPort";
            this.bt_refreshPort.Size = new System.Drawing.Size(28, 22);
            this.bt_refreshPort.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.bt_refreshPort.TabIndex = 54;
            this.bt_refreshPort.TabStop = false;
            this.bt_refreshPort.Click += new System.EventHandler(this.bt_refreshPort_Click);
            this.bt_refreshPort.MouseDown += new System.Windows.Forms.MouseEventHandler(this.bt_MouseDown);
            this.bt_refreshPort.MouseLeave += new System.EventHandler(this.bt_MouseLeave);
            this.bt_refreshPort.MouseUp += new System.Windows.Forms.MouseEventHandler(this.bt_MouseUp);
            // 
            // bt_readMainParams
            // 
            this.bt_readMainParams.BackColor = System.Drawing.Color.WhiteSmoke;
            this.bt_readMainParams.Cursor = System.Windows.Forms.Cursors.Hand;
            this.bt_readMainParams.Image = global::LIC_settings.Properties.Resources.bt_read;
            this.bt_readMainParams.Location = new System.Drawing.Point(332, 78);
            this.bt_readMainParams.Name = "bt_readMainParams";
            this.bt_readMainParams.Size = new System.Drawing.Size(80, 25);
            this.bt_readMainParams.SizeMode = System.Windows.Forms.PictureBoxSizeMode.CenterImage;
            this.bt_readMainParams.TabIndex = 53;
            this.bt_readMainParams.TabStop = false;
            this.bt_readMainParams.Click += new System.EventHandler(this.bt_readMainParams_Click);
            this.bt_readMainParams.MouseDown += new System.Windows.Forms.MouseEventHandler(this.bt_MouseDown);
            this.bt_readMainParams.MouseLeave += new System.EventHandler(this.bt_MouseLeave);
            this.bt_readMainParams.MouseUp += new System.Windows.Forms.MouseEventHandler(this.bt_MouseUp);
            // 
            // bt_writeMainParams
            // 
            this.bt_writeMainParams.BackColor = System.Drawing.Color.WhiteSmoke;
            this.bt_writeMainParams.Cursor = System.Windows.Forms.Cursors.Hand;
            this.bt_writeMainParams.Image = global::LIC_settings.Properties.Resources.bt_write;
            this.bt_writeMainParams.Location = new System.Drawing.Point(332, 109);
            this.bt_writeMainParams.Name = "bt_writeMainParams";
            this.bt_writeMainParams.Size = new System.Drawing.Size(80, 25);
            this.bt_writeMainParams.SizeMode = System.Windows.Forms.PictureBoxSizeMode.CenterImage;
            this.bt_writeMainParams.TabIndex = 52;
            this.bt_writeMainParams.TabStop = false;
            this.bt_writeMainParams.Visible = false;
            this.bt_writeMainParams.Click += new System.EventHandler(this.bt_writeMainParams_Click);
            this.bt_writeMainParams.MouseDown += new System.Windows.Forms.MouseEventHandler(this.bt_MouseDown);
            this.bt_writeMainParams.MouseLeave += new System.EventHandler(this.bt_MouseLeave);
            this.bt_writeMainParams.MouseUp += new System.Windows.Forms.MouseEventHandler(this.bt_MouseUp);
            // 
            // pb_bt_back1
            // 
            this.pb_bt_back1.Cursor = System.Windows.Forms.Cursors.Hand;
            this.pb_bt_back1.Image = global::LIC_settings.Properties.Resources.bt_back;
            this.pb_bt_back1.Location = new System.Drawing.Point(8, 8);
            this.pb_bt_back1.Name = "pb_bt_back1";
            this.pb_bt_back1.Size = new System.Drawing.Size(40, 40);
            this.pb_bt_back1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.pb_bt_back1.TabIndex = 51;
            this.pb_bt_back1.TabStop = false;
            this.pb_bt_back1.Click += new System.EventHandler(this.bt_back1_Click);
            // 
            // tb_workTime
            // 
            this.tb_workTime.Location = new System.Drawing.Point(149, 161);
            this.tb_workTime.Name = "tb_workTime";
            this.tb_workTime.Size = new System.Drawing.Size(121, 20);
            this.tb_workTime.TabIndex = 6;
            this.tb_workTime.Text = "10";
            this.tb_workTime.Visible = false;
            // 
            // label26
            // 
            this.label26.AutoSize = true;
            this.label26.Font = new System.Drawing.Font("Arial Narrow", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label26.Location = new System.Drawing.Point(12, 161);
            this.label26.Margin = new System.Windows.Forms.Padding(3, 15, 3, 0);
            this.label26.Name = "label26";
            this.label26.Size = new System.Drawing.Size(119, 20);
            this.label26.TabIndex = 49;
            this.label26.Text = "Время работы, с";
            this.label26.Visible = false;
            // 
            // tb_stanbyTime
            // 
            this.tb_stanbyTime.Location = new System.Drawing.Point(149, 135);
            this.tb_stanbyTime.Name = "tb_stanbyTime";
            this.tb_stanbyTime.Size = new System.Drawing.Size(121, 20);
            this.tb_stanbyTime.TabIndex = 5;
            this.tb_stanbyTime.Text = "60";
            this.tb_stanbyTime.Visible = false;
            // 
            // label25
            // 
            this.label25.AutoSize = true;
            this.label25.Font = new System.Drawing.Font("Arial Narrow", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label25.Location = new System.Drawing.Point(12, 135);
            this.label25.Margin = new System.Windows.Forms.Padding(3, 15, 3, 0);
            this.label25.Name = "label25";
            this.label25.Size = new System.Drawing.Size(113, 20);
            this.label25.TabIndex = 47;
            this.label25.Text = "Время Stanby, c";
            this.label25.Visible = false;
            // 
            // dt_DateOfProduction
            // 
            this.dt_DateOfProduction.Enabled = false;
            this.dt_DateOfProduction.Location = new System.Drawing.Point(149, 83);
            this.dt_DateOfProduction.MaxDate = new System.DateTime(2050, 12, 31, 0, 0, 0, 0);
            this.dt_DateOfProduction.MinDate = new System.DateTime(2021, 1, 1, 0, 0, 0, 0);
            this.dt_DateOfProduction.Name = "dt_DateOfProduction";
            this.dt_DateOfProduction.Size = new System.Drawing.Size(121, 20);
            this.dt_DateOfProduction.TabIndex = 3;
            // 
            // tb_ModuleSerialNumber
            // 
            this.tb_ModuleSerialNumber.Location = new System.Drawing.Point(149, 109);
            this.tb_ModuleSerialNumber.Name = "tb_ModuleSerialNumber";
            this.tb_ModuleSerialNumber.ReadOnly = true;
            this.tb_ModuleSerialNumber.Size = new System.Drawing.Size(121, 20);
            this.tb_ModuleSerialNumber.TabIndex = 4;
            this.tb_ModuleSerialNumber.Text = "2208000";
            // 
            // label22
            // 
            this.label22.AutoSize = true;
            this.label22.Font = new System.Drawing.Font("Arial Narrow", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label22.Location = new System.Drawing.Point(12, 109);
            this.label22.Margin = new System.Windows.Forms.Padding(3, 15, 3, 0);
            this.label22.Name = "label22";
            this.label22.Size = new System.Drawing.Size(122, 20);
            this.label22.TabIndex = 42;
            this.label22.Text = "Серийный номер";
            // 
            // label23
            // 
            this.label23.AutoSize = true;
            this.label23.Font = new System.Drawing.Font("Arial Narrow", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label23.Location = new System.Drawing.Point(12, 83);
            this.label23.Margin = new System.Windows.Forms.Padding(3, 15, 3, 0);
            this.label23.Name = "label23";
            this.label23.Size = new System.Drawing.Size(131, 20);
            this.label23.TabIndex = 41;
            this.label23.Text = "Дата изготовления";
            // 
            // groupBox1
            // 
            this.groupBox1.BackColor = System.Drawing.Color.White;
            this.groupBox1.Controls.Add(this.bt_sendFWMqtt);
            this.groupBox1.Controls.Add(this.bt_sendFrm);
            this.groupBox1.Controls.Add(this.bt_firmOpen);
            this.groupBox1.Controls.Add(this.bt_resetSettings);
            this.groupBox1.Controls.Add(this.bt_mqttFwVersion);
            this.groupBox1.Controls.Add(this.bt_reprogMqtt);
            this.groupBox1.Controls.Add(this.cb_restartAfterDownload);
            this.groupBox1.Controls.Add(this.bt_mqttReboot);
            this.groupBox1.Controls.Add(this.label35);
            this.groupBox1.Controls.Add(this.label34);
            this.groupBox1.Controls.Add(this.richTextBox1);
            this.groupBox1.Controls.Add(this.tb_mqttTopic);
            this.groupBox1.Controls.Add(this.tb_mqttServer);
            this.groupBox1.Controls.Add(this.progress_firmLoad);
            this.groupBox1.Location = new System.Drawing.Point(7, 199);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(412, 361);
            this.groupBox1.TabIndex = 16;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Обновление ПО";
            // 
            // bt_sendFWMqtt
            // 
            this.bt_sendFWMqtt.Cursor = System.Windows.Forms.Cursors.Hand;
            this.bt_sendFWMqtt.Image = ((System.Drawing.Image)(resources.GetObject("bt_sendFWMqtt.Image")));
            this.bt_sendFWMqtt.Location = new System.Drawing.Point(9, 77);
            this.bt_sendFWMqtt.Name = "bt_sendFWMqtt";
            this.bt_sendFWMqtt.Size = new System.Drawing.Size(160, 25);
            this.bt_sendFWMqtt.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.bt_sendFWMqtt.TabIndex = 21;
            this.bt_sendFWMqtt.TabStop = false;
            this.toolTip.SetToolTip(this.bt_sendFWMqtt, "Проверь MQTT топик!");
            this.bt_sendFWMqtt.Click += new System.EventHandler(this.bt_sendFWMqtt_Click);
            this.bt_sendFWMqtt.MouseDown += new System.Windows.Forms.MouseEventHandler(this.bt_MouseDown);
            this.bt_sendFWMqtt.MouseLeave += new System.EventHandler(this.bt_MouseLeave);
            this.bt_sendFWMqtt.MouseUp += new System.Windows.Forms.MouseEventHandler(this.bt_MouseUp);
            // 
            // bt_sendFrm
            // 
            this.bt_sendFrm.Cursor = System.Windows.Forms.Cursors.Hand;
            this.bt_sendFrm.Image = ((System.Drawing.Image)(resources.GetObject("bt_sendFrm.Image")));
            this.bt_sendFrm.Location = new System.Drawing.Point(9, 48);
            this.bt_sendFrm.Name = "bt_sendFrm";
            this.bt_sendFrm.Size = new System.Drawing.Size(160, 25);
            this.bt_sendFrm.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.bt_sendFrm.TabIndex = 20;
            this.bt_sendFrm.TabStop = false;
            this.bt_sendFrm.Click += new System.EventHandler(this.bt_sendFrm_Click);
            this.bt_sendFrm.MouseDown += new System.Windows.Forms.MouseEventHandler(this.bt_MouseDown);
            this.bt_sendFrm.MouseLeave += new System.EventHandler(this.bt_MouseLeave);
            this.bt_sendFrm.MouseUp += new System.Windows.Forms.MouseEventHandler(this.bt_MouseUp);
            // 
            // bt_firmOpen
            // 
            this.bt_firmOpen.Cursor = System.Windows.Forms.Cursors.Hand;
            this.bt_firmOpen.Image = global::LIC_settings.Properties.Resources.bt_search;
            this.bt_firmOpen.Location = new System.Drawing.Point(9, 19);
            this.bt_firmOpen.Name = "bt_firmOpen";
            this.bt_firmOpen.Size = new System.Drawing.Size(110, 25);
            this.bt_firmOpen.SizeMode = System.Windows.Forms.PictureBoxSizeMode.CenterImage;
            this.bt_firmOpen.TabIndex = 19;
            this.bt_firmOpen.TabStop = false;
            this.bt_firmOpen.Click += new System.EventHandler(this.bt_firmOpen_Click);
            this.bt_firmOpen.MouseDown += new System.Windows.Forms.MouseEventHandler(this.bt_MouseDown);
            this.bt_firmOpen.MouseLeave += new System.EventHandler(this.bt_MouseLeave);
            this.bt_firmOpen.MouseUp += new System.Windows.Forms.MouseEventHandler(this.bt_MouseUp);
            // 
            // bt_resetSettings
            // 
            this.bt_resetSettings.Location = new System.Drawing.Point(209, 61);
            this.bt_resetSettings.Name = "bt_resetSettings";
            this.bt_resetSettings.Size = new System.Drawing.Size(91, 29);
            this.bt_resetSettings.TabIndex = 17;
            this.bt_resetSettings.Text = "reset settings";
            this.toolTip.SetToolTip(this.bt_resetSettings, "Вернуть настройки к заводским (USB)");
            this.bt_resetSettings.UseVisualStyleBackColor = true;
            this.bt_resetSettings.Visible = false;
            this.bt_resetSettings.Click += new System.EventHandler(this.bt_resetSettings_Click);
            // 
            // bt_mqttFwVersion
            // 
            this.bt_mqttFwVersion.Location = new System.Drawing.Point(312, 61);
            this.bt_mqttFwVersion.Name = "bt_mqttFwVersion";
            this.bt_mqttFwVersion.Size = new System.Drawing.Size(91, 29);
            this.bt_mqttFwVersion.TabIndex = 18;
            this.bt_mqttFwVersion.Text = "fw version";
            this.toolTip.SetToolTip(this.bt_mqttFwVersion, "Запросить версию прошивки ОУ (MQTT)");
            this.bt_mqttFwVersion.UseVisualStyleBackColor = true;
            this.bt_mqttFwVersion.Visible = false;
            this.bt_mqttFwVersion.Click += new System.EventHandler(this.bt_mqttFwVersion_Click);
            // 
            // bt_reprogMqtt
            // 
            this.bt_reprogMqtt.Location = new System.Drawing.Point(313, 26);
            this.bt_reprogMqtt.Name = "bt_reprogMqtt";
            this.bt_reprogMqtt.Size = new System.Drawing.Size(91, 29);
            this.bt_reprogMqtt.TabIndex = 16;
            this.bt_reprogMqtt.Text = "reprog flag";
            this.toolTip.SetToolTip(this.bt_reprogMqtt, "Выставить флаг для перепрошивки из флэшки (MQTT)");
            this.bt_reprogMqtt.UseVisualStyleBackColor = true;
            this.bt_reprogMqtt.Visible = false;
            this.bt_reprogMqtt.Click += new System.EventHandler(this.bt_reprogMqtt_Click);
            // 
            // cb_restartAfterDownload
            // 
            this.cb_restartAfterDownload.AutoSize = true;
            this.cb_restartAfterDownload.Checked = true;
            this.cb_restartAfterDownload.CheckState = System.Windows.Forms.CheckState.Checked;
            this.cb_restartAfterDownload.Location = new System.Drawing.Point(209, 100);
            this.cb_restartAfterDownload.Name = "cb_restartAfterDownload";
            this.cb_restartAfterDownload.Size = new System.Drawing.Size(181, 17);
            this.cb_restartAfterDownload.TabIndex = 12;
            this.cb_restartAfterDownload.Text = "Перезагрузка после передачи";
            this.cb_restartAfterDownload.UseVisualStyleBackColor = true;
            // 
            // bt_mqttReboot
            // 
            this.bt_mqttReboot.Location = new System.Drawing.Point(209, 26);
            this.bt_mqttReboot.Name = "bt_mqttReboot";
            this.bt_mqttReboot.Size = new System.Drawing.Size(91, 29);
            this.bt_mqttReboot.TabIndex = 15;
            this.bt_mqttReboot.Text = "reboot mqtt";
            this.toolTip.SetToolTip(this.bt_mqttReboot, "Перезагрузить ОУ (MQTT)");
            this.bt_mqttReboot.UseVisualStyleBackColor = true;
            this.bt_mqttReboot.Visible = false;
            this.bt_mqttReboot.Click += new System.EventHandler(this.bt_mqttReboot_Click);
            // 
            // label35
            // 
            this.label35.AutoSize = true;
            this.label35.Location = new System.Drawing.Point(206, 120);
            this.label35.Name = "label35";
            this.label35.Size = new System.Drawing.Size(70, 13);
            this.label35.TabIndex = 8;
            this.label35.Text = "MQTT топик";
            // 
            // label34
            // 
            this.label34.AutoSize = true;
            this.label34.Location = new System.Drawing.Point(6, 120);
            this.label34.Name = "label34";
            this.label34.Size = new System.Drawing.Size(77, 13);
            this.label34.TabIndex = 7;
            this.label34.Text = "MQTT сервер";
            // 
            // richTextBox1
            // 
            this.richTextBox1.ContextMenuStrip = this.rtb1_menu;
            this.richTextBox1.Location = new System.Drawing.Point(6, 191);
            this.richTextBox1.Name = "richTextBox1";
            this.richTextBox1.ReadOnly = true;
            this.richTextBox1.Size = new System.Drawing.Size(398, 164);
            this.richTextBox1.TabIndex = 17;
            this.richTextBox1.Text = "";
            this.richTextBox1.TextChanged += new System.EventHandler(this.richTextBox1_TextChanged);
            // 
            // rtb1_menu
            // 
            this.rtb1_menu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.clear});
            this.rtb1_menu.Name = "rtb1_menu";
            this.rtb1_menu.RenderMode = System.Windows.Forms.ToolStripRenderMode.Professional;
            this.rtb1_menu.Size = new System.Drawing.Size(127, 26);
            this.rtb1_menu.Text = "Очистить";
            // 
            // clear
            // 
            this.clear.Name = "clear";
            this.clear.Size = new System.Drawing.Size(126, 22);
            this.clear.Text = "Очистить";
            this.clear.Click += new System.EventHandler(this.clear_Click);
            // 
            // tb_mqttTopic
            // 
            this.tb_mqttTopic.Location = new System.Drawing.Point(209, 136);
            this.tb_mqttTopic.Name = "tb_mqttTopic";
            this.tb_mqttTopic.Size = new System.Drawing.Size(195, 20);
            this.tb_mqttTopic.TabIndex = 14;
            this.tb_mqttTopic.Text = "MIET/OU/2208002";
            // 
            // tb_mqttServer
            // 
            this.tb_mqttServer.Location = new System.Drawing.Point(6, 136);
            this.tb_mqttServer.Name = "tb_mqttServer";
            this.tb_mqttServer.Size = new System.Drawing.Size(195, 20);
            this.tb_mqttServer.TabIndex = 13;
            this.tb_mqttServer.Text = "10.0.38.32";
            this.toolTip.SetToolTip(this.tb_mqttServer, "Адрес MQTT брокера");
            // 
            // progress_firmLoad
            // 
            this.progress_firmLoad.Location = new System.Drawing.Point(6, 162);
            this.progress_firmLoad.Name = "progress_firmLoad";
            this.progress_firmLoad.Size = new System.Drawing.Size(398, 23);
            this.progress_firmLoad.Step = 1;
            this.progress_firmLoad.TabIndex = 0;
            // 
            // l_portName
            // 
            this.l_portName.AutoSize = true;
            this.l_portName.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.l_portName.Location = new System.Drawing.Point(104, 23);
            this.l_portName.Name = "l_portName";
            this.l_portName.Size = new System.Drawing.Size(41, 17);
            this.l_portName.TabIndex = 13;
            this.l_portName.Text = "Порт";
            // 
            // cb_portName
            // 
            this.cb_portName.FormattingEnabled = true;
            this.cb_portName.Location = new System.Drawing.Point(145, 22);
            this.cb_portName.Name = "cb_portName";
            this.cb_portName.Size = new System.Drawing.Size(110, 21);
            this.cb_portName.TabIndex = 0;
            // 
            // tab_eth
            // 
            this.tab_eth.BackColor = System.Drawing.Color.WhiteSmoke;
            this.tab_eth.Controls.Add(this.bt_eth_read);
            this.tab_eth.Controls.Add(this.bt_eth_write);
            this.tab_eth.Controls.Add(this.pb_bt_back2);
            this.tab_eth.Controls.Add(this.gb_MQTT);
            this.tab_eth.Controls.Add(this.gb_WebSettings);
            this.tab_eth.Location = new System.Drawing.Point(4, 24);
            this.tab_eth.Name = "tab_eth";
            this.tab_eth.Size = new System.Drawing.Size(426, 563);
            this.tab_eth.TabIndex = 2;
            this.tab_eth.Text = "Ethernet";
            // 
            // bt_eth_read
            // 
            this.bt_eth_read.BackColor = System.Drawing.Color.WhiteSmoke;
            this.bt_eth_read.Cursor = System.Windows.Forms.Cursors.Hand;
            this.bt_eth_read.Image = global::LIC_settings.Properties.Resources.bt_read;
            this.bt_eth_read.Location = new System.Drawing.Point(323, 23);
            this.bt_eth_read.Name = "bt_eth_read";
            this.bt_eth_read.Size = new System.Drawing.Size(80, 25);
            this.bt_eth_read.SizeMode = System.Windows.Forms.PictureBoxSizeMode.CenterImage;
            this.bt_eth_read.TabIndex = 33;
            this.bt_eth_read.TabStop = false;
            this.bt_eth_read.Click += new System.EventHandler(this.bt_eth_read_Click);
            this.bt_eth_read.MouseDown += new System.Windows.Forms.MouseEventHandler(this.bt_MouseDown);
            this.bt_eth_read.MouseLeave += new System.EventHandler(this.bt_MouseLeave);
            this.bt_eth_read.MouseUp += new System.Windows.Forms.MouseEventHandler(this.bt_MouseUp);
            // 
            // bt_eth_write
            // 
            this.bt_eth_write.BackColor = System.Drawing.Color.WhiteSmoke;
            this.bt_eth_write.Cursor = System.Windows.Forms.Cursors.Hand;
            this.bt_eth_write.Image = global::LIC_settings.Properties.Resources.bt_write;
            this.bt_eth_write.Location = new System.Drawing.Point(323, 56);
            this.bt_eth_write.Name = "bt_eth_write";
            this.bt_eth_write.Size = new System.Drawing.Size(80, 25);
            this.bt_eth_write.SizeMode = System.Windows.Forms.PictureBoxSizeMode.CenterImage;
            this.bt_eth_write.TabIndex = 32;
            this.bt_eth_write.TabStop = false;
            this.bt_eth_write.Click += new System.EventHandler(this.bt_eth_send_Click);
            this.bt_eth_write.MouseDown += new System.Windows.Forms.MouseEventHandler(this.bt_MouseDown);
            this.bt_eth_write.MouseLeave += new System.EventHandler(this.bt_MouseLeave);
            this.bt_eth_write.MouseUp += new System.Windows.Forms.MouseEventHandler(this.bt_MouseUp);
            // 
            // pb_bt_back2
            // 
            this.pb_bt_back2.Cursor = System.Windows.Forms.Cursors.Hand;
            this.pb_bt_back2.Image = global::LIC_settings.Properties.Resources.bt_back;
            this.pb_bt_back2.Location = new System.Drawing.Point(8, 8);
            this.pb_bt_back2.Name = "pb_bt_back2";
            this.pb_bt_back2.Size = new System.Drawing.Size(40, 40);
            this.pb_bt_back2.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.pb_bt_back2.TabIndex = 31;
            this.pb_bt_back2.TabStop = false;
            this.pb_bt_back2.Click += new System.EventHandler(this.bt_back1_Click);
            // 
            // gb_MQTT
            // 
            this.gb_MQTT.BackColor = System.Drawing.Color.White;
            this.gb_MQTT.Controls.Add(this.chb_MQTT_Activate);
            this.gb_MQTT.Controls.Add(this.tb_MQTT_Password);
            this.gb_MQTT.Controls.Add(this.tb_MQTT_User);
            this.gb_MQTT.Controls.Add(this.label14);
            this.gb_MQTT.Controls.Add(this.tb_MQTT_ID);
            this.gb_MQTT.Controls.Add(this.label13);
            this.gb_MQTT.Controls.Add(this.label12);
            this.gb_MQTT.Controls.Add(this.tb_MQQTTopicOutput);
            this.gb_MQTT.Controls.Add(this.tb_BrokerPort);
            this.gb_MQTT.Controls.Add(this.label10);
            this.gb_MQTT.Controls.Add(this.label9);
            this.gb_MQTT.Controls.Add(this.tb_BrokerIP);
            this.gb_MQTT.Controls.Add(this.label8);
            this.gb_MQTT.Location = new System.Drawing.Point(15, 262);
            this.gb_MQTT.Name = "gb_MQTT";
            this.gb_MQTT.Size = new System.Drawing.Size(403, 294);
            this.gb_MQTT.TabIndex = 20;
            this.gb_MQTT.TabStop = false;
            this.gb_MQTT.Text = "Настройки MQTT";
            // 
            // chb_MQTT_Activate
            // 
            this.chb_MQTT_Activate.AutoSize = true;
            this.chb_MQTT_Activate.Enabled = false;
            this.chb_MQTT_Activate.Font = new System.Drawing.Font("Microsoft Sans Serif", 11F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.chb_MQTT_Activate.Location = new System.Drawing.Point(271, 206);
            this.chb_MQTT_Activate.Name = "chb_MQTT_Activate";
            this.chb_MQTT_Activate.Size = new System.Drawing.Size(123, 22);
            this.chb_MQTT_Activate.TabIndex = 14;
            this.chb_MQTT_Activate.Text = "Активировать";
            this.chb_MQTT_Activate.UseVisualStyleBackColor = true;
            this.chb_MQTT_Activate.CheckedChanged += new System.EventHandler(this.chb_MQTT_Activate_CheckedChanged);
            // 
            // tb_MQTT_Password
            // 
            this.tb_MQTT_Password.Enabled = false;
            this.tb_MQTT_Password.Location = new System.Drawing.Point(138, 208);
            this.tb_MQTT_Password.Name = "tb_MQTT_Password";
            this.tb_MQTT_Password.Size = new System.Drawing.Size(127, 20);
            this.tb_MQTT_Password.TabIndex = 13;
            this.tb_MQTT_Password.Text = "password";
            this.tb_MQTT_Password.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // tb_MQTT_User
            // 
            this.tb_MQTT_User.Enabled = false;
            this.tb_MQTT_User.Location = new System.Drawing.Point(138, 173);
            this.tb_MQTT_User.Name = "tb_MQTT_User";
            this.tb_MQTT_User.Size = new System.Drawing.Size(127, 20);
            this.tb_MQTT_User.TabIndex = 12;
            this.tb_MQTT_User.Text = "user";
            this.tb_MQTT_User.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Font = new System.Drawing.Font("Arial Narrow", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label14.Location = new System.Drawing.Point(16, 206);
            this.label14.Margin = new System.Windows.Forms.Padding(3, 15, 3, 0);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(116, 20);
            this.label14.TabIndex = 26;
            this.label14.Text = "PASSWORD mqtt";
            // 
            // tb_MQTT_ID
            // 
            this.tb_MQTT_ID.Enabled = false;
            this.tb_MQTT_ID.Location = new System.Drawing.Point(138, 138);
            this.tb_MQTT_ID.Name = "tb_MQTT_ID";
            this.tb_MQTT_ID.Size = new System.Drawing.Size(127, 20);
            this.tb_MQTT_ID.TabIndex = 11;
            this.tb_MQTT_ID.Text = "%sn";
            this.tb_MQTT_ID.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Font = new System.Drawing.Font("Arial Narrow", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label13.Location = new System.Drawing.Point(16, 171);
            this.label13.Margin = new System.Windows.Forms.Padding(3, 15, 3, 0);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(77, 20);
            this.label13.TabIndex = 26;
            this.label13.Text = "USER mqtt";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Font = new System.Drawing.Font("Arial Narrow", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label12.Location = new System.Drawing.Point(16, 136);
            this.label12.Margin = new System.Windows.Forms.Padding(3, 15, 3, 0);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(54, 20);
            this.label12.TabIndex = 26;
            this.label12.Text = "ID mqtt";
            // 
            // tb_MQQTTopicOutput
            // 
            this.tb_MQQTTopicOutput.Enabled = false;
            this.tb_MQQTTopicOutput.Location = new System.Drawing.Point(138, 100);
            this.tb_MQQTTopicOutput.Name = "tb_MQQTTopicOutput";
            this.tb_MQQTTopicOutput.Size = new System.Drawing.Size(127, 20);
            this.tb_MQQTTopicOutput.TabIndex = 9;
            this.tb_MQQTTopicOutput.Text = "MIET/OU";
            this.tb_MQQTTopicOutput.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // tb_BrokerPort
            // 
            this.tb_BrokerPort.Enabled = false;
            this.tb_BrokerPort.Location = new System.Drawing.Point(138, 65);
            this.tb_BrokerPort.Name = "tb_BrokerPort";
            this.tb_BrokerPort.Size = new System.Drawing.Size(127, 20);
            this.tb_BrokerPort.TabIndex = 8;
            this.tb_BrokerPort.Text = "1883";
            this.tb_BrokerPort.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Font = new System.Drawing.Font("Arial Narrow", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label10.Location = new System.Drawing.Point(16, 98);
            this.label10.Margin = new System.Windows.Forms.Padding(3, 15, 3, 0);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(112, 20);
            this.label10.TabIndex = 24;
            this.label10.Text = "Топик отправки";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Font = new System.Drawing.Font("Arial Narrow", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label9.Location = new System.Drawing.Point(16, 63);
            this.label9.Margin = new System.Windows.Forms.Padding(3, 15, 3, 0);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(97, 20);
            this.label9.TabIndex = 22;
            this.label9.Text = "Порт брокера";
            // 
            // tb_BrokerIP
            // 
            this.tb_BrokerIP.Enabled = false;
            this.tb_BrokerIP.Location = new System.Drawing.Point(138, 30);
            this.tb_BrokerIP.Name = "tb_BrokerIP";
            this.tb_BrokerIP.Size = new System.Drawing.Size(127, 20);
            this.tb_BrokerIP.TabIndex = 7;
            this.tb_BrokerIP.Text = "10.0.38.32";
            this.tb_BrokerIP.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.tb_BrokerIP.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.checkIPFormat);
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Font = new System.Drawing.Font("Arial Narrow", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label8.Location = new System.Drawing.Point(16, 28);
            this.label8.Margin = new System.Windows.Forms.Padding(3, 15, 3, 0);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(79, 20);
            this.label8.TabIndex = 20;
            this.label8.Text = "IP брокера";
            // 
            // gb_WebSettings
            // 
            this.gb_WebSettings.BackColor = System.Drawing.Color.White;
            this.gb_WebSettings.Controls.Add(this.chb_ETH_Activate);
            this.gb_WebSettings.Controls.Add(this.chb_DHCP);
            this.gb_WebSettings.Controls.Add(this.tb_IP);
            this.gb_WebSettings.Controls.Add(this.tb_MAC);
            this.gb_WebSettings.Controls.Add(this.label4);
            this.gb_WebSettings.Controls.Add(this.tb_Gateway);
            this.gb_WebSettings.Controls.Add(this.label5);
            this.gb_WebSettings.Controls.Add(this.tb_Mask);
            this.gb_WebSettings.Controls.Add(this.label6);
            this.gb_WebSettings.Controls.Add(this.label7);
            this.gb_WebSettings.Location = new System.Drawing.Point(15, 89);
            this.gb_WebSettings.Margin = new System.Windows.Forms.Padding(10, 3, 3, 3);
            this.gb_WebSettings.Name = "gb_WebSettings";
            this.gb_WebSettings.Size = new System.Drawing.Size(403, 165);
            this.gb_WebSettings.TabIndex = 19;
            this.gb_WebSettings.TabStop = false;
            this.gb_WebSettings.Text = "Настройки Ethernet";
            // 
            // chb_ETH_Activate
            // 
            this.chb_ETH_Activate.AutoSize = true;
            this.chb_ETH_Activate.Font = new System.Drawing.Font("Microsoft Sans Serif", 11F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.chb_ETH_Activate.Location = new System.Drawing.Point(271, 127);
            this.chb_ETH_Activate.Name = "chb_ETH_Activate";
            this.chb_ETH_Activate.Size = new System.Drawing.Size(123, 22);
            this.chb_ETH_Activate.TabIndex = 6;
            this.chb_ETH_Activate.Text = "Активировать";
            this.chb_ETH_Activate.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.chb_ETH_Activate.UseVisualStyleBackColor = true;
            this.chb_ETH_Activate.CheckedChanged += new System.EventHandler(this.chb_ETH_Activate_CheckedChanged);
            // 
            // chb_DHCP
            // 
            this.chb_DHCP.AutoSize = true;
            this.chb_DHCP.Enabled = false;
            this.chb_DHCP.Font = new System.Drawing.Font("Arial Narrow", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.chb_DHCP.Location = new System.Drawing.Point(271, 21);
            this.chb_DHCP.Name = "chb_DHCP";
            this.chb_DHCP.Size = new System.Drawing.Size(64, 24);
            this.chb_DHCP.TabIndex = 2;
            this.chb_DHCP.Text = "DHCP";
            this.chb_DHCP.UseVisualStyleBackColor = true;
            // 
            // tb_IP
            // 
            this.tb_IP.Enabled = false;
            this.tb_IP.Location = new System.Drawing.Point(138, 24);
            this.tb_IP.Name = "tb_IP";
            this.tb_IP.Size = new System.Drawing.Size(127, 20);
            this.tb_IP.TabIndex = 1;
            this.tb_IP.Text = "10.0.38.31";
            this.tb_IP.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.tb_IP.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.checkIPFormat);
            // 
            // tb_MAC
            // 
            this.tb_MAC.Enabled = false;
            this.tb_MAC.Location = new System.Drawing.Point(138, 129);
            this.tb_MAC.Mask = "CC-CC-CC-CC-CC-CC";
            this.tb_MAC.Name = "tb_MAC";
            this.tb_MAC.Size = new System.Drawing.Size(127, 20);
            this.tb_MAC.TabIndex = 5;
            this.tb_MAC.Text = "a0b2c3d4e5f6";
            this.tb_MAC.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.tb_MAC.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.checkIPFormat);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Arial Narrow", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label4.Location = new System.Drawing.Point(16, 22);
            this.label4.Margin = new System.Windows.Forms.Padding(3, 15, 3, 0);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(63, 20);
            this.label4.TabIndex = 9;
            this.label4.Text = "IP адрес";
            // 
            // tb_Gateway
            // 
            this.tb_Gateway.Enabled = false;
            this.tb_Gateway.Location = new System.Drawing.Point(138, 94);
            this.tb_Gateway.Name = "tb_Gateway";
            this.tb_Gateway.Size = new System.Drawing.Size(127, 20);
            this.tb_Gateway.TabIndex = 4;
            this.tb_Gateway.Text = "10.0.0.1";
            this.tb_Gateway.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.tb_Gateway.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.checkIPFormat);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Arial Narrow", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label5.Location = new System.Drawing.Point(16, 57);
            this.label5.Margin = new System.Windows.Forms.Padding(3, 15, 3, 0);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(48, 20);
            this.label5.TabIndex = 10;
            this.label5.Text = "Маска";
            // 
            // tb_Mask
            // 
            this.tb_Mask.Enabled = false;
            this.tb_Mask.Location = new System.Drawing.Point(138, 59);
            this.tb_Mask.Name = "tb_Mask";
            this.tb_Mask.Size = new System.Drawing.Size(127, 20);
            this.tb_Mask.TabIndex = 3;
            this.tb_Mask.Text = "255.255.0.0";
            this.tb_Mask.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.tb_Mask.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.checkIPFormat);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("Arial Narrow", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label6.Location = new System.Drawing.Point(16, 92);
            this.label6.Margin = new System.Windows.Forms.Padding(3, 15, 3, 0);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(48, 20);
            this.label6.TabIndex = 11;
            this.label6.Text = "Шлюз";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Font = new System.Drawing.Font("Arial Narrow", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label7.Location = new System.Drawing.Point(16, 127);
            this.label7.Margin = new System.Windows.Forms.Padding(3, 15, 3, 0);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(38, 20);
            this.label7.TabIndex = 12;
            this.label7.Text = "MAC";
            // 
            // tab_lora
            // 
            this.tab_lora.BackColor = System.Drawing.Color.WhiteSmoke;
            this.tab_lora.Controls.Add(this.cb_loraDatarate);
            this.tab_lora.Controls.Add(this.label41);
            this.tab_lora.Controls.Add(this.cb_loraMessageType);
            this.tab_lora.Controls.Add(this.bt_LoRa_read);
            this.tab_lora.Controls.Add(this.bt_LoRa_send);
            this.tab_lora.Controls.Add(this.pb_bt_back3);
            this.tab_lora.Controls.Add(this.chb_LoRa_activate);
            this.tab_lora.Controls.Add(this.image_LoRa_logo);
            this.tab_lora.Controls.Add(this.chb_AutoDevEUI);
            this.tab_lora.Controls.Add(this.tb_LORA_AppPort);
            this.tab_lora.Controls.Add(this.tb_LORA_AppEUI);
            this.tab_lora.Controls.Add(this.tb_LORA_DevEUI);
            this.tab_lora.Controls.Add(this.tb_LORA_AppKey);
            this.tab_lora.Controls.Add(this.chb_LORA_ADR);
            this.tab_lora.Controls.Add(this.label21);
            this.tab_lora.Controls.Add(this.label20);
            this.tab_lora.Controls.Add(this.label19);
            this.tab_lora.Controls.Add(this.label18);
            this.tab_lora.Controls.Add(this.label17);
            this.tab_lora.Location = new System.Drawing.Point(4, 24);
            this.tab_lora.Name = "tab_lora";
            this.tab_lora.Size = new System.Drawing.Size(426, 563);
            this.tab_lora.TabIndex = 3;
            this.tab_lora.Text = "LoRa";
            // 
            // cb_loraDatarate
            // 
            this.cb_loraDatarate.Enabled = false;
            this.cb_loraDatarate.FormattingEnabled = true;
            this.cb_loraDatarate.Items.AddRange(new object[] {
            "SF12 - BW125",
            "SF11 - BW125",
            "SF10 - BW125",
            "SF9 - BW125",
            "SF8 - BW125",
            "SF7 - BW125"});
            this.cb_loraDatarate.Location = new System.Drawing.Point(142, 238);
            this.cb_loraDatarate.Name = "cb_loraDatarate";
            this.cb_loraDatarate.Size = new System.Drawing.Size(127, 21);
            this.cb_loraDatarate.TabIndex = 65;
            // 
            // label41
            // 
            this.label41.AutoSize = true;
            this.label41.Font = new System.Drawing.Font("Arial Narrow", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label41.Location = new System.Drawing.Point(20, 262);
            this.label41.Margin = new System.Windows.Forms.Padding(3, 15, 3, 0);
            this.label41.Name = "label41";
            this.label41.Size = new System.Drawing.Size(93, 20);
            this.label41.TabIndex = 64;
            this.label41.Text = "Message type";
            // 
            // cb_loraMessageType
            // 
            this.cb_loraMessageType.Enabled = false;
            this.cb_loraMessageType.FormattingEnabled = true;
            this.cb_loraMessageType.Items.AddRange(new object[] {
            "Unconfirmed",
            "Confirmed"});
            this.cb_loraMessageType.Location = new System.Drawing.Point(142, 264);
            this.cb_loraMessageType.Name = "cb_loraMessageType";
            this.cb_loraMessageType.Size = new System.Drawing.Size(127, 21);
            this.cb_loraMessageType.TabIndex = 63;
            // 
            // bt_LoRa_read
            // 
            this.bt_LoRa_read.BackColor = System.Drawing.Color.WhiteSmoke;
            this.bt_LoRa_read.Cursor = System.Windows.Forms.Cursors.Hand;
            this.bt_LoRa_read.Image = global::LIC_settings.Properties.Resources.bt_read;
            this.bt_LoRa_read.Location = new System.Drawing.Point(324, 362);
            this.bt_LoRa_read.Name = "bt_LoRa_read";
            this.bt_LoRa_read.Size = new System.Drawing.Size(80, 25);
            this.bt_LoRa_read.SizeMode = System.Windows.Forms.PictureBoxSizeMode.CenterImage;
            this.bt_LoRa_read.TabIndex = 62;
            this.bt_LoRa_read.TabStop = false;
            this.bt_LoRa_read.Click += new System.EventHandler(this.bt_LoRa_read_Click);
            this.bt_LoRa_read.MouseDown += new System.Windows.Forms.MouseEventHandler(this.bt_MouseDown);
            this.bt_LoRa_read.MouseLeave += new System.EventHandler(this.bt_MouseLeave);
            this.bt_LoRa_read.MouseUp += new System.Windows.Forms.MouseEventHandler(this.bt_MouseUp);
            // 
            // bt_LoRa_send
            // 
            this.bt_LoRa_send.BackColor = System.Drawing.Color.WhiteSmoke;
            this.bt_LoRa_send.Cursor = System.Windows.Forms.Cursors.Hand;
            this.bt_LoRa_send.Image = global::LIC_settings.Properties.Resources.bt_write;
            this.bt_LoRa_send.Location = new System.Drawing.Point(324, 395);
            this.bt_LoRa_send.Name = "bt_LoRa_send";
            this.bt_LoRa_send.Size = new System.Drawing.Size(80, 25);
            this.bt_LoRa_send.SizeMode = System.Windows.Forms.PictureBoxSizeMode.CenterImage;
            this.bt_LoRa_send.TabIndex = 61;
            this.bt_LoRa_send.TabStop = false;
            this.bt_LoRa_send.Click += new System.EventHandler(this.bt_LoRa_send_Click);
            this.bt_LoRa_send.MouseDown += new System.Windows.Forms.MouseEventHandler(this.bt_MouseDown);
            this.bt_LoRa_send.MouseLeave += new System.EventHandler(this.bt_MouseLeave);
            this.bt_LoRa_send.MouseUp += new System.Windows.Forms.MouseEventHandler(this.bt_MouseUp);
            // 
            // pb_bt_back3
            // 
            this.pb_bt_back3.Cursor = System.Windows.Forms.Cursors.Hand;
            this.pb_bt_back3.Image = global::LIC_settings.Properties.Resources.bt_back;
            this.pb_bt_back3.Location = new System.Drawing.Point(8, 8);
            this.pb_bt_back3.Name = "pb_bt_back3";
            this.pb_bt_back3.Size = new System.Drawing.Size(40, 40);
            this.pb_bt_back3.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.pb_bt_back3.TabIndex = 60;
            this.pb_bt_back3.TabStop = false;
            this.pb_bt_back3.Click += new System.EventHandler(this.bt_back1_Click);
            // 
            // chb_LoRa_activate
            // 
            this.chb_LoRa_activate.AutoSize = true;
            this.chb_LoRa_activate.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.chb_LoRa_activate.Location = new System.Drawing.Point(142, 310);
            this.chb_LoRa_activate.Name = "chb_LoRa_activate";
            this.chb_LoRa_activate.Size = new System.Drawing.Size(137, 24);
            this.chb_LoRa_activate.TabIndex = 9;
            this.chb_LoRa_activate.Text = "Активировать";
            this.chb_LoRa_activate.UseVisualStyleBackColor = true;
            this.chb_LoRa_activate.CheckedChanged += new System.EventHandler(this.chb_LoRa_activate_CheckedChanged);
            // 
            // image_LoRa_logo
            // 
            this.image_LoRa_logo.BackColor = System.Drawing.Color.White;
            this.image_LoRa_logo.Image = global::LIC_settings.Properties.Resources.LoRa_logo;
            this.image_LoRa_logo.InitialImage = null;
            this.image_LoRa_logo.Location = new System.Drawing.Point(64, 8);
            this.image_LoRa_logo.Name = "image_LoRa_logo";
            this.image_LoRa_logo.Size = new System.Drawing.Size(340, 60);
            this.image_LoRa_logo.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.image_LoRa_logo.TabIndex = 58;
            this.image_LoRa_logo.TabStop = false;
            // 
            // chb_AutoDevEUI
            // 
            this.chb_AutoDevEUI.AutoSize = true;
            this.chb_AutoDevEUI.Enabled = false;
            this.chb_AutoDevEUI.Font = new System.Drawing.Font("Arial Narrow", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.chb_AutoDevEUI.Location = new System.Drawing.Point(275, 212);
            this.chb_AutoDevEUI.Name = "chb_AutoDevEUI";
            this.chb_AutoDevEUI.Size = new System.Drawing.Size(81, 21);
            this.chb_AutoDevEUI.TabIndex = 6;
            this.chb_AutoDevEUI.Text = "AUTO EUI";
            this.chb_AutoDevEUI.UseVisualStyleBackColor = true;
            // 
            // tb_LORA_AppPort
            // 
            this.tb_LORA_AppPort.Enabled = false;
            this.tb_LORA_AppPort.Location = new System.Drawing.Point(142, 212);
            this.tb_LORA_AppPort.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.tb_LORA_AppPort.Name = "tb_LORA_AppPort";
            this.tb_LORA_AppPort.ReadOnly = true;
            this.tb_LORA_AppPort.Size = new System.Drawing.Size(127, 20);
            this.tb_LORA_AppPort.TabIndex = 5;
            this.tb_LORA_AppPort.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.tb_LORA_AppPort.Value = new decimal(new int[] {
            2,
            0,
            0,
            0});
            // 
            // tb_LORA_AppEUI
            // 
            this.tb_LORA_AppEUI.Enabled = false;
            this.tb_LORA_AppEUI.Location = new System.Drawing.Point(142, 160);
            this.tb_LORA_AppEUI.Mask = "CC-CC-CC-CC-CC-CC-CC-CC";
            this.tb_LORA_AppEUI.Name = "tb_LORA_AppEUI";
            this.tb_LORA_AppEUI.Size = new System.Drawing.Size(262, 20);
            this.tb_LORA_AppEUI.TabIndex = 3;
            this.tb_LORA_AppEUI.Text = "dca632fffe409b25";
            this.tb_LORA_AppEUI.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // tb_LORA_DevEUI
            // 
            this.tb_LORA_DevEUI.Enabled = false;
            this.tb_LORA_DevEUI.Location = new System.Drawing.Point(142, 134);
            this.tb_LORA_DevEUI.Mask = "CC-CC-CC-CC-CC-CC-CC-CC";
            this.tb_LORA_DevEUI.Name = "tb_LORA_DevEUI";
            this.tb_LORA_DevEUI.Size = new System.Drawing.Size(262, 20);
            this.tb_LORA_DevEUI.TabIndex = 2;
            this.tb_LORA_DevEUI.Text = "195136328b347735";
            this.tb_LORA_DevEUI.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // tb_LORA_AppKey
            // 
            this.tb_LORA_AppKey.Enabled = false;
            this.tb_LORA_AppKey.Location = new System.Drawing.Point(142, 186);
            this.tb_LORA_AppKey.Mask = "CC-CC-CC-CC-CC-CC-CC-CC-CC-CC-CC-CC-CC-CC-CC-CC";
            this.tb_LORA_AppKey.Name = "tb_LORA_AppKey";
            this.tb_LORA_AppKey.Size = new System.Drawing.Size(262, 20);
            this.tb_LORA_AppKey.TabIndex = 4;
            this.tb_LORA_AppKey.Text = "88888888888888888888888888888801";
            this.tb_LORA_AppKey.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // chb_LORA_ADR
            // 
            this.chb_LORA_ADR.AutoSize = true;
            this.chb_LORA_ADR.Enabled = false;
            this.chb_LORA_ADR.Font = new System.Drawing.Font("Arial Narrow", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.chb_LORA_ADR.Location = new System.Drawing.Point(275, 238);
            this.chb_LORA_ADR.Name = "chb_LORA_ADR";
            this.chb_LORA_ADR.Size = new System.Drawing.Size(129, 21);
            this.chb_LORA_ADR.TabIndex = 8;
            this.chb_LORA_ADR.Text = "Adaptive Data Rate";
            this.chb_LORA_ADR.UseVisualStyleBackColor = true;
            // 
            // label21
            // 
            this.label21.AutoSize = true;
            this.label21.Font = new System.Drawing.Font("Arial Narrow", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label21.Location = new System.Drawing.Point(20, 210);
            this.label21.Margin = new System.Windows.Forms.Padding(3, 15, 3, 0);
            this.label21.Name = "label21";
            this.label21.Size = new System.Drawing.Size(110, 20);
            this.label21.TabIndex = 49;
            this.label21.Text = "Application Port";
            // 
            // label20
            // 
            this.label20.AutoSize = true;
            this.label20.Font = new System.Drawing.Font("Arial Narrow", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label20.Location = new System.Drawing.Point(20, 236);
            this.label20.Margin = new System.Windows.Forms.Padding(3, 15, 3, 0);
            this.label20.Name = "label20";
            this.label20.Size = new System.Drawing.Size(114, 20);
            this.label20.TabIndex = 47;
            this.label20.Text = "Default Data Rate";
            // 
            // label19
            // 
            this.label19.AutoSize = true;
            this.label19.Font = new System.Drawing.Font("Arial Narrow", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label19.Location = new System.Drawing.Point(20, 184);
            this.label19.Margin = new System.Windows.Forms.Padding(3, 15, 3, 0);
            this.label19.Name = "label19";
            this.label19.Size = new System.Drawing.Size(107, 20);
            this.label19.TabIndex = 46;
            this.label19.Text = "Application Key";
            // 
            // label18
            // 
            this.label18.AutoSize = true;
            this.label18.Font = new System.Drawing.Font("Arial Narrow", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label18.Location = new System.Drawing.Point(20, 158);
            this.label18.Margin = new System.Windows.Forms.Padding(3, 15, 3, 0);
            this.label18.Name = "label18";
            this.label18.Size = new System.Drawing.Size(104, 20);
            this.label18.TabIndex = 45;
            this.label18.Text = "App/Server EUI";
            // 
            // label17
            // 
            this.label17.AutoSize = true;
            this.label17.Font = new System.Drawing.Font("Arial Narrow", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label17.Location = new System.Drawing.Point(20, 132);
            this.label17.Margin = new System.Windows.Forms.Padding(3, 15, 3, 0);
            this.label17.Name = "label17";
            this.label17.Size = new System.Drawing.Size(76, 20);
            this.label17.TabIndex = 44;
            this.label17.Text = "Device EUI";
            // 
            // tab_zigbee
            // 
            this.tab_zigbee.BackColor = System.Drawing.Color.WhiteSmoke;
            this.tab_zigbee.Controls.Add(this.pb_bt_back4);
            this.tab_zigbee.Controls.Add(this.groupBox7);
            this.tab_zigbee.Controls.Add(this.groupBox6);
            this.tab_zigbee.Controls.Add(this.bt_zigbeeSensors);
            this.tab_zigbee.Controls.Add(this.bt_zigbeeConnect);
            this.tab_zigbee.Controls.Add(this.rtb_zigbee);
            this.tab_zigbee.Controls.Add(this.image_zigbee_logo);
            this.tab_zigbee.Location = new System.Drawing.Point(4, 24);
            this.tab_zigbee.Name = "tab_zigbee";
            this.tab_zigbee.Size = new System.Drawing.Size(426, 563);
            this.tab_zigbee.TabIndex = 7;
            this.tab_zigbee.Text = "ZigBee";
            // 
            // pb_bt_back4
            // 
            this.pb_bt_back4.BackColor = System.Drawing.Color.WhiteSmoke;
            this.pb_bt_back4.Cursor = System.Windows.Forms.Cursors.Hand;
            this.pb_bt_back4.Image = global::LIC_settings.Properties.Resources.bt_back;
            this.pb_bt_back4.Location = new System.Drawing.Point(8, 8);
            this.pb_bt_back4.Name = "pb_bt_back4";
            this.pb_bt_back4.Size = new System.Drawing.Size(40, 40);
            this.pb_bt_back4.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.pb_bt_back4.TabIndex = 68;
            this.pb_bt_back4.TabStop = false;
            this.pb_bt_back4.Click += new System.EventHandler(this.bt_back1_Click);
            // 
            // groupBox7
            // 
            this.groupBox7.BackColor = System.Drawing.Color.White;
            this.groupBox7.Controls.Add(this.bt_zigbeeFrmGetFile);
            this.groupBox7.Controls.Add(this.bt_zigbeeFrmSend);
            this.groupBox7.Controls.Add(this.pb_zigbee);
            this.groupBox7.Location = new System.Drawing.Point(64, 427);
            this.groupBox7.Name = "groupBox7";
            this.groupBox7.Size = new System.Drawing.Size(340, 98);
            this.groupBox7.TabIndex = 67;
            this.groupBox7.TabStop = false;
            this.groupBox7.Text = "Прошивка";
            // 
            // bt_zigbeeFrmGetFile
            // 
            this.bt_zigbeeFrmGetFile.Cursor = System.Windows.Forms.Cursors.Hand;
            this.bt_zigbeeFrmGetFile.Image = global::LIC_settings.Properties.Resources.bt_search;
            this.bt_zigbeeFrmGetFile.Location = new System.Drawing.Point(13, 23);
            this.bt_zigbeeFrmGetFile.Name = "bt_zigbeeFrmGetFile";
            this.bt_zigbeeFrmGetFile.Size = new System.Drawing.Size(110, 25);
            this.bt_zigbeeFrmGetFile.SizeMode = System.Windows.Forms.PictureBoxSizeMode.CenterImage;
            this.bt_zigbeeFrmGetFile.TabIndex = 70;
            this.bt_zigbeeFrmGetFile.TabStop = false;
            this.bt_zigbeeFrmGetFile.Click += new System.EventHandler(this.bt_zigbeeFrmGetFile_Click);
            this.bt_zigbeeFrmGetFile.MouseDown += new System.Windows.Forms.MouseEventHandler(this.bt_MouseDown);
            this.bt_zigbeeFrmGetFile.MouseLeave += new System.EventHandler(this.bt_MouseLeave);
            this.bt_zigbeeFrmGetFile.MouseUp += new System.Windows.Forms.MouseEventHandler(this.bt_MouseUp);
            // 
            // bt_zigbeeFrmSend
            // 
            this.bt_zigbeeFrmSend.Cursor = System.Windows.Forms.Cursors.Hand;
            this.bt_zigbeeFrmSend.Image = global::LIC_settings.Properties.Resources.bt_send;
            this.bt_zigbeeFrmSend.Location = new System.Drawing.Point(207, 23);
            this.bt_zigbeeFrmSend.Name = "bt_zigbeeFrmSend";
            this.bt_zigbeeFrmSend.Size = new System.Drawing.Size(100, 25);
            this.bt_zigbeeFrmSend.SizeMode = System.Windows.Forms.PictureBoxSizeMode.CenterImage;
            this.bt_zigbeeFrmSend.TabIndex = 69;
            this.bt_zigbeeFrmSend.TabStop = false;
            this.bt_zigbeeFrmSend.Click += new System.EventHandler(this.bt_zigbeeFrmSend_Click);
            this.bt_zigbeeFrmSend.MouseDown += new System.Windows.Forms.MouseEventHandler(this.bt_MouseDown);
            this.bt_zigbeeFrmSend.MouseLeave += new System.EventHandler(this.bt_MouseLeave);
            this.bt_zigbeeFrmSend.MouseUp += new System.Windows.Forms.MouseEventHandler(this.bt_MouseUp);
            // 
            // pb_zigbee
            // 
            this.pb_zigbee.Location = new System.Drawing.Point(6, 60);
            this.pb_zigbee.Name = "pb_zigbee";
            this.pb_zigbee.Size = new System.Drawing.Size(328, 23);
            this.pb_zigbee.Step = 1;
            this.pb_zigbee.TabIndex = 64;
            // 
            // groupBox6
            // 
            this.groupBox6.BackColor = System.Drawing.Color.White;
            this.groupBox6.Controls.Add(this.bt_zigbee_read);
            this.groupBox6.Controls.Add(this.bt_zigbee_send);
            this.groupBox6.Controls.Add(this.chb_ZigBee_Activate);
            this.groupBox6.Location = new System.Drawing.Point(64, 268);
            this.groupBox6.Name = "groupBox6";
            this.groupBox6.Size = new System.Drawing.Size(340, 143);
            this.groupBox6.TabIndex = 66;
            this.groupBox6.TabStop = false;
            this.groupBox6.Text = "Параметры";
            // 
            // bt_zigbee_read
            // 
            this.bt_zigbee_read.Cursor = System.Windows.Forms.Cursors.Hand;
            this.bt_zigbee_read.Image = global::LIC_settings.Properties.Resources.bt_read;
            this.bt_zigbee_read.Location = new System.Drawing.Point(207, 71);
            this.bt_zigbee_read.Name = "bt_zigbee_read";
            this.bt_zigbee_read.Size = new System.Drawing.Size(80, 25);
            this.bt_zigbee_read.SizeMode = System.Windows.Forms.PictureBoxSizeMode.CenterImage;
            this.bt_zigbee_read.TabIndex = 7;
            this.bt_zigbee_read.TabStop = false;
            this.bt_zigbee_read.Click += new System.EventHandler(this.bt_zigbee_read_Click);
            this.bt_zigbee_read.MouseDown += new System.Windows.Forms.MouseEventHandler(this.bt_MouseDown);
            this.bt_zigbee_read.MouseLeave += new System.EventHandler(this.bt_MouseLeave);
            this.bt_zigbee_read.MouseUp += new System.Windows.Forms.MouseEventHandler(this.bt_MouseUp);
            // 
            // bt_zigbee_send
            // 
            this.bt_zigbee_send.Cursor = System.Windows.Forms.Cursors.Hand;
            this.bt_zigbee_send.Image = global::LIC_settings.Properties.Resources.bt_write;
            this.bt_zigbee_send.Location = new System.Drawing.Point(207, 105);
            this.bt_zigbee_send.Name = "bt_zigbee_send";
            this.bt_zigbee_send.Size = new System.Drawing.Size(80, 25);
            this.bt_zigbee_send.SizeMode = System.Windows.Forms.PictureBoxSizeMode.CenterImage;
            this.bt_zigbee_send.TabIndex = 6;
            this.bt_zigbee_send.TabStop = false;
            this.bt_zigbee_send.Click += new System.EventHandler(this.bt_zigbee_send_Click);
            this.bt_zigbee_send.MouseDown += new System.Windows.Forms.MouseEventHandler(this.bt_MouseDown);
            this.bt_zigbee_send.MouseLeave += new System.EventHandler(this.bt_MouseLeave);
            this.bt_zigbee_send.MouseUp += new System.Windows.Forms.MouseEventHandler(this.bt_MouseUp);
            // 
            // chb_ZigBee_Activate
            // 
            this.chb_ZigBee_Activate.AutoSize = true;
            this.chb_ZigBee_Activate.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.chb_ZigBee_Activate.Location = new System.Drawing.Point(6, 19);
            this.chb_ZigBee_Activate.Name = "chb_ZigBee_Activate";
            this.chb_ZigBee_Activate.Size = new System.Drawing.Size(137, 24);
            this.chb_ZigBee_Activate.TabIndex = 3;
            this.chb_ZigBee_Activate.Text = "Активировать";
            this.chb_ZigBee_Activate.UseVisualStyleBackColor = true;
            // 
            // bt_zigbeeSensors
            // 
            this.bt_zigbeeSensors.Location = new System.Drawing.Point(271, 210);
            this.bt_zigbeeSensors.Name = "bt_zigbeeSensors";
            this.bt_zigbeeSensors.Size = new System.Drawing.Size(127, 36);
            this.bt_zigbeeSensors.TabIndex = 2;
            this.bt_zigbeeSensors.Text = "Подключенные датчики";
            this.bt_zigbeeSensors.UseVisualStyleBackColor = true;
            // 
            // bt_zigbeeConnect
            // 
            this.bt_zigbeeConnect.Location = new System.Drawing.Point(70, 210);
            this.bt_zigbeeConnect.Name = "bt_zigbeeConnect";
            this.bt_zigbeeConnect.Size = new System.Drawing.Size(127, 36);
            this.bt_zigbeeConnect.TabIndex = 1;
            this.bt_zigbeeConnect.Text = "Режим сопряжения";
            this.bt_zigbeeConnect.UseVisualStyleBackColor = true;
            // 
            // rtb_zigbee
            // 
            this.rtb_zigbee.ContextMenuStrip = this.rtb1_menu;
            this.rtb_zigbee.Location = new System.Drawing.Point(64, 74);
            this.rtb_zigbee.Name = "rtb_zigbee";
            this.rtb_zigbee.ReadOnly = true;
            this.rtb_zigbee.Size = new System.Drawing.Size(340, 130);
            this.rtb_zigbee.TabIndex = 63;
            this.rtb_zigbee.Text = "";
            // 
            // image_zigbee_logo
            // 
            this.image_zigbee_logo.BackColor = System.Drawing.Color.White;
            this.image_zigbee_logo.Image = global::LIC_settings.Properties.Resources.zigbee_logo;
            this.image_zigbee_logo.InitialImage = null;
            this.image_zigbee_logo.Location = new System.Drawing.Point(64, 8);
            this.image_zigbee_logo.Name = "image_zigbee_logo";
            this.image_zigbee_logo.Size = new System.Drawing.Size(340, 60);
            this.image_zigbee_logo.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.image_zigbee_logo.TabIndex = 59;
            this.image_zigbee_logo.TabStop = false;
            // 
            // tab_rs1
            // 
            this.tab_rs1.BackColor = System.Drawing.Color.WhiteSmoke;
            this.tab_rs1.Controls.Add(this.pb_bt_back5);
            this.tab_rs1.Controls.Add(this.gb_rs1_sensors);
            this.tab_rs1.Controls.Add(this.gb_rs1_settings);
            this.tab_rs1.Location = new System.Drawing.Point(4, 24);
            this.tab_rs1.Name = "tab_rs1";
            this.tab_rs1.Size = new System.Drawing.Size(426, 563);
            this.tab_rs1.TabIndex = 4;
            this.tab_rs1.Text = "RS1";
            // 
            // pb_bt_back5
            // 
            this.pb_bt_back5.Cursor = System.Windows.Forms.Cursors.Hand;
            this.pb_bt_back5.Image = global::LIC_settings.Properties.Resources.bt_back;
            this.pb_bt_back5.Location = new System.Drawing.Point(8, 8);
            this.pb_bt_back5.Name = "pb_bt_back5";
            this.pb_bt_back5.Size = new System.Drawing.Size(40, 40);
            this.pb_bt_back5.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.pb_bt_back5.TabIndex = 32;
            this.pb_bt_back5.TabStop = false;
            this.pb_bt_back5.Click += new System.EventHandler(this.bt_back1_Click);
            // 
            // gb_rs1_sensors
            // 
            this.gb_rs1_sensors.BackColor = System.Drawing.Color.White;
            this.gb_rs1_sensors.Controls.Add(this.lb_rs1_sensorsCount);
            this.gb_rs1_sensors.Controls.Add(this.bt_rs1_sensorsWrite);
            this.gb_rs1_sensors.Controls.Add(this.bt_rs1_sensorsRead);
            this.gb_rs1_sensors.Controls.Add(this.dg_rs1_sensors);
            this.gb_rs1_sensors.Location = new System.Drawing.Point(8, 248);
            this.gb_rs1_sensors.Name = "gb_rs1_sensors";
            this.gb_rs1_sensors.Size = new System.Drawing.Size(410, 310);
            this.gb_rs1_sensors.TabIndex = 6;
            this.gb_rs1_sensors.TabStop = false;
            this.gb_rs1_sensors.Text = "Датчики";
            // 
            // lb_rs1_sensorsCount
            // 
            this.lb_rs1_sensorsCount.AutoSize = true;
            this.lb_rs1_sensorsCount.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lb_rs1_sensorsCount.Location = new System.Drawing.Point(6, 280);
            this.lb_rs1_sensorsCount.Name = "lb_rs1_sensorsCount";
            this.lb_rs1_sensorsCount.Size = new System.Drawing.Size(107, 17);
            this.lb_rs1_sensorsCount.TabIndex = 12;
            this.lb_rs1_sensorsCount.Text = "rs1_sensorsCnt";
            // 
            // bt_rs1_sensorsWrite
            // 
            this.bt_rs1_sensorsWrite.Cursor = System.Windows.Forms.Cursors.Hand;
            this.bt_rs1_sensorsWrite.Image = global::LIC_settings.Properties.Resources.bt_write;
            this.bt_rs1_sensorsWrite.Location = new System.Drawing.Point(293, 277);
            this.bt_rs1_sensorsWrite.Name = "bt_rs1_sensorsWrite";
            this.bt_rs1_sensorsWrite.Size = new System.Drawing.Size(80, 25);
            this.bt_rs1_sensorsWrite.SizeMode = System.Windows.Forms.PictureBoxSizeMode.CenterImage;
            this.bt_rs1_sensorsWrite.TabIndex = 11;
            this.bt_rs1_sensorsWrite.TabStop = false;
            this.bt_rs1_sensorsWrite.Click += new System.EventHandler(this.bt_rs1_sensorsWrite_Click);
            this.bt_rs1_sensorsWrite.MouseDown += new System.Windows.Forms.MouseEventHandler(this.bt_MouseDown);
            this.bt_rs1_sensorsWrite.MouseLeave += new System.EventHandler(this.bt_MouseLeave);
            this.bt_rs1_sensorsWrite.MouseUp += new System.Windows.Forms.MouseEventHandler(this.bt_MouseUp);
            // 
            // bt_rs1_sensorsRead
            // 
            this.bt_rs1_sensorsRead.Cursor = System.Windows.Forms.Cursors.Hand;
            this.bt_rs1_sensorsRead.Image = global::LIC_settings.Properties.Resources.bt_read;
            this.bt_rs1_sensorsRead.Location = new System.Drawing.Point(202, 277);
            this.bt_rs1_sensorsRead.Name = "bt_rs1_sensorsRead";
            this.bt_rs1_sensorsRead.Size = new System.Drawing.Size(80, 25);
            this.bt_rs1_sensorsRead.SizeMode = System.Windows.Forms.PictureBoxSizeMode.CenterImage;
            this.bt_rs1_sensorsRead.TabIndex = 10;
            this.bt_rs1_sensorsRead.TabStop = false;
            this.bt_rs1_sensorsRead.Click += new System.EventHandler(this.bt_rs1_sensorsRead_Click);
            this.bt_rs1_sensorsRead.MouseDown += new System.Windows.Forms.MouseEventHandler(this.bt_MouseDown);
            this.bt_rs1_sensorsRead.MouseLeave += new System.EventHandler(this.bt_MouseLeave);
            this.bt_rs1_sensorsRead.MouseUp += new System.Windows.Forms.MouseEventHandler(this.bt_MouseUp);
            // 
            // dg_rs1_sensors
            // 
            this.dg_rs1_sensors.AllowUserToResizeColumns = false;
            this.dg_rs1_sensors.AllowUserToResizeRows = false;
            this.dg_rs1_sensors.BackgroundColor = System.Drawing.SystemColors.Control;
            this.dg_rs1_sensors.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dg_rs1_sensors.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.c_sensorType,
            this.c_reqPeriod,
            this.c_address,
            this.c_id});
            this.dg_rs1_sensors.ContextMenuStrip = this.rs_sensors_menu;
            this.dg_rs1_sensors.Location = new System.Drawing.Point(6, 19);
            this.dg_rs1_sensors.Name = "dg_rs1_sensors";
            this.dg_rs1_sensors.RowHeadersVisible = false;
            this.dg_rs1_sensors.Size = new System.Drawing.Size(398, 252);
            this.dg_rs1_sensors.TabIndex = 0;
            this.dg_rs1_sensors.CellMouseEnter += new System.Windows.Forms.DataGridViewCellEventHandler(this.dg_rs1_sensors_CellMouseEnter);
            this.dg_rs1_sensors.CellValidating += new System.Windows.Forms.DataGridViewCellValidatingEventHandler(this.dg_rs1_sensors_CellValidating);
            this.dg_rs1_sensors.CellValueChanged += new System.Windows.Forms.DataGridViewCellEventHandler(this.dg_rs1_sensors_CellValueChanged);
            this.dg_rs1_sensors.CurrentCellDirtyStateChanged += new System.EventHandler(this.dg_rs1_sensors_CurrentCellDirtyStateChanged);
            // 
            // c_sensorType
            // 
            this.c_sensorType.Frozen = true;
            this.c_sensorType.HeaderText = "Датчик";
            this.c_sensorType.MinimumWidth = 100;
            this.c_sensorType.Name = "c_sensorType";
            this.c_sensorType.Width = 130;
            // 
            // c_reqPeriod
            // 
            this.c_reqPeriod.Frozen = true;
            this.c_reqPeriod.HeaderText = "Период опроса, с";
            this.c_reqPeriod.Name = "c_reqPeriod";
            this.c_reqPeriod.Width = 120;
            // 
            // c_address
            // 
            this.c_address.HeaderText = "Адрес ModBus";
            this.c_address.Name = "c_address";
            this.c_address.Width = 105;
            // 
            // c_id
            // 
            this.c_id.HeaderText = "ID";
            this.c_id.Name = "c_id";
            this.c_id.Width = 40;
            // 
            // rs_sensors_menu
            // 
            this.rs_sensors_menu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.loadRSSensorsConfig,
            this.saveRSSensorsConfig,
            this.saveAllToolStripMenuItem,
            this.sepToolStripMenuItem,
            this.reqMQTTToolStripMenuItem,
            this.addSensorMQTTToolStripMenuItem,
            this.delSensorMQTTToolStripMenuItem,
            this.delAllMQTTToolStripMenuItem,
            this.rrToolStripMenuItem,
            this.deleteRowToolStripMenuItem,
            this.clear_rsSensorsTable});
            this.rs_sensors_menu.Name = "rs_sensors_menu";
            this.rs_sensors_menu.Size = new System.Drawing.Size(220, 214);
            // 
            // loadRSSensorsConfig
            // 
            this.loadRSSensorsConfig.Image = global::LIC_settings.Properties.Resources.open;
            this.loadRSSensorsConfig.Name = "loadRSSensorsConfig";
            this.loadRSSensorsConfig.Size = new System.Drawing.Size(219, 22);
            this.loadRSSensorsConfig.Text = "Загрузить";
            this.loadRSSensorsConfig.Click += new System.EventHandler(this.loadRSSensorsConfig_Click);
            // 
            // saveRSSensorsConfig
            // 
            this.saveRSSensorsConfig.Image = global::LIC_settings.Properties.Resources.save;
            this.saveRSSensorsConfig.Name = "saveRSSensorsConfig";
            this.saveRSSensorsConfig.Size = new System.Drawing.Size(219, 22);
            this.saveRSSensorsConfig.Text = "Сохранить";
            this.saveRSSensorsConfig.Click += new System.EventHandler(this.saveRSSensorsConfig_Click);
            // 
            // saveAllToolStripMenuItem
            // 
            this.saveAllToolStripMenuItem.Image = global::LIC_settings.Properties.Resources.save_all;
            this.saveAllToolStripMenuItem.Name = "saveAllToolStripMenuItem";
            this.saveAllToolStripMenuItem.Size = new System.Drawing.Size(219, 22);
            this.saveAllToolStripMenuItem.Text = "Сохранить все интерфесы";
            this.saveAllToolStripMenuItem.Click += new System.EventHandler(this.saveAllToolStripMenuItem_Click);
            // 
            // sepToolStripMenuItem
            // 
            this.sepToolStripMenuItem.Name = "sepToolStripMenuItem";
            this.sepToolStripMenuItem.Size = new System.Drawing.Size(216, 6);
            // 
            // reqMQTTToolStripMenuItem
            // 
            this.reqMQTTToolStripMenuItem.Image = global::LIC_settings.Properties.Resources.request;
            this.reqMQTTToolStripMenuItem.Name = "reqMQTTToolStripMenuItem";
            this.reqMQTTToolStripMenuItem.Size = new System.Drawing.Size(219, 22);
            this.reqMQTTToolStripMenuItem.Text = "Запросить по MQTT";
            this.reqMQTTToolStripMenuItem.Click += new System.EventHandler(this.reqMQTTToolStripMenuItem_Click);
            // 
            // addSensorMQTTToolStripMenuItem
            // 
            this.addSensorMQTTToolStripMenuItem.Image = global::LIC_settings.Properties.Resources.add;
            this.addSensorMQTTToolStripMenuItem.Name = "addSensorMQTTToolStripMenuItem";
            this.addSensorMQTTToolStripMenuItem.Size = new System.Drawing.Size(219, 22);
            this.addSensorMQTTToolStripMenuItem.Text = "Добавить по MQTT";
            this.addSensorMQTTToolStripMenuItem.Click += new System.EventHandler(this.addSensorMQTTToolStripMenuItem_Click);
            // 
            // delSensorMQTTToolStripMenuItem
            // 
            this.delSensorMQTTToolStripMenuItem.Image = global::LIC_settings.Properties.Resources.trash;
            this.delSensorMQTTToolStripMenuItem.Name = "delSensorMQTTToolStripMenuItem";
            this.delSensorMQTTToolStripMenuItem.Size = new System.Drawing.Size(219, 22);
            this.delSensorMQTTToolStripMenuItem.Text = "Удалить по MQTT";
            this.delSensorMQTTToolStripMenuItem.Click += new System.EventHandler(this.delSensorMQTTToolStripMenuItem_Click);
            // 
            // delAllMQTTToolStripMenuItem
            // 
            this.delAllMQTTToolStripMenuItem.Image = global::LIC_settings.Properties.Resources.delete;
            this.delAllMQTTToolStripMenuItem.Name = "delAllMQTTToolStripMenuItem";
            this.delAllMQTTToolStripMenuItem.Size = new System.Drawing.Size(219, 22);
            this.delAllMQTTToolStripMenuItem.Text = "Удалить все по MQTT";
            this.delAllMQTTToolStripMenuItem.Click += new System.EventHandler(this.delAllMQTTToolStripMenuItem_Click);
            // 
            // rrToolStripMenuItem
            // 
            this.rrToolStripMenuItem.Name = "rrToolStripMenuItem";
            this.rrToolStripMenuItem.Size = new System.Drawing.Size(216, 6);
            // 
            // deleteRowToolStripMenuItem
            // 
            this.deleteRowToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("deleteRowToolStripMenuItem.Image")));
            this.deleteRowToolStripMenuItem.Name = "deleteRowToolStripMenuItem";
            this.deleteRowToolStripMenuItem.Size = new System.Drawing.Size(219, 22);
            this.deleteRowToolStripMenuItem.Text = "Удалить строку";
            this.deleteRowToolStripMenuItem.Click += new System.EventHandler(this.deleteRowToolStripMenuItem_Click);
            // 
            // clear_rsSensorsTable
            // 
            this.clear_rsSensorsTable.Image = global::LIC_settings.Properties.Resources.clear;
            this.clear_rsSensorsTable.Name = "clear_rsSensorsTable";
            this.clear_rsSensorsTable.Size = new System.Drawing.Size(219, 22);
            this.clear_rsSensorsTable.Text = "Очистить таблицу";
            this.clear_rsSensorsTable.Click += new System.EventHandler(this.clear_rsSensorsTable_Click);
            // 
            // gb_rs1_settings
            // 
            this.gb_rs1_settings.BackColor = System.Drawing.Color.White;
            this.gb_rs1_settings.ContextMenuStrip = this.rs_settings_menu;
            this.gb_rs1_settings.Controls.Add(this.label36);
            this.gb_rs1_settings.Controls.Add(this.num_rs1Errors);
            this.gb_rs1_settings.Controls.Add(this.label11);
            this.gb_rs1_settings.Controls.Add(this.num_rs1Delay);
            this.gb_rs1_settings.Controls.Add(this.bt_rs1SettingsWrite);
            this.gb_rs1_settings.Controls.Add(this.bt_rs1SettingsRead);
            this.gb_rs1_settings.Controls.Add(this.chb_rs1_activate);
            this.gb_rs1_settings.Controls.Add(this.cb_rs1_stopbits);
            this.gb_rs1_settings.Controls.Add(this.cb_rs1_parity);
            this.gb_rs1_settings.Controls.Add(this.cb_rs1_databits);
            this.gb_rs1_settings.Controls.Add(this.cb_rs1_baudrate);
            this.gb_rs1_settings.Controls.Add(this.label15);
            this.gb_rs1_settings.Controls.Add(this.label3);
            this.gb_rs1_settings.Controls.Add(this.label2);
            this.gb_rs1_settings.Controls.Add(this.label1);
            this.gb_rs1_settings.Location = new System.Drawing.Point(8, 55);
            this.gb_rs1_settings.Name = "gb_rs1_settings";
            this.gb_rs1_settings.Size = new System.Drawing.Size(410, 187);
            this.gb_rs1_settings.TabIndex = 5;
            this.gb_rs1_settings.TabStop = false;
            this.gb_rs1_settings.Text = "Настройки RS1";
            this.gb_rs1_settings.VisibleChanged += new System.EventHandler(this.gb_rs1_VisibleChanged);
            // 
            // rs_settings_menu
            // 
            this.rs_settings_menu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.readRSSettingsMQTTToolStripMenuItem,
            this.writeRSSettingsMQTTToolStripMenuItem});
            this.rs_settings_menu.Name = "rs_settings_menu";
            this.rs_settings_menu.Size = new System.Drawing.Size(176, 48);
            // 
            // readRSSettingsMQTTToolStripMenuItem
            // 
            this.readRSSettingsMQTTToolStripMenuItem.Image = global::LIC_settings.Properties.Resources.read;
            this.readRSSettingsMQTTToolStripMenuItem.Name = "readRSSettingsMQTTToolStripMenuItem";
            this.readRSSettingsMQTTToolStripMenuItem.Size = new System.Drawing.Size(175, 22);
            this.readRSSettingsMQTTToolStripMenuItem.Text = "Считать по MQTT";
            this.readRSSettingsMQTTToolStripMenuItem.Click += new System.EventHandler(this.readRSSettingsMQTTToolStripMenuItem_Click);
            // 
            // writeRSSettingsMQTTToolStripMenuItem
            // 
            this.writeRSSettingsMQTTToolStripMenuItem.Image = global::LIC_settings.Properties.Resources.write;
            this.writeRSSettingsMQTTToolStripMenuItem.Name = "writeRSSettingsMQTTToolStripMenuItem";
            this.writeRSSettingsMQTTToolStripMenuItem.Size = new System.Drawing.Size(175, 22);
            this.writeRSSettingsMQTTToolStripMenuItem.Text = "Записать по MQTT";
            this.writeRSSettingsMQTTToolStripMenuItem.Click += new System.EventHandler(this.writeRSSettingsMQTTToolStripMenuItem_Click);
            // 
            // label36
            // 
            this.label36.AutoSize = true;
            this.label36.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label36.Location = new System.Drawing.Point(13, 153);
            this.label36.Margin = new System.Windows.Forms.Padding(3, 3, 3, 0);
            this.label36.Name = "label36";
            this.label36.Size = new System.Drawing.Size(61, 17);
            this.label36.TabIndex = 13;
            this.label36.Text = "Ошибки";
            this.label36.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.toolTip.SetToolTip(this.label36, "Количество ошибок считывания датчика перед его отключением");
            // 
            // num_rs1Errors
            // 
            this.num_rs1Errors.Location = new System.Drawing.Point(124, 153);
            this.num_rs1Errors.Name = "num_rs1Errors";
            this.num_rs1Errors.Size = new System.Drawing.Size(122, 20);
            this.num_rs1Errors.TabIndex = 12;
            this.num_rs1Errors.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.num_rs1Errors.Value = new decimal(new int[] {
            20,
            0,
            0,
            0});
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label11.Location = new System.Drawing.Point(13, 127);
            this.label11.Margin = new System.Windows.Forms.Padding(3, 3, 3, 0);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(88, 17);
            this.label11.TabIndex = 11;
            this.label11.Text = "Задержка, с";
            this.label11.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.toolTip.SetToolTip(this.label11, "Задержка перед первым считыванием после включения");
            // 
            // num_rs1Delay
            // 
            this.num_rs1Delay.Location = new System.Drawing.Point(124, 127);
            this.num_rs1Delay.Maximum = new decimal(new int[] {
            60,
            0,
            0,
            0});
            this.num_rs1Delay.Name = "num_rs1Delay";
            this.num_rs1Delay.Size = new System.Drawing.Size(122, 20);
            this.num_rs1Delay.TabIndex = 10;
            this.num_rs1Delay.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.num_rs1Delay.Value = new decimal(new int[] {
            10,
            0,
            0,
            0});
            // 
            // bt_rs1SettingsWrite
            // 
            this.bt_rs1SettingsWrite.Cursor = System.Windows.Forms.Cursors.Hand;
            this.bt_rs1SettingsWrite.Image = global::LIC_settings.Properties.Resources.bt_write;
            this.bt_rs1SettingsWrite.Location = new System.Drawing.Point(293, 148);
            this.bt_rs1SettingsWrite.Name = "bt_rs1SettingsWrite";
            this.bt_rs1SettingsWrite.Size = new System.Drawing.Size(80, 25);
            this.bt_rs1SettingsWrite.SizeMode = System.Windows.Forms.PictureBoxSizeMode.CenterImage;
            this.bt_rs1SettingsWrite.TabIndex = 9;
            this.bt_rs1SettingsWrite.TabStop = false;
            this.bt_rs1SettingsWrite.Click += new System.EventHandler(this.bt_rs1SettingsWrite_Click);
            this.bt_rs1SettingsWrite.MouseDown += new System.Windows.Forms.MouseEventHandler(this.bt_MouseDown);
            this.bt_rs1SettingsWrite.MouseLeave += new System.EventHandler(this.bt_MouseLeave);
            this.bt_rs1SettingsWrite.MouseUp += new System.Windows.Forms.MouseEventHandler(this.bt_MouseUp);
            // 
            // bt_rs1SettingsRead
            // 
            this.bt_rs1SettingsRead.Cursor = System.Windows.Forms.Cursors.Hand;
            this.bt_rs1SettingsRead.Image = global::LIC_settings.Properties.Resources.bt_read;
            this.bt_rs1SettingsRead.Location = new System.Drawing.Point(293, 122);
            this.bt_rs1SettingsRead.Name = "bt_rs1SettingsRead";
            this.bt_rs1SettingsRead.Size = new System.Drawing.Size(80, 25);
            this.bt_rs1SettingsRead.SizeMode = System.Windows.Forms.PictureBoxSizeMode.CenterImage;
            this.bt_rs1SettingsRead.TabIndex = 8;
            this.bt_rs1SettingsRead.TabStop = false;
            this.bt_rs1SettingsRead.Click += new System.EventHandler(this.bt_rs1SettingsRead_Click);
            this.bt_rs1SettingsRead.MouseDown += new System.Windows.Forms.MouseEventHandler(this.bt_MouseDown);
            this.bt_rs1SettingsRead.MouseLeave += new System.EventHandler(this.bt_MouseLeave);
            this.bt_rs1SettingsRead.MouseUp += new System.Windows.Forms.MouseEventHandler(this.bt_MouseUp);
            // 
            // chb_rs1_activate
            // 
            this.chb_rs1_activate.AutoSize = true;
            this.chb_rs1_activate.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.chb_rs1_activate.Location = new System.Drawing.Point(274, 20);
            this.chb_rs1_activate.Name = "chb_rs1_activate";
            this.chb_rs1_activate.Size = new System.Drawing.Size(118, 21);
            this.chb_rs1_activate.TabIndex = 2;
            this.chb_rs1_activate.Text = "Активировать";
            this.chb_rs1_activate.UseVisualStyleBackColor = true;
            // 
            // cb_rs1_stopbits
            // 
            this.cb_rs1_stopbits.FormattingEnabled = true;
            this.cb_rs1_stopbits.Items.AddRange(new object[] {
            "1",
            "2"});
            this.cb_rs1_stopbits.Location = new System.Drawing.Point(124, 100);
            this.cb_rs1_stopbits.Name = "cb_rs1_stopbits";
            this.cb_rs1_stopbits.Size = new System.Drawing.Size(121, 21);
            this.cb_rs1_stopbits.TabIndex = 5;
            // 
            // cb_rs1_parity
            // 
            this.cb_rs1_parity.FormattingEnabled = true;
            this.cb_rs1_parity.Items.AddRange(new object[] {
            "none",
            "even",
            "odd"});
            this.cb_rs1_parity.Location = new System.Drawing.Point(124, 73);
            this.cb_rs1_parity.Name = "cb_rs1_parity";
            this.cb_rs1_parity.Size = new System.Drawing.Size(121, 21);
            this.cb_rs1_parity.TabIndex = 4;
            // 
            // cb_rs1_databits
            // 
            this.cb_rs1_databits.FormattingEnabled = true;
            this.cb_rs1_databits.Items.AddRange(new object[] {
            "8",
            "9"});
            this.cb_rs1_databits.Location = new System.Drawing.Point(124, 46);
            this.cb_rs1_databits.Name = "cb_rs1_databits";
            this.cb_rs1_databits.Size = new System.Drawing.Size(121, 21);
            this.cb_rs1_databits.TabIndex = 3;
            // 
            // cb_rs1_baudrate
            // 
            this.cb_rs1_baudrate.FormattingEnabled = true;
            this.cb_rs1_baudrate.Items.AddRange(new object[] {
            "9600",
            "19200",
            "115200",
            "256000"});
            this.cb_rs1_baudrate.Location = new System.Drawing.Point(124, 19);
            this.cb_rs1_baudrate.Name = "cb_rs1_baudrate";
            this.cb_rs1_baudrate.Size = new System.Drawing.Size(121, 21);
            this.cb_rs1_baudrate.TabIndex = 1;
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label15.Location = new System.Drawing.Point(12, 101);
            this.label15.Margin = new System.Windows.Forms.Padding(3, 3, 3, 0);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(63, 17);
            this.label15.TabIndex = 3;
            this.label15.Text = "Stop bits";
            this.label15.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label3.Location = new System.Drawing.Point(12, 74);
            this.label3.Margin = new System.Windows.Forms.Padding(3, 3, 3, 0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(44, 17);
            this.label3.TabIndex = 2;
            this.label3.Text = "Parity";
            this.label3.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label2.Location = new System.Drawing.Point(12, 47);
            this.label2.Margin = new System.Windows.Forms.Padding(3, 3, 3, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(64, 17);
            this.label2.TabIndex = 1;
            this.label2.Text = "Data bits";
            this.label2.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label1.Location = new System.Drawing.Point(12, 20);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(70, 17);
            this.label1.TabIndex = 0;
            this.label1.Text = "Baud rate";
            this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // tab_rs2
            // 
            this.tab_rs2.BackColor = System.Drawing.Color.WhiteSmoke;
            this.tab_rs2.Controls.Add(this.pb_bt_back6);
            this.tab_rs2.Controls.Add(this.groupBox2);
            this.tab_rs2.Controls.Add(this.gb_rs2_settings);
            this.tab_rs2.Location = new System.Drawing.Point(4, 24);
            this.tab_rs2.Name = "tab_rs2";
            this.tab_rs2.Size = new System.Drawing.Size(426, 563);
            this.tab_rs2.TabIndex = 5;
            this.tab_rs2.Text = "RS2";
            // 
            // pb_bt_back6
            // 
            this.pb_bt_back6.Cursor = System.Windows.Forms.Cursors.Hand;
            this.pb_bt_back6.Image = global::LIC_settings.Properties.Resources.bt_back;
            this.pb_bt_back6.Location = new System.Drawing.Point(8, 8);
            this.pb_bt_back6.Name = "pb_bt_back6";
            this.pb_bt_back6.Size = new System.Drawing.Size(40, 40);
            this.pb_bt_back6.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.pb_bt_back6.TabIndex = 32;
            this.pb_bt_back6.TabStop = false;
            this.pb_bt_back6.Click += new System.EventHandler(this.bt_back1_Click);
            // 
            // groupBox2
            // 
            this.groupBox2.BackColor = System.Drawing.Color.White;
            this.groupBox2.Controls.Add(this.lb_rs2_sensorsCount);
            this.groupBox2.Controls.Add(this.bt_rs2_sensorsWrite);
            this.groupBox2.Controls.Add(this.bt_rs2_sensorsRead);
            this.groupBox2.Controls.Add(this.dg_rs2_sensors);
            this.groupBox2.Location = new System.Drawing.Point(8, 248);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(410, 310);
            this.groupBox2.TabIndex = 9;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Датчики";
            // 
            // lb_rs2_sensorsCount
            // 
            this.lb_rs2_sensorsCount.AutoSize = true;
            this.lb_rs2_sensorsCount.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lb_rs2_sensorsCount.Location = new System.Drawing.Point(6, 280);
            this.lb_rs2_sensorsCount.Name = "lb_rs2_sensorsCount";
            this.lb_rs2_sensorsCount.Size = new System.Drawing.Size(107, 17);
            this.lb_rs2_sensorsCount.TabIndex = 13;
            this.lb_rs2_sensorsCount.Text = "rs2_sensorsCnt";
            // 
            // bt_rs2_sensorsWrite
            // 
            this.bt_rs2_sensorsWrite.Cursor = System.Windows.Forms.Cursors.Hand;
            this.bt_rs2_sensorsWrite.Image = global::LIC_settings.Properties.Resources.bt_write;
            this.bt_rs2_sensorsWrite.Location = new System.Drawing.Point(293, 277);
            this.bt_rs2_sensorsWrite.Name = "bt_rs2_sensorsWrite";
            this.bt_rs2_sensorsWrite.Size = new System.Drawing.Size(80, 25);
            this.bt_rs2_sensorsWrite.SizeMode = System.Windows.Forms.PictureBoxSizeMode.CenterImage;
            this.bt_rs2_sensorsWrite.TabIndex = 11;
            this.bt_rs2_sensorsWrite.TabStop = false;
            this.bt_rs2_sensorsWrite.Click += new System.EventHandler(this.bt_rs2_sensorsWrite_Click);
            this.bt_rs2_sensorsWrite.MouseDown += new System.Windows.Forms.MouseEventHandler(this.bt_MouseDown);
            this.bt_rs2_sensorsWrite.MouseLeave += new System.EventHandler(this.bt_MouseLeave);
            this.bt_rs2_sensorsWrite.MouseUp += new System.Windows.Forms.MouseEventHandler(this.bt_MouseUp);
            // 
            // bt_rs2_sensorsRead
            // 
            this.bt_rs2_sensorsRead.Cursor = System.Windows.Forms.Cursors.Hand;
            this.bt_rs2_sensorsRead.Image = global::LIC_settings.Properties.Resources.bt_read;
            this.bt_rs2_sensorsRead.Location = new System.Drawing.Point(202, 277);
            this.bt_rs2_sensorsRead.Name = "bt_rs2_sensorsRead";
            this.bt_rs2_sensorsRead.Size = new System.Drawing.Size(80, 25);
            this.bt_rs2_sensorsRead.SizeMode = System.Windows.Forms.PictureBoxSizeMode.CenterImage;
            this.bt_rs2_sensorsRead.TabIndex = 10;
            this.bt_rs2_sensorsRead.TabStop = false;
            this.bt_rs2_sensorsRead.Click += new System.EventHandler(this.bt_rs2_sensorsRead_Click);
            this.bt_rs2_sensorsRead.MouseDown += new System.Windows.Forms.MouseEventHandler(this.bt_MouseDown);
            this.bt_rs2_sensorsRead.MouseLeave += new System.EventHandler(this.bt_MouseLeave);
            this.bt_rs2_sensorsRead.MouseUp += new System.Windows.Forms.MouseEventHandler(this.bt_MouseUp);
            // 
            // dg_rs2_sensors
            // 
            this.dg_rs2_sensors.AllowUserToResizeColumns = false;
            this.dg_rs2_sensors.AllowUserToResizeRows = false;
            this.dg_rs2_sensors.BackgroundColor = System.Drawing.SystemColors.Control;
            this.dg_rs2_sensors.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dg_rs2_sensors.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.c_rs2_name,
            this.c_rs2_pollPeriod,
            this.c_rs2_address,
            this.c_rs2_id});
            this.dg_rs2_sensors.ContextMenuStrip = this.rs_sensors_menu;
            this.dg_rs2_sensors.Location = new System.Drawing.Point(6, 19);
            this.dg_rs2_sensors.Name = "dg_rs2_sensors";
            this.dg_rs2_sensors.RowHeadersVisible = false;
            this.dg_rs2_sensors.Size = new System.Drawing.Size(398, 252);
            this.dg_rs2_sensors.TabIndex = 0;
            this.dg_rs2_sensors.CellMouseEnter += new System.Windows.Forms.DataGridViewCellEventHandler(this.dg_rs1_sensors_CellMouseEnter);
            this.dg_rs2_sensors.CellValidating += new System.Windows.Forms.DataGridViewCellValidatingEventHandler(this.dg_rs1_sensors_CellValidating);
            this.dg_rs2_sensors.CellValueChanged += new System.Windows.Forms.DataGridViewCellEventHandler(this.dg_rs1_sensors_CellValueChanged);
            this.dg_rs2_sensors.CurrentCellDirtyStateChanged += new System.EventHandler(this.dg_rs1_sensors_CurrentCellDirtyStateChanged);
            // 
            // c_rs2_name
            // 
            this.c_rs2_name.Frozen = true;
            this.c_rs2_name.HeaderText = "Датчик";
            this.c_rs2_name.MinimumWidth = 100;
            this.c_rs2_name.Name = "c_rs2_name";
            this.c_rs2_name.Width = 130;
            // 
            // c_rs2_pollPeriod
            // 
            this.c_rs2_pollPeriod.Frozen = true;
            this.c_rs2_pollPeriod.HeaderText = "Период опроса, с";
            this.c_rs2_pollPeriod.Name = "c_rs2_pollPeriod";
            this.c_rs2_pollPeriod.Width = 120;
            // 
            // c_rs2_address
            // 
            this.c_rs2_address.HeaderText = "Адрес ModBus";
            this.c_rs2_address.Name = "c_rs2_address";
            this.c_rs2_address.Width = 105;
            // 
            // c_rs2_id
            // 
            this.c_rs2_id.HeaderText = "ID";
            this.c_rs2_id.Name = "c_rs2_id";
            this.c_rs2_id.Width = 40;
            // 
            // gb_rs2_settings
            // 
            this.gb_rs2_settings.BackColor = System.Drawing.Color.White;
            this.gb_rs2_settings.ContextMenuStrip = this.rs_settings_menu;
            this.gb_rs2_settings.Controls.Add(this.label37);
            this.gb_rs2_settings.Controls.Add(this.num_rs2Errors);
            this.gb_rs2_settings.Controls.Add(this.label38);
            this.gb_rs2_settings.Controls.Add(this.num_rs2Delay);
            this.gb_rs2_settings.Controls.Add(this.bt_rs2SettingsWrite);
            this.gb_rs2_settings.Controls.Add(this.bt_rs2SettingsRead);
            this.gb_rs2_settings.Controls.Add(this.chb_rs2_activate);
            this.gb_rs2_settings.Controls.Add(this.cb_rs2_stopbits);
            this.gb_rs2_settings.Controls.Add(this.cb_rs2_parity);
            this.gb_rs2_settings.Controls.Add(this.cb_rs2_databits);
            this.gb_rs2_settings.Controls.Add(this.cb_rs2_baudrate);
            this.gb_rs2_settings.Controls.Add(this.label24);
            this.gb_rs2_settings.Controls.Add(this.label27);
            this.gb_rs2_settings.Controls.Add(this.label28);
            this.gb_rs2_settings.Controls.Add(this.label29);
            this.gb_rs2_settings.Location = new System.Drawing.Point(8, 55);
            this.gb_rs2_settings.Name = "gb_rs2_settings";
            this.gb_rs2_settings.Size = new System.Drawing.Size(410, 187);
            this.gb_rs2_settings.TabIndex = 8;
            this.gb_rs2_settings.TabStop = false;
            this.gb_rs2_settings.Text = "Настройки RS2";
            // 
            // label37
            // 
            this.label37.AutoSize = true;
            this.label37.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label37.Location = new System.Drawing.Point(13, 153);
            this.label37.Margin = new System.Windows.Forms.Padding(3, 3, 3, 0);
            this.label37.Name = "label37";
            this.label37.Size = new System.Drawing.Size(61, 17);
            this.label37.TabIndex = 17;
            this.label37.Text = "Ошибки";
            this.label37.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.toolTip.SetToolTip(this.label37, "Количество ошибок считывания датчика перед его отключением");
            // 
            // num_rs2Errors
            // 
            this.num_rs2Errors.Location = new System.Drawing.Point(124, 153);
            this.num_rs2Errors.Name = "num_rs2Errors";
            this.num_rs2Errors.Size = new System.Drawing.Size(122, 20);
            this.num_rs2Errors.TabIndex = 16;
            this.num_rs2Errors.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.num_rs2Errors.Value = new decimal(new int[] {
            20,
            0,
            0,
            0});
            // 
            // label38
            // 
            this.label38.AutoSize = true;
            this.label38.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label38.Location = new System.Drawing.Point(13, 127);
            this.label38.Margin = new System.Windows.Forms.Padding(3, 3, 3, 0);
            this.label38.Name = "label38";
            this.label38.Size = new System.Drawing.Size(88, 17);
            this.label38.TabIndex = 15;
            this.label38.Text = "Задержка, с";
            this.label38.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.toolTip.SetToolTip(this.label38, "Задержка перед первым считыванием после включения");
            // 
            // num_rs2Delay
            // 
            this.num_rs2Delay.Location = new System.Drawing.Point(124, 127);
            this.num_rs2Delay.Maximum = new decimal(new int[] {
            60,
            0,
            0,
            0});
            this.num_rs2Delay.Name = "num_rs2Delay";
            this.num_rs2Delay.Size = new System.Drawing.Size(122, 20);
            this.num_rs2Delay.TabIndex = 14;
            this.num_rs2Delay.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.num_rs2Delay.Value = new decimal(new int[] {
            10,
            0,
            0,
            0});
            // 
            // bt_rs2SettingsWrite
            // 
            this.bt_rs2SettingsWrite.Cursor = System.Windows.Forms.Cursors.Hand;
            this.bt_rs2SettingsWrite.Image = global::LIC_settings.Properties.Resources.bt_write;
            this.bt_rs2SettingsWrite.Location = new System.Drawing.Point(293, 148);
            this.bt_rs2SettingsWrite.Name = "bt_rs2SettingsWrite";
            this.bt_rs2SettingsWrite.Size = new System.Drawing.Size(80, 25);
            this.bt_rs2SettingsWrite.SizeMode = System.Windows.Forms.PictureBoxSizeMode.CenterImage;
            this.bt_rs2SettingsWrite.TabIndex = 9;
            this.bt_rs2SettingsWrite.TabStop = false;
            this.bt_rs2SettingsWrite.Click += new System.EventHandler(this.bt_rs2SettingsWrite_Click);
            this.bt_rs2SettingsWrite.MouseDown += new System.Windows.Forms.MouseEventHandler(this.bt_MouseDown);
            this.bt_rs2SettingsWrite.MouseLeave += new System.EventHandler(this.bt_MouseLeave);
            this.bt_rs2SettingsWrite.MouseUp += new System.Windows.Forms.MouseEventHandler(this.bt_MouseUp);
            // 
            // bt_rs2SettingsRead
            // 
            this.bt_rs2SettingsRead.Cursor = System.Windows.Forms.Cursors.Hand;
            this.bt_rs2SettingsRead.Image = global::LIC_settings.Properties.Resources.bt_read;
            this.bt_rs2SettingsRead.Location = new System.Drawing.Point(293, 122);
            this.bt_rs2SettingsRead.Name = "bt_rs2SettingsRead";
            this.bt_rs2SettingsRead.Size = new System.Drawing.Size(80, 25);
            this.bt_rs2SettingsRead.SizeMode = System.Windows.Forms.PictureBoxSizeMode.CenterImage;
            this.bt_rs2SettingsRead.TabIndex = 8;
            this.bt_rs2SettingsRead.TabStop = false;
            this.bt_rs2SettingsRead.Click += new System.EventHandler(this.bt_rs2SettingsRead_Click);
            this.bt_rs2SettingsRead.MouseDown += new System.Windows.Forms.MouseEventHandler(this.bt_MouseDown);
            this.bt_rs2SettingsRead.MouseLeave += new System.EventHandler(this.bt_MouseLeave);
            this.bt_rs2SettingsRead.MouseUp += new System.Windows.Forms.MouseEventHandler(this.bt_MouseUp);
            // 
            // chb_rs2_activate
            // 
            this.chb_rs2_activate.AutoSize = true;
            this.chb_rs2_activate.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.chb_rs2_activate.Location = new System.Drawing.Point(274, 20);
            this.chb_rs2_activate.Name = "chb_rs2_activate";
            this.chb_rs2_activate.Size = new System.Drawing.Size(118, 21);
            this.chb_rs2_activate.TabIndex = 2;
            this.chb_rs2_activate.Text = "Активировать";
            this.chb_rs2_activate.UseVisualStyleBackColor = true;
            // 
            // cb_rs2_stopbits
            // 
            this.cb_rs2_stopbits.FormattingEnabled = true;
            this.cb_rs2_stopbits.Items.AddRange(new object[] {
            "1",
            "2"});
            this.cb_rs2_stopbits.Location = new System.Drawing.Point(124, 100);
            this.cb_rs2_stopbits.Name = "cb_rs2_stopbits";
            this.cb_rs2_stopbits.Size = new System.Drawing.Size(121, 21);
            this.cb_rs2_stopbits.TabIndex = 5;
            // 
            // cb_rs2_parity
            // 
            this.cb_rs2_parity.FormattingEnabled = true;
            this.cb_rs2_parity.Items.AddRange(new object[] {
            "none",
            "even",
            "odd"});
            this.cb_rs2_parity.Location = new System.Drawing.Point(124, 73);
            this.cb_rs2_parity.Name = "cb_rs2_parity";
            this.cb_rs2_parity.Size = new System.Drawing.Size(121, 21);
            this.cb_rs2_parity.TabIndex = 4;
            // 
            // cb_rs2_databits
            // 
            this.cb_rs2_databits.FormattingEnabled = true;
            this.cb_rs2_databits.Items.AddRange(new object[] {
            "8",
            "9"});
            this.cb_rs2_databits.Location = new System.Drawing.Point(124, 46);
            this.cb_rs2_databits.Name = "cb_rs2_databits";
            this.cb_rs2_databits.Size = new System.Drawing.Size(121, 21);
            this.cb_rs2_databits.TabIndex = 3;
            // 
            // cb_rs2_baudrate
            // 
            this.cb_rs2_baudrate.FormattingEnabled = true;
            this.cb_rs2_baudrate.Items.AddRange(new object[] {
            "9600",
            "19200",
            "115200",
            "256000"});
            this.cb_rs2_baudrate.Location = new System.Drawing.Point(124, 19);
            this.cb_rs2_baudrate.Name = "cb_rs2_baudrate";
            this.cb_rs2_baudrate.Size = new System.Drawing.Size(121, 21);
            this.cb_rs2_baudrate.TabIndex = 1;
            // 
            // label24
            // 
            this.label24.AutoSize = true;
            this.label24.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label24.Location = new System.Drawing.Point(12, 101);
            this.label24.Margin = new System.Windows.Forms.Padding(3, 3, 3, 0);
            this.label24.Name = "label24";
            this.label24.Size = new System.Drawing.Size(63, 17);
            this.label24.TabIndex = 3;
            this.label24.Text = "Stop bits";
            this.label24.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // label27
            // 
            this.label27.AutoSize = true;
            this.label27.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label27.Location = new System.Drawing.Point(12, 74);
            this.label27.Margin = new System.Windows.Forms.Padding(3, 3, 3, 0);
            this.label27.Name = "label27";
            this.label27.Size = new System.Drawing.Size(44, 17);
            this.label27.TabIndex = 2;
            this.label27.Text = "Parity";
            this.label27.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // label28
            // 
            this.label28.AutoSize = true;
            this.label28.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label28.Location = new System.Drawing.Point(12, 47);
            this.label28.Margin = new System.Windows.Forms.Padding(3, 3, 3, 0);
            this.label28.Name = "label28";
            this.label28.Size = new System.Drawing.Size(64, 17);
            this.label28.TabIndex = 1;
            this.label28.Text = "Data bits";
            this.label28.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // label29
            // 
            this.label29.AutoSize = true;
            this.label29.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label29.Location = new System.Drawing.Point(12, 20);
            this.label29.Name = "label29";
            this.label29.Size = new System.Drawing.Size(70, 17);
            this.label29.TabIndex = 0;
            this.label29.Text = "Baud rate";
            this.label29.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // tab_rs3
            // 
            this.tab_rs3.BackColor = System.Drawing.Color.WhiteSmoke;
            this.tab_rs3.Controls.Add(this.pb_bt_back7);
            this.tab_rs3.Controls.Add(this.groupBox4);
            this.tab_rs3.Controls.Add(this.gb_rs3_settings);
            this.tab_rs3.Location = new System.Drawing.Point(4, 24);
            this.tab_rs3.Name = "tab_rs3";
            this.tab_rs3.Size = new System.Drawing.Size(426, 563);
            this.tab_rs3.TabIndex = 6;
            this.tab_rs3.Text = "RS3";
            // 
            // pb_bt_back7
            // 
            this.pb_bt_back7.Cursor = System.Windows.Forms.Cursors.Hand;
            this.pb_bt_back7.Image = global::LIC_settings.Properties.Resources.bt_back;
            this.pb_bt_back7.Location = new System.Drawing.Point(8, 8);
            this.pb_bt_back7.Name = "pb_bt_back7";
            this.pb_bt_back7.Size = new System.Drawing.Size(40, 40);
            this.pb_bt_back7.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.pb_bt_back7.TabIndex = 32;
            this.pb_bt_back7.TabStop = false;
            this.pb_bt_back7.Click += new System.EventHandler(this.bt_back1_Click);
            // 
            // groupBox4
            // 
            this.groupBox4.BackColor = System.Drawing.Color.White;
            this.groupBox4.Controls.Add(this.lb_rs3_sensorsCount);
            this.groupBox4.Controls.Add(this.bt_rs3_sensorsWrite);
            this.groupBox4.Controls.Add(this.bt_rs3_sensorsRead);
            this.groupBox4.Controls.Add(this.dg_rs3_sensors);
            this.groupBox4.Location = new System.Drawing.Point(8, 248);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(410, 310);
            this.groupBox4.TabIndex = 12;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "Датчики";
            // 
            // lb_rs3_sensorsCount
            // 
            this.lb_rs3_sensorsCount.AutoSize = true;
            this.lb_rs3_sensorsCount.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lb_rs3_sensorsCount.Location = new System.Drawing.Point(6, 280);
            this.lb_rs3_sensorsCount.Name = "lb_rs3_sensorsCount";
            this.lb_rs3_sensorsCount.Size = new System.Drawing.Size(107, 17);
            this.lb_rs3_sensorsCount.TabIndex = 14;
            this.lb_rs3_sensorsCount.Text = "rs3_sensorsCnt";
            // 
            // bt_rs3_sensorsWrite
            // 
            this.bt_rs3_sensorsWrite.Cursor = System.Windows.Forms.Cursors.Hand;
            this.bt_rs3_sensorsWrite.Image = global::LIC_settings.Properties.Resources.bt_write;
            this.bt_rs3_sensorsWrite.Location = new System.Drawing.Point(293, 277);
            this.bt_rs3_sensorsWrite.Name = "bt_rs3_sensorsWrite";
            this.bt_rs3_sensorsWrite.Size = new System.Drawing.Size(80, 25);
            this.bt_rs3_sensorsWrite.SizeMode = System.Windows.Forms.PictureBoxSizeMode.CenterImage;
            this.bt_rs3_sensorsWrite.TabIndex = 11;
            this.bt_rs3_sensorsWrite.TabStop = false;
            this.bt_rs3_sensorsWrite.Click += new System.EventHandler(this.bt_rs3_sensorsWrite_Click);
            this.bt_rs3_sensorsWrite.MouseDown += new System.Windows.Forms.MouseEventHandler(this.bt_MouseDown);
            this.bt_rs3_sensorsWrite.MouseLeave += new System.EventHandler(this.bt_MouseLeave);
            this.bt_rs3_sensorsWrite.MouseUp += new System.Windows.Forms.MouseEventHandler(this.bt_MouseUp);
            // 
            // bt_rs3_sensorsRead
            // 
            this.bt_rs3_sensorsRead.Cursor = System.Windows.Forms.Cursors.Hand;
            this.bt_rs3_sensorsRead.Image = global::LIC_settings.Properties.Resources.bt_read;
            this.bt_rs3_sensorsRead.Location = new System.Drawing.Point(202, 277);
            this.bt_rs3_sensorsRead.Name = "bt_rs3_sensorsRead";
            this.bt_rs3_sensorsRead.Size = new System.Drawing.Size(80, 25);
            this.bt_rs3_sensorsRead.SizeMode = System.Windows.Forms.PictureBoxSizeMode.CenterImage;
            this.bt_rs3_sensorsRead.TabIndex = 10;
            this.bt_rs3_sensorsRead.TabStop = false;
            this.bt_rs3_sensorsRead.Click += new System.EventHandler(this.bt_rs3_sensorsRead_Click);
            this.bt_rs3_sensorsRead.MouseDown += new System.Windows.Forms.MouseEventHandler(this.bt_MouseDown);
            this.bt_rs3_sensorsRead.MouseLeave += new System.EventHandler(this.bt_MouseLeave);
            this.bt_rs3_sensorsRead.MouseUp += new System.Windows.Forms.MouseEventHandler(this.bt_MouseUp);
            // 
            // dg_rs3_sensors
            // 
            this.dg_rs3_sensors.AllowUserToResizeColumns = false;
            this.dg_rs3_sensors.AllowUserToResizeRows = false;
            this.dg_rs3_sensors.BackgroundColor = System.Drawing.SystemColors.Control;
            this.dg_rs3_sensors.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dg_rs3_sensors.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.c_rs3_name,
            this.c_rs3_pollPeriod,
            this.c_rs3_address,
            this.c_rs3_id});
            this.dg_rs3_sensors.ContextMenuStrip = this.rs_sensors_menu;
            this.dg_rs3_sensors.Location = new System.Drawing.Point(6, 19);
            this.dg_rs3_sensors.Name = "dg_rs3_sensors";
            this.dg_rs3_sensors.RowHeadersVisible = false;
            this.dg_rs3_sensors.Size = new System.Drawing.Size(398, 252);
            this.dg_rs3_sensors.TabIndex = 0;
            this.dg_rs3_sensors.CellMouseEnter += new System.Windows.Forms.DataGridViewCellEventHandler(this.dg_rs1_sensors_CellMouseEnter);
            this.dg_rs3_sensors.CellValidating += new System.Windows.Forms.DataGridViewCellValidatingEventHandler(this.dg_rs1_sensors_CellValidating);
            this.dg_rs3_sensors.CellValueChanged += new System.Windows.Forms.DataGridViewCellEventHandler(this.dg_rs1_sensors_CellValueChanged);
            this.dg_rs3_sensors.CurrentCellDirtyStateChanged += new System.EventHandler(this.dg_rs1_sensors_CurrentCellDirtyStateChanged);
            // 
            // c_rs3_name
            // 
            this.c_rs3_name.Frozen = true;
            this.c_rs3_name.HeaderText = "Датчик";
            this.c_rs3_name.MinimumWidth = 130;
            this.c_rs3_name.Name = "c_rs3_name";
            this.c_rs3_name.Width = 130;
            // 
            // c_rs3_pollPeriod
            // 
            this.c_rs3_pollPeriod.Frozen = true;
            this.c_rs3_pollPeriod.HeaderText = "Период опроса, с";
            this.c_rs3_pollPeriod.Name = "c_rs3_pollPeriod";
            this.c_rs3_pollPeriod.Width = 120;
            // 
            // c_rs3_address
            // 
            this.c_rs3_address.Frozen = true;
            this.c_rs3_address.HeaderText = "Адрес ModBus";
            this.c_rs3_address.Name = "c_rs3_address";
            this.c_rs3_address.Width = 105;
            // 
            // c_rs3_id
            // 
            this.c_rs3_id.Frozen = true;
            this.c_rs3_id.HeaderText = "ID";
            this.c_rs3_id.Name = "c_rs3_id";
            this.c_rs3_id.Width = 40;
            // 
            // gb_rs3_settings
            // 
            this.gb_rs3_settings.BackColor = System.Drawing.Color.White;
            this.gb_rs3_settings.ContextMenuStrip = this.rs_settings_menu;
            this.gb_rs3_settings.Controls.Add(this.label39);
            this.gb_rs3_settings.Controls.Add(this.num_rs3Errors);
            this.gb_rs3_settings.Controls.Add(this.label40);
            this.gb_rs3_settings.Controls.Add(this.num_rs3Delay);
            this.gb_rs3_settings.Controls.Add(this.bt_rs3SettingsWrite);
            this.gb_rs3_settings.Controls.Add(this.bt_rs3SettingsRead);
            this.gb_rs3_settings.Controls.Add(this.chb_rs3_activate);
            this.gb_rs3_settings.Controls.Add(this.cb_rs3_stopbits);
            this.gb_rs3_settings.Controls.Add(this.cb_rs3_parity);
            this.gb_rs3_settings.Controls.Add(this.cb_rs3_databits);
            this.gb_rs3_settings.Controls.Add(this.cb_rs3_baudrate);
            this.gb_rs3_settings.Controls.Add(this.label30);
            this.gb_rs3_settings.Controls.Add(this.label31);
            this.gb_rs3_settings.Controls.Add(this.label32);
            this.gb_rs3_settings.Controls.Add(this.label33);
            this.gb_rs3_settings.Location = new System.Drawing.Point(8, 55);
            this.gb_rs3_settings.Name = "gb_rs3_settings";
            this.gb_rs3_settings.Size = new System.Drawing.Size(410, 187);
            this.gb_rs3_settings.TabIndex = 11;
            this.gb_rs3_settings.TabStop = false;
            this.gb_rs3_settings.Text = "Настройки RS3";
            // 
            // label39
            // 
            this.label39.AutoSize = true;
            this.label39.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label39.Location = new System.Drawing.Point(13, 153);
            this.label39.Margin = new System.Windows.Forms.Padding(3, 3, 3, 0);
            this.label39.Name = "label39";
            this.label39.Size = new System.Drawing.Size(61, 17);
            this.label39.TabIndex = 21;
            this.label39.Text = "Ошибки";
            this.label39.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.toolTip.SetToolTip(this.label39, "Количество ошибок считывания датчика перед его отключением");
            // 
            // num_rs3Errors
            // 
            this.num_rs3Errors.Location = new System.Drawing.Point(124, 153);
            this.num_rs3Errors.Name = "num_rs3Errors";
            this.num_rs3Errors.Size = new System.Drawing.Size(122, 20);
            this.num_rs3Errors.TabIndex = 20;
            this.num_rs3Errors.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.num_rs3Errors.Value = new decimal(new int[] {
            20,
            0,
            0,
            0});
            // 
            // label40
            // 
            this.label40.AutoSize = true;
            this.label40.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label40.Location = new System.Drawing.Point(13, 127);
            this.label40.Margin = new System.Windows.Forms.Padding(3, 3, 3, 0);
            this.label40.Name = "label40";
            this.label40.Size = new System.Drawing.Size(88, 17);
            this.label40.TabIndex = 19;
            this.label40.Text = "Задержка, с";
            this.label40.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.toolTip.SetToolTip(this.label40, "Задержка перед первым считыванием после включения");
            // 
            // num_rs3Delay
            // 
            this.num_rs3Delay.Location = new System.Drawing.Point(124, 127);
            this.num_rs3Delay.Maximum = new decimal(new int[] {
            60,
            0,
            0,
            0});
            this.num_rs3Delay.Name = "num_rs3Delay";
            this.num_rs3Delay.Size = new System.Drawing.Size(122, 20);
            this.num_rs3Delay.TabIndex = 18;
            this.num_rs3Delay.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.num_rs3Delay.Value = new decimal(new int[] {
            10,
            0,
            0,
            0});
            // 
            // bt_rs3SettingsWrite
            // 
            this.bt_rs3SettingsWrite.Cursor = System.Windows.Forms.Cursors.Hand;
            this.bt_rs3SettingsWrite.Image = global::LIC_settings.Properties.Resources.bt_write;
            this.bt_rs3SettingsWrite.Location = new System.Drawing.Point(293, 148);
            this.bt_rs3SettingsWrite.Name = "bt_rs3SettingsWrite";
            this.bt_rs3SettingsWrite.Size = new System.Drawing.Size(80, 25);
            this.bt_rs3SettingsWrite.SizeMode = System.Windows.Forms.PictureBoxSizeMode.CenterImage;
            this.bt_rs3SettingsWrite.TabIndex = 9;
            this.bt_rs3SettingsWrite.TabStop = false;
            this.bt_rs3SettingsWrite.Click += new System.EventHandler(this.bt_rs3SettingsWrite_Click);
            this.bt_rs3SettingsWrite.MouseDown += new System.Windows.Forms.MouseEventHandler(this.bt_MouseDown);
            this.bt_rs3SettingsWrite.MouseLeave += new System.EventHandler(this.bt_MouseLeave);
            this.bt_rs3SettingsWrite.MouseUp += new System.Windows.Forms.MouseEventHandler(this.bt_MouseUp);
            // 
            // bt_rs3SettingsRead
            // 
            this.bt_rs3SettingsRead.Cursor = System.Windows.Forms.Cursors.Hand;
            this.bt_rs3SettingsRead.Image = global::LIC_settings.Properties.Resources.bt_read;
            this.bt_rs3SettingsRead.Location = new System.Drawing.Point(293, 122);
            this.bt_rs3SettingsRead.Name = "bt_rs3SettingsRead";
            this.bt_rs3SettingsRead.Size = new System.Drawing.Size(80, 25);
            this.bt_rs3SettingsRead.SizeMode = System.Windows.Forms.PictureBoxSizeMode.CenterImage;
            this.bt_rs3SettingsRead.TabIndex = 8;
            this.bt_rs3SettingsRead.TabStop = false;
            this.bt_rs3SettingsRead.Click += new System.EventHandler(this.bt_rs3SettingsRead_Click);
            this.bt_rs3SettingsRead.MouseDown += new System.Windows.Forms.MouseEventHandler(this.bt_MouseDown);
            this.bt_rs3SettingsRead.MouseLeave += new System.EventHandler(this.bt_MouseLeave);
            this.bt_rs3SettingsRead.MouseUp += new System.Windows.Forms.MouseEventHandler(this.bt_MouseUp);
            // 
            // chb_rs3_activate
            // 
            this.chb_rs3_activate.AutoSize = true;
            this.chb_rs3_activate.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.chb_rs3_activate.Location = new System.Drawing.Point(274, 20);
            this.chb_rs3_activate.Name = "chb_rs3_activate";
            this.chb_rs3_activate.Size = new System.Drawing.Size(118, 21);
            this.chb_rs3_activate.TabIndex = 2;
            this.chb_rs3_activate.Text = "Активировать";
            this.chb_rs3_activate.UseVisualStyleBackColor = true;
            // 
            // cb_rs3_stopbits
            // 
            this.cb_rs3_stopbits.FormattingEnabled = true;
            this.cb_rs3_stopbits.Items.AddRange(new object[] {
            "1",
            "2"});
            this.cb_rs3_stopbits.Location = new System.Drawing.Point(124, 100);
            this.cb_rs3_stopbits.Name = "cb_rs3_stopbits";
            this.cb_rs3_stopbits.Size = new System.Drawing.Size(121, 21);
            this.cb_rs3_stopbits.TabIndex = 5;
            // 
            // cb_rs3_parity
            // 
            this.cb_rs3_parity.FormattingEnabled = true;
            this.cb_rs3_parity.Items.AddRange(new object[] {
            "none",
            "even",
            "odd"});
            this.cb_rs3_parity.Location = new System.Drawing.Point(124, 73);
            this.cb_rs3_parity.Name = "cb_rs3_parity";
            this.cb_rs3_parity.Size = new System.Drawing.Size(121, 21);
            this.cb_rs3_parity.TabIndex = 4;
            // 
            // cb_rs3_databits
            // 
            this.cb_rs3_databits.FormattingEnabled = true;
            this.cb_rs3_databits.Items.AddRange(new object[] {
            "8",
            "9"});
            this.cb_rs3_databits.Location = new System.Drawing.Point(124, 46);
            this.cb_rs3_databits.Name = "cb_rs3_databits";
            this.cb_rs3_databits.Size = new System.Drawing.Size(121, 21);
            this.cb_rs3_databits.TabIndex = 3;
            // 
            // cb_rs3_baudrate
            // 
            this.cb_rs3_baudrate.FormattingEnabled = true;
            this.cb_rs3_baudrate.Items.AddRange(new object[] {
            "9600",
            "19200",
            "115200",
            "256000"});
            this.cb_rs3_baudrate.Location = new System.Drawing.Point(124, 19);
            this.cb_rs3_baudrate.Name = "cb_rs3_baudrate";
            this.cb_rs3_baudrate.Size = new System.Drawing.Size(121, 21);
            this.cb_rs3_baudrate.TabIndex = 1;
            // 
            // label30
            // 
            this.label30.AutoSize = true;
            this.label30.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label30.Location = new System.Drawing.Point(12, 101);
            this.label30.Margin = new System.Windows.Forms.Padding(3, 3, 3, 0);
            this.label30.Name = "label30";
            this.label30.Size = new System.Drawing.Size(63, 17);
            this.label30.TabIndex = 3;
            this.label30.Text = "Stop bits";
            this.label30.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // label31
            // 
            this.label31.AutoSize = true;
            this.label31.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label31.Location = new System.Drawing.Point(12, 74);
            this.label31.Margin = new System.Windows.Forms.Padding(3, 3, 3, 0);
            this.label31.Name = "label31";
            this.label31.Size = new System.Drawing.Size(44, 17);
            this.label31.TabIndex = 2;
            this.label31.Text = "Parity";
            this.label31.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // label32
            // 
            this.label32.AutoSize = true;
            this.label32.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label32.Location = new System.Drawing.Point(12, 47);
            this.label32.Margin = new System.Windows.Forms.Padding(3, 3, 3, 0);
            this.label32.Name = "label32";
            this.label32.Size = new System.Drawing.Size(64, 17);
            this.label32.TabIndex = 1;
            this.label32.Text = "Data bits";
            this.label32.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // label33
            // 
            this.label33.AutoSize = true;
            this.label33.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label33.Location = new System.Drawing.Point(12, 20);
            this.label33.Name = "label33";
            this.label33.Size = new System.Drawing.Size(70, 17);
            this.label33.TabIndex = 0;
            this.label33.Text = "Baud rate";
            this.label33.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // tab_encryption
            // 
            this.tab_encryption.BackColor = System.Drawing.Color.WhiteSmoke;
            this.tab_encryption.Controls.Add(this.groupBox3);
            this.tab_encryption.Controls.Add(this.bt_back_8);
            this.tab_encryption.Location = new System.Drawing.Point(4, 24);
            this.tab_encryption.Name = "tab_encryption";
            this.tab_encryption.Size = new System.Drawing.Size(426, 563);
            this.tab_encryption.TabIndex = 8;
            this.tab_encryption.Text = "ENC";
            // 
            // groupBox3
            // 
            this.groupBox3.BackColor = System.Drawing.Color.White;
            this.groupBox3.Controls.Add(this.bt_encWrite);
            this.groupBox3.Controls.Add(this.chb_enc_hard);
            this.groupBox3.Controls.Add(this.bt_encRead);
            this.groupBox3.Controls.Add(this.chb_enc_soft);
            this.groupBox3.Location = new System.Drawing.Point(8, 54);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(410, 136);
            this.groupBox3.TabIndex = 53;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Шифрование";
            // 
            // bt_encWrite
            // 
            this.bt_encWrite.Cursor = System.Windows.Forms.Cursors.Hand;
            this.bt_encWrite.Image = global::LIC_settings.Properties.Resources.bt_write;
            this.bt_encWrite.Location = new System.Drawing.Point(279, 55);
            this.bt_encWrite.Name = "bt_encWrite";
            this.bt_encWrite.Size = new System.Drawing.Size(80, 25);
            this.bt_encWrite.SizeMode = System.Windows.Forms.PictureBoxSizeMode.CenterImage;
            this.bt_encWrite.TabIndex = 55;
            this.bt_encWrite.TabStop = false;
            this.bt_encWrite.Click += new System.EventHandler(this.bt_encWrite_Click);
            this.bt_encWrite.MouseDown += new System.Windows.Forms.MouseEventHandler(this.bt_MouseDown);
            this.bt_encWrite.MouseLeave += new System.EventHandler(this.bt_MouseLeave);
            this.bt_encWrite.MouseUp += new System.Windows.Forms.MouseEventHandler(this.bt_MouseUp);
            // 
            // chb_enc_hard
            // 
            this.chb_enc_hard.AutoSize = true;
            this.chb_enc_hard.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.chb_enc_hard.Location = new System.Drawing.Point(18, 65);
            this.chb_enc_hard.Name = "chb_enc_hard";
            this.chb_enc_hard.Size = new System.Drawing.Size(107, 21);
            this.chb_enc_hard.TabIndex = 55;
            this.chb_enc_hard.Text = "Аппаратное";
            this.chb_enc_hard.UseVisualStyleBackColor = true;
            // 
            // bt_encRead
            // 
            this.bt_encRead.Cursor = System.Windows.Forms.Cursors.Hand;
            this.bt_encRead.Image = global::LIC_settings.Properties.Resources.bt_read;
            this.bt_encRead.Location = new System.Drawing.Point(279, 29);
            this.bt_encRead.Name = "bt_encRead";
            this.bt_encRead.Size = new System.Drawing.Size(80, 25);
            this.bt_encRead.SizeMode = System.Windows.Forms.PictureBoxSizeMode.CenterImage;
            this.bt_encRead.TabIndex = 54;
            this.bt_encRead.TabStop = false;
            this.bt_encRead.Click += new System.EventHandler(this.bt_encRead_Click);
            this.bt_encRead.MouseDown += new System.Windows.Forms.MouseEventHandler(this.bt_MouseDown);
            this.bt_encRead.MouseLeave += new System.EventHandler(this.bt_MouseLeave);
            this.bt_encRead.MouseUp += new System.Windows.Forms.MouseEventHandler(this.bt_MouseUp);
            // 
            // chb_enc_soft
            // 
            this.chb_enc_soft.AutoSize = true;
            this.chb_enc_soft.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.chb_enc_soft.Location = new System.Drawing.Point(18, 29);
            this.chb_enc_soft.Name = "chb_enc_soft";
            this.chb_enc_soft.Size = new System.Drawing.Size(116, 21);
            this.chb_enc_soft.TabIndex = 54;
            this.chb_enc_soft.Text = "Программное";
            this.chb_enc_soft.UseVisualStyleBackColor = true;
            // 
            // bt_back_8
            // 
            this.bt_back_8.Cursor = System.Windows.Forms.Cursors.Hand;
            this.bt_back_8.Image = global::LIC_settings.Properties.Resources.bt_back;
            this.bt_back_8.Location = new System.Drawing.Point(8, 8);
            this.bt_back_8.Name = "bt_back_8";
            this.bt_back_8.Size = new System.Drawing.Size(40, 40);
            this.bt_back_8.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.bt_back_8.TabIndex = 52;
            this.bt_back_8.TabStop = false;
            this.bt_back_8.Click += new System.EventHandler(this.bt_back1_Click);
            // 
            // USB_serial
            // 
            this.USB_serial.BaudRate = 115200;
            this.USB_serial.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.USB_serial_DataReceived);
            // 
            // serialPortControl
            // 
            this.serialPortControl.Enabled = true;
            this.serialPortControl.Tick += new System.EventHandler(this.serialPortControl_Tick);
            // 
            // toolTip
            // 
            this.toolTip.AutoPopDelay = 5000;
            this.toolTip.InitialDelay = 100;
            this.toolTip.ReshowDelay = 100;
            // 
            // Main_window
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.White;
            this.ClientSize = new System.Drawing.Size(434, 591);
            this.Controls.Add(this.tabControl1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.KeyPreview = true;
            this.MaximizeBox = false;
            this.MaximumSize = new System.Drawing.Size(450, 630);
            this.MinimumSize = new System.Drawing.Size(450, 630);
            this.Name = "Main_window";
            this.Text = "Настройки оконечного устройства";
            this.Load += new System.EventHandler(this.Main_window_Load);
            this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.main_window_KeyDown);
            this.tabControl1.ResumeLayout(false);
            this.tab_main.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pb_EthStatus)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pb_loraStatus)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pb_zigbeeStatus)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.image_status)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.main_window_menu.ResumeLayout(false);
            this.tab_frm.ResumeLayout(false);
            this.tab_frm.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.rebootUSB)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.bt_connect)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.bt_refreshPort)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.bt_readMainParams)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.bt_writeMainParams)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pb_bt_back1)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.bt_sendFWMqtt)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.bt_sendFrm)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.bt_firmOpen)).EndInit();
            this.rtb1_menu.ResumeLayout(false);
            this.tab_eth.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.bt_eth_read)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.bt_eth_write)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pb_bt_back2)).EndInit();
            this.gb_MQTT.ResumeLayout(false);
            this.gb_MQTT.PerformLayout();
            this.gb_WebSettings.ResumeLayout(false);
            this.gb_WebSettings.PerformLayout();
            this.tab_lora.ResumeLayout(false);
            this.tab_lora.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.bt_LoRa_read)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.bt_LoRa_send)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pb_bt_back3)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.image_LoRa_logo)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.tb_LORA_AppPort)).EndInit();
            this.tab_zigbee.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pb_bt_back4)).EndInit();
            this.groupBox7.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.bt_zigbeeFrmGetFile)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.bt_zigbeeFrmSend)).EndInit();
            this.groupBox6.ResumeLayout(false);
            this.groupBox6.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.bt_zigbee_read)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.bt_zigbee_send)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.image_zigbee_logo)).EndInit();
            this.tab_rs1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pb_bt_back5)).EndInit();
            this.gb_rs1_sensors.ResumeLayout(false);
            this.gb_rs1_sensors.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.bt_rs1_sensorsWrite)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.bt_rs1_sensorsRead)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dg_rs1_sensors)).EndInit();
            this.rs_sensors_menu.ResumeLayout(false);
            this.gb_rs1_settings.ResumeLayout(false);
            this.gb_rs1_settings.PerformLayout();
            this.rs_settings_menu.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.num_rs1Errors)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.num_rs1Delay)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.bt_rs1SettingsWrite)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.bt_rs1SettingsRead)).EndInit();
            this.tab_rs2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pb_bt_back6)).EndInit();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.bt_rs2_sensorsWrite)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.bt_rs2_sensorsRead)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dg_rs2_sensors)).EndInit();
            this.gb_rs2_settings.ResumeLayout(false);
            this.gb_rs2_settings.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.num_rs2Errors)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.num_rs2Delay)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.bt_rs2SettingsWrite)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.bt_rs2SettingsRead)).EndInit();
            this.tab_rs3.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pb_bt_back7)).EndInit();
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.bt_rs3_sensorsWrite)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.bt_rs3_sensorsRead)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dg_rs3_sensors)).EndInit();
            this.gb_rs3_settings.ResumeLayout(false);
            this.gb_rs3_settings.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.num_rs3Errors)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.num_rs3Delay)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.bt_rs3SettingsWrite)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.bt_rs3SettingsRead)).EndInit();
            this.tab_encryption.ResumeLayout(false);
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.bt_encWrite)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.bt_encRead)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.bt_back_8)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tab_main;
        private System.Windows.Forms.TabPage tab_frm;
        private System.Windows.Forms.PictureBox pictureBox1;
        private TransparentPanel panel_encryption;
        private System.Windows.Forms.Label l_portName;
        private System.Windows.Forms.ComboBox cb_portName;
        private System.IO.Ports.SerialPort USB_serial;
        private System.Windows.Forms.RichTextBox richTextBox1;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.ProgressBar progress_firmLoad;
        private System.Windows.Forms.Timer serialPortControl;
        private TransparentPanel panel_eth;
        private System.Windows.Forms.TabPage tab_eth;
        private System.Windows.Forms.GroupBox gb_WebSettings;
        private System.Windows.Forms.CheckBox chb_DHCP;
        private System.Windows.Forms.TextBox tb_IP;
        private System.Windows.Forms.MaskedTextBox tb_MAC;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox tb_Gateway;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox tb_Mask;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.GroupBox gb_MQTT;
        private System.Windows.Forms.TextBox tb_MQTT_Password;
        private System.Windows.Forms.TextBox tb_MQTT_User;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.TextBox tb_MQTT_ID;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.TextBox tb_MQQTTopicOutput;
        private System.Windows.Forms.TextBox tb_BrokerPort;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.TextBox tb_BrokerIP;
        private System.Windows.Forms.Label label8;
        private TransparentPanel panel_main;
        private TransparentPanel panel_lora;
        private System.Windows.Forms.TabPage tab_lora;
        private System.Windows.Forms.PictureBox image_status;
        private System.Windows.Forms.CheckBox chb_AutoDevEUI;
        private System.Windows.Forms.NumericUpDown tb_LORA_AppPort;
        private System.Windows.Forms.MaskedTextBox tb_LORA_AppEUI;
        private System.Windows.Forms.MaskedTextBox tb_LORA_DevEUI;
        private System.Windows.Forms.MaskedTextBox tb_LORA_AppKey;
        private System.Windows.Forms.CheckBox chb_LORA_ADR;
        private System.Windows.Forms.Label label21;
        private System.Windows.Forms.Label label20;
        private System.Windows.Forms.Label label19;
        private System.Windows.Forms.Label label18;
        private System.Windows.Forms.Label label17;
        private TransparentPanel panel_RS1;
        private System.Windows.Forms.TabPage tab_rs1;
        private System.Windows.Forms.TabPage tab_rs2;
        private System.Windows.Forms.TabPage tab_rs3;
        private System.Windows.Forms.GroupBox gb_rs1_settings;
        private System.Windows.Forms.CheckBox chb_rs1_activate;
        private System.Windows.Forms.ComboBox cb_rs1_stopbits;
        private System.Windows.Forms.ComboBox cb_rs1_parity;
        private System.Windows.Forms.ComboBox cb_rs1_databits;
        private System.Windows.Forms.ComboBox cb_rs1_baudrate;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.GroupBox gb_rs1_sensors;
        private System.Windows.Forms.DataGridView dg_rs1_sensors;
        private System.Windows.Forms.TextBox tb_workTime;
        private System.Windows.Forms.Label label26;
        private System.Windows.Forms.TextBox tb_stanbyTime;
        private System.Windows.Forms.Label label25;
        private System.Windows.Forms.DateTimePicker dt_DateOfProduction;
        private System.Windows.Forms.TextBox tb_ModuleSerialNumber;
        private System.Windows.Forms.Label label22;
        private System.Windows.Forms.Label label23;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.DataGridView dg_rs2_sensors;
        private System.Windows.Forms.GroupBox gb_rs2_settings;
        private System.Windows.Forms.CheckBox chb_rs2_activate;
        private System.Windows.Forms.ComboBox cb_rs2_stopbits;
        private System.Windows.Forms.ComboBox cb_rs2_parity;
        private System.Windows.Forms.ComboBox cb_rs2_databits;
        private System.Windows.Forms.ComboBox cb_rs2_baudrate;
        private System.Windows.Forms.Label label24;
        private System.Windows.Forms.Label label27;
        private System.Windows.Forms.Label label28;
        private System.Windows.Forms.Label label29;
        private TransparentPanel panel_rs2;
        private TransparentPanel panel_rs3;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.DataGridView dg_rs3_sensors;
        private System.Windows.Forms.GroupBox gb_rs3_settings;
        private System.Windows.Forms.CheckBox chb_rs3_activate;
        private System.Windows.Forms.ComboBox cb_rs3_stopbits;
        private System.Windows.Forms.ComboBox cb_rs3_parity;
        private System.Windows.Forms.ComboBox cb_rs3_databits;
        private System.Windows.Forms.ComboBox cb_rs3_baudrate;
        private System.Windows.Forms.Label label30;
        private System.Windows.Forms.Label label31;
        private System.Windows.Forms.Label label32;
        private System.Windows.Forms.Label label33;
        private System.Windows.Forms.Label label35;
        private System.Windows.Forms.Label label34;
        private System.Windows.Forms.TextBox tb_mqttTopic;
        private System.Windows.Forms.TextBox tb_mqttServer;
        private System.Windows.Forms.Button bt_mqttReboot;
        private System.Windows.Forms.CheckBox cb_restartAfterDownload;
        private System.Windows.Forms.Button bt_reprogMqtt;
        private System.Windows.Forms.Button bt_mqttFwVersion;
        private System.Windows.Forms.Button bt_resetSettings;
        private System.Windows.Forms.PictureBox image_LoRa_logo;
        private System.Windows.Forms.TabPage tab_zigbee;
        private TransparentPanel panel_zigbee;
        private System.Windows.Forms.PictureBox image_zigbee_logo;
        private System.Windows.Forms.CheckBox chb_LoRa_activate;
        private System.Windows.Forms.CheckBox chb_ETH_Activate;
        private System.Windows.Forms.CheckBox chb_MQTT_Activate;
        private System.Windows.Forms.CheckBox chb_ZigBee_Activate;
        private System.Windows.Forms.RichTextBox rtb_zigbee;
        private System.Windows.Forms.GroupBox groupBox6;
        private System.Windows.Forms.Button bt_zigbeeSensors;
        private System.Windows.Forms.Button bt_zigbeeConnect;
        private System.Windows.Forms.GroupBox groupBox7;
        private System.Windows.Forms.ProgressBar pb_zigbee;
        private System.Windows.Forms.ContextMenuStrip rtb1_menu;
        private System.Windows.Forms.ToolStripMenuItem clear;
        private System.Windows.Forms.PictureBox pb_bt_back2;
        private System.Windows.Forms.PictureBox pb_bt_back1;
        private System.Windows.Forms.PictureBox pb_bt_back3;
        private System.Windows.Forms.PictureBox pb_bt_back4;
        private System.Windows.Forms.PictureBox pb_bt_back5;
        private System.Windows.Forms.PictureBox pb_bt_back6;
        private System.Windows.Forms.PictureBox pb_bt_back7;
        private System.Windows.Forms.PictureBox bt_eth_write;
        private System.Windows.Forms.PictureBox bt_eth_read;
        private System.Windows.Forms.PictureBox bt_readMainParams;
        private System.Windows.Forms.PictureBox bt_writeMainParams;
        private System.Windows.Forms.PictureBox bt_refreshPort;
        private System.Windows.Forms.PictureBox bt_LoRa_read;
        private System.Windows.Forms.PictureBox bt_LoRa_send;
        private System.Windows.Forms.ToolTip toolTip;
        private System.Windows.Forms.PictureBox bt_rs1SettingsRead;
        private System.Windows.Forms.PictureBox bt_rs1SettingsWrite;
        private System.Windows.Forms.PictureBox bt_rs2SettingsRead;
        private System.Windows.Forms.PictureBox bt_rs2SettingsWrite;
        private System.Windows.Forms.PictureBox bt_rs3SettingsRead;
        private System.Windows.Forms.PictureBox bt_rs3SettingsWrite;
        private System.Windows.Forms.PictureBox bt_rs1_sensorsWrite;
        private System.Windows.Forms.PictureBox bt_rs1_sensorsRead;
        private System.Windows.Forms.PictureBox bt_rs2_sensorsWrite;
        private System.Windows.Forms.PictureBox bt_rs2_sensorsRead;
        private System.Windows.Forms.PictureBox bt_rs3_sensorsRead;
        private System.Windows.Forms.PictureBox bt_rs3_sensorsWrite;
        private System.Windows.Forms.PictureBox bt_zigbee_read;
        private System.Windows.Forms.PictureBox bt_zigbee_send;
        private System.Windows.Forms.PictureBox bt_zigbeeFrmSend;
        private System.Windows.Forms.PictureBox bt_zigbeeFrmGetFile;
        private System.Windows.Forms.PictureBox bt_firmOpen;
        private System.Windows.Forms.PictureBox bt_sendFrm;
        private System.Windows.Forms.PictureBox bt_sendFWMqtt;
        private System.Windows.Forms.PictureBox bt_connect;
        private System.Windows.Forms.ContextMenuStrip rs_sensors_menu;
        private System.Windows.Forms.ToolStripMenuItem clear_rsSensorsTable;
        private System.Windows.Forms.ToolStripMenuItem loadRSSensorsConfig;
        private System.Windows.Forms.ToolStripMenuItem saveRSSensorsConfig;
        private System.Windows.Forms.ToolStripMenuItem saveAllToolStripMenuItem;
        private System.Windows.Forms.DataGridViewComboBoxColumn c_sensorType;
        private System.Windows.Forms.DataGridViewTextBoxColumn c_reqPeriod;
        private System.Windows.Forms.DataGridViewTextBoxColumn c_address;
        private System.Windows.Forms.DataGridViewTextBoxColumn c_id;
        private System.Windows.Forms.DataGridViewComboBoxColumn c_rs2_name;
        private System.Windows.Forms.DataGridViewTextBoxColumn c_rs2_pollPeriod;
        private System.Windows.Forms.DataGridViewTextBoxColumn c_rs2_address;
        private System.Windows.Forms.DataGridViewTextBoxColumn c_rs2_id;
        private System.Windows.Forms.DataGridViewComboBoxColumn c_rs3_name;
        private System.Windows.Forms.DataGridViewTextBoxColumn c_rs3_pollPeriod;
        private System.Windows.Forms.DataGridViewTextBoxColumn c_rs3_address;
        private System.Windows.Forms.DataGridViewTextBoxColumn c_rs3_id;
        private System.Windows.Forms.ToolStripSeparator sepToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem deleteRowToolStripMenuItem;
        private System.Windows.Forms.ContextMenuStrip main_window_menu;
        private System.Windows.Forms.ToolStripMenuItem readAllToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem writeAllToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator сепToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem loadAllToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveAllSettingsToolStripMenuItem;
        private System.Windows.Forms.PictureBox rebootUSB;
        private System.Windows.Forms.ToolStripMenuItem addSensorMQTTToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator rrToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem delSensorMQTTToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem reqMQTTToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem delAllMQTTToolStripMenuItem;
        private System.Windows.Forms.Label lb_rs1_sensorsCount;
        private System.Windows.Forms.Label lb_rs2_sensorsCount;
        private System.Windows.Forms.Label lb_rs3_sensorsCount;
        private System.Windows.Forms.ContextMenuStrip rs_settings_menu;
        private System.Windows.Forms.ToolStripMenuItem readRSSettingsMQTTToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem writeRSSettingsMQTTToolStripMenuItem;
        private System.Windows.Forms.TabPage tab_encryption;
        private System.Windows.Forms.PictureBox bt_back_8;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.PictureBox bt_encWrite;
        private System.Windows.Forms.CheckBox chb_enc_hard;
        private System.Windows.Forms.PictureBox bt_encRead;
        private System.Windows.Forms.CheckBox chb_enc_soft;
        private System.Windows.Forms.PictureBox pb_loraStatus;
        private System.Windows.Forms.PictureBox pb_zigbeeStatus;
        private System.Windows.Forms.PictureBox pb_EthStatus;
        private System.Windows.Forms.Label label36;
        private System.Windows.Forms.NumericUpDown num_rs1Errors;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.NumericUpDown num_rs1Delay;
        private System.Windows.Forms.Label label37;
        private System.Windows.Forms.NumericUpDown num_rs2Errors;
        private System.Windows.Forms.Label label38;
        private System.Windows.Forms.NumericUpDown num_rs2Delay;
        private System.Windows.Forms.Label label39;
        private System.Windows.Forms.NumericUpDown num_rs3Errors;
        private System.Windows.Forms.Label label40;
        private System.Windows.Forms.NumericUpDown num_rs3Delay;
        private System.Windows.Forms.Label label41;
        private System.Windows.Forms.ComboBox cb_loraMessageType;
        private System.Windows.Forms.ComboBox cb_loraDatarate;
    }
}

