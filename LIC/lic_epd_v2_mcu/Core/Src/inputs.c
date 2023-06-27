#include "inputs.h"
//#include "main.h"
#include "stdlib.h"


typedef struct DigitalInput
{
    uint16_t            input_id;
    GPIO_TypeDef*       GPIOx;    
    uint16_t            GPIO_Pin;
    GPIO_PinState       state;
    uint16_t            set_filter;
    uint16_t            release_filter;
    uint16_t            threshold;
    struct DigitalInput *pNextInput;   
} DigitalInput, *pDigitalInput; 



static pDigitalInput pFirst = NULL;
static pDI_Event pFirstEvent = NULL;

static void PutInputEvent(pDigitalInput pInput);

void AddInputs(uint16_t InputID, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, uint32_t threshold)
{
  //GPIO_InitTypeDef GPIO_InitStruct;
  pDigitalInput pNewInput;
  
  pNewInput = malloc(sizeof(DigitalInput));
  if ( pNewInput == NULL ) return;//Error_Handler();
  pNewInput->input_id = InputID;
  pNewInput->GPIOx = GPIOx;
  pNewInput->GPIO_Pin = GPIO_Pin;
  pNewInput->threshold = threshold;
  pNewInput->set_filter = 0;
  pNewInput->release_filter = 0;
  pNewInput->pNextInput = NULL;
  pNewInput->state = 0xFF;//GPIO_PIN_RESET;
  
  if ( pFirst == NULL ) pFirst = pNewInput;
  else 
  {
    pDigitalInput pInput = pFirst;
    while( pInput->pNextInput != NULL ) pInput = pInput->pNextInput;
    pInput->pNextInput = pNewInput;
  }
  
//  GPIO_InitStruct.Pin = GPIO_Pin;
//  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
//  HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

uint32_t PollInputs(void)
{
  pDigitalInput pInput = pFirst;
  
  while ( pInput )
  {
    if ( HAL_GPIO_ReadPin(pInput->GPIOx, pInput->GPIO_Pin) == GPIO_PIN_RESET )
    {
      if ( pInput->state != GPIO_PIN_RESET )
      {
        if ( pInput->release_filter++ >= pInput->threshold ) 
        {
          pInput->state = GPIO_PIN_RESET;
          PutInputEvent(pInput);
        }
      }
      else pInput->release_filter = 0;
      pInput->set_filter = 0;
    }
    else     
    {
      if ( pInput->state != GPIO_PIN_SET )
      {
        if ( pInput->set_filter++ >= pInput->threshold ) 
        {
          pInput->state = GPIO_PIN_SET;
          PutInputEvent(pInput);
        }
      }
      else pInput->set_filter = 0;
      pInput->release_filter = 0;
    }
    
    pInput = pInput->pNextInput;
  }
  
  if ( pFirstEvent ) return 1;
  return 0;
}

void GetInputEvent(pDI_Event pEvent)
{
  if ( pFirstEvent == NULL ) 
  {
    pEvent->input_id = 0xFFFF;
    return;
  }
  *pEvent = *pFirstEvent;
  pDI_Event pNextEvent = pFirstEvent->pNextEvent;
  free(pFirstEvent);
  pFirstEvent = pNextEvent;  
}

GPIO_PinState GetStateByID(uint32_t id)
{
  pDigitalInput pInput = pFirst;
  
  while ( pInput )
  {
    if ( pInput->input_id == id ) return pInput->state;
    pInput = pInput->pNextInput;
  }
  
  return GPIO_PIN_RESET;
}


static void PutInputEvent(pDigitalInput pInput)
{
  pDI_Event pNewEvent;
  
  pNewEvent = malloc(sizeof(DI_Event));
  if ( pNewEvent == NULL ) return;//Error_Handler();
  pNewEvent->input_id = pInput->input_id;
  pNewEvent->state = pInput->state;
  pNewEvent->pNextEvent = NULL;
  
  if ( pFirstEvent == NULL ) pFirstEvent = pNewEvent;
  else 
  {
    pDI_Event pEvent = pFirstEvent;
    while( pEvent->pNextEvent != NULL ) pEvent = pEvent->pNextEvent;
    pEvent->pNextEvent = pNewEvent;
  }
}