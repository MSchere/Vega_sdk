#ifndef CCLEDTASK_H_
#define CCLEDTASK_H_

//******************************************************************************
// EDROOM Service Library

#define _EDROOM_IS_EMBEDDED_

#include <public/edroomsl_iface_v1.h>

/**
 * \class   CCLEDTask
 *
 */
class CCLEDTask: public CEDROOMComponent {

public:

	/**
	 * \enum TEDROOMCCLEDTaskSignal
	 * \brief Component Signal Enum Type
	 *
	 */
	 enum TEDROOMCCLEDTaskSignal { EDROOMSignalTimeout, 
							EDROOMSignalDestroy, 
							SIamAlive };

	/**
	 * \class CCLEDTask::CEDROOMMemory
	 * \brief Component Memory
	 *
	 */
	class CEDROOMMemory: public CEDROOMComponentMemory{

		private:

			//!Array of Message Queue Heads, one for each priority
			CEDROOMQueue::CQueueHead QueueHeads[EDROOMprioMINIMUM+1];

			//************ Component Timing Service Memory************

			//!Component Timing Service Timer Info Memory
			CEDROOMTimerInfo TimerInf[3];
			//!Component Timing Service Timer Info Marks Memory
			bool TimerInfMarks[3];
			//!Component Timing Service TimeOut Messages Memory
			CEDROOMTimeOutMessage TimeOutMsgs[3];
			//!Component Timing Service TimeOut Messages Marks Memory
			bool TimeOutMsgsMarks[3];

		public: 

			//!Component Timing Service Memory Object
			CEDROOMTimingMemory TimingMemory;



			/** \brief This function is used for setting the Component Memory
			 * 
			 * \param numberOfMsgs number of messages that the component can store
			 * \param msgsMemory memory for the messages that the component can store
			 * \param msgsMemoryMarks memory marks for the messages that the component can store
			 * \param numberOfNodes number of nodes that the component needs
			 * \param queueNodesMemory memory for the component message queues 
			 * \param queueNodesMemoryMarks memory marks for the component message queues 
			 */
			void SetMemory(TEDROOMUInt32 numberOfMsgs
						, CEDROOMMessage * msgsMemory
						, bool * msgsMemoryMarks
						, TEDROOMUInt32 numberOfNodes
						, CEDROOMQueue::CQueueNode * queueNodesMemory
						, bool * queueNodesMemoryMarks);

	};


	// ********************************************************************
	//******************  Component Communication Ports *******************
	// ********************************************************************

	//! SwWatchdog5 Component Port
	CEDROOMInterface	SwWatchdog5;
	//! SwWatchdog4 Component Port
	CEDROOMInterface	SwWatchdog4;
	//! SwWatchdog3 Component Port
	CEDROOMInterface	SwWatchdog3;
	//! SwWatchdog2 Component Port
	CEDROOMInterface	SwWatchdog2;
	//! SwWatchdog Component Port
	CEDROOMInterface	SwWatchdog;


	// ********************************************************************
	// ********************  Timing Service Interface *********************
	// ********************************************************************

	//! Timing Service Access Point. It is common to all timing ports.
	CEDROOMTimingSAP	 EDROOMtimingSAP;


	//! Timer Timing Port
	CEDROOMTimingInterface	Timer;




	// *************************************************************************
	// **************************** Frame Service Methods	********************
	// *************************************************************************



	//! Constructor
	CCLEDTask(TEDROOMComponentID id, TEDROOMUInt32 roomNumMaxMens, TEDROOMPriority roomtaskPrio, 
		TEDROOMStackSizeType roomStack, CEDROOMMemory * pActorMemory );




	//! Component Configuration 
	 int EDROOMConfig();


	//! Component Start 
	 int EDROOMStart();




	#ifdef _EDROOM_SYSTEM_CLOSE

	//! Method that returns true if component is finished 
	bool EDROOMIsComponentFinished();


	#endif

protected:



	//! Component behaviour 
	virtual void EDROOMBehaviour();




public:

	// *****************************	Behaviour  *************************

	// ***********************************************************************

	// class EDROOM_CTX_Top_0

	// ***********************************************************************



	class EDROOM_CTX_Top_0 {

	protected:

	/**
	 * \enum TEDROOMCCLEDTaskSignal
	 * \brief Component Signal Enum Type
	 *
	 */
	enum TEDROOMCCLEDTaskSignal { EDROOMSignalTimeout,
		EDROOMSignalDestroy,
		SIamAlive };


		friend class CCLEDTask;

		//!component reference
		CCLEDTask &EDROOMcomponent;

		//!Current message pointer reference
		CEDROOMMessage * &Msg;

		//!Synchronous message back pointer reference
		CEDROOMMessage * &MsgBack;

		//!Component ports
		CEDROOMInterface & SwWatchdog5;
		CEDROOMInterface & SwWatchdog4;
		CEDROOMInterface & SwWatchdog3;
		CEDROOMInterface & SwWatchdog2;
		CEDROOMInterface & SwWatchdog;
		CEDROOMTimingInterface & Timer;


		//! State Identifiers
		enum TEDROOMStateID{I,
			LED_OFF,
			LED_ON};

		//!Transition Identifiers
		enum TEDROOMTransitionID{Init,
			Switch_ON,
			Switch_OFF,
			TaskIsAlive,
			EDROOMMemoryTrans };



		//!Variables
		Pr_Time *VAliveMsgTimeout;
		Pr_Time *VTaskIsAlive;




		//!Constructor
		EDROOM_CTX_Top_0 (CCLEDTask &act,
				Pr_Time * EDROOMpVarVAliveMsgTimeout,
				Pr_Time * EDROOMpVarVTaskIsAlive );

		//!Copy constructor
		EDROOM_CTX_Top_0 (EDROOM_CTX_Top_0 &context);

	public:

		/**
		 * \brief Search Context transition 
		 * \param edroomCurrentTrans returns the context transition 

		 * \return true if context transition is found 

		 */
		bool EDROOMSearchContextTrans(TEDROOMTransId &edroomCurrentTrans);

		//! \brief Get new message from the Queue

		void EDROOMNewMessage()
		{ EDROOMcomponent.EDROOMNewMsg(); }

		/**
		 * \brief Get and Clear the Error Flags 
		 * \return the error flags  

		 */
		 TEDROOMUInt32 GetAndClearErrorFlags(){ return EDROOMcomponent.GetAndClearErrorFlags();}

		// User-defined Functions

		/**
		 * \brief  
		 */
		void	FInit();

		/**
		 * \brief  
		 */
		void	FLED_OFF();

		/**
		 * \brief  
		 */
		void	FLED_ON();

		/**
		 * \brief  
		 */
		void	FProgTimer();

		/**
		 * \brief  
		 */
		void	FTaskIsAlive();

	};

	// ***********************************************************************

	// class EDROOM_SUB_Top_0

	// ***********************************************************************



	class EDROOM_SUB_Top_0 : public EDROOM_CTX_Top_0 {

	protected:



		//!current state identifier
		EDROOM_CTX_Top_0::TEDROOMStateID edroomCurrentState;

		//!next state identifier
		EDROOM_CTX_Top_0::TEDROOMStateID edroomNextState;

		//!Variables
		Pr_Time VAliveMsgTimeout[5];
		Pr_Time VTaskIsAlive[5];




	public:

		//! Constructor
		EDROOM_SUB_Top_0 (CCLEDTask &act );


		//! Top Context Behaviour 

		void EDROOMBehaviour();

		//!Top Context Init
		void EDROOMInit();

		//! Initial substate arrival
		TEDROOMTransId EDROOMIArrival();

		// ***********************************************************************

		// Leaf SubState LED_OFF

		// ***********************************************************************



		TEDROOMTransId EDROOMLED_OFFArrival();

		// ***********************************************************************

		// Leaf SubState LED_ON

		// ***********************************************************************



		TEDROOMTransId EDROOMLED_ONArrival();

	};

protected:

	//!Top State
	EDROOM_SUB_Top_0 edroomTopState;



};
#endif
