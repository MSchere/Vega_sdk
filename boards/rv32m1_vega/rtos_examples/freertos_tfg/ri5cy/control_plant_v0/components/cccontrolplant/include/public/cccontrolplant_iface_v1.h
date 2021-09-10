#ifndef CCCONTROLPLANT_H_
#define CCCONTROLPLANT_H_

//******************************************************************************
// EDROOM Service Library

#define _EDROOM_IS_EMBEDDED_

#include <public/edroomsl_iface_v1.h>

//******************************************************************************
// Data Classes

#include <public/cdcontrolparam_iface_v1.h>


/**
 * \class   CCControlPlant
 *
 */
class CCControlPlant: public CEDROOMComponent {

public:

	/**
	 * \enum TEDROOMCCControlPlantSignal
	 * \brief Component Signal Enum Type
	 *
	 */
	 enum TEDROOMCCControlPlantSignal { EDROOMSignalTimeout, 
							EDROOMSignalDestroy, 
							SIamAlive, 
							SUpdateControlParam };

	/**
	 * \class CCControlPlant::CEDROOMMemory
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

	// ********************************************************************
	// ******************* Component Message Data Pools *******************
	// ********************************************************************

			//! TEDROOMUInt8 Data Pool Memory
			TEDROOMUInt8	poolTEDROOMUInt8[10+1];
			//! TEDROOMUInt8 Data Pool Marks Memory
			bool	poolMarkTEDROOMUInt8[10];


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

	//! SwWatchdog Component Port
	CEDROOMInterface	SwWatchdog;
	//! RS232Command Component Port
	CEDROOMInterface	RS232Command;
	//! KeybCommand Component Port
	CEDROOMInterface	KeybCommand;


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
	CCControlPlant(TEDROOMComponentID id, TEDROOMUInt32 roomNumMaxMens, TEDROOMPriority roomtaskPrio, 
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
	 * \enum TEDROOMCCControlPlantSignal
	 * \brief Component Signal Enum Type
	 *
	 */
	enum TEDROOMCCControlPlantSignal { EDROOMSignalTimeout,
		EDROOMSignalDestroy,
		SIamAlive,
		SUpdateControlParam };


		friend class CCControlPlant;

		//!component reference
		CCControlPlant &EDROOMcomponent;

		//!Current message pointer reference
		CEDROOMMessage * &Msg;

		//!Synchronous message back pointer reference
		CEDROOMMessage * &MsgBack;

		//!Component ports
		CEDROOMInterface & SwWatchdog;
		CEDROOMInterface & RS232Command;
		CEDROOMInterface & KeybCommand;
		CEDROOMTimingInterface & Timer;


		//! State Identifiers
		enum TEDROOMStateID{I,
			ProgAlgorithmExec,
			ProgControl};

		//!Transition Identifiers
		enum TEDROOMTransitionID{Init,
			ControlAlgorithm,
			ApplyControl,
			UpdateControlParam,
			EDROOMMemoryTrans };



		//!Variables
		TEDROOMUInt8 &CCONTROL_PLANT_ID;
		TEDROOMFloat &VKd;
		TEDROOMFloat &VKi;
		TEDROOMFloat &VKp;
		Pr_Time &VNextTimer;


		// Pools *************************************************

		class CEDROOMPOOLTEDROOMUInt8:public CEDROOMProtectedMemoryPool {
			public:
			CEDROOMPOOLTEDROOMUInt8(TEDROOMUInt32 elemCount,TEDROOMUInt8 *pMem, bool *pMarks);
			TEDROOMUInt8	* AllocData();
		};
		CEDROOMPOOLTEDROOMUInt8	& EDROOMPoolTEDROOMUInt8;


		//!Constructor
		EDROOM_CTX_Top_0 (CCControlPlant &act,
				TEDROOMUInt8 & EDROOMpVarCCONTROL_PLANT_ID,
				TEDROOMFloat & EDROOMpVarVKd,
				TEDROOMFloat & EDROOMpVarVKi,
				TEDROOMFloat & EDROOMpVarVKp,
				Pr_Time & EDROOMpVarVNextTimer,
				CEDROOMPOOLTEDROOMUInt8 & EDROOMpPoolTEDROOMUInt8 );

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
		void	FApplyControl();

		/**
		 * \brief  
		 */
		void	FControlAlgorithm();

		/**
		 * \brief  
		 */
		void	FIamAlive();

		/**
		 * \brief  
		 */
		void	FInitTimer();

		/**
		 * \brief  
		 */
		void	FUpdateAlgorithmParam();

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
		TEDROOMUInt8 CCONTROL_PLANT_ID;
		TEDROOMFloat VKd;
		TEDROOMFloat VKi;
		TEDROOMFloat VKp;
		Pr_Time VNextTimer;


		// Pools**************************************************
		CEDROOMPOOLTEDROOMUInt8	EDROOMPoolTEDROOMUInt8;


	public:

		//! Constructor
		EDROOM_SUB_Top_0 (CCControlPlant &act, CEDROOMMemory *pEDROOMMemory  );


		//! Top Context Behaviour 

		void EDROOMBehaviour();

		//!Top Context Init
		void EDROOMInit();

		//! Initial substate arrival
		TEDROOMTransId EDROOMIArrival();

		// ***********************************************************************

		// Leaf SubState ProgAlgorithmExec

		// ***********************************************************************



		TEDROOMTransId EDROOMProgAlgorithmExecArrival();

		// ***********************************************************************

		// Leaf SubState ProgControl

		// ***********************************************************************



		TEDROOMTransId EDROOMProgControlArrival();

	};

protected:

	//!Top State
	EDROOM_SUB_Top_0 edroomTopState;



};
#endif