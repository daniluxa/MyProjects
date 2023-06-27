using System;

namespace LIC_settings
{
    // Класс для сохранения настроек датчиков из таблицы
    class RSSensor
    {
        public String view;
        public Sensor sensor;

        public RSSensor()
        {
        }

        public RSSensor(String view, Sensor sensor)
        {
            this.view = view;
            this.sensor = sensor;
        }
    }

}
