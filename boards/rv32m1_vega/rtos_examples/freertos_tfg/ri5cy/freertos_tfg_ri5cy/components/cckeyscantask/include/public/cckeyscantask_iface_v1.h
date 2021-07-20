#ifndef CCKEYSCANTASK_H_
#define CCKEYSCANTASK_H_

//******************************************************************************
// EDROOM Service Library

#define _EDROOM_IS_EMBEDDED_

#include <public/edroomsl_iface_v1.h>

//******************************************************************************
// Data Classes

#include <public/cdcontrolparam_iface_v1.h>


/**
 * \class   CCKeyScanTask
 *
 */
class CCKeyScanTask: public CEDROOMComponent {

public:

	/**
	 * \enum TEDROOMCCKeyScanTaskSignal
	 * \brief Component Signal Enum Type
	 *
	 */
	 enum TEDROOMCCKeyScanTaskSignal { EDROOMSignalTimeout, 
							EDROOMSignalDestroy, 
							SIamAlive, 
							SUpdateControlParam, 
							SNewChar };

	/**
	 * \class CCKeyScanTask::CEDROOMMemory
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

			//! CDControlParam Data Pool Memory
			CDControlParam	poolCDControlParam[10+1];
			//! CDControlParam Data Pool Marks Memory
			bool	poolMarkCDControlParam[10];
			//! TEDROOMByte Data Pool Memory
			TEDROOMByte	poolTEDROOMByte[100+1];
			//! TEDROOMByte Data Pool Marks Memory
			bool	poolMarkTEDROOMByte[100];
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
	//! Command Component Port
	CEDROOMInterface	Command;
	//! MonitorDataStream Component Port
	CEDROOMInterface	MonitorDataStream;


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
	CCKeyScanTask(TEDROOMComponentID id, TEDROOMUInt32 roomNumMaxMens, TEDROOMPriority roomtaskPrio, 
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
	 * \enum TEDROOMCCKeyScanTaskSignal
	 * \brief Component Signal Enum Type
	 *
	 */
	enum TEDROOMCCKeyScanTaskSignal { EDROOMSignalTimeout,
		EDROOMSignalDestroy,
		SIamAlive,
		SUpdateControlParam,
		SNewChar };


		friend class CCKeyScanTask;

		//!component reference
		CCKeyScanTask &EDROOMcomponent;

		//!Current message pointer reference
		CEDROOMMessage * &Msg;

		//!Synchronous message back pointer reference
		CEDROOMMessage * &MsgBack;

		//!Component ports
		CEDROOMInterface & SwWatchdog;
		CEDROOMInterface & Command;
		CEDROOMInterface & MonitorDataStream;
		CEDROOMTimingInterface & Timer;


		//! State Identifiers
		enum TEDROOMStateID{I,
			Ready};

		//!Transition Identifiers
		enum TEDROOMTransitionID{Init,
			ScanKeyb,
			ScanKeyb_CommandCompleted,
			ScanKeyb_NewChar,
			ScanKeyb_NoChar,
			EDROOMMemoryTrans };

		//!Constants
		const TEDROOMUInt8 CKEYB_SCAN_ID;


		//!Variables
		TEDROOMUInt8 &VAuxIndex;
		TEDROOMByte *VAuxKeybChannel;
		TEDROOMByte *VCommandBuffer;
		TEDROOMInt8 &VCommBufferControl;
		TEDROOMUInt8 &VdummyCounter;
		TEDROOMUInt8 &VIndex;
		Pr_Time &VNextTimer;
		TEDROOMByte &VRxChar;


		// Pools *************************************************

		class CEDROOMPOOLCDControlParam:public CEDROOMProtectedMemoryPool {
			public:
			CEDROOMPOOLCDControlParam(TEDROOMUInt32 elemCount,CDControlParam *pMem, bool *pMarks);
			CDControlParam	* AllocData();
		};
		CEDROOMPOOLCDControlParam	& EDROOMPoolCDControlParam;
		class CEDROOMPOOLTEDROOMByte:public CEDROOMProtectedMemoryPool {
			public:
			CEDROOMPOOLTEDROOMByte(TEDROOMUInt32 elemCount,TEDROOMByte *pMem, bool *pMarks);
			TEDROOMByte	* AllocData();
		};
		CEDROOMPOOLTEDROOMByte	& EDROOMPoolTEDROOMByte;
		class CEDROOMPOOLTEDROOMUInt8:public CEDROOMProtectedMemoryPool {
			public:
			CEDROOMPOOLTEDROOMUInt8(TEDROOMUInt32 elemCount,TEDROOMUInt8 *pMem, bool *pMarks);
			TEDROOMUInt8	* AllocData();
		};
		CEDROOMPOOLTEDROOMUInt8	& EDROOMPoolTEDROOMUInt8;


		//!Constructor
		EDROOM_CTX_Top_0 (CCKeyScanTask &act,
				TEDROOMUInt8 & EDROOMpVarVAuxIndex,
				TEDROOMByte * EDROOMpVarVAuxKeybChannel,
				TEDROOMByte * EDROOMpVarVCommandBuffer,
				TEDROOMInt8 & EDROOMpVarVCommBufferControl,
				TEDROOMUInt8 & EDROOMpVarVdummyCounter,
				TEDROOMUInt8 & EDROOMpVarVIndex,
				Pr_Time & EDROOMpVarVNextTimer,
				TEDROOMByte & EDROOMpVarVRxChar,
				CEDROOMPOOLCDControlParam & EDROOMpPoolCDControlParam,
				CEDROOMPOOLTEDROOMByte & EDROOMpPoolTEDROOMByte,
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
		void	FIamAlive();

		/**
		 * \brief  
		 */
		void	FInit();

		/**
		 * \brief  
		 */
		void	FProgNextScan();

		/**
		 * \brief  
		 */
		void	FScanKeyb();

		/**
		 * \brief  
		 */
		void	FSendCharToMonitor();

		/**
		 * \brief  
		 */
		void	FSendCommand();

		/**
		 * \brief  
		 */
		bool	GCommandCompleted();

		/**
		 * \brief  
		 */
		bool	GNewChar();

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
		TEDROOMUInt8 VAuxIndex;
		TEDROOMByte VAuxKeybChannel[40];
		TEDROOMByte VCommandBuffer[7];
		TEDROOMInt8 VCommBufferControl;
		TEDROOMUInt8 VdummyCounter;
		TEDROOMUInt8 VIndex;
		Pr_Time VNextTimer;
		TEDROOMByte VRxChar;


		// Pools**************************************************
		CEDROOMPOOLCDControlParam	EDROOMPoolCDControlParam;
		CEDROOMPOOLTEDROOMByte	EDROOMPoolTEDROOMByte;
		CEDROOMPOOLTEDROOMUInt8	EDROOMPoolTEDROOMUInt8;


	public:

		//! Constructor
		EDROOM_SUB_Top_0 (CCKeyScanTask &act, CEDROOMMemory *pEDROOMMemory  );


		//! Top Context Behaviour 

		void EDROOMBehaviour();

		//!Top Context Init
		void EDROOMInit();

		//! Initial substate arrival
		TEDROOMTransId EDROOMIArrival();

		// ***********************************************************************

		// Leaf SubState Ready

		// ***********************************************************************



		TEDROOMTransId EDROOMReadyArrival();

	};

protected:

	//!Top State
	EDROOM_SUB_Top_0 edroomTopState;



};
#endif