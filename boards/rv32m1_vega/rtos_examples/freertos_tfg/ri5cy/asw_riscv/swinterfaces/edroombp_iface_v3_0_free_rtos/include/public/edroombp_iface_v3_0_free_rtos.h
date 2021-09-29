/********************************************************************
 * Copyright 2004-20016 (c) by Oscar Rodriguez Polo, Aitor Viana Sanchez
 * , Miguel Gallego Conde
 *   Space Research Group
 *   University of Alcala,
 *   Computer Engineering Department.
 *    
 *
 *   This program is free software; you can redistribute it and/or
 *   modify it under the terms of the GNU General Public License
 *   as published by the Free Software Foundation; either version 2
 *   of the License, or (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307,USA.
 *
 *
 ****************************************************************************/
 
#ifndef PUBLIC__EDROOMBP_IFACE_V3_0_FREE_RTOS_API_H
#define PUBLIC__EDROOMBP_IFACE_V3_0_FREE_RTOS_API_H


/*global definitions*/
#include <public/config.h>
//#include <platform/basic_types.h>
#include <stdint.h>
// Required software interfaces
#include <public/edroom_types_iface_v1.h>
#include <public/timespec.h>
/* FreeRTOS */
/* Basic FreeRTOS definitions. */
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>

#include <stdio.h>

/*PROTECTED REGION ID(public_edroombp_iface_h) ENABLED START*/
/**
 *  @addtogroup ICUSW_SERVICE_MODULES ICUSw Service Modules
 *  @{
 */
/**
 *  @addtogroup EDROOMSL EDROOM SERVICE LIBRARY
 *  @{
 */
/**
 *  @defgroup EDROOMBP EDROOM BASIC PRIMITIVES
 *  @{
 */

#define EDROOMPrioWRAPPER   (EDROOMprioIDLE + 1)

#define GETPRIORITY(prio)   (EDROOMPrioWRAPPER - prio)

/*	EDROOM priorities	*/
enum TEDROOMPriority{
    EDROOMprioURGENT = 1,
    EDROOMprioVeryHigh,
    EDROOMprioHigh,
    EDROOMprioNormal,
    EDROOMprioLow,
    EDROOMprioVeryLow,
    EDROOMprioMINIMUM,
    EDROOMprioIDLE,
};


struct t_timespec {
    unsigned long   tv_sec;        /* seconds */
    unsigned long   tv_nsec;       /* nanoseconds */
};

#define EDROOM_PRIO_MINIMUM EDROOMprioIDLE

typedef unsigned int TEDROOMStackSizeType;
//Changed from EDROOMClockTicksType to TickType_t. Variable now named EDROOMClockTicksType
typedef TickType_t EDROOMClockTicksType;

typedef unsigned char EDROOMByte;

typedef void Pr_TaskRV_t;		/*return value of the test task*/
/*no parameter passed to the task*/
#define Pr_TaskP_t void

typedef void Pr_IRQHandler_RetType;		/*	return type for IRQ handlers	*/

//*****************************************************

class Pr_Time;
class Pr_Task;

//***************************************************************
class lista_tarea //Changed all xTaskHandle to TaskHandle_t
{
  private:
		struct S_nodo
		{	TaskHandle_t handle;
			 Pr_Task *pr_tarea;
			struct S_nodo * next;
		};
		struct S_nodo *first;
  public:
	  lista_tarea();
	  lista_tarea & add(TaskHandle_t handle,Pr_Task *pr_tarea);
	  lista_tarea & remove(TaskHandle_t handle);
	  Pr_Task * find(TaskHandle_t handle);
};

extern "C" //Corrects undefined ref to __dso_handle
{
void *__dso_handle = NULL;
}

extern "C" //Corrects undefined ref to __cxa_pure_virtual (never accessed)
{
void __cxa_pure_virtual() {while (1);}
}

//********************************************************
//********************  Pr_Kernel  ***********************
//********************************************************

class Pr_Kernel
{
	friend void Pr_Receive(void * ap_data,unsigned datalength);
	friend class Pr_Task;
private:
	static lista_tarea lista;
public:

    Pr_Kernel();
    ~Pr_Kernel(){};

    /**
     * Kernel start method
     *
     * This methos may be invoqued to start the kernel threads.
     */
    void Start();

    /** Kernel panic.  This method will halt the system */
    static void Panic (const char * msg);
};

//********************************************************
//********************  Pr_Semaphore  ********************
//********************************************************

class Pr_Time;
/**
 * \class Pr_Semaphore
 * \brief	semaphore class declaration
 */
class Pr_Semaphore
{

protected:
    /** This attribute is the class mutex   */
	SemaphoreHandle_t xSemaphore; //Changed from xSemaphoreHandle to SemaphoreHandle_t

public:
    /**
     * \todo Default constructor.
     *
     * \param _value :   This parameter is the semaphore counter value.
     *
     * The default semaphore value is 1.
     */
    Pr_Semaphore(uint32_t _value=0);

    /**
     * Semaphore Signal
     */
    void Signal();

    /**
     * Semaphore Wait
     */
    void Wait();

    /**
     * Semaphore conditional wait.
     *
     * The method catch the semaphore if it is possible. In any other case the
     * thread is not blocked.
     *
     * \return The method return 1 in case of the semaphore is catched. In any
     * other case the method returns 0.
     */
    int WaitCond();

    /**
     * \brief	the method try to catch the semaphore during a period of time.
     *	\param	interval	interval to wait
     * \return true if catched, false otherwise.
     */
    bool WaitTimed(const Pr_Time & interval);

    /**
     * Destructor
     */
    ~Pr_Semaphore()
    {
      vQueueDelete(xSemaphore);
    }

};

//********************************************************
//********************  Pr_SemaphoreBin  *****************
//********************************************************

/**
 * \class Pr_SemaphoreBin
 * \brief	Binary semaphore class declaration
 */
class Pr_SemaphoreBin  :  public Pr_Semaphore
{


public:



    const char *name;

    Pr_SemaphoreBin(const char *p_name, uint32_t _value);


    /**
     * Default Constructor.
     */
    Pr_SemaphoreBin(uint32_t _value=0);


    /**
     * Semaphore Signal
     */
    void Signal();

    /**
     * Semaphore Wait
     */
    void Wait();

    /**
     * Semaphore conditional wait.
     *
     * The method catch the semaphore if it is possible. In any other case the
     * thread is not blocked.
     *
     * \return The method return 1 in case of the semaphore is catched. In any
     * other case the method returns 0.
     */
    int32_t WaitCond();

    /**
	 * \brief	the method try to catch the semaphore during a period of time.
	 *	\param	interval	interval to wait
	 *
	 * \return true if catched, false otherwise.
	 */
    bool WaitTimed(const Pr_Time & interval);

    /**
     * Default Destructor.
     *
     * The destructor destroys the semaphore.
     */
    ~Pr_SemaphoreBin(){;}

};


//********************************************************
//********************  Pr_SemaphoreRec  *****************
//********************************************************


#define Pr_Mutex Pr_SemaphoreRec

/**
 * \class Pr_SemaphoreRec
 * \brief	Resource semaphore class declaration
 */
class Pr_SemaphoreRec : public Pr_Semaphore
{

public:



    const char * name;

    /** Default Debug constructor */
    Pr_SemaphoreRec(const char *name);

    /** Constructor for priority ceiling resource sempahore */
    Pr_SemaphoreRec(const char *name, int32_t prioceiling); //Changed from int to int32_t


    /** Default constructor */
    Pr_SemaphoreRec();

    /** Constructor for priority ceiling resource sempahore */
    Pr_SemaphoreRec(int32_t prioceiling);



    /**
     * Mutex lock.
     */
    void Lock(void);
    /**
     * Mutex Wait. Equivalent to Lock
     */
    void Wait(void){Lock();};

    /**
     * Mutex UnLock.
     */
    void UnLock(void);
    /**
     * Mutex Signal. Equivalent to Unlock
     */
    void Signal(void){UnLock();};
    /**
     * Semaphore conditional wait.
     *
     * The method catch the semaphore if it is possible. In any other case the
     * thread is not blocked.
     *
     * \return The method return 1 in case of the semaphore is catched. In any
     * other case the method returns 0.
     */
    int32_t WaitCond(void);

    /* Not implemented	*/
    int32_t WaitTimed(Pr_Time & interval);

    /**
     * Default Destructor
     */
    ~Pr_SemaphoreRec(){;}
};

//********************************************************
//********************  Pr_Task  *************************
//********************************************************



class Pr_Task
{
/**
 * This method sends information to any other task.
 *
 * \param _task :     This is the receiver task.
 * \param _p_data :   This parameter is the data pointer to be sent.
 */
friend void Pr_Send(Pr_Task & _task, void * _p_data);

/**
 * This method receives a data from sent by other task.
 *
 * \param _p_data :      This parameter is the pointer to the received data.
 * \param _datalength :   This parameter is the data length.
 */
friend void Pr_Receive(void * _p_data,unsigned _datalength);

private:

    /** This member is the task identifier  */
	TaskHandle_t taskID;
	//StaticTask_t xTaskBuffer;

    /** This is the task name   */
    const char *name;

    /** This is the thread attributes defined in <sys/types.h<   */
    unsigned short usStackDepth;
    unsigned portBASE_TYPE uxPriority;

    /** Pointer to the data sent through Pr_Send method  */
    void  *p_data;

    //*************   SEMAPHORES *****************

    /**
     * This semaphore is used in the Pr_Send/Pr_Receive methods to synchronize
     * the sender and receiver threads
     */
   Pr_SemaphoreBin semSend;

    /**
     * This semaphore is used in the Pr_Send/Pr_Receive methods to synchronize
     * the sender and receiver threads
     */
   Pr_SemaphoreBin semReceive;

    /**
     * Change the task priority
     *
     * \param _priority :    This parameter is the task priority
     */
    void ChangePriority(TEDROOMPriority _priority);

    /**
     * This member is the IP task pointer.
     */
    Pr_TaskRV_t (*TaskIP)(Pr_TaskP_t);

		/**
     * Static function that wraps the user function associated to the Pr_Task.
    */
    static Pr_TaskRV_t TaskFunction(Pr_TaskP_t);


protected:

    /**
     * Message priority.
     *
     * This is the message treatment priority
     */
    TEDROOMPriority priorityMsg;

    /**
     * Temporal priority.
     */
    TEDROOMPriority priorityTmp;

public:



    /**
     * \brief return the current prio of the TASK
     * @return
     */
    TEDROOMPriority GetCurrentTaskPrio();



    /**
     * Default Constructor
     */
    Pr_Task():taskID(0),
        name("null"),
        usStackDepth(0),
        p_data(NULL),
        semSend((unsigned int)0),
        semReceive((unsigned int)0),
        TaskIP(NULL),
        priorityMsg(EDROOMprioIDLE),
        priorityTmp(EDROOMprioIDLE)
        {/*uxPriority=0;*/}



    /**
     * Debug Constructor
     *
     * \param _taskCode:    This parameter is the pointer to the task code
     * \param _p_name:      This parameter is the task name
     * \param _priority:    This parameter is the task priority
     * \param _stackSize:   This parameter is the task stack size
     *
     * The constructor creates a task. Assigns the needed stack size and the
     * IP code pointer to the task structure.
     */
    Pr_Task(Pr_TaskRV_t (*_taskCode)(Pr_TaskP_t), /*  Task IP */
            const char *_p_name,              /*  Task name   */
            TEDROOMPriority _priority,     /*  task priority   */
            unsigned _stackSize);       /*  stack size  */


    /**
     * Not Debug Constructor
     *
     * \param _taskCode :    This parameter is the pointer to the task code
     * \param _priority :    This parameter is the task priority
     * \param _stackSize :   This parameter is the task stack size
     *
     * The constructor creates a task. Assigns the needed stack size and the
     * IP code pointer to the task structure.
     */
    Pr_Task(Pr_TaskRV_t (*_taskCode)(Pr_TaskP_t), /*  Task IP */
            TEDROOMPriority _priority,     /*  task priority   */
            unsigned _stackSize);       /*  stack size  */


    /**
     * This methos stablis the task priority
     *
     * \param _priority :    This parameter is the task priority
     */
    void SetPriority(TEDROOMPriority _priority);

    /**
     * This method modifies temporally the task priority.
     *
     * \param _priority :    the task priority
     *
     * The task priority is only modify when the priority pass argument is
     * greater than the current task priority. The attribute priorityTmp takes
     * the mayor value between the priority passed an its value.
     * The attribute priorityMsg is not modified.
     */
    void SetMaxPrioTmp(TEDROOMPriority _priority);

    /**
     * This method stablish the message treatment priority.
     *
     * \param _priority :    the task priority
     *
     * The priorityMsg attribute is modified only if the priority passed
     * argument is greater than priorityMsg.
     * The attributes priorityMsg and priorityTmp takes the greater value
     * between these and the priority passed argument.
     */
    void SetMaxPrioMsg(TEDROOMPriority _priority);

    /**
     * This method restores the task priority to the message priority.
     *
     * The method is invoked after been modified the temporal priority task
     * (priorityTmp). The priorityTmp takes the priorityMsg value to maintain
     * the coherence between the real priority task and the priorityTmp value.
     */
    void RestorePrioMsg(void);

    /**
     * Returns the task priority
     *
     * \return This method returns the current task priority.
     */
    TEDROOMPriority GetTaskPrio();

    /**
     * Defaul Destructor
     */
    ~Pr_Task(){}
};

/* Pr_Send function header */
void Pr_Send(Pr_Task &task, void *p_data);
void Pr_Receive(void * ap_data,unsigned datalength);

//********************************************************
//********************  Pr_Time  *************************
//********************************************************

/**
 * \class Pr_Time
 *
 * \brief   This class implements the time EDROOM time management.
 *
 * The class allows to modify the time, set absolute and relative delays and
 * work with the time in many units.
 */
class Pr_Time
{
friend class Pr_Kernel;
friend class Pr_SemaphoreBin;
friend class Pr_IRQEvent;


private:

    /** This parameter stores the system time    */
    struct timespec time;

public:

    /**
     * Default Constructor
     */
    Pr_Time();

    /**
     * Constructor.
     *
     * \param   _time	the time value
     *
     * The constructor inits the object with the time value and units passed
     * as parameters.
     */
    Pr_Time(struct timespec _time);

   /**
	 * Constructor.
	 *
	 * \param   _secs	the seconds value
	 *	\param   _usecs	the microseconds value
	 * The constructor inits the object with the time value and units passed
	 * as parameters.
	 */

	 Pr_Time(uint32_t _secs, uint32_t _usecs);


    /**
     * Constructor.
     *
     * \param   _time :  This parameter is a Pr_Time object used to init the
     * current object.
     *
     * This contructor inits the current object with the same value of the object
     * passed as parameter.
     */
    Pr_Time(const Pr_Time & _time);

    /**
     * \brief	Relative Delay method.
     *
     * \param   _interval :  This parameter is the time delay
     *
     * The method sleeps the caller task during the delay passed as parameter.
     */
    friend void Pr_DelayIn( const Pr_Time & _interval);

    /**
     * \brief	Absolute Delay method.
     *
     * \param   _time :  This parameter is the time to be awaked
     *
     * The method sleeps the caller. The system awake the task at the specified
     * time  (_time)
     */
    friend void Pr_DelayAt( const Pr_Time & _time);

    /**
     * Get the current system time.
     *
     * This method stores in the _time object the current system time.
     */
    void GetTime(void);
    void UpdateToCurrentTime(void){GetTime();}
    

    /**
     * + Operator overload
     *
     * \param   _time :  This parameter is the time structure.
     */
    Pr_Time& operator+=(const Pr_Time& _time);

    /**
     * - Operator overload
     *
     * \param   _time :  This parameter is the time structure.
     */
    Pr_Time& operator-=(const Pr_Time& _time);

    /**
     * = operator overload
     *
     * \param   _time :  This parameter is the time structure.
     */
    Pr_Time& operator=(const Pr_Time& _time);

    /**
     * == operator overload
     *
     * \param   _time :  This parameter is the time structure.
     */
    int operator==(const Pr_Time& _time);

    /**
     * != operator overload
     *
     * \param   _time :  This parameter is the time structure.
     */
    int operator!=(const Pr_Time & _time);

    /**
     * > operator overload
     *
     * \param   _time :  This parameter is the time structure.
     */
    int operator>(const Pr_Time& _time);

    /**
     * < operator overload
     *
     * \param   _time :  This parameter is the time structure.
     */
    int operator<(const Pr_Time& _time);

    /**
     * >= operator overload
     *
     * \param   _time :  This parameter is the time structure.
     */
    int operator>=(const Pr_Time& _time);

    /**
     * <= operator overload
     *
     * \param   _time :  This parameter is the time structure.
     */
    int operator<=(const Pr_Time& _time);

    /**
     * Value of Pr_Time in ticks
     *
     * \return This method returns the value of variable in ticks.
     */
    EDROOMClockTicksType Ticks() const;

    /**
      * Round up or down to the closer ticks
      */
     void RoudMicrosToTicks();

     /**
       * \brief Get Value of the time in seconds + microseconds
       *
 	   * \param   _secs	returns the seconds
	   *	\param   _usecs	returns the microseconds
       */
     void GetValue(uint32_t &_secs, uint32_t &_usecs){
    	 _secs=time.tv_sec;
    	 _usecs=time.tv_nsec*1000;
     }

    /**
        * Value of the system clock in ticks
        *
        * \return This method returns the value of the system clock in ticks.
        */
     EDROOMClockTicksType GetTicks();



};

//********************************************************
//********************  Pr_IRQManager ********************
//********************************************************

/** Interrupt handler routine prototype */
typedef void (* Pr_IRQHandler) (void);

typedef uint8_t TEDROOMIRQMask;

class Pr_IRQManager{


public:

 	/*!
 	 * \brief Set a new IRQ Mask
 	 * @param irqMask
 	 */
	static inline void NewIRQMask(TEDROOMIRQMask irqMask);

 	/*!
     * \brief Get the current IRQ Mask
     * \
     */
	static inline TEDROOMIRQMask GetIRQMask(void);

    /*!
     * \brief This method disables all interrupts but does not change the IRQ
     * mask
     */
	static void DisableAllIRQs(void);

    /*!
     * \brief This method apply the curent IRQ Mask that was in NewIRQMask
     */
	static void ApplyCurrentIRQMask(void);

    /*!
     * \brief This method installs a user interrupt service routine
     * @param handler	pointer to the handler
     * @param IRQLevel	level of the IRQ
     * @param IRQVectorNumber number of the IRQ
     */
	static void InstallIRQHandler(Pr_IRQHandler handler,
                        uint8_t IRQLevel,
                        uint8_t IRQVectorNumber );

    /*!
     * \brief This method deinstall therestore the original service routines
     * @param IRQLevel level of the IRQ
     * @param IRQVectorNumber number of the IRQ
     */
	static void DeinstallIRQHandler(unsigned char IRQLevel
   											,unsigned char IRQVectorNumber);


    /**
     * Prologue hook for an interrupt handler
     *
     * This method must be called from the first line of an application-defined
     * interrupt service routine.  Its implementation may call (if needed) to
     * to the kernel isr prologue.
     *
     * Note that, for the EDROOMBP implementation over FreeRTOS, this is a dummy
     * method
     */
    static inline void HandlerEntry (void) {;};

    /**
     * Epilogue hook for an interrupt handler
     *
     * This method must be called from the last line of an application-defined
     * interrupt service routine.  Its implementation may call (if needed) to
     * to the kernel isr prologue.
     *
     * Note that, for the EDROOMBP implementation over FreeRTOS, this is a dummy
     * method
     */
    static inline void HandlerExit (void) {;};
    /**
     * \brief	 disable an IRQ
     * @param IRQVectorNumber	the number of IRQ
     */
    static void DisableIRQ(uint32_t IRQVectorNumber);
    /**
     * \brief	enable an IRQ
     * @param IRQVectorNumber the number of IRQ
     */
    static void EnableIRQ(uint32_t IRQVectorNumber);

};

//********************************************************
//********************  Pr_IRQEvent **********************
//********************************************************

/**
 * \class Pr_IRQEvent
 * This class implements the event handling. The class allows the threads
 * waitting for an interrupt event with the Wait methods.
 * The irq handlers will also signal the event to propagate it to the waiting
 * threads.
 */

class Pr_IRQEvent{

protected:
	//uint32_t irq_event;
	//uint32_t caller_task_id;
    /** This attribute is the semaphore */
	SemaphoreHandle_t xSemaphore; //Changed from xSemaphoreHandle to SemaphoreHandle_t
    /** Check if a task is woken after signal*/
    portBASE_TYPE xHigherPriorityTaskWoken;

public:


    const char *name;

    /**
     * Debug Constructor.
     *
     * \param name: This parameter is the irq event name.
     * \param IRQ:  This parameter is the IRQ vector number.
     */
    Pr_IRQEvent(const char * name,unsigned char IRQ);



    /**
     * Constructor.
     *
     * \param IRQ :  This parameter is the IRQ vector number.
     */
    Pr_IRQEvent(unsigned char IRQ);



    /**
     * Signal event.
     *
     * This method signals an interrupt event. The signaling provokes the event
     * propagation to the waiting threads.
     */
    void Signal();

    /**
     * Signal event from task.
     *
     * This method signals an interrupt event from a task.
     * The signaling provokes the event propagation to the waiting threads.
     */
    void SignalFromTask();

    /**
     * Wait for an event.
     *
     * This method allows threads to wait for an interrupt event.
     */
    void Wait();

    /**
     * Conditional Wait for an event.
     *
     * This method allows threads to wait for an interrupt event.
     */
    bool WaitCond();

    /**
     * Timed Waitting for an event.
     *
     * This method allows threads to wait for an interrupt event for a time.
     * \param time interval to wait.
     */
    bool WaitTimed(const Pr_Time &time);

};


/**
 * @}
 */
/**
 * @}
 */
/**
 * @}
 */

/*PROTECTED REGION END*/

#endif // PUBLIC__EDROOMBP_IFACE_V3_0_RTEMSAPI_4_8_IMPR_H
