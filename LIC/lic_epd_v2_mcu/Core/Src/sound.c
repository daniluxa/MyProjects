#include <stdlib.h>
#include <string.h>
#include "stdio.h"
#include "sound.h"
#include "timers.h"

extern TIM_HandleTypeDef htim5;

const char alarm1[] = "#25c6 #25C6 #25d6 #25D6 #25e6 #25f6 #25F6 #25g6 #25G6 #25a6 #25A6 #25b6";
const char alarm4[] = "#25b6 #25A6 #25a6 #25G6 #25g6 #25F6 #25f6 #25e6 #25D6 #25d6 #25C6 #25c6";
const char alarm2[] = "t125 %16d5 %16a4 %16e5 %16a4 %16f5 %16a4 %16d5 %16a4 %16e5 %16a4 %16f5 %16a4 %16g5 %16a4 %16e5 %16a4 %16f5 %16a4 %16g5 %16a4 %16a5 %16a4 %16f5 %16a4 %16g5 %16a4 %16a5 %16a4 %16A5 %16a4 %16g5 %16a4 %16a5 %16a4 %16f5 %16a4 %16g5 %16a4 %16e5 %16a4 %16f5 %16a4 %16d5 %16a4 %16e5 %16a4 %16C5 %16a4 %4d5 %4p";
const char alarm3[] = "t120 %4g3 %4g3 %4g3 %8D3 %16- %16A3 %4g3 %8D3 %16- %16A3 %2g3 %4d4 %4d4 %4d4 %8D4 %16- %16A3 %4F3 %8D3 %16- %16A3 %2g3 %4g4 %8g3 %16- %16g3 %4g4 %8F4 %16- %16f4 %16e4 %16D4 %4e4 %8G3 %4C4 %8c4 %16- %16b3 %16A3 %16a3 %4A3 %8D3 %4F3 %8D3 %16- %16A3 %2g3 %4-";
const char rt_notready[] = "#100F3 #100e3 #100d3 #100c3";
const char rt_wdt[] = "#80e3 #50c3";
const char rt_turnon[] = "#70b4 #70b3 #70b2";

char const *play_str;

uint8_t  playing = FALSE;                                                           // TRUE, если в данный момент что-то проигрываем
uint32_t sound_tmr = 0xFF;                                                          // Таймер, который отсчитывает время отведенное на каждую ноту
uint32_t bpm = 125;                                                                 // beats per minute. Темп мелодии
uint8_t  alarm = 0;
int8_t   oct_offset = 0;

/* период */
const uint32_t period_table[108] = {
                                    366936, 
                                    346342, 
                                    326903, 
                                    308555, 
                                    291237, 
                                    274891, 
                                    259463, 
                                    244900, 
                                    231155, 
                                    218181, 
                                    205936, 
                                    194377, 
                                    183468, 
                                    173171, 
                                    163451, 
                                    154277, 
                                    145618, 
                                    137445, 
                                    129731, 
                                    122450, 
                                    115577, 
                                    109090, 
                                    102968, 
                                    97188, 
                                    91734, 
                                    86585, 
                                    81725, 
                                    77138, 
                                    72809, 
                                    68722, 
                                    64865, 
                                    61225, 
                                    57788, 
                                    54545, 
                                    51484, 
                                    48594, 
                                    45867, 
                                    43292, 
                                    40862, 
                                    38569, 
                                    36404, 
                                    34361, 
                                    32432, 
                                    30612, 
                                    28894, 
                                    27272, 
                                    25742, 
                                    24297, 
                                    22933, 
                                    21646, 
                                    20431, 
                                    19284, 
                                    18202, 
                                    17180, 
                                    16216, 
                                    15306, 
                                    14447, 
                                    13636, 
                                    12871, 
                                    12148, 
                                    11466, 
                                    10823, 
                                    10215, 
                                    9642, 
                                    9101, 
                                    8590, 
                                    8108, 
                                    7653, 
                                    7223, 
                                    6818, 
                                    6435, 
                                    6074, 
                                    5733, 
                                    5411, 
                                    5107, 
                                    4821, 
                                    4550, 
                                    4295, 
                                    4054, 
                                    3826, 
                                    3611, 
                                    3409, 
                                    3217, 
                                    3037, 
                                    2866, 
                                    2705, 
                                    2553, 
                                    2410, 
                                    2275, 
                                    2147, 
                                    2027, 
                                    1913, 
                                    1805, 
                                    1704, 
                                    1608, 
                                    1518, 
                                    1433, 
                                    1352, 
                                    1276, 
                                    1205, 
                                    1137, 
                                    1073, 
                                    1013, 
                                    956, 
                                    902, 
                                    852, 
                                    804, 
                                    759};

char const *last_sound = NULL;


void play_rt(char const *str, uint8_t alarm_flag, int8_t offset)
{
    alarm = alarm_flag;
    if ( playing ) sound_stop();
    
    last_sound = play_str = str;
    oct_offset = offset;
    
    if ( *(play_str) == 't' )
      play_str += sscanf(play_str, "t%d", &bpm);

    playing = TRUE;
    if ( IS_TIMER_FREE(sound_tmr) ) sound_tmr = get_timer();
    init_timer(sound_tmr, 0);
    htim5.Instance->CCR1 = 0;
    HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_1);      
}

/*  Формат проигрываемой строки выглядит следующим образом:
    "tZZ %XXnY ... #XXnY ... "
    где t указывает на то, что следом задаётся bpm - ZZ
    % указывает на то, что длительность указана в долях ноты
    в этом случае XX указывает длительность следующим образом: 
    "1" | 1/1 (целая нота) 
    "2" | 1/2 
    "4" | 1/4 
    "8" | 1/8 
    "16"| 1/16 
    "32"| 1/32 
    # длительность указана в милисекундах (XX). Если XX = 0, то до бесконечности
    n - проигрываемая нота, принимает значения:
    a, A, b, c, C, d, D, e, f, F, g, G это означает соответствующую
    ноту, либо, если стоит p - паузу. 
    Y - указывает используемую октаву. От 0 до 8.
*/

void sound_processing(void)
{
    uint32_t play_time = 0;
    float mult;
    uint32_t note_num;
    uint32_t octave;
    uint32_t type;   
    char note;
    
    if ( IS_TIMER_FREE(sound_tmr) ) return;
    if ( check_timer(sound_tmr) == 0 )
    {
        while ( *play_str != '%' && *play_str != '#' && *play_str != NULL ) play_str++;
        if (*play_str == NULL )
        {
            sound_stop();
            if ( alarm ) play_rt(last_sound, 1, oct_offset);
            return;
        }
        if ( *(play_str++) == '#' ) type = 1;
        else type = 0;
        
        play_time = atoi(play_str);                                             // считываем длительность
        while ( *play_str >= '0' && *play_str <= '9') play_str++;               // пропускаем считанные цифры
        
        note = *(play_str++);                                                   // считываем ноту
        if ( note == '.' || note == ';' || note == '&' )                        // здесь оказалось, что нота вовсе и не нота, а спецсимвол, увеличивающий длительность
        {
            switch ( note )
            {                
                case '.': mult = 1.5; break;
                case ';': mult = 2.0; break;
                case '&': mult = 2.5; break;                
            }
            note = *(play_str++);                                               // а вот это уже в этом случае нормальная нота
        }
        else mult = 1.0;
        
        if ( note != 'p' && note != '-') octave = (uint8_t)atoi(play_str++);    // считываем октаву, если не пауза
        else octave = 3;
        
        octave += oct_offset;
        
        if ( octave > 8 ) octave = 8;

        switch ( note )
        {
          case 'c': note_num = 0; break;
          case 'C': note_num = 1; break;
          case 'd': note_num = 2; break;            
          case 'D': note_num = 3; break;              
          case 'e': note_num = 4; break;
          case 'f': note_num = 5; break;
          case 'F': note_num = 6; break;
          case 'g': note_num = 7; break;
          case 'G': note_num = 8; break;
          case 'a': note_num = 9; break;
          case 'A': note_num = 10; break;
          case 'b': note_num = 11; break;
          case 'p': 
          case '-': 
          default:  note_num = 12;
        }
        
        __HAL_TIM_DISABLE(&htim5);
        if ( note_num != 12 )
        {
          
          /* Set the Autoreload value */
          htim5.Instance->ARR = period_table[octave*12+note_num]-1;

          /* Set the Prescaler value */
          //htim5.Instance->PSC = period_table[octave*12+note_num][PRESCALER]-1;
          
          htim5.Instance->CCR1 = period_table[octave*12+note_num]/2-1;
        }
        else
          htim5.Instance->CCR1 = 0;
        
        htim5.Instance->CNT = 0;
        __HAL_TIM_ENABLE(&htim5);
        
        if ( type == 0 )
            play_time = (uint32_t)(( ( 60000.0f/( (float)bpm/4 ) )/(float)play_time )*mult);   

        if ( play_time != 0 ) init_timer( sound_tmr, play_time );            
        else free_timer( &sound_tmr );
    }
}


void sound_stop(void)
{
  HAL_TIM_PWM_Stop(&htim5, TIM_CHANNEL_1);  
  playing = FALSE;
  free_timer( &sound_tmr );   
}

uint8_t is_playing(void)
{
  return playing;
}
