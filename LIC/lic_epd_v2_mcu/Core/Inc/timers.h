#ifndef __TIMERS_H
#define __TIMERS_H

#include "stm32f4xx_hal.h"

#define NUM_OF_TIMERS   50

#define OUT_OF_TIMERS   0xFF
#define TIMER_NOT_INIT  0xFF

#define IS_TIMER_FREE(x)        (x == 0xFF)
#define IS_TIMER_NOTFREE(x)     (x != 0xFF)

typedef enum 
{
  TIMER_FREE = 0, 
  TIMER_NOT_FREE = !TIMER_FREE
} TimerState;

typedef struct TimersTypeDef
{
  volatile uint32_t timeout;
  volatile TimerState state;
}TimersTypeDef;

extern TimersTypeDef timer_pool[NUM_OF_TIMERS];


void      timer_pool_init(void);		                                        /* Init the pool when uC starts	*/
uint32_t  get_timer(void);		                                                /* Get Timer from Timer Pool 	*/
void      init_timer(uint32_t, uint32_t);	                                        /* Init timers timeout value	*/
void      free_timer(uint32_t*);		                                        /* Return Timer to Timer Pool	*/
uint32_t  check_timer(uint32_t);		                                        /* Return Timers value			*/ 	

__STATIC_INLINE void decrement_timers(void)
{
  for( uint32_t i = 0; i < NUM_OF_TIMERS; i++ )
    if( timer_pool[i].state == TIMER_NOT_FREE && timer_pool[i].timeout > 0 )                                  
      timer_pool[i].timeout--;
}

#endif // __TIMERS_H
