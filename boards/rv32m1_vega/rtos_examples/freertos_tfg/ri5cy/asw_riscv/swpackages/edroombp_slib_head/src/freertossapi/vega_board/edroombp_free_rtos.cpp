/*
    Copyright 2004-2005 (c) by Aitor Viana Sanchez,
    Space Research Group,
    University of Alcala.

    For further information, please visit http://srg.aut.uah.es

    This software is provided under the terms of the GNU General Public v2
    Licence. A full copy of the GNU GPL is provided in the file COPYING
    found in the development root of ERCOS-RT.
*/
/* use global definitions */
#include <public/config.h>
//#include <edroom_glue/edroomdf.h>

#include <stdio.h>

/* FreeRTOS */
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>

/* others */
#include <public/edroombp_iface_v3_0_free_rtos.h>
#include <public/timespec.h>
//#include <public/debug_primitives.h>
//#include <public/string.h>

Pr_IRQHandler Pr_IRQHandler17=NULL;

//Custom handler, replaces the original LPUART0_DriverIRQHandler

#if defined(USE_EDROOMBP_LPUART0_IRQ_HANDLER)
extern "C" void LPUART0_DriverIRQHandler(void)
{
	 if (LPUART_STAT_OR_MASK & LPUART0->STAT) {
			/* Clear overrun flag, otherwise the RX does not work. */
		 LPUART0->STAT = ((LPUART0->STAT & 0x3FE00000U) | LPUART_STAT_OR_MASK);
	 }

	 if(Pr_IRQHandler17) {

		 Pr_IRQHandler17();
	 }

}
#endif


////********************************************************
////********************  Pr_IRQManager ********************
////********************************************************


/*!
   * \brief Set a new IRQ Mask
   * @param irqMask
   */
  void Pr_IRQManager::NewIRQMask(TEDROOMIRQMask irqMask) {};

  /*!
     * \brief Get the current IRQ Mask
     */
  TEDROOMIRQMask Pr_IRQManager::GetIRQMask(void) { return 0; };



  void Pr_IRQManager::DisableAllIRQs(void)
  {
	  portDISABLE_INTERRUPTS(); //Changed from to vPortDisableInterrupts() to portDISABLE_INTERRUPTS()
  }

  void Pr_IRQManager::ApplyCurrentIRQMask(void)
  {
	  portENABLE_INTERRUPTS(); //Changed from to vPortEnableInterrupts() to porENABLE_INTERRUPTS()
  }



  //Installs handler
  void Pr_IRQManager::InstallIRQHandler(Pr_IRQHandler handler,
      uint8_t IRQLevel, uint8_t IRQVectorNumber )
  {

	  switch (IRQVectorNumber){
		  case(17):
				  Pr_IRQHandler17=handler;
		  break;
		  default:;
	  }
  }

  void Pr_IRQManager::DeinstallIRQHandler(unsigned char IRQLevel,
      unsigned char IRQVectorNumber)
  {

    //intr_restore (IRQVectorNumber);
  }




  void Pr_IRQManager::DisableIRQ(uint32_t IRQVectorNumber)
  {
  //  intr_lock (IRQVectorNumber);
  }

  void Pr_IRQManager::EnableIRQ(uint32_t IRQVectorNumber)
  {
     // intr_unlock (IRQVectorNumber);
  }


////********************************************************
////********************  Pr_IRQEvent ********************
////********************************************************





void Pr_IRQEvent::Signal()
{

  xHigherPriorityTaskWoken = pdFALSE;
      /* 'Give' the semaphore to unblock the task. */
  xSemaphoreGiveFromISR( xSemaphore, &xHigherPriorityTaskWoken );

  if( xHigherPriorityTaskWoken == pdTRUE )
  {
        /* Giving the semaphore unblocked a task, and the priority of the
          unblocked task is higher than the currently running task - force
          a context switch to ensure that the interrupt returns directly to
          the unblocked (higher priority) task.
          NOTE: The actual macro to use to force a context switch from an
          ISR is dependent on the port.  This is the correct macro for the
          Open Watcom DOS port.  Other ports may require different syntax.
          Refer to the examples provided for the port being used to determine
          the syntax required. */
	  	  portYIELD_FROM_ISR(1); //Changed from vPortYieldFromISR() to portYIELD_FROM_ISR(1)

  }
}



