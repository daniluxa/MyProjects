/**
  ******************************************************************************
  ******************************************************************************
  */  

/* Includes ------------------------------------------------------------------*/
#include "timers.h"


TimersTypeDef timer_pool[NUM_OF_TIMERS];

/*----------------------------------------------------------------------------*/

void timer_pool_init (void)
{
  for( uint32_t i = 0; i < NUM_OF_TIMERS; i++ )
  {
    timer_pool[i].timeout = 0;
    timer_pool[i].state = TIMER_FREE;	
  }
}

/*----------------------------------------------------------------------------*/

uint32_t get_timer (void)
{
	
  for( uint32_t i = 0; i < NUM_OF_TIMERS; i++ )
    if( timer_pool[i].state == TIMER_FREE )                                  
    {
      timer_pool[i].state = TIMER_NOT_FREE;                                 
      return i;		                                       
    }	
  while(1);
}

/*----------------------------------------------------------------------------*/
void init_timer ( uint32_t nbr, uint32_t tout )
{
  if( nbr > (NUM_OF_TIMERS-1) ) 
  {
    while(1);
  }

  if( timer_pool[nbr].state == TIMER_FREE ) 
    return;
              
  timer_pool[nbr].timeout = tout;
} 

/*----------------------------------------------------------------------------*/

void free_timer (uint32_t *pTimer)
{
  /* Make a simple check */
  if ( *pTimer > (NUM_OF_TIMERS-1) ) return; 

  timer_pool[*pTimer].state  = TIMER_FREE;
  timer_pool[*pTimer].timeout = 0;
  *pTimer = 0xFF;
}

/*----------------------------------------------------------------------------*/

//#pragma inline=forced 
/*void decrement_timers(void)
{
  for( uint32_t i = 0; i < NUM_OF_TIMERS; i++ )
    if( timer_pool[i].state == TIMER_NOT_FREE )                                  
      timer_pool[i].timeout--;
}*/

/*----------------------------------------------------------------------------*/

uint32_t check_timer(uint32_t timer)
{
  return timer_pool[timer].timeout;
}