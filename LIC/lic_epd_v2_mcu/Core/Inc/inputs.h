#ifndef __INPUTS_H
#define __INPUTS_H

#include "stm32f4xx_hal.h"

#define RS1_CONN        1
#define RS2_CONN        2
#define RS3_CONN        3
#define CAN_CONN        4
#define AN1_CONN        5
#define AN2_CONN        6
#define BAT_TAMPER_DET  7
#define CASE_TAMPER_DET 8
#define BQ25887_PG      9
#define BQ25887_STATUS  10
#define TPS25942x_PG    11
#define OVL_RS1         12
#define OVL_RS2         13
#define OVL_RS3         14
#define OVL_CAN         15
#define OVL_AN1         16
#define OVL_AN2         17

typedef struct DI_Event
{
  uint16_t            input_id;
  GPIO_PinState       state;
  struct DI_Event     *pNextEvent;   
} DI_Event, *pDI_Event; 

void          AddInputs(uint16_t InputID, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, uint32_t threshold);
uint32_t      PollInputs(void);
void          GetInputEvent(pDI_Event pEvent);
GPIO_PinState GetStateByID(uint32_t id);


#endif // __INPUTS_H