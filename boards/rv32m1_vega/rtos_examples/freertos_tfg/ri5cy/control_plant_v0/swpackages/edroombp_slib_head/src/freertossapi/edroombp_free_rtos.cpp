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
/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

/* Freescale includes. */
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "board.h"

#include "fsl_lpuart_freertos.h"
#include "fsl_lpuart.h"

#include "pin_mux.h"
#include "clock_config.h"
/* others */
#include <public/edroombp_iface_v3_0_free_rtos.h>
#include <public/timespec.h>
//#include <public/debug_primitives.h>
//#include <public/string.h>


//////////////////////////////////////////////////////////////////////
// Clase Lista Tareas Existentes                                    //
//////////////////////////////////////////////////////////////////////

lista_tarea::lista_tarea() {first=NULL;};
//Changed from xTaskHandle to TaskHandle_t
lista_tarea & lista_tarea::add(TaskHandle_t handle,Pr_Task *pr_tarea)
{
	struct S_nodo *aux;
	aux= new S_nodo;
	aux->handle=handle;
	aux->pr_tarea=pr_tarea;
	aux->next=first;
	first=aux;
	return *this;
}
//Changed from xTaskHandle to TaskHandle_t
lista_tarea & lista_tarea::remove(TaskHandle_t handle)
{
	struct S_nodo *aux,*prev=NULL;
	aux=first;

	while (aux!=NULL)
	{
		if (aux->handle==handle)
		{
			if (prev==NULL)
				first=aux->next;
			else
				prev->next=aux->next;
			delete aux;
			break;
		}
		else
		{
			prev=aux;
			aux=aux->next;
		}
	}
	return *this;
}
//Changed from xTaskHandle to TaskHandle_t
Pr_Task * lista_tarea::find(TaskHandle_t handle)
{
	struct S_nodo *aux;
	aux=first;

	while (aux!=NULL)
	{
		if (aux->handle==handle)
		{
			return aux->pr_tarea;
		}
		else
		{
			aux=aux->next;
		}
	}
	return NULL;
}


//******************************************************
//****************  Pr_Kernel **************************
//******************************************************

// VARIABLES ESTATICAS
lista_tarea Pr_Kernel::lista;

Pr_Kernel::Pr_Kernel()
{
	BOARD_InitPins();
	BOARD_BootClockRUN();
	BOARD_InitDebugConsole();
	NVIC_SetPriority(LPUART0_IRQn, 5);

}

void Pr_Kernel::Start()
{
	// Iniciamos el planificador de tareas
	vTaskStartScheduler();
	printf("PLANIFICADOR INICIADO: vTaskStartScheduler()\n");
}

void Pr_Kernel::Panic (const char * msg)
{
	vTaskEndScheduler();
	//printf("PLANIFICADOR FINALIZADO: vTaskEndScheduler()\n");
}


//******************************************************
//****************  Pr_Task ****************************
//******************************************************

//****************  CONSTRUCTORS ***********************

//TaskHandle_t taskID = NULL;
Pr_Task::Pr_Task(Pr_TaskRV_t (*_taskCode)(Pr_TaskP_t), 	/*  Task IP */
                const char *_p_name,              		/*  Task name   */
                TEDROOMPriority _priority,     			/*  task priority   */
                unsigned _stackSize):					/*  stack size  */
                name(_p_name),
                semSend("TaskSem Send",0),
                semReceive("TaskSem recv",0)
{
	this->name = _p_name;
	p_data=NULL;

	 this->TaskIP =  _taskCode;
	    this->usStackDepth = _stackSize;
	    this->uxPriority = priorityMsg = priorityTmp = _priority;

	    unsigned portBASE_TYPE aux_priority = EDROOM_PRIO_MINIMUM - _priority;
	    aux_priority = (aux_priority < 0) ? 0 : aux_priority;
	    //printf("\r\nDirección handle task 1:%p\r\n", &taskID);
	    //Changed task intialization arguments so they match new definition
	    if (pdPASS == xTaskCreate((TaskFunction_t) _taskCode, (const char *) this->name, (uint16_t)_stackSize, NULL, (UBaseType_t)aux_priority, &taskID))
	    {
	      // Asociamos y guardamos el manejador de FreeRTOS y el puntero al objeto Pr_Task de la tarea actual.
	      Pr_Kernel::lista.add(taskID,this);
	    }
	    else
	    {
	      printf("ERROR al crear la TAREA: nombre:%s, taskID:%d, prioridad:%d\n", this->name, (int)taskID,  (int)aux_priority);
	    }
	}

Pr_Task::Pr_Task(Pr_TaskRV_t (*_taskCode)(Pr_TaskP_t), 	/*  Task IP */
                TEDROOMPriority _priority,     			/*  task priority   */
                unsigned _stackSize):        			/*  stack size  */
				name("task"),
				semSend((unsigned int)0),
                semReceive((unsigned int)0)

{

    p_data=NULL;

    this->TaskIP =  _taskCode;
    this->usStackDepth = _stackSize;
    this->uxPriority = priorityMsg = priorityTmp = _priority;

    unsigned portBASE_TYPE aux_priority = EDROOM_PRIO_MINIMUM - _priority;
    aux_priority = (aux_priority < 0) ? 0 : aux_priority;
    //printf("\r\nDirección handle task 2:%p\r\n", &taskID);
    if (pdPASS == xTaskCreate((TaskFunction_t) _taskCode, (const char *) this->name, (uint16_t)_stackSize, NULL, (UBaseType_t)aux_priority, &taskID))
    {
    	// Asociamos y guardamos el manejador de FreeRTOS y el puntero al objeto Pr_Task de la tarea actual.
    	Pr_Kernel::lista.add(taskID,this);
    }
    else
    {
    	printf("ERROR al crear la TAREA: nombre:%s, taskID:%d, prioridad:%d\n", this->name, (int)taskID,  (int)aux_priority);
    }
}

void Pr_Task::SetPriority(TEDROOMPriority _priority)
{
    priorityMsg = _priority;

    if (priorityTmp != priorityMsg)
    {
        priorityTmp = priorityMsg;
        ChangePriority(_priority);
    }
}

void Pr_Task::SetMaxPrioTmp(TEDROOMPriority _priority)
{
    /*
     * We only change the priority if the new priority is greater than
     * (less value) the priorityTmp value
     */
    if (_priority < priorityTmp)
    {
        priorityTmp = _priority;
        ChangePriority(_priority);
    }
}

void Pr_Task::SetMaxPrioMsg(TEDROOMPriority _priority)
{
    if (_priority < priorityMsg)
    {
        priorityMsg = _priority;
        if (priorityMsg < priorityTmp)
        {
            priorityTmp = priorityMsg;
            ChangePriority(_priority);
        }
    }
}

void Pr_Task::RestorePrioMsg(void)
{
    if (priorityTmp != priorityMsg)
    {
        priorityTmp = priorityMsg;
        ChangePriority(priorityMsg);
    }
}

TEDROOMPriority Pr_Task::GetTaskPrio()
{
	return (TEDROOMPriority) uxTaskPriorityGet(taskID);
}

void Pr_Task::ChangePriority(TEDROOMPriority _priority)
{
	// Las prioridades en FreeRTOS son al contrario que en EDROOM
    unsigned portBASE_TYPE aux_priority = EDROOM_PRIO_MINIMUM - _priority;
    aux_priority = (aux_priority < 0) ? 0 : aux_priority;

	vTaskPrioritySet(taskID, aux_priority);
}


//******************************************************
//****************  Pr_Time ****************************
//******************************************************

//****************  CONSTRUCTORS ***********************
// PARA CONVERTIR ==> TICKS=t(s)*configTICK_RATE_HZ ó t(s)=TICKS/configTICK_RATE_HZ
Pr_Time::Pr_Time()
{
    time.tv_sec = 0;
    time.tv_nsec = 0;
}

Pr_Time::Pr_Time(const Pr_Time &_time)
{
    time.tv_nsec = _time.time.tv_nsec;
    time.tv_sec = _time.time.tv_sec;
}

Pr_Time::Pr_Time(uint32_t sec, uint32_t microsec)
{
    time.tv_sec = sec;
    time.tv_nsec = microsec*1000;
}

Pr_Time::Pr_Time(struct timespec _time)
{
    unsigned long nsec;
    unsigned long sec;

    sec = (unsigned long)(_time.tv_nsec / 1000000000);
    time.tv_sec = _time.tv_sec + sec;
    nsec = _time.tv_nsec - (sec * 1000000000);
    time.tv_nsec = nsec;
}


//**************** MODIFIYING METHODS **********************

void Pr_Time::GetTime(void)
{
		EDROOMClockTicksType ticksFromStart = xTaskGetTickCount();
		long secs = ticksFromStart / configTICK_RATE_HZ;

        time.tv_sec = (unsigned long)secs;
        secs -= time.tv_sec;
        time.tv_nsec = (unsigned long)(secs * 1000000000);
}
//Changed from EDROOMClockTicksType to TickType_t
TickType_t Pr_Time::GetTicks()
{
	TickType_t  ticks = 0;
    unsigned long ms_from_ns = 0;

    ticks=time.tv_sec*configTICK_RATE_HZ;
    ms_from_ns=time.tv_nsec/1000000;
    ticks+=(ms_from_ns*configTICK_RATE_HZ)/1000;
    return ticks;
}

//**********   OPERATORS OVERLOAD  *********************

Pr_Time& Pr_Time::operator+=(const Pr_Time &_time)
{
    timespec_add (&time, &(_time.time));
    return *this;
}

Pr_Time& Pr_Time::operator-=(const Pr_Time &_time)
{
    if (_time.time.tv_sec <= time.tv_sec)
    {
        time.tv_sec -= _time.time.tv_sec;
        if (_time.time.tv_nsec > time.tv_nsec)
        {
            if (time.tv_sec)
            {
                time.tv_sec--;
                time.tv_nsec += 1000000000 - _time.time.tv_nsec;
            }
            else
                time.tv_sec = time.tv_nsec = 0;
        }
        else
            time.tv_nsec -= _time.time.tv_nsec;
    }
    else
        time.tv_sec = time.tv_nsec = 0;

    return *this;
}

Pr_Time& Pr_Time::operator=(const Pr_Time &_time)
{
    time.tv_nsec = _time.time.tv_nsec;
    time.tv_sec = _time.time.tv_sec;
    return *this;
}

int Pr_Time::operator==(const Pr_Time &_time)
{
    return timespec_eq (&time, &(_time.time));
}

int Pr_Time::operator!=(const Pr_Time &_time)
{
    return ! timespec_eq (&time, &(_time.time));
}

int Pr_Time::operator>(const Pr_Time &_time)
{
    return timespec_gt (&time, &(_time.time));
}

int Pr_Time::operator<(const Pr_Time &_time)
{
    return timespec_lt (&time, &(_time.time));
}

int Pr_Time::operator>=(const Pr_Time &_time)
{
    return timespec_ge (&time, &(_time.time));
}

int Pr_Time::operator<=(const Pr_Time &_time)
{
    return timespec_le (&time, &(_time.time));
}



TickType_t Pr_Time::Ticks() const //Changed from EDROOMClockTicksType to TickType_t
{

    return xTaskGetTickCount();
}

void Pr_Time::RoudMicrosToTicks()
{

  uint32_t  ticksFromNanoseconds;
  int32_t  nanosecondsFromTicks;
  uint32_t  NSEC_PER_TIC=(1000000000/configTICK_RATE_HZ);

  ticksFromNanoseconds = time.tv_nsec/NSEC_PER_TIC;
  nanosecondsFromTicks = ticksFromNanoseconds*NSEC_PER_TIC;

  if (time.tv_nsec != nanosecondsFromTicks)
  {
      nanosecondsFromTicks += NSEC_PER_TIC / 2;
    if (nanosecondsFromTicks <= time.tv_nsec)
    {
      struct timespec aux;
      aux.tv_sec=0;
      aux.tv_nsec=NSEC_PER_TIC;
      timespec_add(&time,&aux);
    }
  }
}


void Pr_DelayIn(const Pr_Time &_interval)
{
	Pr_Time aux_interval = _interval;
    vTaskDelay(aux_interval.GetTicks());
}

void Pr_DelayAt( const Pr_Time &_time)
{
    Pr_Time aux_time;
    EDROOMClockTicksType tickCountNow, tickCountFinal, init = 0;

    aux_time = _time;
	tickCountNow = xTaskGetTickCount();
	tickCountFinal = aux_time.GetTicks();
	if(tickCountFinal>tickCountNow)
	{
		vTaskDelayUntil( &init, tickCountFinal );
	}
	else
	{
		printf("Pr_DelayAt(): El tiempo de finalizacion [%lu] no puede ser anterior al inicial [%lu].\n"
								, (unsigned long) tickCountFinal
								, (unsigned long) tickCountNow);
	}
}

//********************************************************
//********************  Pr_Semaphore  ********************
//********************************************************

Pr_Semaphore::Pr_Semaphore(uint32_t _value) //Changed from unsigned int to uint32_t
{
  xSemaphore=0;
}


//********************************************************
//********************  Pr_SemaphoreBin  *****************
//********************************************************


Pr_SemaphoreBin::Pr_SemaphoreBin(const char *p_name, uint32_t _value) :
 Pr_Semaphore((uint32_t)_value), name(p_name)
{
	xSemaphore = xSemaphoreCreateCounting( 1, _value );
	//printf("\r\nDirección semaphore counting:%p\r\n", &xSemaphore);
    if( xSemaphore == NULL )
    {
    	printf("ERROR al CREAR xSemaphoreCreateCounting(  1, _value ): %d, nombre:%s, valor:%d\n",  (int)xSemaphore, p_name,  (int)_value);
    }
}



Pr_SemaphoreBin::Pr_SemaphoreBin(uint32_t _value) : Pr_Semaphore(_value)
{
  name="sem";
	xSemaphore = xSemaphoreCreateCounting( 1, _value );
	//printf("\r\nDirección semaphore sem counting:%p\r\n", &xSemaphore);
    if( xSemaphore == NULL )
    {
    	printf("ERROR al CREAR xSemaphoreCreateCounting( 1, _value  ): %d, valor:%d\n",  (int)xSemaphore,  (int)_value);
    }
}



void Pr_SemaphoreBin::Signal()
{
    if( xSemaphoreGive( xSemaphore ) != pdTRUE )
    {
        printf("xSemaphoreGive ERROR al devolver el semaforo: xSemaphoreGive(xSemaphore): %d\n",  (int) xSemaphore);
    }
}

void Pr_SemaphoreBin::Wait()
{
    if( xSemaphoreTake( xSemaphore, ( EDROOMClockTicksType ) portMAX_DELAY ) != pdTRUE )
    {
        printf("xSemaphoreTake ERROR al COGER el semaforo: xSemaphoreTake(xSemaphore, portMAX_DELAY): %d, %lu\n",  (int)xSemaphore
        							,  (unsigned long) portMAX_DELAY);
    }
}

int32_t Pr_SemaphoreBin::WaitCond() //Changed from int to int32_t
{
    int retval = 0;

    retval = (int) xSemaphoreTake( xSemaphore, 0 );

    return retval;
}

bool Pr_SemaphoreBin::WaitTimed(const Pr_Time &_waittime)
{
    bool retval;
    Pr_Time aux_waittime = _waittime;

    retval = xSemaphoreTake( xSemaphore, aux_waittime.GetTicks() );

    return retval;
}


//********************************************************
//********************  Pr_SemaphoreRec  *****************
//********************************************************



Pr_SemaphoreRec::Pr_SemaphoreRec(const char *p_name) : name(p_name)
{
  xSemaphore = xSemaphoreCreateMutex();
  //printf("\r\nDirección semaphore mutex:%p\r\n", &xSemaphore);
    if( xSemaphore == NULL )
    {
      printf("ERROR al CREAR xSemaphoreCreateMutex(): %d\n", (int)xSemaphore);
    }
}


Pr_SemaphoreRec::Pr_SemaphoreRec()

{
  name="Sem";
	xSemaphore = xSemaphoreCreateMutex();
	//printf("\r\nDirección semaphore Sem mutex:%p\r\n", &xSemaphore);
    if( xSemaphore == NULL )
    {
    	printf("ERROR al CREAR xSemaphoreCreateMutex(): %d\n", (int)xSemaphore);
    }
}



Pr_SemaphoreRec::Pr_SemaphoreRec(const char *p_name, int32_t prioceiling) : name(p_name)

{
//    int priority_ceiling;
//
//    priority_ceiling = EDROOM_PRIO_MINIMUM - prioceiling;
//    priority_ceiling = (priority_ceiling < 0) ? 0 : priority_ceiling;

    xSemaphore = xSemaphoreCreateMutex();
    //printf("\r\nDirección semaphore mutex prioceiling:%p\r\n", &xSemaphore);
    if( xSemaphore == NULL )
    {
      printf("ERROR al CREAR xSemaphoreCreateMutex(): %d\n", (int)xSemaphore);
    }
}


Pr_SemaphoreRec::Pr_SemaphoreRec(int32_t prioceiling)


{
  name="sem";
//    int priority_ceiling;
//
//    priority_ceiling = EDROOM_PRIO_MINIMUM - prioceiling;
//    priority_ceiling = (priority_ceiling < 0) ? 0 : priority_ceiling;

    xSemaphore = xSemaphoreCreateMutex();
    //printf("\r\nDirección semaphore sem mutex prioceiling:%p\r\n", &xSemaphore);
    if( xSemaphore == NULL )
    {
    	printf("ERROR al CREAR xSemaphoreCreateMutex(): %d\n", (int)xSemaphore);
    }
}

void Pr_SemaphoreRec::UnLock()
{
    if( xSemaphoreGive( xSemaphore ) != pdTRUE )
    {
        printf("ERROR al DEVOLVER el semaforo: xSemaphoreGive(xSemaphore): %d\n", (int)xSemaphore);
    }
}

void Pr_SemaphoreRec::Lock()
{
    if( xSemaphoreTake( xSemaphore, ( EDROOMClockTicksType ) portMAX_DELAY ) != pdTRUE )
    {
        printf("ERROR al COGER el semaforo: xSemaphoreTake(xSemaphore, portMAX_DELAY): %d, %lu\n"
        									, (int) xSemaphore, (unsigned long) portMAX_DELAY);
    }
}



void Pr_Send(Pr_Task &_task, void *_p_data)
{
    _task.p_data = _p_data;
    _task.semReceive.Signal();
    _task.semSend.Wait();
}

void Pr_Receive(void * _p_data,unsigned _datalength)
{
	Pr_Task *receiver = Pr_Kernel::lista.find(xTaskGetCurrentTaskHandle());

	receiver->semReceive.Wait();

    uint8_t *p_dataAux, *p_dataAuxReceiver;

    p_dataAux = (uint8_t *)_p_data;
    p_dataAuxReceiver = (uint8_t *)receiver->p_data;

    for (unsigned int i = 0; i < _datalength; ++i)
    {
    	*(p_dataAux + i) = *(p_dataAuxReceiver + i);
    }

    receiver->semSend.Signal();
}


////********************************************************
////********************  Pr_IRQManager ********************
////********************************************************
//
//void Pr_IRQManager::DisableIRQ(uint32_t IRQVectorNumber)
//{
////	intr_lock (IRQVectorNumber);
//}
//
//void Pr_IRQManager::EnableIRQ(uint32_t IRQVectorNumber)
//{
////	intr_unlock (IRQVectorNumber);
//}
//
//void Pr_IRQManager::DisableAllIRQs(void)
//{
//	intr_disable ();
//}
//
//void Pr_IRQManager::ApplyCurrentIRQMask(void)
//{
//	intr_enable ();
//}
//
//void Pr_IRQManager::InstallIRQHandler(Pr_IRQHandler handler,
//		uint8_t IRQLevel, uint8_t IRQVectorNumber )
//{
//
//	intr_capture((void (*) (int)) handler, IRQVectorNumber);
//}
//
//void Pr_IRQManager::DeinstallIRQHandler(unsigned char IRQLevel,
//		unsigned char IRQVectorNumber)
//{
//
//	intr_restore (IRQVectorNumber);
//}
//
////********************************************************
////********************  Pr_IRQEvent ********************
////********************************************************



//********************************************************
//********************  Pr_SemaphoreBin  *****************
//********************************************************

Pr_IRQEvent::Pr_IRQEvent(const char * pname,unsigned char IRQ)
{
	//xHigherPriorityTaskWoken=false;
  name=pname;
  vSemaphoreCreateBinary( xSemaphore );
  //printf("\r\nDirección semaphore binary (irq_event):%p\r\n", &xSemaphore);
  if( xSemaphore == NULL )
    {
      printf("ERROR al CREAR xSemaphore(  1, _value ): %d, name:%s\n",  (int)xSemaphore, name);
    }
}



Pr_IRQEvent::Pr_IRQEvent(unsigned char IRQ)
{
  name="irq_event";
  //vSemaphoreCreateBinary( xSemaphore );
  xSemaphore=xSemaphoreCreateCounting( 1, 0);
  //printf("\r\nDirección semaphore counting (irq_event):%p\r\n", &xSemaphore);
    if( xSemaphore == NULL )
    {
            printf("ERROR al CREAR xSemaphore(  1, _value ): %d, name:%s\n",  (int)xSemaphore, name);
    }
}


void Pr_IRQEvent::SignalFromTask()
{

  if( xSemaphoreGive( xSemaphore ) != pdTRUE )
  {
      printf("xSemaphoreGive ERROR al devolver el semaforo: xSemaphoreGive(xSemaphore): %d\n",  (int) xSemaphore);
  }
}




void Pr_IRQEvent::Wait()
{
    if( xSemaphoreTake( xSemaphore, ( EDROOMClockTicksType ) portMAX_DELAY ) != pdTRUE )
    {
        printf("xSemaphoreTake ERROR al COGER el semaforo: xSemaphoreTake(xSemaphore, portMAX_DELAY): %d, %lu\n",  (int)xSemaphore
                      ,  (unsigned long) portMAX_DELAY);
    }
}

bool Pr_IRQEvent::WaitCond()
{
    int retval = 0;

    retval = (int) xSemaphoreTake( xSemaphore, 0 );

    return (0 != retval);
}

bool Pr_IRQEvent::WaitTimed(const Pr_Time &_waittime)
{
    int retval;
    Pr_Time aux_waittime = _waittime;

    retval = xSemaphoreTake( xSemaphore, aux_waittime.GetTicks() );

    return (0 != retval);
}




