/***************************************************************************
 *
 *		EDROOM SERVICE LIBRARY
 *
 *		Copyright (C) 2007-2010  Oscar Rodriguez Polo
 *
 *      Contact: opolo@aut.uah.es
 *
 ****************************************************************************/

/****************************************************************************
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

/*!
 * \brief edroom services library header
 *
 * \author Oscar Rodrguez Polo
 * \date $Date: 2010-02-15 10:09:39 $
 * \version $Revision: 1.1.4.2 $
 */

#ifndef PUBLIC__EDROOMSL_IFACE_V1_H
#define PUBLIC__EDROOMSL_IFACE_V1_H

#include <public/config.h>
//#include <platform/basic_types.h>
#include <stdint.h>

/*PROTECTED REGION ID(public_edroomsl_iface_h) ENABLED START*/
/**
 *  @addtogroup ICUSW_SERVICE_MODULES ICUSw Service Modules
 *  @{
 */
/**
 *  @defgroup EDROOMSL EDROOM SERVICE LIBRARY
 *  @{
 */
#include <public/edroombp_iface_v3_0_free_rtos.h>
#include <public/edroom_types_iface_v1.h>
#include <public/edroomdf.h>

/*!
 * \brief edroommemory header (edroom services library)
 *
 * \author Oscar Rodrguez Polo
 * \date $Date: 2010-03-04 09:08:17 $
 * \version $Revision: 1.1.4.5 $
 *
 * $Log: edroommemory.h,v $
 * Revision 1.1.4.5  2010-03-04 09:08:17  opolo
 * Changed the names of the attributes
 *
 * Revision 1.1.4.4  2010-02-15 10:08:11  opolo
 * actualizados los nombres de los archivos y servicios
 *
 * Revision 1.1.4.3  2006/11/09 15:20:55  opolo
 * Rename of the classes that manage the pools as
 * 	EDROOMPool EDROOMMemoryPool and EDROOMProtectedMemoryPool
 *
 * Revision 1.1.4.2  2006/10/18 18:31:51  opolo
 * Add Log
 *
 *
 * Revision 1.1.4.1  2006/10/18 18:07:20  opolo
 * *** empty log message ***
 *
 */



#ifndef __EDROOMMemory_H
#define __EDROOMMemory_H



/*!
 * \class CEDROOMPool
 * \brief Virtual base class used to support different kind of pools
 *
 * \author Oscar Rodriguez Polo
 */

class CEDROOMPool{

	public:

    /*!
     * This function give back an element to the pool .
     * \param pData pointer to the element
     *
     * \return  0 only if there is none error.
     */

	virtual TEDROOMInt8 FreeData(void * pData)=0;

    /*!
     * Destructor, only to avoid warnings
	*/
	virtual ~CEDROOMPool(){};


};

/*!
 * \class CEDROOMMemoryPool
 * \brief This class defines memory pools that emulate dynamic memory in EDROOM.
 *        The maximun number of elements of the pool is 2?-1
 *
 * \author Oscar Rodriguez Polo
 */


class CEDROOMMemoryPool : public CEDROOMPool {

  protected:

  //!Stores the number of elements
   /*
   * Maximun number of elements = 2-1
   */
  TEDROOMUInt32 Dimension;

  //! True if Pool is empty
  TEDROOMBool Empty;

  //! Pointer to the Data Memory
  TEDROOMByte   * PDataMemory;

  //! Size of each element of the pool
  TEDROOMUInt32 ElementSize;

  //!Array for marking which elements are free
  TEDROOMBool * PFreeMarks;

  //!Index to the next free element.
  /*!
   * If this index is equal to UINT_MAX,
   * there is not free elements
   */

  TEDROOMUInt32 NextFreeIndex;


  public:



  /*!
   * \brief Set the memory of the pool. The memory contains
   *   a number of elements equal to dimension +1. The extra element
   *   is returned only when the pool is empty.
   *   The function does not check the dimension or the memory received.
   *   It assumes they are valid.
   * \param dimension defines the pool dimension
   * \param pDataMemory pointer to the data memory pool.
   * \param pMarksMemory pointer to the memory that stores the free marks
   * \param elementSize size of each element of the pool
   */

  void SetMemory(TEDROOMUInt32 dimension
  					, void * pDataMemory
  					, TEDROOMBool * pMarksMemory
  					, TEDROOMUInt32 elementSize);


  /*!
   * Allocation of a free element,
   * \return a pointer to the element or NULL if none element is available
   */

	TEDROOMByte * AllocData(void);

  /*!
   * Allocation of a free element,
   * \param rElemIndex reference to the index of the element, modified by this
   * 				  method
   * \return a pointer to the element or NULL if none element is available
   */

	TEDROOMByte * AllocData(TEDROOMUInt32& rElemIndex);


    /*!
     * This function give back an element to the pool and marks it as free.
     * \param pData pointer to the element. It must not be NULL, this has been
     * checked before
     *
     * \return  0 only if there is none error.
     * 			-1 if the element does not allow to this pool
     */

	TEDROOMInt8 FreeData(void * pData);


    /*!
     * This function checks when the pool is empty.
     *
     * \return true only if the pool is empty.
     */

	TEDROOMBool IsEmpty(){return NextFreeIndex==Dimension;}

    /*!
     * Destructor, only to avoid warnings
	*/
	~CEDROOMMemoryPool(){}


};


/*!
 * \class CEDROOMProtectedMemoryPool
 * \brief This class defines memory pools that emulate dynamic memory in EDROOM.
 *	The pool is protected in order to be accessible from different Components
 *  The maximun number of elements of the pool is 2-1
 *
 * \author Oscar Rodriguez Polo
 */



class CEDROOMProtectedMemoryPool:public CEDROOMMemoryPool
{
  private:

	//!Semaphore for Mutual Exclusion
	Pr_SemaphoreRec Mutex;



  public:


	CEDROOMProtectedMemoryPool();

	/*!
    * The constructor set the memory of the pool
    * \param dimension defines the pool dimension
   * \param pDataMemory pointer to the data memory pool
   * \param pMarksMemory pointer to the memory that stores the free marks
    * \param elementSize size of each element of the pool
    */
	CEDROOMProtectedMemoryPool(TEDROOMUInt32 dimension
							, void * pDataMemory
							, TEDROOMBool * pMarksMemory
							, TEDROOMUInt32 elementSize);

	/*!
    * Allocation of a free element using mutex
    * \return a pointer to the element or NULL if none element is available
    */

	TEDROOMByte * AllocData(void);


    /*!
    * Allocation of a free element using mutex
    * \param rElemIndex reference to the index of the element, modified by this
    * 				  method
    * \return a pointer to the element or NULL if none element is available
    */

	TEDROOMByte * AllocData(TEDROOMUInt32& rElemIndex);


    /*!
     * This function give back an element to the pool and marks it as free.
	 * The operation is done in mutual exclusion
     * \param pData pointer to the element
     *
     * \return  0 only if there is none error.
     * 			-1 if the element does not allow to this pool
     * 			-2 if the element was free
     */

	TEDROOMInt8 FreeData(void * pData);



    /*!
     * Destructor, only to avoid warnings
	*/
	~CEDROOMProtectedMemoryPool(){}

};



#endif




/*!
 * \brief edroomtypes header (edroom services library)
 *
 * \author Oscar Rodrguez Polo
 * \date $Date: 2010-03-04 09:08:17 $
 * \version $Revision: 1.1.2.2 $
 *
 * $Log: edroomsl_types.h,v $
 * Revision 1.1.2.2  2010-03-04 09:08:17  opolo
 * Changed the names of the attributes
 *
 * Revision 1.1.2.1  2010-02-15 10:08:11  opolo
 * actualizados los nombres de los archivos y servicios
 *
 * Revision 1.1.4.3  2006/11/09 15:23:12  opolo
 * Use the new name of the classes that manage the pools
 * 	EDROOMPool EDROOMMemoryPool and EDROOMProtectedMemoryPool
 *
 * Revision 1.1.4.2  2006/10/18 18:31:51  opolo
 * Add Log
 *
 *
 * Revision 1.1.4.1  2006/10/18 18:07:20  opolo
 * *** empty log message ***
 *
 */



#ifndef __EDROOM_TYPES_H
#define __EDROOM_TYPES_H

//******************************************************************************
//******************************************************************************
// EDROOMTYPES
//******************************************************************************
//******************************************************************************

/*!
 * \struct TEDROOMTransId
 * \brief struct that implements the transition identificator
 * \author Oscar Rodriguez Polo
 */

struct TEDROOMTransId{

  		//!Local identifier in the context where the transition happens
		TEDROOMInt16 localId;

  		//!Distance to the context where the transition happens
		TEDROOMInt8	distanceToContext;

};


//  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Component Types

class CEDROOMComponent;

class CEDROOMComponentMemory;


//  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Timing Types

/*!
 * \enum EDROOMTimerState
 * \brief enum that defines the timer state
 */
enum EDROOMTimerState{edroomTimerCancelled,edroomTimerReady, edroomTimerActive,
	edroomTimerSent, edroomTimerDummy};

class CEDROOMTimerInfo;

class CEDROOMTimingMemory;


//  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Communication Types


class CEDROOMConnection;
class CEDROOMTXChannel;
class CEDROOMLocalTXChannel;
class CEDROOMLocalCommSAP;

typedef int TEDROOMConnectionId;

enum TEDROOMMessageType {msgTypeSend, msgTypeInvoke, msgTypeReply};

//  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Message Types

class CEDROOMMessage;
class CEDROOMSynchrMessage;
class CEDROOMTimeOutMessage;
class CEDROOMSynchrMessagesPool;

class CEDROOMMessagesPool;
class CEDROOMTimeOutMessagesPool;

typedef int TEDROOMSignal;

//const TEDROOMSignal EDROOMNoSignal=-1;

#define EDROOMNoSignal -1

//  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Interface Types


class CEDROOMInterface;
class CEDROOMTimingInterface;
class CEDROOMIRQInterface;


/*!
 * \brief Typedef for connection identifier
 */
typedef TEDROOMWord32 TEDROOMInterfaceID ;

/*!
 * \brief Typedef for component identifier
 */
typedef TEDROOMWord32 TEDROOMComponentID ;


//******************************************************************************
//******************************************************************************
// END EDROOMTYPES
//******************************************************************************
//******************************************************************************

#endif


/**
 * \enum TEDROOMEventType
 * This enumerate defines the Event types
 */
enum TEDROOMEventType
{
  EDROOMEvTypeUndefined=0x00,
  EDROOMEvTypePerioric=0x01,
  EDROOMEvTypeSporadic=0x02,
  EDROOMEvTypeBursty=0x04
};

/**
 * \enum TEDROOMEventError
 * This enumerate defines the Event errors
 */
enum TEDROOMEventError
{
  EDROOMEvNoError=0x00,
  /** The Periodic Event has a Rate Overflow. */
  EDROOMEvErrorPeriodicEvRateOverflow=0x01,
  /** The Periodic Event has a Queue Overflow. */
  EDROOMEvErrorPeriodicEvQueueOverflow=0x02,
  /** The Bursty Eventhas a Rate Overflow. */
  EDROOMEvErrorBurstyEvRateOverflow=0x04,
  /** The Bursty Event has a Queue Overflow. */
  EDROOMEvErrorBurstyEvQueueOverflow=0x08,
  /** The Event associated to an Interrupt triggers a Rate Overflow Alarm. */
  EDROOMEvErrorBurstOverlapped=0x10,
  /** The Sporadic Event has a Queue Overflow. */
  EDROOMEvErrorSporadicEvRateOverflow=0x20,
  /** The Periodic Event has a Queue Alarm. */
  EDROOMEvErrorPeriodicEvQueueAlarm=0x40

};



/*!
 * \class CEDROOMEventCtrl
 * \brief class that implements the event controler.
 * \author Oscar Rodriguez Polo
 */
class CEDROOMEventCtrl{

  friend class CEDROOMInterface;
  friend class CEDROOMTimingInterface;
  friend class CEDROOMIRQInterface;
  friend class CEDROOMComponent;

private:

  //! The Pr_Time that controls the event rate overflow
  Pr_Time m_EvRateOverflowTimeout;

  //! The Pr_Time that controls the burst rate overflow
  Pr_Time m_BurstRateOverflowTimeout;

  //! The Pr_Time that defines the event minimum inter-arrival interval
  Pr_Time m_EvMinInterArrivalTime;

  //! The Pr_Time that defines the Burst minimum inter-arrival interval
  Pr_Time m_BurstMinInterArrivalTime;

  //! The maximum number of elements in the event buffer
  TEDROOMUInt32 m_max_event_buffer;

  //! not processed event counter
  TEDROOMUInt32 m_not_processed_event_counter;

  //! burst event counter
  TEDROOMUInt32 m_burst_event_counter;

  //! Event Type
  TEDROOMEventType m_Type;

  //! Event Type
  TEDROOMByte m_errorNotMasked;

  protected:

  /*!
      * \brief Constructor.
      */
  CEDROOMEventCtrl();
  /*!
      * \brief method that configures Event as Periodic.
      * \param evMinInterArrivalTime minimum inter-arrival time
      * \param max_event_buffer maximum number of elements in the event buffer
      * \param errorMask error mask that defines which errors do not block the
      *       event dispatch. Set to 0x00 if the event dispatch is blocked at every error
      */

  void SetEventAsPeriodic(Pr_Time evMinInterArrivalTime,
                          TEDROOMUInt32 max_event_buffer,
                          TEDROOMByte errorMask);

  /*!
      * \brief method that configures Event as Periodic.
      * \param evMinInterArrivalTime minimum inter-arrival time
      * \param errorMask error mask that defines which errors do not block the
      *       event dispatch. Set to 0x00 if the event dispatch is blocked at every error
      */
  void SetEventAsSporadic(Pr_Time evMinInterArrivalTime,
                          TEDROOMByte errorMask);

  /*!
       * \brief method that configures Event as Periodic.
       * \param evMinInterArrivalTime minimum inter-arrival time
       * \param max_event_per_burst maximum number of events per burst
       * \param evMinInterArrivalTime minimum inter-arrival time
      * \param errorMask error mask that defines which errors do not block the
      *       event dispatch. Set to 0x00 if the event dispatch is blocked at every error
       */

   void SetEventAsBursty(Pr_Time evMinInterArrivalTime,
                           TEDROOMUInt32 max_event_buffer,
                           Pr_Time burstMinInterArrivalTime,
                           TEDROOMByte errorMask);
  /*!
      * \brief New Event triggered
      */
  TEDROOMEventError NewEvent();

  /*!
      * \brief New Periodic Event triggered
      */
  TEDROOMEventError NewPeriodicEvent();

  /*!
      * \brief New Sporadic Event triggered
      */
  TEDROOMEventError NewSporadicEvent();

  /*!
       * \brief New Bursty Event triggered
       */
  TEDROOMEventError NewBurstyEvent();

  /*!
      * \brief Return true if the event must be dispatched
      */
  TEDROOMBool DispatchEvent(TEDROOMEventError error){
    return (0==(error&m_errorNotMasked));
  }

  /*!
  * \brief Event processed
  */
  void EventProcessed(){
    m_not_processed_event_counter--;
  }

};

/*!
 * \brief edroommessage header (edroom services library)
 *
 * \author Oscar Rodrguez Polo
 * \date $Date: 2010-03-04 09:08:17 $
 * \version $Revision: 1.1.4.5 $
 *
 * $Log: edroommessage.h,v $
 * Revision 1.1.4.5  2010-03-04 09:08:17  opolo
 * Changed the names of the attributes
 *
 * Revision 1.1.4.4  2010-02-15 10:08:11  opolo
 * actualizados los nombres de los archivos y servicios
 *
 * Revision 1.1.4.3  2006/11/09 15:23:12  opolo
 * Use the new name of the classes that manage the pools
 * 	EDROOMPool EDROOMMemoryPool and EDROOMProtectedMemoryPool
 *
 * Revision 1.1.4.2  2006/10/18 18:31:51  opolo
 * Add Log
 *
 *
 * Revision 1.1.4.1  2006/10/18 18:07:20  opolo
 * *** empty log message ***
 *
 */


#ifndef EDROOM_MESSAGE_H
#define EDROOM_MESSAGE_H




/*!
 * \class CEDROOMMessage
 * \brief class that implements the asynchronous messages. It is also the base
 * class for any other type of messages
 * \author Oscar Rodriguez Polo
 */
class CEDROOMMessage
{

    //@{ Friend classes
	friend class CEDROOMComponent;
	friend class CEDROOMQueue;
	friend class CEDROOMInterface;
	friend class CEDROOMIRQInterface;
	friend class CEDROOMLocalTXChannel;
	//@}



	/*!
    * \brief Virtual method that free delivery information. It is called after
    * the message is taken from the message queue.
    */

	virtual void FreeDeliveryInfo();

public:

	//!Pointer to the interface that receives the message
	CEDROOMInterface   * mp_Interface;

	//Public attributes
//public:

  	//!Pointer to the Message Pool
	CEDROOMPool *mp_MsgPool;

  	//!Pointer to the Data Pool
	CEDROOMMemoryPool *mp_DataPool;

	//!Time when the message was sent
	Pr_Time   		Time;
	//!message signal
	TEDROOMSignal      signal;
	//!message priority
	TEDROOMPriority    priority;
	//!pointer to optional data
	void            *data;
	//! Type of the message (msgTypeSend, msgTypeInvoke, msgTypeReply)
	//TEDROOMMessageType type;


	/*!
    * \brief Access to the interface on wich message arrived
    * \return pointer to the interface
    */
	CEDROOMInterface   * GetPInterface();

	/*!
    * \brief reply to the received Msg, it does not include an attached data
    * \param signal of the reply message
    */
	virtual void reply(TEDROOMSignal signal);

	/*!
    * \brief reply to the received Msg, it does include an attached data
    * \param signal signal of the reply message
    * \param pData pointer to the attached data
    * \param pDataPool pointer to the data pool of pData
    */
	virtual void reply(TEDROOMSignal signal
						,void * pData
						,CEDROOMMemoryPool *pDataPool);


	/*!
 	* \brief Constructor. Init mp_MsgPool and mp_DataPool to NULL
	*/

	CEDROOMMessage();

   /*!
 	* \brief Destructor, only to avoid warnings
	*/
	virtual ~CEDROOMMessage(){};


};



/*!
 * \class CEDROOMSynchrMessage
 * \brief class that implements the synchronous messages.
 * \author Oscar Rodriguez Polo
 */


class CEDROOMSynchrMessage:public CEDROOMMessage
{
    //@{ Friend classes
	friend class CEDROOMInterface;
	friend class CEDROOMLocalTXChannel;
	friend class CEDROOMRemoteTXChannel;
	//@}

protected:

	/** Semaphore used for the synchronization between the sender and the
	*receiver
	*/
	Pr_SemaphoreBin         m_SynchrSem;

	//!Pointer to the Msg Back
	CEDROOMMessage     *mp_MsgBack;

	//!Is Sender is waiting?
	TEDROOMBool         m_IsSenderWaiting;


public:

	/*!
    * \brief reply to the received Msg, it does not include an attached data
    * \param signal of the reply message
    */
	void virtual reply(TEDROOMSignal signal);

	/*!
    * \brief reply to the received Msg, it does include an attached data
    * \param signal signal of the reply message
    * \param pData pointer to the attached data
    * \param pDataPool pointer to the data pool of pData
    */
	void virtual reply(TEDROOMSignal signal
						,void * pData
						,CEDROOMMemoryPool *pDataPool);


	/*!
 	* \brief Constructor. Init PMsgPool and PDataPool to NULL
	*/

	CEDROOMSynchrMessage();

	/*!
 	* \brief Destructor, only to avoid warnings
	*/

	virtual ~CEDROOMSynchrMessage(){};

};


/*!
 * \class CEDROOMTimeOutMessage
 * \brief class that implements the timeout messages.
 * \author Oscar Rodriguez Polo
 */

class CEDROOMTimeOutMessage:public CEDROOMMessage
{
	//@{ Friend classes
	friend class CEDROOMTimingSAP;
	friend class CEDROOMComponent;
	//@}


protected:

	/*!
    * \brief Virtual method that says if the message is cancelled or not
    * \return true if the message has been cancelled, false if not
    */

	void virtual FreeDeliveryInfo();

private:

  	//!Pointer to the Timer Info
	CEDROOMTimerInfo *mp_TimerInfo;

  	//!Pointer to the Timer Info Pool
	CEDROOMMemoryPool *mp_TimerInfoPool;

    //!Semaphore used for mutual exclusion
	Pr_SemaphoreRec *mp_Mutex;


public:

	/*!
 	* Destructor, only to avoid warnings
	*/
	virtual ~CEDROOMTimeOutMessage(){};


};

/*!
 * \class CEDROOMMessagesPool
 * \brief class that implements the messages pool.
 * \author Oscar Rodriguez Polo
 */

class CEDROOMMessagesPool : public CEDROOMMemoryPool {

public:


  	/*!
	* Set the memory of the pool
   	* \param dimension defines the pool dimension
   	* \param pMessagePool pointer to the message pool
   	* \param pMemoryMarks pointer to the memory that stores the free marks
   	*/

	void SetMemory(TEDROOMUInt32 dimension
					, CEDROOMMessage * pMessagePool
  					, TEDROOMBool * pMemoryMarks);

	/*!
    * Allocation of a free CEDROOMMessage
    * \return a pointer to the CEDROOMMessage or NULL if none element
    * 		  is available
    */
	CEDROOMMessage * AllocData();

	/*!
    * Destructor, only to avoid warnings
	*/

	~CEDROOMMessagesPool(){};
};

/*!
 * \class CEDROOMTimeOutMessagesPool
 * \brief class that implements the timeout messages pool.
 * \author Oscar Rodriguez Polo
 */

class CEDROOMTimeOutMessagesPool: public CEDROOMMemoryPool {

public:

  	/*!
	* Set the memory of the pool
	* \param dimension defines the pool dimension
	* \param pTimeOutMessagePool pointer to the timeout message pool
	* \param pMemoryMarks pointer to the memory that stores the free marks
	*/

  	void SetMemory(TEDROOMUInt32 dimension
					, CEDROOMTimeOutMessage * pTimeOutMessagePool
  					, TEDROOMBool * pMemoryMarks);

	/*!
	* Allocation of a free CEDROOMTimeOutMessage
	* \return a pointer to the CEDROOMTimeOutMessage or NULL if none element
	* 		  is available
	*/
	CEDROOMTimeOutMessage * AllocData();

	/*!
     * Destructor, only to avoid warnings
	*/

	~CEDROOMTimeOutMessagesPool(){};

};

/*!
 * \class CEDROOMSynchrMessageManager
 * \brief class that implements the synchronous messages pool.
 * \author Oscar Rodriguez Polo
 */


class CEDROOMSynchrMessagesPool:public CEDROOMPool{

   //!Pointer to the unique synchronous message that the pool has
	CEDROOMSynchrMessage *  mp_SynchrMsg;

   //!Semaphore used for control the access to the synchronous message
	Pr_SemaphoreBin        m_Sem;

public:


	/*!
 	* Constructor, inits the PSynchrMsg attribute with the pSynchrMsg parameter
    * \param pSynchrMsg pointer to the synchronous message
	*/
	CEDROOMSynchrMessagesPool(CEDROOMSynchrMessage *  pSynchrMsg);

	/*!
    * Allocation of a free CEDROOMSynchrMessage, waiting until the message is
    * available
    * \return a pointer to a free CEDROOMSynchrMessage
    */

	CEDROOMSynchrMessage *  AllocData(void);


	/*!
    * Virtual method that marks the CEDROOMSynchrMessage as free
    * \param pData pointer to the CEDROOMSynchrMessage, it is not used
    *
    * \return always 0
    */

	TEDROOMInt8 FreeData(void * pData);


	/*!
 	* Destructor, only to avoid warnings
	*/
	~CEDROOMSynchrMessagesPool(){};

};


#endif


/*!
 * \brief edroominterface header (edroom services library)
 *
 * \author Oscar Rodrguez Polo
 * \date $Date: 2010-03-04 09:08:17 $
 * \version $Revision: 1.1.4.5 $
 *
 * $Log: edroominterface.h,v $
 * Revision 1.1.4.5  2010-03-04 09:08:17  opolo
 * Changed the names of the attributes
 *
 * Revision 1.1.4.4  2010-02-15 10:08:11  opolo
 * actualizados los nombres de los archivos y servicios
 *
 * Revision 1.1.4.3  2006/11/09 15:23:12  opolo
 * Use the new name of the classes that manage the pools
 * 	EDROOMPool EDROOMMemoryPool and EDROOMProtectedMemoryPool
 *
 * Revision 1.1.4.2  2006/10/18 18:31:51  opolo
 * Add Log
 *
 *
 * Revision 1.1.4.1  2006/10/18 18:07:20  opolo
 * *** empty log message ***
 *
 */




#ifndef __EDROOM_Interface
#define __EDROOM_Interface





/*!
 * \class CEDROOMInterface
 * \brief class that implements the component interfaces.
 * \author Oscar Rodriguez Polo
 */

class CEDROOMInterface{

	//@{ Friend classes
	friend class CEDROOMLocalCommSAP;
	friend class CEDROOMTimingSAP;
	friend class CEDROOMLocalTXChannel;
	friend class CEDROOMMessage;
	friend class CEDROOMSynchrMessage;
	friend class CEDROOMComponent;
	//@}f


protected:

	//!Pointer to the component that owns the interface
	CEDROOMComponent* mp_Component;

	//!Pointer to the channel connected to the interface
	CEDROOMTXChannel * mp_Channel;
	
	//!Interface Global identifier
	TEDROOMInterfaceID m_IdInterface;

  //!Pointer to the event controller
  CEDROOMEventCtrl * mp_EventCtrl;

  //! Component Event Ctrol Error Flags
  TEDROOMUInt32       m_EvCtrlErrorFlags;

  /*!
   * New Event
   */
  TEDROOMEventError NewEvent(){ return mp_EventCtrl->NewEvent();}

  /*!
  * \brief Return true if the event must be dispatched
  */
  TEDROOMBool DispatchEvent(TEDROOMEventError error){
    TEDROOMBool dispatchEvent;
    if(mp_EventCtrl)
      dispatchEvent=mp_EventCtrl->DispatchEvent(error);
    else
      dispatchEvent=true;
    return dispatchEvent;
  }

  /*!
  * the Event message has been processed
  */
  void EventMsgProcessed();


  /** method that sets one component event ctrl error flag.
      * Does not clear the previous value of the ErrorCtrlFlags
      */
  void SetEvCtrlErrorFlag(TEDROOMEventError eventError){
      m_EvCtrlErrorFlags|=(TEDROOMUInt32)eventError;}


public:


  /*!
    * Constructor
    */
  CEDROOMInterface();

	/*!
    * send an asynchronous message with no attached data
    * \param signal message identifier
    */
	void	send (TEDROOMSignal signal);

	/*!
    * send an asynchronous message with attached data
    * \param signal message identifier
    * \param pData pointer to the attached data
    * \param pDataPool pointer to the attached data pool
    */
	void	send (TEDROOMSignal signal
								, void *pData, CEDROOMMemoryPool * pDataPool);


	// synchronous communication primitives:

	/*!
    * send an synchronous message with no attached data and wait the answer
    * \param signal message identifier
    * \return the reply message
    */
	CEDROOMMessage *invoke(TEDROOMSignal signal);


	/*!
    * send an asynchronous message with attached data
    * \param signal message identifier
    * \param pData pointer to the attached data
    * \param apMemDats pointer to the attached data pool
    * \return the reply message
    */

	CEDROOMMessage *invoke(TEDROOMSignal signal,
									void *pData, CEDROOMMemoryPool * apMemDats);


	/*!
    * operator == comparare with other CEDROOMInterface using idInterface
    * \param edroominterface reference to the other interface
    * \return true if match, false if not
    */
	TEDROOMBool operator ==(CEDROOMInterface &edroominterface);

	/*!
    * operator != comparare with other CEDROOMInterface using idInterface
    * \param edroominterface reference to the other interface
    * \return false if match, true if not
    */
	TEDROOMBool operator !=(CEDROOMInterface &edroominterface);

	/*!
    * applyConverFunct, convert the local signal identifier to the signal
    * identifier of the destiny component
    * \return the signal indentifier of the destiny component
    */
	TEDROOMSignal applyConverFunct(TEDROOMSignal signal);


	/** method that returns the Component Event Ctrl Error Flags
	  * \return the error Flags
	  * */
	TEDROOMUInt32 GetEvCtrlErrorFlags(){return m_EvCtrlErrorFlags;}


	/** method that clears the Component event ctrl error flags
	  * */
	void ClearEvCtrlErrorFlags();

	/** method that returns the Component ErrorFlags and clears them
	* \return the error Flags
	* */
	TEDROOMUInt32 GetAndClearEvCtrlErrorFlags();


};

#ifdef _EDROOM_HANDLE_IRQS

/*!
 * \class CEDROOMIRQInterface
 * \brief class that implements the component interfaces with interrupt handlers
 * \author Oscar Rodriguez Polo
 */

class CEDROOMIRQInterface: public CEDROOMInterface{

protected:

	//!IRQ Handler
	Pr_IRQHandler HandIRQ;

	//!Idle IRQ Handler
	Pr_IRQHandler HandIdle;

	//!End IRQ Look Semaphore
	Pr_SemaphoreBin * EndIRQLook;

	//!IRQEvent Look
	Pr_IRQEvent *IRQEventLook;

	//!IRQ number
	TEDROOMInt8 IRQ;

	//!Is IRQ Installed
	bool IRQInstalled;

  //!Event Control
  CEDROOMEventCtrl m_EventCtrl;

public:

	/*!
    * Constructor
    * \param irqHandler Interrupt Handler
    * \param idleIrqHandler Idle Interrupt Handler
    * \param endIrqLook Semaphore for waiting the end of the irq service
    * \param irqLevel Interrupt Level
    */

	CEDROOMIRQInterface(Pr_IRQHandler irqHandler, Pr_IRQHandler idleIrqHandler
							,Pr_IRQEvent &IRQEventLook
							,Pr_SemaphoreBin & endIrqLook
							,TEDROOMInt8 irqLevel);


	/*!
    * New IRQ message is received
    * \param signal message signal
    * \param pData pointer to the data attached
    * \param pDataPool pointer to the data pool
    */
	void	NewIRQMsg(TEDROOMSignal signal, void * pData=NULL
										, CEDROOMMemoryPool * pDataPool=NULL);

	/*!
    * Install IRQ handler
    */

	void InstallHandler();

	/*!
    * Deinstall IRQ handler (install the dummy handler)
    */
	void DeInstallHandler();

	/*!
    * End IRQ Handler Task
    */
	void EndIRQHandlerTask();



	/*!
	      * \brief method that configures Event as Periodic.
	      * \param evMinInterArrivalTime minimum inter-arrival time
	      * \param max_event_buffer maximum number of elements in the event buffer
	      * \param errorMask error mask that defines which errors do not block the
	      *        event dispatch. Set to 0x00 if the event dispatch is blocked at every error
	      *
	      */

	  void SetEventAsPeriodic(Pr_Time evMinInterArrivalTime,
	                          TEDROOMUInt32 max_event_buffer,
	                          TEDROOMByte errorMask){
	    m_EventCtrl.SetEventAsPeriodic(evMinInterArrivalTime,
	                                   max_event_buffer,
	                                   errorMask);
	  }

	  /*!
	      * \brief method that configures Event as Periodic.
	      * \param evMinInterArrivalTime minimum inter-arrival time
        * \param errorMask error mask that defines which errors do not block the
        *        event dispatch. Set to 0x00 if the event dispatch is blocked at every error
	      */
	  void SetEventAsSporadic(Pr_Time evMinInterArrivalTime,
                            TEDROOMByte errorMask){
	    m_EventCtrl.SetEventAsSporadic(evMinInterArrivalTime,errorMask);
	  }

	  /*!
	       * \brief method that configures Event as Periodic.
	       * \param evMinInterArrivalTime minimum inter-arrival time
	       * \param max_event_per_burst maximum number of events per burst
	       * \param evMinInterArrivalTime minimum inter-arrival time
         * \param errorMask error mask that defines which errors do not block the
         *        event dispatch. Set to 0x00 if the event dispatch is blocked at every error

	       */

	   void SetEventAsBursty(Pr_Time evMinInterArrivalTime,
	                           TEDROOMUInt32 max_event_buffer,
	                           Pr_Time burstMinInterArrivalTime,
	                            TEDROOMByte errorMask){
	     m_EventCtrl.SetEventAsBursty(evMinInterArrivalTime, //Invalid arguments
	                                   max_event_buffer,
	                                   burstMinInterArrivalTime,
	                                   errorMask);
	   }

};

/*!
 * \class CEDROOMNonMaskableIRQsnterface
 * \brief class that implements the component interfaces with non-maskable
 *  interrupt handlers
 * \author Oscar Rodriguez Polo
 */

class CEDROOMNonMaskIRQInterface: public CEDROOMIRQInterface{

	  //!IRQ Vector Count
    TEDROOMUInt8 m_IRQVectorCount;

	  //!IRQ Vectors
    TEDROOMUInt8 *mp_IRQVectors;

public:
  /*!
    * Constructor
    * \param irqHandler Interrupt Handler
    * \param idleIrqHandler Idle Interrupt Handler
    * \param endIrqLook Semaphore for waiting the end of the irq service
    * \param IRQVectorCount
    */

	CEDROOMNonMaskIRQInterface(Pr_IRQHandler irqHandler
  																,Pr_IRQHandler idleIrqHandler
																	,Pr_IRQEvent &IRQEventLook
																	,Pr_SemaphoreBin & endIrqLook
                                  ,TEDROOMUInt8 irqVectorCount
                                  ,TEDROOMUInt8 *pirqVectors);



	/*!
    * Install IRQ handler
    */

	void InstallHandler();

	/*!
    * Deinstall IRQ handler (install the dummy handler)
    */
	void DeInstallHandler();

	/*!
    * End IRQ Handler Task
    */
	void EndIRQHandlerTask();


};


#endif



#endif


/*!
 * \brief edroomtiming header (edroom services library)
 *
 * \author Oscar Rodrguez Polo
 * \date $Date: 2010-03-04 09:08:17 $
 * \version $Revision: 1.1.4.5 $
 *
 * $Log: edroomtiming.h,v $
 * Revision 1.1.4.5  2010-03-04 09:08:17  opolo
 * Changed the names of the attributes
 *
 * Revision 1.1.4.4  2010-02-15 10:08:11  opolo
 * actualizados los nombres de los archivos y servicios
 *
 * Revision 1.1.4.3  2006/11/09 15:20:16  opolo
 * Define the EDROOMTimingInterface class
 * Use the new name of the classes that manage the pools
 * 	CEDROOMPool EDROOMMemoryPool and EDROOMProtectedMemoryPool
 *
 * Revision 1.1.4.2  2006/10/18 18:31:51  opolo
 * Add Log
 *
 *
 * Revision 1.1.4.1  2006/10/18 18:07:20  opolo
 * *** empty log message ***
 *
 */


#ifndef __EDROOM_TIMING_SERVICE_H
#define __EDROOM_TIMING_SERVICE_H

class   CEDROOMTimingSAP;

//***************************************************************************

//! Define the Stack of the Timing Task
#define _EDROOM_TIMING_TASK_STACK       1024

//***************************************************************************


//***************************************************************************
/*!
*  \class CEDROOMTimerInfo
*  \brief Contains the information about an EDROOMTimer.
*  \author Oscar Rodriguez Polo
*/
//***************************************************************************

class CEDROOMTimerInfo{

//@{ Friend classes

friend class   CEDROOMTimingSAP;
friend class   CEDROOMTimeOutMessage;
//@}


private:


	//! Time when the Timeout Message will be sent to the component
	Pr_Time m_Time;

	//! Pointer to the next CEDROOMTimerInfo
	/*
	 * It is used to build a list of CEDROOMTimerInfo
	 */
	CEDROOMTimerInfo *mp_Next;

	//! Timer State
	EDROOMTimerState m_State;

	//! Pointer to the Timeout Message
	CEDROOMTimeOutMessage *mp_Msg;


};

//***************************************************************************
/*!
*  \class CEDROOMTimerInfoPool
*  \brief Manages as a Pool the memory of EDROOMTimerInf elements.
*  \author Oscar Rodriguez Polo
*/
//***************************************************************************

class CEDROOMTimerInfoPool: public CEDROOMMemoryPool {


public:

  	 /*!
   	 * \brief Set the memory of the pool
   	 * \param dimension defines the pool dimension
   	 * \param pTimerInfoPool pointer to the CEDROOMTimerInfo memory pool
   	 * \param pMarksMemory pointer to the memory that stores the free marks
   	 */

	void SetMemory(TEDROOMUInt32 dimension, CEDROOMTimerInfo* pTimerInfoPool
	 				,TEDROOMBool * pMarksMemory );

    /*!
   	* \brief Allocation of a free CEDROOMTimerInfo
    * \param rElemIndex reference to the index of the element, modified by this
    * 				  method
    * \return a pointer to the element or NULL if none element is available
    */
	CEDROOMTimerInfo * AllocData(TEDROOMUInt32& rElemIndex);

};


//***************************************************************************
/*!
*  \class CEDROOMTimer
*  \brief The application code can use it to cancel the programmed timers.
*  \author Oscar Rodriguez Polo
*/
//***************************************************************************


class CEDROOMTimer{

friend class   CEDROOMTimingSAP;

	//! Index used to identify the Timer
	TEDROOMUInt32 m_Index;

	//! Pointer to the Timer Information
	CEDROOMTimerInfo * mp_TimerInfo;


public:

	/*!
   	* \brief Constructor
    */
	CEDROOMTimer();


	/*!
   	* \brief Check if the Timer is valid
    * \return true if it is valid, false if it is not
    */

	TEDROOMBool IsValid();


};

//***************************************************************************
/*!
*  \class CEDROOMTimerConfig
*  \brief It is used to send the timer information to the Timing Task
*  \author Oscar Rodriguez Polo
*/
//***************************************************************************


class CEDROOMTimerConfig {

friend class   CEDROOMTimingSAP;

		//! Time when the Timeout Message will be sent to the component
		Pr_Time m_Time;

		//! Pointer to the Timer Information
		CEDROOMTimerInfo * mp_TimerInfo;

};

//***************************************************************************
/*!
*  \class CEDROOMTimingInterface
*  \brief Used to define the Timing Ports
*  \author Oscar Rodriguez Polo
*/
//***************************************************************************


class CEDROOMTimingInterface:public CEDROOMInterface{

friend class CEDROOMComponent;

protected:

   //! Pointer to the Timing SAP
   CEDROOMTimingSAP * mp_TimingSAP;

   //! Maximun Number of Timers
   TEDROOMUInt32 m_MaxNumTimers;

   //!Event Control
   CEDROOMEventCtrl m_EventCtrl;

public:

    /*!
   	* \brief Constructor
    * \param pTimingSAP pointer to the Timing SAP
    * \param maxNumTimers maximun number of Timers
    */

	CEDROOMTimingInterface( CEDROOMTimingSAP * pTimingSAP
												,TEDROOMUInt32 maxNumTimers);



    /*!
   	* \brief Method for programming a Timer using absolute time
    * \param timeValue is the absolute time reference of the timer
    * 		when the time reference will be reach
    * \return an CEDROOMTimer object that can be used to check if the timer has
    * been properly programmed or to cancel the timer
    */


	CEDROOMTimer InformAt(Pr_Time timeValue);



   /*!
   	* \brief Method for programming a Timer using relative time
    * \param interval is the relative time reference of the timer
    * \return an CEDROOMTimer object that can be used to check if the timer has
    * been properly programmed or to cancel the timer
    */


	CEDROOMTimer InformIn  (Pr_Time interval);


	/*!
   	* \brief Method for get Current Time:
    * \param time reference to the Timer Identification
	*/

	void currentTime(Pr_Time &time);

	/*!
   	* \brief Method for get Current Time:
	*/
	Pr_Time currentTime();


  /*!
      * \brief method that configures Event as Periodic.
      * \param evMinInterArrivalTime minimum inter-arrival time
      * \param max_event_buffer maximum number of elements in the event buffer
      * \param errorMask error mask that defines which errors do not block the
      *        event dispatch. Set to 0x00 if the event dispatch is blocked at every error
      *
      */

  void SetEventAsPeriodic(Pr_Time evMinInterArrivalTime,
                          TEDROOMUInt32 max_event_buffer,
                          TEDROOMByte errorMask){
    m_EventCtrl.SetEventAsPeriodic(evMinInterArrivalTime, //Invalid arguments
                                   max_event_buffer,
                                   errorMask);
  }

  /*!
      * \brief method that configures Event as Periodic.
      * \param evMinInterArrivalTime minimum inter-arrival time
      * \param errorMask error mask that defines which errors do not block the
      *        event dispatch. Set to 0x00 if the event dispatch is blocked at every error
      */
  void SetEventAsSporadic(Pr_Time evMinInterArrivalTime,
                          TEDROOMByte errorMask){
    m_EventCtrl.SetEventAsSporadic(evMinInterArrivalTime,errorMask);
  }

  /*!
       * \brief method that configures Event as Periodic.
       * \param evMinInterArrivalTime minimum inter-arrival time
       * \param max_event_per_burst maximum number of events per burst
       * \param evMinInterArrivalTime minimum inter-arrival time
       * \param errorMask error mask that defines which errors do not block the
       *        event dispatch. Set to 0x00 if the event dispatch is blocked at every error

       */

   void SetEventAsBursty(Pr_Time evMinInterArrivalTime,
                           TEDROOMUInt32 max_event_buffer,
                           Pr_Time burstMinInterArrivalTime,
                            TEDROOMByte errorMask){
     m_EventCtrl.SetEventAsBursty(evMinInterArrivalTime, //Invalid arguments
                                   max_event_buffer,
                                   burstMinInterArrivalTime,
                                   errorMask);
   }


};

//***************************************************************************
/*!
*  \class CEDROOMTimingSAP
*  \brief Class that implements the Timing Service Access Point.
*  \author Oscar Rodriguez Polo
*/
//***************************************************************************


class CEDROOMTimingSAP{


	friend class CEDROOMTimingInterface;

private:

	//! Pointer to the component owner of the Timing SAP
	CEDROOMComponent * mp_Component;


	//! Resource Semaphore for the mutual exclusion access of the Timing SAP
	Pr_SemaphoreRec m_Mutex;

	//! Semaphore for synchronization
	Pr_SemaphoreBin m_SynchrSem;

	//! Memory Pool for dynamic allocation of the timers information
	CEDROOMTimerInfoPool *mp_TimerInfoPool;

	//! Pointer to the next TimerInfo when the TimerInfo is in a List
	CEDROOMTimerInfo *mp_NextTimer;

	//! Memory Pool for dynamic allocation of the TimeOut Messages
	CEDROOMTimeOutMessagesPool *mp_TimeOutMsgPool;

	//! Pointer to timer task object
	Pr_Task *mp_TimerTask;

	//! Timer task object
	Pr_Task m_TimerTask;

	//! Semaphore for waiting Component
	Pr_SemaphoreBin m_WaitComponentSem;


public:


    /*!
   	* \brief Constructor
    * \param pComponent pointer to Component that
    * \param maxNumTimers Maximun number of Timers
    * \param pTimmingMemory pointer to Memory of the TimingSAP
    */
	CEDROOMTimingSAP(CEDROOMComponent * pComponent,unsigned int maxNumTimers,
										CEDROOMTimingMemory *pTimmingMemory);


	/*!
   	* \brief Method for programming a Timer using an absolute time with a data
   	* attached
    * \param interface is the interface that requires the timing service
    * \param timeValue is the absolute time reference of the timer
    * \return an CEDROOMTimer object that can be used to check if the timer has
    * 		been properly programmed or to cancel the timer
    */
	CEDROOMTimer InformAt(CEDROOMTimingInterface* interface, Pr_Time timeValue);



	/*!
   	* Code that implements the task associated to Timing SAP
    */

    static Pr_TaskRV_t EDROOMfunTimer(Pr_TaskP_t);



	/*!
   	* Method for starting the Timing Service
	*/

	void  Start();


};

//***************************************************************************
/*!
*  \class CEDROOMTimingMemory
*  \brief Class that implements the Timing Service Memory.
*  \author Oscar Rodriguez Polo
*/
//***************************************************************************


class CEDROOMTimingMemory{

friend class CEDROOMTimingSAP;

	public:

	/*!
   	* Memory of the timer information
	*/
	  CEDROOMTimerInfoPool  m_TimerInfoMem;

	/*!
   	* Memory of the timeout messages
	*/
	  CEDROOMTimeOutMessagesPool  m_TimeOutMessMem;

	/*!
   * Set the memory of the timing service
   * \param elemNumber defines the number of elements of timing service
   * \param pTimerInfoMem pointer to the data memory pool of the timing
   * 							information elements
   * \param pTimerInfoMemMarks pointer to the memory that stores the free marks
   * 							of the timing information elements
   * \param pTimeOutMessageMem pointer to the data memory pool of the timeout
   * 							messages
   * \param pTimeOutMessageMemMarks pointer to the memory that stores the free
   * 							marks of the timeout messages
   */

	  void SetMemory(TEDROOMUInt32  elemNumber, CEDROOMTimerInfo * pTimerInfoMem
	  				, TEDROOMBool * pTimerInfoMemMarks
	  				, CEDROOMTimeOutMessage* pTimeOutMessageMem
	  				, TEDROOMBool *pTimeOutMessageMemMarks);

};



#endif


/*!
 * \brief edroomqueue header (edroom services library)
 *
 * \author Oscar Rodrguez Polo
 * \date $Date: 2010-03-04 09:08:17 $
 * \version $Revision: 1.1.4.5 $
 *
 * $Log: edroomqueue.h,v $
 * Revision 1.1.4.5  2010-03-04 09:08:17  opolo
 * Changed the names of the attributes
 *
 * Revision 1.1.4.4  2010-02-15 10:08:11  opolo
 * actualizados los nombres de los archivos y servicios
 *
 * Revision 1.1.4.3  2006/11/09 15:23:12  opolo
 * Use the new name of the classes that manage the pools
 * 	EDROOMPool EDROOMMemoryPool and EDROOMProtectedMemoryPool
 *
 * Revision 1.1.4.2  2006/10/18 18:31:51  opolo
 * Add Log
 *
 *
 * Revision 1.1.4.1  2006/10/18 18:07:20  opolo
 * *** empty log message ***
 *
 */



#ifndef __EDROOM_QUEUE_H
#define __EDROOM_QUEUE_H

//***************************************************************************
/*!
*  \class CEDROOMQueue
*  \brief It implements the message queues of the components
*  \author Oscar Rodriguez Polo
*/
//***************************************************************************


class CEDROOMQueue
{

public:

//***************************************************************************
/*!
*  \class CQueueNode
*  \brief It implements a queue node
*  \author Oscar Rodriguez Polo
*/
//***************************************************************************

  class CQueueNode{
	friend class CEDROOMQueue;

	//! Pointer to the message
	CEDROOMMessage * mp_Msg;
	//! Pointer to the message next node
	CQueueNode *mp_Next;

	public:

	/*!
   	* \brief Constructor
    */
	CQueueNode();

  };


//***************************************************************************
/*!
*  \class CEDROOMQueueNodesPool
*  \brief it handles the memory of the queue
*  \author Oscar Rodriguez Polo
*/
//***************************************************************************


   class CEDROOMQueueNodesPool: public CEDROOMMemoryPool {

	friend class CEDROOMComponentMemory;

	   public:

		/*!
	   * \brief Set the memory of the timing service
	   * \param elemNumber defines the number of elements of the queue
	   * \param pPoolData pointer to the data memory of the queue
	   * \param pPoolMarks pointer to the memory that stores the free marks
	   * 							of the queue elements
	   */

		void SetMemory(TEDROOMUInt32 elemNumber, CQueueNode * pPoolData
													,TEDROOMBool * pPoolMarks);


 	 	/*!
	   * \brief Alloc Data from the pool
	   * \return a node from the pool
	   */
		CQueueNode * AllocData();

  };


//***************************************************************************
/*!
*  \class CQueueHead
*  \brief it implements the head of the queue
*  \author Oscar Rodriguez Polo
*/
//***************************************************************************

  class CQueueHead{

	friend class CEDROOMQueue;

	//!Priority of the queue
	TEDROOMPriority m_Priority;
	//!Pointer to the first element
	CQueueNode *mp_First;
	//!Pointer to the last element
	CQueueNode *mp_Last;
	//!Pointer to the head of the next queue
	CQueueHead *mp_Next;

	public:
	/*!
   	* \brief Constructor
    */

	CQueueHead();
  };

public:


  	/*!
   	* \brief Constructor
    * \param Max_Num_Mess Maximum number of Messages
    * \param pTask pointer to the Component task
    * \param pMutexSem pointer to the mutex
    * \param prioNumber number of diferent priorities
    * \param pNodesPool  pointer to component memory that includes the
    * 							queue nodes memory
    * \param pQueueHeads pointer to component queue heads.
    */


	CEDROOMQueue(TEDROOMUInt32 Max_Num_Mess,
						Pr_Task * pTask,
						Pr_SemaphoreRec * pMutexSem,
						TEDROOMUInt16 prioNumber,
						CEDROOMQueueNodesPool * pNodesPool,
						CQueueHead * pQueueHeads);


	/*!
   	* \brief Check if the queue is full
   	* \return true if queue is full
    */

	TEDROOMBool IsFull();


	/*!
   	* \brief Put a message in the queue, keeping it sorted by message priority
    * \param pMsg message pointer
    */

	void In (CEDROOMMessage* pMsg);


	/*!
   	* \brief Take a message from the queue
    * \param p_Msg reference to the message pointer
    * \return true everything is OK
    */

	TEDROOMBool Out(CEDROOMMessage * & p_Msg);



protected:

// ****************************************************************************
//		Protected attributes
// ****************************************************************************

	//! Pointer to the Task owner of the queue
	Pr_Task        *mp_Task;

	Pr_SemaphoreRec * mp_MutexSem;

	//! number of different priorities
	TEDROOMUInt16 m_PrioNumber;

	//! maximum number of messages
	TEDROOMUInt32 m_MaxNumMsg;


	//! Queue messages counter
	TEDROOMUInt32 m_MsgCounter;


	/*! New Message semaphore. Out method waits for this semaphore when queue is
	*   empty
	*/
	Pr_SemaphoreBin 		m_NewMsgSem;


	//! Component Task is blocked

	TEDROOMBool m_IsBlocked;

	//! Queue Heads. The queue is in facts an array of queues, one per priority
	CQueueHead  * mp_QueueHeads;

	/*! pointer to the first queue head that contains highest priority messages
	*   and is the first node of a list of queue heads sorted by priority
	*/
	CQueueHead  * mp_FirstQueueHead;


	//! pointer to the queue nodes memory pool
	CEDROOMQueueNodesPool   *mp_NodesPool;


// ****************************************************************************
//		Protected methods
// ****************************************************************************

	/*!
   	* \brief Update the sorted (by priority) list of queue heads
   	* \param newMsgPriority is the priority of the new message added that
   	* 		 				causes the updating
    */

	void UpDateSortedQueueHeadsList(TEDROOMPriority newMsgPriority);


	/*!
   	* \brief Put a node in the queue
   	* \param queueHead is the queue head where the node is added
   	* \param node is the node that is going to be added
   	* \return true if the queue head was empty
    */

	TEDROOMBool PutInNode(CQueueHead *queueHead , CQueueNode * node);

	/*!
   	* \brief Take out a node from the highest priority queue
   	* \param rpNode is a reference to the pointer that is taken
   	* \param rPriority is a reference to priority of the highest priority queue
   	*/

	void TakeOutNode(CQueueNode * &rpNode, TEDROOMPriority &rPriority);


};




#endif



/*!
 * \brief edroomcomm header (edroom services library)
 *
 * \author Oscar Rodrguez Polo
 * \date $Date: 2010-03-04 09:08:17 $
 * \version $Revision: 1.1.4.5 $
 *
 * $Log: edroomcomm.h,v $
 * Revision 1.1.4.5  2010-03-04 09:08:17  opolo
 * Changed the names of the attributes
 *
 * Revision 1.1.4.4  2010-02-15 10:08:11  opolo
 * actualizados los nombres de los archivos y servicios
 *
 */



#ifndef __EDROOM_CSAP_H
#define __EDROOM_CSAP_H

//******************************************************************************
/*!
 * \class CEDROOMLocalTXChannel
 * \brief This is the base class for TX EDROOM connection channels
 *
 * \author Oscar Rodriguez Polo
 */
//******************************************************************************

class CEDROOMTXChannel{

friend class CEDROOMLocalCommSAP;
friend class CEDROOMRemoteCommSAP;

friend class CEDROOMInterface;
friend class CEDROOMConnection;

protected:

	//! pointer to the sender to receiver signal translator
	TEDROOMSignal  (*mp_SenderToReceiverSignalTranslator) (TEDROOMSignal );

public:

	/** Constructor, it inits NULL all the attributes
	 */
	CEDROOMTXChannel(){mp_SenderToReceiverSignalTranslator=NULL;}

	/** Destructor
	 */
	virtual ~CEDROOMTXChannel(){}

	/*!
    * \brief send an asynchronous message
    * \param signal message identifier
    * \param pData pointer to the attached data
    * \param pDataPool pointer to the attached data pool
    */
	virtual void send (TEDROOMSignal signal
								, void *pData
								, CEDROOMMemoryPool * pDataPool)=0;

	/*!
    * \brief send an asynchronous message
    * \param signal message identifier
    * \param pData pointer to the attached data
    * \param pDataPool pointer to the attached data pool
    * \return the reply message
    */
	virtual CEDROOMMessage *invoke(TEDROOMSignal signal
								, void *pData, CEDROOMMemoryPool * pDataPool)=0;


};


//******************************************************************************
/*!
 * \class CEDROOMLocalTXChannel
 * \brief This class implements the EDROOM connection channels
 *
 * \author Oscar Rodriguez Polo
 */
//******************************************************************************

class CEDROOMLocalTXChannel: public CEDROOMTXChannel{

friend class CEDROOMLocalCommSAP;
friend class CEDROOMInterface;
friend class CEDROOMLocalConnection;

protected:

	//! pointer to Sender Port
	CEDROOMInterface * mp_SenderPort;
	//! pointer to Receiver Port
	CEDROOMInterface * mp_ReceiverPort;


	//! pointer to Sender Component
	CEDROOMComponent  *mp_SenderCmp;
	//! pointer to Receiver Task
	CEDROOMComponent  *mp_ReceiverCmp;



	//! pointer to Message Back
	CEDROOMMessage * mp_MessageBack;


public:

	/** Constructor, it inits NULL all the attributes
	 */
	CEDROOMLocalTXChannel();

	/** Destructor, it inits NULL all the attributes
	 */
	virtual ~CEDROOMLocalTXChannel(){};

	/*!
    * \brief send an asynchronous message
    * \param signal message identifier
    * \param pData pointer to the attached data
    * \param pDataPool pointer to the attached data pool
    */
	void send (TEDROOMSignal signal,  void *pData
								, CEDROOMMemoryPool * pDataPool);

	/*!
    * \brief send an asynchronous message
    * \param signal message identifier
    * \param pData pointer to the attached data
    * \param pDataPool pointer to the attached data pool
    * \return the reply message
    */
	CEDROOMMessage *invoke(TEDROOMSignal signal
								, void *pData, CEDROOMMemoryPool * pDataPool);


};

//******************************************************************************
/*!
 * \class CEDROOMLocalConnection
 * \brief This class implements the EDROOM local connection
 *
 * \author Oscar Rodriguez Polo
 */
//******************************************************************************

class CEDROOMLocalConnection{

friend class CEDROOMLocalCommSAP;

	//! connection channel 1
	CEDROOMLocalTXChannel m_Channel1;
	//! connection channel 2
	CEDROOMLocalTXChannel m_Channel2;


};


//******************************************************************************
/*!
 * \class CEDROOMLocalCommSAP
 * \brief This class implements the EDROOM local communication service access
 * point
 *
 * \author Oscar Rodriguez Polo
 */
//******************************************************************************

class CEDROOMLocalCommSAP{


public:


	/*!
    * \brief register the Interface
    * \param id interface local identifier
    * \param interface reference to the interface
    * \param pComponent pointer to the component
    * \return a value !=0 if there is an error
    */
	TEDROOMInt32 RegisterInterface( TEDROOMInterfaceID id
						, CEDROOMInterface & interface
						, CEDROOMComponent* pComponent);


	/*!
    * \brief Connect the components interfaces
    * \param interfaceComp1 reference to component 1 interface
    * \param interfaceComp2 reference to component 2 interface
    * \param connection reference to the object that handles the connection
    * \param comp1ToComp2SignalTranslator component1 to component2 signal
    * 			translator
    * \param comp2ToComp1SignalTranslator component2 to component1 signal
    * 			translator
    */
	void Connect(CEDROOMInterface & interfaceComp1
				,CEDROOMInterface & interfaceComp2
				,CEDROOMLocalConnection &connection
				,TEDROOMSignal  (comp1ToComp2SignalTranslator) (TEDROOMSignal)
				,TEDROOMSignal  (comp2ToComp1SignalTranslator) (TEDROOMSignal));


};

#endif


/*!
 * \brief edroomcomponent header (edroom services library)
 *
 * \author Oscar Rodrguez Polo
 * \date $Date: 2010-03-04 09:08:17 $
 * \version $Revision: 1.1.2.2 $
 *
 * $Log: edroomcomponent.h,v $
 * Revision 1.1.2.2  2010-03-04 09:08:17  opolo
 * Changed the names of the attributes
 *
 * Revision 1.1.2.1  2010-02-15 10:08:11  opolo
 * actualizados los nombres de los archivos y servicios
 *
 */


#ifndef _EDROOM_COMPONENT_H
#define _EDROOM_COMPONENT_H

/**
 * \enum TEDROOMCmpError
 * This enumerate defines the component errors
 */
enum TEDROOMCmpError
{
	EDROOMNoError=0x00,
	/**	The message could not be queued because the
	 *  message queue is full. */
	EDROOMMsgQueueFull=0x01,
	/** The asynchronous message could not be queued because
	 *  the asynchronous message Pool was empty. */
	EDROOMAsyncMsgPoolEmpty=0x02,
	/**	The message associated to a Timing Service could not be queued because
	 * 	the messages Pool was empty.	*/
	EDROOMTimeoutMsgPoolEmpty=0x04,
	/**	The data attached to an Interrupt message could not be allocated because
	 * 	the data Pool was empty. A spare data item is used instead, so no lack
	 * 	of memory happens, but the Pool status is reported.*/
	EDROOMIRQDataPoolEmpty=0x08,
	/**	The data attached to an Asynchronous message could not be allocated
	 * 	because the data Pool was empty. A spare data item is used instead,
	 * 	so no lack of memory happens, but the Pool status is reported. */
	EDROOMSendDataPoolEmpty=0x10,
	/**	The data attached to a Synchronous Invoke message could not be allocated
	 * 	because the data Pool was empty. A spare data item is used instead, so
	 * 	no lack of memory happens, but the Pool status is reported. */
	EDROOMInvokeDataPoolEmpty=0x20,
	/**	The data attached to a Synchronous Reply message could not be allocated
	 * 	because the data Pool was empty. A spare data item is used instead, so
	 * 	no lack of memory happens, but the Pool status is reported. */
	EDROOMReplyDataPoolEmpty=0x40,
	/**	The data attached to a message does not come from the data Pool
	 * 	associated to the message, so it cannot be returned. */
	EDROOMDataOutOfPool=0x80
};


//************************************************************************
/*!
 * \class CEDROOMComponent
 * \brief This class implements an component on an EDROOM Model .
 *
 * \author Oscar Rodriguez Polo
 */
//************************************************************************


class CEDROOMComponent{

	friend class CEDROOMLocalCommSAP;
	friend class CEDROOMTimingSAP;
	friend class CEDROOMLocalTXChannel;
	friend class CEDROOMQueue;
	friend class CEDROOMIRQInterface;
	friend class CEDROOMInterface;
	friend class CEDROOMSynchrMessage;


	//*************************************************************************
		//Protected Attributes
	//*************************************************************************


protected:


	// !Component's global ID
	TEDROOMComponentID		m_ComponentID;

	//! Component resources Mutex
	Pr_SemaphoreRec 			m_Mutex;

	//! Message Back in a Synchronous Communication
	CEDROOMMessage 				m_MessageBack;

	//! Message Out in a Synchronous Communication
	CEDROOMSynchrMessage 		m_SynchrMsgOut;

	//!	Synchronous Messages Pool
	CEDROOMSynchrMessagesPool 	m_SynchrMsgPool;


	//! Message Pool Pointer
	CEDROOMMessagesPool 		*mp_MsgPool;


	//! Nominal priority of the component
	TEDROOMPriority 			m_NomPriority;


	// !Component Task
	Pr_Task 					m_ComponentTask;

	// !Pointer to Component Task
	Pr_Task 				*	mp_ComponentTask;

	//! Component Messages Queue
	CEDROOMQueue 				m_MsgQueue;


	//! Component Error Flags
	TEDROOMUInt32				m_ErrorFlags;

	//! Component Event Ctrol Error Flags
	TEDROOMUInt32       m_EvCtrlErrorFlags;

//*************************************************************************
		//Protected Methods
//*************************************************************************

	/*!
   	* Code that implements the component task
    */
    static Pr_TaskRV_t EDROOMComponentTask(Pr_TaskP_t);


	//! virtual method that will implement the component behaviour
	virtual void EDROOMBehaviour()=0;


	//! function that frees a message
	void EDROOMFreeMessage(CEDROOMMessage *&);

	//! function that frees the message back data in a synchronous communication
	void EDROOMFreeMsgBackData();


  /** method that sets one component event ctrl error flag.
    * Does not clear the previous value of the ErrorCtrlFlags
    */
  void SetEvCtrlErrorFlag(TEDROOMEventError eventError){
    m_EvCtrlErrorFlags|=(TEDROOMUInt32)eventError;}


//*************************************************************************
		//Public Attributes
//*************************************************************************


public:


	/** current message that component handles after it has been got
	 * from the component message queue. The memory related with the message
	 * is freed after message is handled
	 */
	CEDROOMMessage *Msg;

	//! message back in a synchronous communication.
	CEDROOMMessage *MsgBack;


	/** Method that gets new message from the component queue and it is pointed
	 * by Msg.
	 *  Previous message pointed by Msg is freed.
	 */
	void EDROOMNewMsg();


	/** Component constructor in Debug mode
	 * \param componentID identifier of the component
	 * \param numPri number of different message priorities that component
	 * 			handles
	 * \param numMaxM maximum number of messages in Queue
	 * \param prioTask priority when component task is created
	 * \param stack component task stack
	 * \param pComponentMemory pointer to component memory
	 */

	CEDROOMComponent(				TEDROOMComponentID componentID,
									TEDROOMUInt16 numPri,
									TEDROOMUInt32 numMaxM,
									TEDROOMPriority prioTask,
									TEDROOMUInt32 stack,
									CEDROOMComponentMemory * pComponentMemory);




	/** Component Start creates the Component task from virtual EDROOMBehaviour method
	 * \return 0
	 */
	int EDROOMStart ();


	/** virtual Component destructor, only for avoid warnings
	 */
	virtual ~CEDROOMComponent();


	/** method that forces Component destruction
	 */
	//void EDROOMDestroy();

	/** method that returns the Component ErrorFlags
	* \return the error Flags
	* */
	TEDROOMUInt32 GetErrorFlags(){return m_ErrorFlags;}

	/** method that sets one component error flag. Does not clear the previous
	 * value of the ErrorFlags
	*/
	void SetErrorFlag(TEDROOMCmpError cmpError){
								m_ErrorFlags|=(TEDROOMUInt32)cmpError;}


	/** method that clears the Component ErrorFlags
	* */
	void ClearErrorFlags(){ m_Mutex.Lock(); m_ErrorFlags=0; m_Mutex.UnLock();}

	/** method that returns the Component ErrorFlags and clears them
	* \return the error Flags
	* */
	TEDROOMUInt32 GetAndClearErrorFlags()
	{
		TEDROOMUInt32 errorFlags=GetErrorFlags();

		ClearErrorFlags();

		return errorFlags;
	}


	/** method that returns the Component Event Ctrl Error Flags
	  * \return the error Flags
	  * */
  TEDROOMUInt32 GetEvCtrlErrorFlags(){return m_EvCtrlErrorFlags;}

  /** method that clears the Component event ctrl error flags
    * */
  void ClearEvCtrlErrorFlags(){  m_Mutex.Lock(); m_EvCtrlErrorFlags=0;  m_Mutex.UnLock();}

  /** method that returns the Component ErrorFlags and clears them
  * \return the error Flags
  * */
  TEDROOMUInt32 GetAndClearEvCtrlErrorFlags()
  {
    TEDROOMUInt32 errorFlags;
    m_Mutex.Lock();

    errorFlags=GetEvCtrlErrorFlags();
    m_EvCtrlErrorFlags=0;

    m_Mutex.UnLock();
    return errorFlags;
  }


	//! Nominal priority of the component
	/** method that returns the Component Nominal Priority
	* \return the nominal priority
	* */
	TEDROOMPriority GetNomPriority(){	return m_NomPriority;}

};

//************************************************************************
/*!
 * \class CEDROOMComponentMemory
 * \brief This class implements the component memory on an EDROOM Model.
 *
 * \author Oscar Rodriguez Polo
 */
//************************************************************************

class CEDROOMComponentMemory{


	friend class CEDROOMComponent;
	friend class CEDROOMQueue;
	friend class CEDROOMTimingSAP;

	protected:

	//! messages pool
	CEDROOMMessagesPool  					m_MessagesPool;
	//! queue nodes pool
	CEDROOMQueue::CEDROOMQueueNodesPool  	m_QueueNodesPool;
	//! pointer to queue heads
	CEDROOMQueue::CQueueHead        * 		mp_QueueHeads;


	/** Set Memory
		 * \param asynMsgNumber Asynchronous Messages number
	 * \param pMessagesMemory  pointer to connections memory
	 * \param pMessagesMarksMemory pointer to connections used marks memory
		 * \param queueNodesNumber queueNodes number. It must be = AsynMsgs
		 * + TimeoutMsgs + SynchrMsgs
	 * \param pQueueNodesMemory  queue nodes memory
	 * \param pQueueNodesMarksMemory queue nodes used marks memory
	 * \param pQueueHeadsMemory queue heads memory
	 */

		void SetMemory(		TEDROOMUInt32 					asynMsgNumber,
						CEDROOMMessage  			* 	pMessagesMemory,
						TEDROOMBool 				*	pMessagesMarksMemory,
							TEDROOMUInt32 					queueNodesNumber,
						CEDROOMQueue::CQueueNode	* 	pQueueNodesMemory,
						TEDROOMBool 				*	pQueueNodesMarksMemory,
						CEDROOMQueue::CQueueHead 	*	pQueueHeadsMemory

				);


};

#endif


/**
 * @}
 */
/**
 * @}
 */
/*PROTECTED REGION END*/

#endif // PUBLIC__EDROOMSL_IFACE_V1_H
